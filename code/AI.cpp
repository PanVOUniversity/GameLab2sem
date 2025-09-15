// AI.cpp
#include "AI.h"
#include "player.h" // Explicitly include player.h for full definition
#include "field.h"  // Explicitly include field.h for full definition
#include "unit.h"
#include "functions.h"
#include "spells.h"
#include "engineer.h"
#include "fortress.h"
#include "manaminefield.h"
#include "bombedfield.h"
#include "archer.h"
#include "infantry.h"
#include "priest.h"
#include "hill.h"
#include "cursespell.h"
#include "fireballspell.h"
#include "bombspell.h"
#include "morogspell.h"
#include "shieldedfield.h"
#include "burnedfield.h"
#include "cannon.h"
#include "hospitalfield.h"

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cmath>
#include <utility>
#include <memory>
#include <stdexcept>
#include <typeinfo>
#include <numeric>
#include <random>
#include <chrono>

// Forward declarations (can keep these, but including headers is also fine)
// Removed duplicate forward declarations as they are now in AI.h
Unit* createUnit(const std::string& type, bool isPlayer); // Keep only one declaration
bool tryAICreateSpecificUnit(Player* aiPlayer, std::vector<std::vector<Field*>>& board, const std::string& unitType, int& manaRemaining);
bool tryAICastSpecificSpell(Player* aiPlayer, std::vector<std::vector<Field*>>& board, Spell* spellToCast, int& manaRemaining);
bool tryAIEngineerBuildSpecific(Engineer* engineer, Player* aiPlayer, int engX, int engY, std::vector<std::vector<Field*>>& board, const std::string& buildType, int& manaRemaining);

// Helper function to find a random valid empty adjacent field for building
std::pair<int, int> findRandomAdjacentEmptyField(int x, int y, const std::vector<std::vector<Field*>>& board) {
    size_t boardWidth = board.size();
    size_t boardHeight = board[0].size();
    std::vector<std::pair<int, int>> possibleTargets;
    for(int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue;
            int nx = x + dx;
            int ny = y + dy;
            if (nx >= 0 && static_cast<size_t>(nx) < boardWidth &&
                ny >= 0 && static_cast<size_t>(ny) < boardHeight)
            {
                 Field* field = board[nx][ny];
                 // Check if field exists, is empty, and not special terrain that blocks building
                 if (field && !field->getUnit() && !dynamic_cast<Hill*>(field) && !dynamic_cast<Fortress*>(field) &&
                     !dynamic_cast<ManaMineField*>(field) && !dynamic_cast<BombedField*>(field) &&
                     !dynamic_cast<ShieldedField*>(field) && !dynamic_cast<BurnedField*>(field) &&
                     !dynamic_cast<HospitalField*>(field)) { // Added HospitalField
                     possibleTargets.push_back({nx, ny});
                 }
            }
        }
    }

    if (possibleTargets.empty()) {
        return {-1, -1}; // Indicate no valid target found
    }
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    std::default_random_engine rng(seed);
    std::shuffle(possibleTargets.begin(), possibleTargets.end(), rng);
    return possibleTargets[0];
}


// Helper function to find a random valid empty field in the AI's creation area
std::pair<int, int> findRandomAICreateSpot(const std::vector<std::vector<Field*>>& board) {
    size_t boardWidth = board.size();
    size_t boardHeight = board[0].size();
    // Restrict AI creation to fields with y <= 4
    size_t maxY = std::min(static_cast<size_t>(4), boardHeight - 1);
    std::vector<std::pair<int, int>> possibleSpawns;
    for (size_t y = 0; y <= maxY; ++y) { // Iterate y from 0 to 4
        for (size_t x = 0; x < boardWidth; ++x) {
             Field* field = board[x][y];
            // Check if field exists, is empty, and not a special blocking terrain
            if (field && !field->getUnit() && !dynamic_cast<Fortress*>(field) && !dynamic_cast<Hill*>(field) &&
                !dynamic_cast<ManaMineField*>(field) && !dynamic_cast<BombedField*>(field) &&
                !dynamic_cast<ShieldedField*>(field) && !dynamic_cast<BurnedField*>(field) &&
                !dynamic_cast<HospitalField*>(field)) { // Added HospitalField

              possibleSpawns.push_back({static_cast<int>(x), static_cast<int>(y)});
            }
        }
    }

    if (possibleSpawns.empty()) {
        return {-1, -1}; // Indicate no valid spot found
    }
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    std::default_random_engine rng(seed);
    std::shuffle(possibleSpawns.begin(), possibleSpawns.end(), rng);
    return possibleSpawns[0];
}

// Helper function to find a random enemy unit's coordinates
std::pair<int, int> findRandomEnemyUnitCoords(const std::vector<std::vector<Field*>>& board) {
    size_t boardWidth = board.size();
    size_t boardHeight = board[0].size();
    std::vector<std::pair<int, int>> enemyUnitCoords;

    for (size_t x = 0; x < boardWidth; ++x) {
        for (size_t y = 0; y < boardHeight; ++y) {
            Field* field = board[x][y];
            if (field) {
                Unit* unit = field->getUnit();
                // Assuming AI player has getPlayer() == false, enemy has getPlayer() == true
                if (unit && unit->getPlayer()) {
                    enemyUnitCoords.push_back({static_cast<int>(x), static_cast<int>(y)});
                }
            }
        }
    }

    if (enemyUnitCoords.empty()) {
        return {-1, -1}; // Indicate no enemy unit found
    }
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    std::default_random_engine rng(seed);
    std::shuffle(enemyUnitCoords.begin(), enemyUnitCoords.end(), rng);
    return enemyUnitCoords[0];
}

// AI attempts to create a specific unit with allocated mana
bool tryAICreateSpecificUnit(Player* aiPlayer, std::vector<std::vector<Field*>>& board, const std::string& unitType, int& manaRemaining) {
    if (!aiPlayer || manaRemaining <= 0 || board.empty() || board[0].empty()) return false;
    int unitCost = 0;
    if (unitType == "archer") unitCost = 3;
    else if (unitType == "infantry") unitCost = 2;
    else if (unitType == "priest") unitCost = 5;
    else if (unitType == "engineer") unitCost = 5;
    else return false; // Unknown unit type

    if (manaRemaining < unitCost || aiPlayer->getMana() < unitCost) return false; // Not enough allocated or total mana

    std::pair<int, int> spawnSpot = findRandomAICreateSpot(board);
    if (spawnSpot.first == -1) return false; // No valid spawn location in the allowed area

    int spawnX = spawnSpot.first;
    int spawnY = spawnSpot.second;

    Unit* newUnit = createUnit(unitType, false); // false for AI player
    if (newUnit) {
        board[spawnX][spawnY]->setUnit(newUnit);
        aiPlayer->setMana(aiPlayer->getMana() - unitCost); // Deduct actual cost
        manaRemaining -= unitCost; // Deduct from allocated mana
        std::cout << "AI created " << unitType << " at (" << spawnX << "," << spawnY
                  << ") spending " << unitCost << " mana.\n";
        return true;
    }
    return false;
}

// AI attempts to cast a specific spell with allocated mana
bool tryAICastSpecificSpell(Player* aiPlayer, std::vector<std::vector<Field*>>& board, Spell* spellToCast, int& manaRemaining) {
    if (!aiPlayer || manaRemaining <= 0 || !spellToCast || board.empty() || board[0].empty()) return false;
    int spellCost = spellToCast->getManaCost();
    if (manaRemaining < spellCost || aiPlayer->getMana() < spellCost) return false; // Not enough allocated or total mana

    std::pair<int, int> targetCoords = findRandomEnemyUnitCoords(board); // Prioritize targeting enemy units
    if (targetCoords.first == -1) {
        // If no enemy unit, try a random spot
        size_t boardWidth = board.size();
        size_t boardHeight = board[0].size();
        unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
        std::default_random_engine rng(seed);
        std::uniform_int_distribution<int> distX(0, boardWidth - 1);
        std::uniform_int_distribution<int> distY(0, boardHeight - 1);
        targetCoords = {distX(rng), distY(rng)};
    }

    int targetX = targetCoords.first;
    int targetY = targetCoords.second;
    if (spellToCast->cast(board, targetX, targetY)) {
        aiPlayer->setMana(aiPlayer->getMana() - spellCost); // Deduct actual cost
        manaRemaining -= spellCost; // Deduct from allocated mana
        std::cout << "AI successfully cast spell spending " << spellCost << " mana.\n";
        return true; // Spell cast successfully
    } else {
         std::cout << "AI failed to cast spell.\n"; // Debug print
    }

    return false; // Spell cast failed
}

// AI attempts to use an Engineer's build ability with allocated mana
bool tryAIEngineerBuildSpecific(Engineer* engineer, Player* aiPlayer, int engX, int engY, std::vector<std::vector<Field*>>& board, const std::string& buildType, int& manaRemaining) {
    if (!engineer || !aiPlayer || engineer->getWill() <= 0 || manaRemaining <= 0 || board.empty() || board[0].empty()) {
        return false;
    }

    int buildCost = 0;
    if (buildType == "Fortress") buildCost = 3;
    else if (buildType == "Mana Mine") buildCost = 4;
    else if (buildType == "Trap") buildCost = 2;
    else if (buildType == "Cannon") buildCost = 0;
    else return false; // Unknown build type

    if (manaRemaining < buildCost || aiPlayer->getMana() < buildCost) return false; // Not enough allocated or total mana

    std::pair<int, int> targetSpot = findRandomAdjacentEmptyField(engX, engY, board);
    if (targetSpot.first == -1) return false; // No valid adjacent build location

    int targetX = targetSpot.first;
    int targetY = targetSpot.second;

    Field* newField = nullptr;
    // Need to preserve the unit if there is one on the field when creating a special field
    Unit* unitOnField = board[targetX][targetY]->getUnit();
    if (buildType == "Fortress") newField = engineer->createFortress(targetX, targetY);
    else if (buildType == "Mana Mine") newField = engineer->createManaMine(targetX, targetY);
    else if (buildType == "Trap") newField = engineer->createTrap(targetX, targetY);

    if (newField) {
        // Before deleting, check if the field is different from the new one to avoid self-deletion issues
        if (board[targetX][targetY] != newField) {
            delete board[targetX][targetY]; // Delete the old field object
        }
        board[targetX][targetY] = newField; // Place the new field
        // Re-set the unit if it was there, as the new field constructor might not handle it
        if(unitOnField && newField->getUnit() == nullptr) {
             board[targetX][targetY]->setUnit(unitOnField);
        }


        aiPlayer->setMana(aiPlayer->getMana() - buildCost); // Deduct actual cost
        manaRemaining -= buildCost; // Deduct from allocated mana
        engineer->setWill(engineer->getWill() - 1); // Consume engineer's will
        std::cout << "AI Engineer built " << buildType << " at (" << targetX << "," << targetY << ") spending " << buildCost << " mana.\n";
        return true;
    } else {
         std::cout << "AI Engineer failed to build " << buildType << ".\n"; // Debug print
    }

    return false; // Build failed
}

// Main AI function - Rewritten based on the new algorithm
bool AIact(Player* aiPlayer, std::vector<std::vector<Field*>>& board) {
    // Ensure this is an AI player's turn
    if (!aiPlayer || !aiPlayer->getAI() || !aiPlayer->getMyTurn() || board.empty() || board[0].empty()) {
        return false; // Return false if AI cannot act
    }

    std::cout << "\n=== AI Player's turn ===\n";
    std::cout << "Current mana: " << aiPlayer->getMana() << "\n";

    // Seed the random number generator
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    std::default_random_engine rng(seed);

    int currentMana = aiPlayer->getMana();
    int manaSpent = 0; // Declare and initialize manaSpent

    // 1. AI make 3 random numbers for mana allocation
    std::uniform_int_distribution<int> dist1(0, currentMana);
    int manaForUnits = dist1(rng);
    int manaRemainingAfterUnits = currentMana - manaForUnits;

    std::uniform_int_distribution<int> dist2(0, manaRemainingAfterUnits);
    int manaForBuild = dist2(rng);
    int manaRemainingAfterBuild = manaRemainingAfterUnits - manaForBuild;

    std::uniform_int_distribution<int> dist3(0, manaRemainingAfterBuild);
    int manaForSpells = dist3(rng);
    int manaForAttackMove = currentMana - manaForUnits - manaForBuild - manaForSpells; // Mana not allocated to specific actions

    // --- FIX: Ensure at least one allocation is nonzero if AI has mana ---
    if (currentMana > 0 && manaForUnits == 0 && manaForBuild == 0 && manaForSpells == 0 && manaForAttackMove == 0) {
        // Prefer to allocate to units, but fallback to build or spells if needed
        if (currentMana >= 2) { // Infantry cost
            manaForUnits = 2;
        } else if (currentMana >= 3) { // Fortress cost
            manaForBuild = 3;
        } else if (currentMana >= 2) { // Fireball cost
            manaForSpells = 2;
        } else {
            manaForAttackMove = currentMana; // Just try to move/attack
        }
    }
    // --- END FIX ---

    std::cout << "AI allocated Mana: Units=" << manaForUnits << ", Build=" << manaForBuild << ", Spells=" << manaForSpells << ", Attack/Move=" << manaForAttackMove << ".\n";
    bool actionTakenThisTurn = false; // Flag to track if any action was taken during the entire turn

    // 2. Create units until spend 1st number amount of mana
    std::vector<std::string> creatableUnits = {"infantry", "archer", "priest", "engineer"};
    int manaSpentOnUnits = 0;
    while (manaSpentOnUnits < manaForUnits && aiPlayer->getMana() > 0) {
        std::vector<std::string> shuffledUnits = creatableUnits;
        std::shuffle(shuffledUnits.begin(), shuffledUnits.end(), rng);

        bool unitCreatedThisAttempt = false; // Flag to see if a unit was created in this inner loop iteration

        for (const auto& unitTypeToCreate : shuffledUnits) {
            int unitCost = 0;
            if (unitTypeToCreate == "archer") unitCost = 3;
            else if (unitTypeToCreate == "infantry") unitCost = 2;
            else if (unitTypeToCreate == "priest") unitCost = 5;
            else if (unitTypeToCreate == "engineer") unitCost = 5;
            

            if (aiPlayer->getMana() >= unitCost && manaSpentOnUnits + unitCost <= manaForUnits) {
                 std::pair<int, int> spawnSpot = findRandomAICreateSpot(board);
                if (spawnSpot.first != -1) {
                     int x = spawnSpot.first;
                     int y = spawnSpot.second;
                     Unit* newUnit = createUnit(unitTypeToCreate, false); // false for AI player
                     if (newUnit) {
                         board[x][y]->setUnit(newUnit);
                         aiPlayer->setMana(aiPlayer->getMana() - unitCost);
                         manaSpentOnUnits += unitCost;
                         actionTakenThisTurn = true;
                         unitCreatedThisAttempt = true; // Mark that a unit was created
                         std::cout << "AI created " << unitTypeToCreate << " at (" << x << "," << y << ") for " << unitCost << " mana.\n";
                         // No break here, continue trying to create more units within the allocated mana
                     }
                 }
            }
        }
        // If no unit was created in this attempt through all shuffled types, break the outer while loop
        if (!unitCreatedThisAttempt) break;
    }
    manaSpent += manaSpentOnUnits; // Add mana spent on units to total

    // 3. Build things with engineer until spend 2nd number amount of mana
    int manaSpentOnBuild = 0;
    // Find an AI-controlled engineer - Need to re-find engineer after potential unit creation
    Engineer* engineerUnit = nullptr;
    size_t boardWidth = board.size(); // Use this declaration
    size_t boardHeight = board[0].size(); // Use this declaration
    for (size_t x = 0; x < boardWidth; ++x) {
        for (size_t y = 0; y < boardHeight; ++y) {
            Field* field = board[x][y];
            if (field) {
                Unit* unit = field->getUnit();
                if (unit && !unit->getPlayer() && dynamic_cast<Engineer*>(unit)) {
                    engineerUnit = dynamic_cast<Engineer*>(unit);
                    break; // Found an engineer, take the first one
                }
            }
        }
        if (engineerUnit) break;
    }

    if (engineerUnit) {
         std::vector<std::string> creatableBuildings = {"Fortress", "Mana Mine", "Trap", "cannon"};
         while (manaSpentOnBuild < manaForBuild && aiPlayer->getMana() > 0 && engineerUnit->getWill() > 0) {
             bool buildingAttemptedThisRound = false;
             std::vector<std::string> shuffledBuildings = creatableBuildings;
             std::shuffle(shuffledBuildings.begin(), shuffledBuildings.end(), rng);
             for (const auto& buildType : shuffledBuildings) {
                 int buildCost = 0;
                 if (buildType == "Fortress") buildCost = 3;
                 else if (buildType == "Mana Mine") buildCost = 4;
                 else if (buildType == "Trap") buildCost = 2;
                 else if (buildType == "cannon") buildCost = 2;

                 if (aiPlayer->getMana() >= buildCost && manaSpentOnBuild + buildCost <= manaForBuild && engineerUnit->getWill() > 0) {
                      // Re-find engineer position in case it moved (unlikely for engineer)
                     int currentEngX = -1, currentEngY = -1;
                     bool engineerFound = false;
                     for(size_t x = 0; x < boardWidth; ++x) {
                         for(size_t y = 0; y < boardHeight; ++y) {
                             if(board[x][y]->getUnit() == engineerUnit) {

                                 currentEngX = static_cast<int>(x);
                                 currentEngY = static_cast<int>(y);
                                 engineerFound = true;
                                 break;
                             }
                         }
                         if(engineerFound) break;
                     }

                     if (!engineerFound) break; // Engineer is gone

                     int tempManaRemaining = manaForBuild - manaSpentOnBuild; // Pass remaining allocated mana for build
                     if (tryAIEngineerBuildSpecific(engineerUnit, aiPlayer, currentEngX, currentEngY, board, buildType, tempManaRemaining)) {
                          manaSpentOnBuild += (manaForBuild - manaSpentOnBuild) - tempManaRemaining; // Update mana spent
                          actionTakenThisTurn = true;
                          buildingAttemptedThisRound = true;
                     }
                 }
             }
             if (!buildingAttemptedThisRound) break; // If no building was attempted in this round, stop.
         }
    }
    manaSpent += manaSpentOnBuild; // Add mana spent on build to total


    // 4. Cast spells until spend 3d amount of mana
    int manaSpentOnSpells = 0;
    std::vector<Spell*> creatableSpells;
    // Create instances of spells to get their costs
    creatableSpells.push_back(new MorogSpell()); // 5 mana
    creatableSpells.push_back(new FireballSpell()); // 2 mana
    creatableSpells.push_back(new CurseSpell()); // 3 mana
    creatableSpells.push_back(new BombSpell()); // 4 mana

    while (manaSpentOnSpells < manaForSpells && aiPlayer->getMana() > 0) {
        bool spellCastThisAttempt = false;
        std::vector<Spell*> shuffledSpells = creatableSpells;
         unsigned seed_spell = std::chrono::steady_clock::now().time_since_epoch().count();
        std::shuffle(shuffledSpells.begin(), shuffledSpells.end(), std::default_random_engine(seed_spell));
        for (Spell* spellToCast : shuffledSpells) {
            int spellCost = spellToCast->getManaCost();
            if (aiPlayer->getMana() >= spellCost && manaSpentOnSpells + spellCost <= manaForSpells) {
                 int tempManaRemaining = manaForSpells - manaSpentOnSpells; // Pass remaining allocated mana for spells
                 if (tryAICastSpecificSpell(aiPlayer, board, spellToCast, tempManaRemaining)) {
                     manaSpentOnSpells += (manaForSpells - manaSpentOnSpells) - tempManaRemaining; // Update mana spent
                     actionTakenThisTurn = true;
                     spellCastThisAttempt = true;
                 }
             }
        }
        if (!spellCastThisAttempt) break; // If no spell was cast in this round of attempts, stop.
    }

    // Clean up dynamically allocated spell objects
    for(Spell* spell : creatableSpells) {
        delete spell;
    }
    creatableSpells.clear();
    manaSpent += manaSpentOnSpells; // Add mana spent on spells to total


    // 5. tries to attack and spend on as much will as it can (attack in functions) with all units
    // 6. tries to move until spend all will
    // Collect AI units' current positions after mana spending
    std::vector<std::pair<int, int>> aiUnitsCoords;
    // size_t boardWidth = board.size(); // Removed redeclaration
    // size_t boardHeight = board[0].size(); // Removed redeclaration
    for (size_t x = 0; x < boardWidth; ++x) {
        for (size_t y = 0; y < boardHeight; ++y) {
            Field* field = board[x][y];
            if (field) {
                Unit* unit = field->getUnit();
                if (unit && !unit->getPlayer()) { // Check for AI units
                     aiUnitsCoords.push_back({static_cast<int>(x), static_cast<int>(y)});
                }
            }
        }
    }
    // Shuffle units to randomize action order
    std::shuffle(aiUnitsCoords.begin(), aiUnitsCoords.end(), rng);
    // Action phase (Attack and Move)
    for (const auto& coords : aiUnitsCoords) {
        int currentX = coords.first;
        int currentY = coords.second;

        // Re-fetch field and unit at the *current* coordinates within the loop
        Field* currentField = nullptr;
        if (currentX >= 0 && static_cast<size_t>(currentX) < boardWidth && currentY >= 0 && static_cast<size_t>(currentY) < boardHeight) {
            currentField = board[currentX][currentY];
        }

        if (!currentField || !currentField->getUnit() || currentField->getUnit()->getPlayer() || currentField->getUnit()->getWill() <= 0) {
             continue; // Skip if no valid AI unit with will at this coordinate
        }

        Unit* unit = currentField->getUnit();
        // Unit action loop based on Will
        while(unit->getWill() > 0) {
            bool unitActionTakenThisIteration = false; // Flag to track if a unit action occurred

            // Prioritize attack over move
            // Use currentX and currentY for actions
            if (tryAIAttack(unit, currentX, currentY, board)) { // tryAIAttack consumes Will on success and returns true if successful
                unitActionTakenThisIteration = true;
                actionTakenThisTurn = true; // Mark that an action was taken this turn

                 // After successful attack, re-verify unit's presence and position
                 Field* fieldAfterAttack = nullptr;
                 if (currentX >= 0 && static_cast<size_t>(currentX) < boardWidth && currentY >= 0 && static_cast<size_t>(currentY) < boardHeight) {
                    fieldAfterAttack = board[currentX][currentY];
                 }

                 if (!fieldAfterAttack || fieldAfterAttack->getUnit() != unit) {
                      break; // Unit was removed or moved
                 }

            } else {
                // If attack not possible, try to move
                int willBeforeMove = unit->getWill();
                tryAIMove(unit, currentX, currentY, board);

                // Find the unit again to check its will and new position
                bool unitFoundAfterMove = false;
                int newX = -1, newY = -1;
                Unit* unitAfterMove = nullptr; // Pointer to the unit after potential move
                 for (size_t bx = 0; bx < boardWidth; ++bx) {
                    for (size_t by = 0; by < boardHeight; ++by) {
                        if (board[bx][by] && board[bx][by]->getUnit() == unit) {

                            newX = static_cast<int>(bx);
                            newY = static_cast<int>(by);
                            unitAfterMove = unit; // Found the unit
                            unitFoundAfterMove = true;
                            break;
                        }
                    }
                    if (unitFoundAfterMove) break;
                }

                // Check if move was successful
                if (unitFoundAfterMove && unitAfterMove->getWill() < willBeforeMove) {
                    unitActionTakenThisIteration = true;
                    actionTakenThisTurn = true;
                    currentX = newX;
                    currentY = newY;
                 } else if (!unitFoundAfterMove) {
                     // Unit disappeared from board after move attempt?
                     // This shouldn't happen.
                     // Log error or break? For now, break the inner loop for this unit.
                     // std::cerr << "Error: AI Unit lost after move attempt.\n";
                     break;
                 } else {
                     // Move attempt failed or did not consume will
                     unitActionTakenThisIteration = false; // Explicitly mark no action
                 }
            }

            // If unit still has will but no action was taken in this iteration, break to prevent infinite loop
            if (unit->getWill() > 0 && !unitActionTakenThisIteration) {
                 break;
            }

            // If the unit's will has become 0 or less, exit the while loop
            if (unit->getWill() <= 0) {
                break;
            }

            // Re-fetch unit pointer in case it was deleted (e.g., counter-attack)
            // Check bounds first
             if (currentX >= 0 && static_cast<size_t>(currentX) < boardWidth && currentY >= 0 && static_cast<size_t>(currentY) < boardHeight) {
                unit = board[currentX][currentY]->getUnit();
                if (!unit) break; // Unit was destroyed, exit loop
             } else {
                 break; // Unit moved out of bounds? Should not happen.
             }


        } // End while(unit->getWill() > 0)
    } // End for (const auto& coords : aiUnitsCoords)


    // --- End Turn ---
    // Corrected: Use aiPlayer instead of currentPlayer
    // Corrected: Use the declared manaSpent variable
    std::cout << "AI turn ended. Mana spent: " << manaSpent << ".\n";
    aiPlayer->setMyTurn(false); // End AI's turn
    return actionTakenThisTurn; // Return whether any action was taken
} // <--- End of AIact function (renamed from getAICommands)

// Creates a new unit based on type string
Unit* createUnit(const std::string& type, bool isPlayer) {
    if (type == "archer") return new Archer(isPlayer);
    if (type == "infantry") return new Infantry(isPlayer);
    if (type == "priest") return new Priest(isPlayer);
    if (type == "engineer") return new Engineer(isPlayer);
    if (type == "cannon") return new Cannon("Cannon", 0, 4, 4, 5, isPlayer);
    return nullptr; // Unknown type
}

// AI attempts to attack a nearby enemy unit
bool tryAIAttack(Unit* unit, int x, int y, std::vector<std::vector<Field*>>& board) {
    if (!unit || unit->getWill() <= 0 || board.empty() || board[0].empty()) return false;
    int attackRange = unit->getAttackDistance();
    size_t boardWidth = board.size();
    size_t boardHeight = board[0].size();

    std::vector<std::pair<int, int>> possibleTargets;
    for (int dx = -attackRange; dx <= attackRange; ++dx) {
        for (int dy = -attackRange; dy <= attackRange; ++dy) {
            if (dx == 0 && dy == 0) continue;
            int targetX = x + dx;
            int targetY = y + dy;
            if (targetX >= 0 && static_cast<size_t>(targetX) < boardWidth &&
                targetY >= 0 && static_cast<size_t>(targetY) < boardHeight)
            {
                Field* targetField = board[targetX][targetY];
                if (!targetField) continue;
                Unit* targetUnit = targetField->getUnit();

                if (targetUnit && targetUnit->getPlayer() != unit->getPlayer()) {
                     // Use Manhattan distance for attack range check
                    if (std::abs(dx) + std::abs(dy) <= attackRange) {
                        possibleTargets.push_back({targetX, targetY});
                    }
                }
            }
        }
    }

    if (!possibleTargets.empty()) {
         unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
         std::default_random_engine rng(seed);
        std::shuffle(possibleTargets.begin(), possibleTargets.end(), rng);

        int targetX = possibleTargets[0].first;
        int targetY = possibleTargets[0].second;
        std::cout << "AI " << unit->getName() << " (" << x << "," << y << ") attacks " << board[targetX][targetY]->getUnit()->getName() << " (" << targetX << "," << targetY << ")\n";
        attack(board, x, y, targetX, targetY);
        return true; // Attack successful
    }

    return false; // No successful attack
}

// AI attempts to move the unit to a random valid adjacent empty field
void tryAIMove(Unit* unit, int x, int y, std::vector<std::vector<Field*>>& board) {
    if (!unit || unit->getWill() <= 0 || board.empty() || board[0].empty()) return;
    int moveRange = unit->getMoveDistance();
    size_t boardWidth = board.size();
    size_t boardHeight = board[0].size();
    std::vector<std::pair<int, int>> possibleMoves; // Store possible moves
    std::vector<std::pair<int, int>> safeMoves; // Moves that are not BombedField

    // Find all valid moves within Manhattan distance
    for (int dx = -moveRange; dx <= moveRange; ++dx) {
        for (int dy = -moveRange; dy <= moveRange; ++dy) {
             if (std::abs(dx) + std::abs(dy) > moveRange || (dx == 0 && dy == 0)) {
                continue;
             }
            int newX = x + dx;
            int newY = y + dy;
            if (newX >= 0 && static_cast<size_t>(newX) < boardWidth &&
                newY >= 0 && static_cast<size_t>(newY) < boardHeight)
            {
                 Field* targetField = board[newX][newY];
                 // Check if the target field is a plain field or a hill, and is empty
                 if(targetField && !targetField->getUnit() &&
                    (dynamic_cast<Field*>(targetField) != nullptr || dynamic_cast<Hill*>(targetField) != nullptr)) {
                     possibleMoves.push_back({newX, newY});
                     if (!dynamic_cast<BombedField*>(targetField)) {
                         safeMoves.push_back({newX, newY});
                     }
                 }
            }
        }
    }

    std::vector<std::pair<int, int>>* movesToUse = &possibleMoves;
    if (!safeMoves.empty()) {
        movesToUse = &safeMoves;
    }

    if (!movesToUse->empty()) {
        // Shuffle the possible moves and pick the first one
        unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
        std::default_random_engine rng(seed);
        std::shuffle(movesToUse->begin(), movesToUse->end(), rng);
        int targetX = (*movesToUse)[0].first;
        int targetY = (*movesToUse)[0].second;
        move(board, x, y, targetX, targetY);
    }
    // If no valid moves, do nothing (will not be reduced)
}

bool getAICommands(Player* currentPlayer, std::vector<std::vector<Field*>>& board) {
    return AIact(currentPlayer, board);
}
