// functions.cpp
#include "functions.h"
#include "field.h"
#include "unit.h"
#include "player.h"
#include "fortress.h"
#include "hill.h"
#include "bombedfield.h"
#include "manaminefield.h"
#include "shieldedfield.h"
#include "burnedfield.h"
#include "hospitalfield.h"


#include <iostream>
#include <vector>
#include <cmath> // For std::abs
#include <algorithm> // For std::max
#include <iomanip> // For std::setw

// Helper function to get the unit's effective defense including field bonus
int getEffectiveDefense(const Field* field, const Unit* unit) {
    if (!unit || !field) return 0; // No unit or field, no defense
    return unit->getCurrentHealth() + field->getDefenseBonus(); // Simple example: Health acts as base defense + field bonus
}


void updateFortressStrength(
    std::vector<std::vector<Field*>>& board,
    int x,
    int y,
    int newStrength
)
{
    size_t boardWidth = board.size();
    size_t boardHeight = board[0].size();

    if (x >= 0 && static_cast<size_t>(x) < boardWidth && y >= 0 && static_cast<size_t>(y) < boardHeight) {
        Field* field = board[x][y];
        Fortress* fortress = dynamic_cast<Fortress*>(field);
        if (fortress) {
            fortress->setStrength(newStrength);
            if (fortress->getStrength() <= 0) {
                std::cout << "Fortress at (" << x << "," << y << ") has been destroyed!\n";
                Unit* unitOnFortress = fortress->getUnit(); // Get unit before deleting fortress
                delete fortress; // Delete the fortress object
                // Replace with a plain field
                board[x][y] = new Field(x, y, "plain");
                board[x][y]->setUnit(unitOnFortress); // Place the unit on the new plain field
            }
        }
    }
}

void checkBombExplosions(std::vector<std::vector<Field*>>& board)
{
    size_t boardWidth = board.size();
    size_t boardHeight = board[0].size();
    std::vector<std::pair<int, int>> bombsToExplode;

    // First, identify all bombs that should explode
    for (size_t y = 0; y < boardHeight; ++y) {
        for (size_t x = 0; x < boardWidth; ++x) {
            Field* field = board[x][y];
            BombedField* bombedField = dynamic_cast<BombedField*>(field);
            if (bombedField && bombedField->shouldExplode()) {
                bombsToExplode.push_back({static_cast<int>(x), static_cast<int>(y)});
            }
        }
    }

    // Then, explode the identified bombs
    for (const auto& coords : bombsToExplode) {
        int x = coords.first;
        int y = coords.second;
        Field* field = board[x][y];
        BombedField* bombedField = dynamic_cast<BombedField*>(field);
        if (bombedField) { // Double check in case the field was already changed by another explosion
            bombedField->explode(board);
        }
    }
}


void applyDamage(std::vector<std::vector<Field*>>& board, int x, int y, int damage, Unit* attackingUnit)
{
    size_t boardWidth = board.size();
    size_t boardHeight = board[0].size();

    if (x >= 0 && static_cast<size_t>(x) < boardWidth && y >= 0 && static_cast<size_t>(y) < boardHeight) {
        Field* field = board[x][y];
        Unit* unit = field->getUnit();
        if (unit) {
            unit->takeDamage(damage, attackingUnit);
            if (unit->getCurrentHealth() <= 0) {
                std::cout << unit->getName() << " at (" << x << "," << y << ") has been defeated!\n";
                delete unit; // Delete the unit object
                field->setUnit(nullptr); // Remove unit from the field
            }
        } else {
             // If there's no unit, check if it's a Fortress and apply damage to it
             Fortress* fortress = dynamic_cast<Fortress*>(field);
             if (fortress) {
                 std::cout << "Fortress at (" << x << "," << y << ") takes " << damage << " damage.\n";
                 updateFortressStrength(board, x, y, fortress->getStrength() - damage);
             }
        }
    }
}


void attack(std::vector<std::vector<Field*>>& board, int attackerX, int attackerY, int targetX, int targetY)
{
    size_t boardWidth = board.size();
    size_t boardHeight = board[0].size();

    // Check if coordinates are within board bounds
    if (attackerX < 0 || static_cast<size_t>(attackerX) >= boardWidth ||
        attackerY < 0 || static_cast<size_t>(attackerY) >= boardHeight ||
        targetX < 0 || static_cast<size_t>(targetX) >= boardWidth ||
        targetY < 0 || static_cast<size_t>(targetY) >= boardHeight)
    {
        std::cerr << "Attack failed: Coordinates out of bounds.\n";
        return;
    }

    Field* attackerField = board[attackerX][attackerY];
    Field* targetField = board[targetX][targetY];
    Unit* attackingUnit = attackerField->getUnit();
    Unit* targetUnit = targetField->getUnit();

    // Check if there are units at both positions
    if (!attackingUnit) {
        std::cerr << "Attack failed: No unit at attacker position (" << attackerX << "," << attackerY << ").\n";
        return;
    }
    if (!targetUnit) {
         // If no target unit, check if the target is a Fortress
         Fortress* targetFortress = dynamic_cast<Fortress*>(targetField);
         if (targetFortress) {
             std::cout << attackingUnit->getName() << " at (" << attackerX << "," << attackerY << ") attacks Fortress at (" << targetX << "," << targetY << ")!\n";
             updateFortressStrength(board, targetX, targetY, targetFortress->getStrength() - attackingUnit->getDamage());
             attackingUnit->setWill(std::max(0, attackingUnit->getWill() - 1)); // Consume will for attack
             return; // Attack on fortress successful
         }
        std::cerr << "Attack failed: No unit or fortress at target position (" << targetX << "," << targetY << ").\n";
        return;
    }

    // Check if the units are on opposing sides
    if (attackingUnit->getPlayer() == targetUnit->getPlayer())
    {
        std::cerr << "Attack failed: Cannot attack friendly unit.\n";
        return;
    }

    // Check if the target is within the attacker's attack distance (Manhattan distance)
    if (std::abs(attackerX - targetX) + std::abs(attackerY - targetY) > attackingUnit->getAttackDistance())
    {
        std::cerr << "Attack failed: Target is out of attack range.\n";
        return;
    }

    // Check if the attacking unit has enough will
    if (attackingUnit->getWill() <= 0) {
        std::cerr << "Attack failed: Attacking unit has no will left.\n";
        return;
    }


    std::cout << attackingUnit->getName() << " at (" << attackerX << "," << attackerY << ") attacks "
              << targetUnit->getName() << " at (" << targetX << "," << targetY << ")!\n";

    // Apply damage to the target unit, considering target field's defense bonus
    int effectiveDamage = attackingUnit->getDamage();
    int targetDefenseBonus = targetField->getDefenseBonus();
    int damageAfterDefense = std::max(0, effectiveDamage - targetDefenseBonus); // Damage cannot be negative

    std::cout << "Damage dealt: " << damageAfterDefense << " (Base: " << effectiveDamage << ", Defense Bonus: " << targetDefenseBonus << ")\n";

    applyDamage(board, targetX, targetY, damageAfterDefense, attackingUnit);

    // Consume will from the attacking unit
    attackingUnit->setWill(std::max(0, attackingUnit->getWill() - 1));

    // Check for counter-attack (if the target unit survived and is adjacent)
    // Assuming counter-attack range is 1 (adjacent)
    if (targetUnit->getCurrentHealth() > 0 && std::abs(attackerX - targetX) + std::abs(attackerY - targetY) == 1)
    {
        // Check if the target unit is an Infantry (example of a unit that can counter-attack)
        Infantry* infantryTarget = dynamic_cast<Infantry*>(targetUnit);
        if (infantryTarget) {
             infantryTarget->counterAttack(attackingUnit);
        }
        // Add checks for other unit types that can counter-attack if applicable
    }

    // After attack, check if the attacking unit is still alive (e.g., from counter-attack)
    // and if it's on a field that applies effects (like BurnedField)
     if (attackingUnit->getCurrentHealth() > 0) {
         // Re-fetch the attacker's field in case it was changed (e.g., by a spell during attack)
         Field* attackerFieldAfterAttack = nullptr;
         if (attackerX >= 0 && static_cast<size_t>(attackerX) < boardWidth && attackerY >= 0 && static_cast<size_t>(attackerY) < boardHeight) {
             attackerFieldAfterAttack = board[attackerX][attackerY];
         }

         if (attackerFieldAfterAttack) {
              attackerFieldAfterAttack->applyEffect(nullptr, board); // Apply field effect on attacker's field
         }
     }

    // After attack, check if the target unit is still alive
     if (targetUnit->getCurrentHealth() > 0) {
         // Apply field effect on target's field
         targetField->applyEffect(nullptr, board); // Apply field effect on target's field
     }
}


void move(std::vector<std::vector<Field*>>& board, int startX, int startY, int endX, int endY)
{
    size_t boardWidth = board.size();
    size_t boardHeight = board[0].size();

    // Check if coordinates are within board bounds
    if (startX < 0 || static_cast<size_t>(startX) >= boardWidth ||
        startY < 0 || static_cast<size_t>(startY) >= boardHeight ||
        endX < 0 || static_cast<size_t>(endX) >= boardWidth ||
        endY < 0 || static_cast<size_t>(endY) >= boardHeight)
    {
        std::cerr << "Move failed: Coordinates out of bounds.\n";
        return;
    }

    Field* startField = board[startX][startY];
    Field* endField = board[endX][endY];
    Unit* unitToMove = startField->getUnit();

    // Check if there's a unit at the start position
    if (!unitToMove)
    {
        std::cerr << "Move failed: No unit at starting position (" << startX << "," << startY << ").\n";
        return;
    }

    // Check if the target field is valid for movement (empty and can be entered by the unit)
    if (!endField->canEnter(unitToMove))
    {
        std::cerr << "Move failed: Cannot move to target field (" << endX << "," << endY << ").\n";
        return;
    }

    // Check if the move is within the unit's move distance (Manhattan distance)
    if (std::abs(startX - endX) + std::abs(startY - endY) > unitToMove->getMoveDistance())
    {
        std::cerr << "Move failed: Target is out of move range.\n";
        return;
    }

     // Check if the unit has enough will to move
    if (unitToMove->getWill() <= 0) {
        std::cerr << "Move failed: Unit has no will left.\n";
        return;
    }


    std::cout << unitToMove->getName() << " moves from (" << startX << "," << startY << ") to (" << endX << "," << endY << ").\n";

    // Handle onLeave effect for the starting field
    startField->onLeave(unitToMove);

    // Move the unit
    startField->setUnit(nullptr); // Remove unit from the starting field
    endField->setUnit(unitToMove); // Place unit on the target field

    // Consume will from the unit
    unitToMove->setWill(std::max(0, unitToMove->getWill() - 1));


    // Handle onEnter effect for the target field
    endField->onEnter(unitToMove);

    // After move, apply field effect on the new field
     if (unitToMove->getCurrentHealth() > 0) { // Check if unit survived onEnter effect
        endField->applyEffect(nullptr, board); // Apply field effect on the new field
     }
}


void createShieldedField(std::vector<std::vector<Field*>>& board, int x, int y, Unit* unitOnField) {
    size_t boardWidth = board.size();
    size_t boardHeight = board[0].size();

    if (x >= 0 && static_cast<size_t>(x) < boardWidth && y >= 0 && static_cast<size_t>(y) < boardHeight) {
        Field* oldField = board[x][y];
        // Ensure the old field is deleted before creating the new one
        if (oldField) {
            delete oldField;
        }
        // Create a new ShieldedField with a default duration (e.g., 3 turns)
        board[x][y] = new ShieldedField(x, y, unitOnField, 3);
        std::cout << "Created Shielded Field at (" << x << "," << y << ").\n";
    } else {
        std::cerr << "Failed to create Shielded Field: Coordinates out of bounds.\n";
    }
}

void createHospitalField(std::vector<std::vector<Field*>>& board, int x, int y, Unit* unitOnField) {
     size_t boardWidth = board.size();
    size_t boardHeight = board[0].size();

    if (x >= 0 && static_cast<size_t>(x) < boardWidth && y >= 0 && static_cast<size_t>(y) < boardHeight) {
        Field* oldField = board[x][y];
        // Ensure the old field is deleted before creating the new one
        if (oldField) {
            delete oldField;
        }
        // Create a new HospitalField with a default heal amount (e.g., 3)
        board[x][y] = new HospitalField(x, y, unitOnField, 3);
        std::cout << "Created Hospital Field at (" << x << "," << y << ").\n";
    } else {
        std::cerr << "Failed to create Hospital Field: Coordinates out of bounds.\n";
    }
}

void checkVictory(Player* player1, Player* player2, const std::vector<std::vector<Field*>>& board) {
    bool player1HasUnits = false, player2HasUnits = false;
    bool player1HasFortress = false, player2HasFortress = false;
    for (const auto& row : board) {
        for (const auto& field : row) {
            if (!field) continue;
            Unit* unit = field->getUnit();
            if (unit) {
                if (unit->getPlayer()) player1HasUnits = true;
                else player2HasUnits = true;
            }
            Fortress* fortress = dynamic_cast<Fortress*>(field);
            if (fortress) {
                if (fortress->getOwner() == player1) player1HasFortress = true;
                if (fortress->getOwner() == player2) player2HasFortress = true;
            }
        }
    }
    if ((!player1HasUnits || !player1HasFortress)  && player1->getMana()<=1) {
        std::cout << "Player 2 wins!\n";
    } else if ((!player2HasUnits || !player2HasFortress) && player2->getMana()<=1) {
        std::cout << "Player 1 wins!\n";
    }
}

void displayRules() {
    std::cout << "\n=== GAME RULES ===\n\n";
    
    std::cout << "=== UNITS ===\n";
    std::cout << "1. Infantry (Cost: 1)\n";
    std::cout << "   - Health: 3, Attack: 1, Range: 1\n";
    std::cout << "   - Can move and attack in the same turn\n\n";
    
    std::cout << "2. Archer (Cost: 2)\n";
    std::cout << "   - Health: 2, Attack: 1, Range: 3\n";
    std::cout << "   - Can attack from a distance\n\n";
    
    std::cout << "3. Cannon (Cost: 3)\n";
    std::cout << "   - Health: 2, Attack: 2, Range: 2\n";
    std::cout << "   - Cannot move and attack in the same turn\n\n";
    
    std::cout << "4. Priest (Cost: 2)\n";
    std::cout << "   - Health: 2, Attack: 0, Range: 2\n";
    std::cout << "   - Can heal friendly units\n\n";
    
    std::cout << "5. Engineer (Cost: 2)\n";
    std::cout << "   - Health: 1, Attack: 1, Range: 1\n";
    std::cout << "   - Can build fortresses, mana mines, and traps\n\n";
    
    std::cout << "=== SPELLS ===\n";
    std::cout << "1. Fireball (Cost: 2)\n";
    std::cout << "   - Deals 2 damage to target unit\n\n";
    
    std::cout << "2. Curse (Cost: 3)\n";
    std::cout << "   - Reduces target unit's attack by 1\n\n";
    
    std::cout << "3. Teleport (Cost: 2)\n";
    std::cout << "   - Moves target unit to a new location\n\n";
    
    std::cout << "4. Morog (Cost: 4)\n";
    std::cout << "   - Creates a powerful temporary unit\n\n";
    
    std::cout << "5. Bomb (Cost: 3)\n";
    std::cout << "   - Creates an explosion damaging multiple units\n\n";
    
    std::cout << "=== SPECIAL FIELDS ===\n";
    std::cout << "1. Fortress\n";
    std::cout << "   - Can be captured by units\n";
    std::cout << "   - Provides defensive bonus\n\n";
    
    std::cout << "2. Mana Mine\n";
    std::cout << "   - Generates mana for the owner\n\n";
    
    std::cout << "3. Trap (Bombed Field)\n";
    std::cout << "   - Damages units that step on it\n\n";
    
    std::cout << "=== RESTRICTIONS ===\n";
    std::cout << "1. Units cannot move through other units\n";
    std::cout << "2. Units cannot attack through other units\n";
    std::cout << "3. Units cannot move and attack in the same turn (except Infantry)\n";
    std::cout << "4. Spells require sufficient mana\n";
    std::cout << "5. Units require sufficient gold to purchase\n\n";
    
    std::cout << "=== VICTORY CONDITIONS ===\n";
    std::cout << "1. Capture all fortresses on the map\n";
    std::cout << "2. Eliminate all enemy units\n\n";
}
