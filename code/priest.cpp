// priest.cpp
#include "priest.h"
#include "unit.h"
#include "field.h" // Include Field header
#include "shieldedfield.h" // Include ShieldedField header
#include "functions.h" // Include functions for helper function (createShieldedField)
#include <iostream>
#include <vector>
#include <cmath> // For std::abs

Priest::Priest(bool player)
    : Unit("Priest", 2, 0, 5, 0, player, 1) // Name, Move, Attack, Health, Damage, isPlayer, Will
{
    // Priest: Move 2, Attack 0, Health 5, Damage 0, Will 1, Symbol 'P'
}

// Destructor is defaulted in header, no dynamic memory owned by Priest itself.

// pray: costs 1 Will, expects 3 mana to be handled by caller
bool Priest::pray(std::vector<std::vector<Field*>>& board, int targetX, int targetY)
{
    // Check if the priest has enough will and mana to pray
    // Assuming pray costs 1 Will and some mana (e.g., 3 mana, matching CurseSpell for now)
    // Corrected: Commented out unused variable
    // int prayManaCost = 3; // Example mana cost for Pray
    if (getWill() > 0) {
        // Need access to the player's mana. This requires the board or player pointer.
        // Since this method is called from getPlayerCommands/AIact which have the board,
        // we need to find the player associated with this unit.
        // A more robust design might pass the player pointer to pray,
        // or the unit could have a direct pointer to its owning player.
        // For now, we'll assume the calling function handles mana deduction.
        // The mana deduction logic is handled in getPlayerCommands/AIact before calling pray.

        // Check if target coordinates are valid
        size_t boardWidth = board.size();
        size_t boardHeight = board[0].size();
        if (targetX >= 0 && static_cast<size_t>(targetX) < boardWidth &&
            targetY >= 0 && static_cast<size_t>(targetY) < boardHeight)
        {
            Field* targetField = board[targetX][targetY];

            // Check if the target field is not already a special field that cannot be shielded
            bool isSpecialField = dynamic_cast<ShieldedField*>(targetField) != nullptr ||
                                  dynamic_cast<Fortress*>(targetField) != nullptr ||
                                  dynamic_cast<Hill*>(targetField) != nullptr ||
                                  dynamic_cast<BurnedField*>(targetField) != nullptr ||
                                  dynamic_cast<BombedField*>(targetField) != nullptr ||
                                  dynamic_cast<HospitalField*>(targetField) != nullptr ||
                                  dynamic_cast<ManaMineField*>(targetField) != nullptr;

            if (!isSpecialField) // Can pray on non-special fields
            {
                 // Find the priest's current position to check distance
                 int priestX = -1, priestY = -1;
                 bool priestFound = false;
                 for(size_t i = 0; i < boardWidth; ++i) {
                     for(size_t j = 0; j < boardHeight; ++j) {
                         Field* currentField = board[i][j];
                         Unit* unit = currentField->getUnit();
                         // Human player units have getPlayer() == true
                         if (unit && unit->getPlayer() && dynamic_cast<Priest*>(unit) == this) { // Check if the unit pointer matches 'this' priest
                             priestX = static_cast<int>(i);
                             priestY = static_cast<int>(j);
                             priestFound = true;
                             break;
                         }
                     }
                     if(priestFound) break;
                 }

                 if (priestFound) {
                     // Check if target is within praying range (e.g., Manhattan distance <= 2)
                     int prayRange = 2; // Example praying range
                     if (std::abs(priestX - targetX) + std::abs(priestY - targetY) <= prayRange) {
                         // Create a ShieldedField at the target location
                         Unit* unitOnTarget = targetField->getUnit(); // Get unit before replacing field
                         createShieldedField(board, targetX, targetY, unitOnTarget); // Use helper function
                         setWill(getWill() - 1); // Consume priest's will
                         std::cout << getName() << " prayed at (" << targetX << "," << targetY << ").\n";
                         return true; // Pray successful
                     } else {
                         std::cout << "Pray failed: Target is outside praying range.\n";
                     }
                 } else {
                     std::cout << "Pray failed: Priest unit not found on board.\n";
                 }
            } else {
                std::cout << "Pray failed: Cannot pray on this special field.\n";
            }
        } else {
             std::cout << "Pray failed: Target coordinates out of bounds.\n";
        }
    } else {
        std::cout << "Pray failed: Priest has no will left.\n";
    }
    return false; // Pray failed
}

// Note: Priest does not override useAbility based on the provided headers.
// If there were a general Priest ability (like healing), it would be implemented here.
