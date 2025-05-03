// getcommands.cpp
#include "getcommands.h"
#include "player.h"
#include "field.h"
#include "unit.h"
#include "functions.h"
#include "spells.h"
#include "archer.h"
#include "infantry.h"
#include "priest.h"
#include "engineer.h"
#include "cannon.h" // Include Cannon header
#include "fortress.h" // Include Fortress header
#include "manaminefield.h" // Include ManaMineField header
#include "bombedfield.h" // Include BombedField header
#include "hill.h" // Include Hill header
#include "shieldedfield.h" // Include ShieldedField header
#include "burnedfield.h" // Include BurnedField header
#include "hospitalfield.h" // Include HospitalField header


#include <iostream>
#include <vector>
#include <string>
#include <limits> // Required for numeric_limits
#include <cmath> // Required for abs
#include <algorithm> // Required for std::min/max, std::transform
#include <sstream> // Required for stringstream
#include <cctype> // Required for ::tolower
#include <iomanip> // For std::setw

void unit_map(const std::vector<std::vector<Field*>>& board);
void field_map(const std::vector<std::vector<Field*>>& board);

// Function to get commands from the human player
// This function will parse player input and call appropriate game functions
bool getPlayerCommands(Player* currentPlayer, std::vector<std::vector<Field*>>& board)
{
    bool actionTaken = false; // Track if any action was taken during the turn
    while (true) {
        // Show all available player commands at the start of the turn
        std::cout << "\n=== PLAYER COMMANDS ===\n";
        std::cout << "Current mana: " << currentPlayer->getMana() << "\n";
        std::cout << "MOVE startX startY endX endY         - Move a unit\n";
        std::cout << "ATTACK attackerX attackerY targetX targetY - Attack with a unit\n";
        std::cout << "CREATE unitType X Y                  - Create a unit (infantry, archer, priest, engineer, cannon)\n";
        std::cout << "SPELL spellName X Y                  - Cast a spell (morog, fireball, curse, bomb)\n";
        std::cout << "PRAY X Y                             - Use Priest's pray ability\n";
        std::cout << "BUILD buildType X Y                  - Use Engineer to build (fortress, cannon, manamine, trap)\n";
        std::cout << "UNITS                                - Show unit descriptions\n";
        std::cout << "SPELLS                               - Show spell descriptions\n";
        std::cout << "RULES                                - Show all game rules\n";
        std::cout << "END                                  - End your turn\n";
        std::cout << "MAPS                                 - Show special field maps\n";
        std::cout << "-------------------------------------\n";

    std::string command;
    std::cin >> command;
    std::transform(command.begin(), command.end(), command.begin(), ::tolower);

    if (command == "rules") {
        std::cout << "\n=== GAME RULES ===\n";
        std::cout << "\n--- Turn Structure ---\n";
        std::cout << "1. The game is played on a 10x10 board. Each player takes turns, starting with the human player.\n";
        std::cout << "2. On your turn, you may perform any number of actions (move, attack, create, spell, pray, build) as long as you have enough mana and your units have will points.\n";
        std::cout << "3. You may use meta-commands (RULES, UNITS, SPELLS, MAPS) at any time; these do not count as actions.\n";
        std::cout << "4. To end your turn, use the END command. If you take no action and use END, it counts as a skipped turn.\n";
        std::cout << "NOTE: You can only create units in rows y > 4.\n\n";

        std::cout << "--- Units and Actions ---\n";
        std::cout << "- Each unit has: Health, Damage, Will (actions per turn), Move Distance, Attack Range, and Mana Cost.\n";
        std::cout << "- Units can move, attack, and use special abilities if they have will points left.\n";
        std::cout << "- Infantry can move and attack in the same turn. Other units must choose one action per turn.\n";
        std::cout << "- Engineers can build special fields (Fortress, Mana Mine, Trap, Hospital, Cannon) on empty, valid tiles.\n";
        std::cout << "- Priests can PRAY to create a Shielded Field.\n";
        std::cout << "- Cannons are built by Engineers and cannot move.\n\n";

        std::cout << "--- Resource Management ---\n";
        std::cout << "- Mana is used to create units, cast spells, and build special fields.\n";
        std::cout << "- Mana Mines generate 1 mana per turn for their owner.\n";
        std::cout << "- If you have no units and no mana, you lose the game.\n\n";

        std::cout << "--- Field Effects ---\n";
        std::cout << "- Fortress: Defensive bonus, can be captured, heals units.\n";
        std::cout << "- Mana Mine: Generates mana for the owner.\n";
        std::cout << "- Trap (Bombed Field): Damages units that step on it.\n";
        std::cout << "- Hill: Provides attack/defense bonus.\n";
        std::cout << "- Burned Field: Damages units at the end of turn.\n";
        std::cout << "- Hospital: Heals units at the end of turn.\n";
        std::cout << "- Shielded Field: Absorbs damage for a limited time.\n\n";

        std::cout << "--- Spells ---\n";
        std::cout << "- Morog: 5 mana. Deals 15 damage to a unit.\n";
        std::cout << "- Fireball: 2 mana. Deals 5 damage to a unit.\n";
        std::cout << "- Curse: 3 mana. Reduces a unit's Will by 1.\n";
        std::cout << "- Bomb: 4 mana. Creates a BombedField (trap) at a location.\n\n";

        std::cout << "--- Victory and Defeat ---\n";
        std::cout << "- The game ends if:\n";
        std::cout << "  1. A player has no units and no mana.\n";
        std::cout << "  2. Either player skips 2 turns in a row.\n";
        std::cout << "  3. 16 turns have passed (draw).\n";
        std::cout << "- Capturing all fortresses or eliminating all enemy units also results in victory.\n\n";

        std::cout << "--- Meta-Commands ---\n";
        std::cout << "- UNITS: Show unit descriptions.\n";
        std::cout << "- SPELLS: Show spell descriptions.\n";
        std::cout << "- MAPS: Show special field maps.\n";
        std::cout << "- RULES: Show these rules.\n\n";

        std::cout << "--- Additional Notes ---\n";
        std::cout << "- Units cannot move or attack through other units.\n";
        std::cout << "- Spells and builds require sufficient mana.\n";
        std::cout << "- Units require sufficient mana to create.\n";
        std::cout << "- Use the MAPS command to view the board's special fields and unit positions.\n";
        std::cout << "- Use END to finish your turn if you do not wish to take further actions.\n\n";
        continue;
    }
    if (command == "units") {
        std::cout << "\n=== UNITS ===\n";
        std::cout << "Infantry (I): Move 2, Attack 1, Health 10, Damage 3, Will 2, Cost 2 mana. Can counter-attack.\n";
        std::cout << "Archer (A): Move 2, Attack 2 (3 in Fortress), Health 7, Damage 2, Will 2, Cost 3 mana. Range bonus in Fortress.\n";
        std::cout << "Priest (P): Move 2, Attack 0, Health 5, Damage 0, Will 1, Cost 5 mana. Can pray to create ShieldedField.\n";
        std::cout << "Engineer (E): Move 1, Attack 1, Health 6, Damage 1, Will 3, Cost 5 mana. Can build Fortress, Mana Mine, Trap, Hospital, Cannon.\n";
        std::cout << "Cannon (C): Move 0, Attack 4, Health 4, Damage 5, Will 1, Cost 0 mana (built by Engineer). Static, powerful ranged attack.\n";
        continue;
    }
    if (command == "spells") {
        std::cout << "\n=== SPELLS ===\n";
        std::cout << "Morog: 5 mana. Deals 15 damage to a unit.\n";
        std::cout << "Fireball: 2 mana. Deals 5 damage to a unit.\n";
        std::cout << "Curse: 3 mana. Reduces a unit's Will by 1.\n";
        std::cout << "Bomb: 4 mana. Creates a BombedField (trap) at a location.\n";
        continue;
    }
    if (command == "maps") {
        std::cout << "\n=== MAPS ===\n";
        std::cout << "Available maps: field, unit\n";
        std::cout << "Enter map type: ";
        std::string mapType;
        std::cin >> mapType;
        std::transform(mapType.begin(), mapType.end(), mapType.begin(), ::tolower);
        if (mapType == "field") field_map(board);
        else if (mapType == "unit") unit_map(board);
        else std::cout << "Unknown map type.\n";
        continue;
    }

    // Only show the turn prompt for actionable commands

    if (command == "move")
    {
        int startX, startY, endX, endY;
        if (std::cin >> startX >> startY >> endX >> endY)
        {
            // Check if coordinates are within board bounds
            size_t boardWidth = board.size();
            size_t boardHeight = board[0].size();
            if (startX >= 0 && static_cast<size_t>(startX) < boardWidth &&
                startY >= 0 && static_cast<size_t>(startY) < boardHeight &&
                endX >= 0 && static_cast<size_t>(endX) < boardWidth &&
                endY >= 0 && static_cast<size_t>(endY) < boardHeight)
            {
                Field* startField = board[startX][startY];
                Field* endField = board[endX][endY];

                // Check if there's a unit at the start position and it belongs to the current player
                if (startField->getUnit() && startField->getUnit()->getPlayer() == !currentPlayer->getAI()) // Assuming human player is !getAI()
                {
                    // Check if the unit has enough will to move
                    if (startField->getUnit()->getWill() > 0) {
                        // Check if the target field is valid for movement (empty and not a blocking field)
                        if (endField->canEnter(startField->getUnit())) {
                             // Check if the move is within the unit's move distance (Manhattan distance)
                             if (std::abs(startX - endX) + std::abs(startY - endY) <= startField->getUnit()->getMoveDistance()) {
                                 move(board, startX, startY, endX, endY);
                                 startField->getUnit()->setWill(startField->getUnit()->getWill() - 1); // Consume will
                                 actionTaken = true;
                                 continue;
                             } else {
                                 std::cout << "Invalid move: Target is outside unit's move distance.\n";
                             }
                        } else {
                            std::cout << "Invalid move: Cannot move to this field.\n";
                        }
                    } else {
                        std::cout << "Invalid move: Unit has no will left.\n";
                    }
                }
                else
                {
                    std::cout << "Invalid move: No unit or not your unit at starting position.\n";
                }
            }
            else
            {
                std::cout << "Invalid move: Coordinates out of bounds.\n";
            }
        }
        else
        {
            std::cout << "Invalid MOVE command format. Use: MOVE startX startY endX endY\n";
            std::cin.clear(); // Clear error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        }
    }
    else if (command == "attack")
    {
        int attackerX, attackerY, targetX, targetY;
        if (std::cin >> attackerX >> attackerY >> targetX >> targetY)
        {
            // Check if coordinates are within board bounds
             size_t boardWidth = board.size();
            size_t boardHeight = board[0].size();
            if (attackerX >= 0 && static_cast<size_t>(attackerX) < boardWidth &&
                attackerY >= 0 && static_cast<size_t>(attackerY) < boardHeight &&
                targetX >= 0 && static_cast<size_t>(targetX) < boardWidth &&
                targetY >= 0 && static_cast<size_t>(targetY) < boardHeight)
            {
                Field* attackerField = board[attackerX][attackerY];
                Field* targetField = board[targetX][targetY];

                // Check if there's a unit at the attacker position and it belongs to the current player
                if (attackerField->getUnit() && attackerField->getUnit()->getPlayer() == !currentPlayer->getAI()) // Assuming human player is !getAI()
                {
                    // Check if the unit has enough will to attack
                    if (attackerField->getUnit()->getWill() > 0) {
                        // Check if there's a unit at the target position and it belongs to the opponent
                        if (targetField->getUnit() && targetField->getUnit()->getPlayer() != !currentPlayer->getAI())
                        {
                            // Check if the target is within the attacker's attack distance (Manhattan distance)
                             // Corrected: Changed startY to attackerY
                             if (std::abs(attackerX - targetX) + std::abs(attackerY - targetY) <= attackerField->getUnit()->getAttackDistance()) {
                                 attack(board, attackerX, attackerY, targetX, targetY);
                                 attackerField->getUnit()->setWill(attackerField->getUnit()->getWill() - 1); // Consume will
                                 actionTaken = true;
                                 continue;
                             } else {
                                 std::cout << "Invalid attack: Target is outside unit's attack distance.\n";
                             }
                        }
                        else
                        {
                            std::cout << "Invalid attack: No unit or not an enemy unit at target position.\n";
                        }
                    } else {
                        std::cout << "Invalid attack: Unit has no will left.\n";
                    }
                }
                else
                {
                    std::cout << "Invalid attack: No unit or not your unit at attacking position.\n";
                }
            }
            else
            {
                std::cout << "Invalid ATTACK command format. Coordinates out of bounds.\n";
            }
        }
        else
        {
            std::cout << "Invalid ATTACK command format. Use: ATTACK attackerX attackerY targetX targetY\n";
            std::cin.clear(); // Clear error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        }
    }
    else if (command == "create")
    {
        std::string unitType;
        int x, y;
        if (std::cin >> unitType >> x >> y)
        {
            // Convert unitType to lowercase
            std::transform(unitType.begin(), unitType.end(), unitType.begin(), ::tolower);

            // Check if coordinates are within board bounds
             size_t boardWidth = board.size();
            size_t boardHeight = board[0].size();
            if (x >= 0 && static_cast<size_t>(x) < boardWidth &&
                y >= 0 && static_cast<size_t>(y) < boardHeight) {
                if (y <= 4) {
                    std::cout << "You can only create units in rows y > 4.\n";
                    continue;
                }
                 Field* targetField = board[x][y];
                // Check if the target field is empty and not a special field that blocks creation
                bool isSpecialField = dynamic_cast<ManaMineField*>(targetField) != nullptr ||
                                      dynamic_cast<BombedField*>(targetField) != nullptr ||
                                      dynamic_cast<Fortress*>(targetField) != nullptr ||
                                      dynamic_cast<Hill*>(targetField) != nullptr ||
                                      dynamic_cast<BurnedField*>(targetField) != nullptr ||
                                      dynamic_cast<HospitalField*>(targetField) != nullptr ||
                                      dynamic_cast<ShieldedField*>(targetField) != nullptr;

                if (targetField->getUnit() == nullptr && !isSpecialField) // Corrected condition
                {
                    Unit* newUnit = nullptr;
                    int cost = 0;

                    if (unitType == "infantry") { newUnit = new Infantry(true); cost = 2; }
                    else if (unitType == "archer") { newUnit = new Archer(true); cost = 3; }
                    else if (unitType == "priest") { newUnit = new Priest(true); cost = 5; }
                    else if (unitType == "engineer") { newUnit = new Engineer(true); cost = 5; }
                    else if (unitType == "cannon") { newUnit = new Cannon("Cannon", 0, 4, 4, 5, true); cost = 0; } // Cannon cost is 0

                    if (newUnit)
                    {
                        if (currentPlayer->subtractMana(cost))
                        {
                            board[x][y]->setUnit(newUnit);
                            std::cout << "Created " << unitType << " at (" << x << "," << y << ") for " << cost << " mana.\n";
                            actionTaken = true;
                            continue;
                        }
                        else
                        {
                            std::cout << "Not enough mana to create " << unitType << ".\n";
                            delete newUnit; // Clean up allocated unit
                        }
                    }
                    else
                    {
                        std::cout << "Invalid unit type: " << unitType << ".\n";
                    }
                }
                else
                {
                    std::cout << "Invalid CREATE location: Field is occupied or is a special field.\n";
                }
            }
            else
            {
                std::cout << "Invalid CREATE command format. Coordinates out of bounds.\n";
            }
        }
        else
        {
            std::cout << "Invalid CREATE command format. Use: CREATE unitType X Y\n";
            std::cin.clear(); // Clear error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        }
    }
    else if (command == "spell")
    {
        std::string spellName;
        int x, y;
        if (std::cin >> spellName >> x >> y)
        {
            // Convert spellName to lowercase
            std::transform(spellName.begin(), spellName.end(), spellName.begin(), ::tolower);

            // Check if coordinates are within board bounds
             size_t boardWidth = board.size();
            size_t boardHeight = board[0].size();
            if (x >= 0 && static_cast<size_t>(x) < boardWidth &&
                y >= 0 && static_cast<size_t>(y) < boardHeight)
            {
                Spell* spellToCast = nullptr;
                int cost = 0;

                if (spellName == "morog") { spellToCast = new MorogSpell(); cost = 5; }
                else if (spellName == "fireball") { spellToCast = new FireballSpell(); cost = 2; }
                else if (spellName == "curse") { spellToCast = new CurseSpell(); cost = 3; }
                else if (spellName == "bomb") { spellToCast = new BombSpell(); cost = 4; }
                // else if (spellName == "teleport") { spellToCast = new TeleportSpell(); cost = 6; } // Commented out due to TeleportSpell being abstract
                else {
                    std::cout << "Invalid spell name: " << spellName << ".\n";
                }

                if (spellToCast)
                {
                    if (currentPlayer->subtractMana(cost))
                    {
                        if (spellToCast->cast(board, x, y))
                        {
                            std::cout << "Cast " << spellName << " at (" << x << "," << y << ") for " << cost << " mana.\n";
                            delete spellToCast; // Clean up allocated spell
                            actionTaken = true;
                            continue;
                        }
                        else
                        {
                            std::cout << "Spell failed to cast at (" << x << "," << y << ").\n";
                            currentPlayer->addMana(cost); // Refund mana if spell failed
                            delete spellToCast; // Clean up allocated spell
                        }
                    }
                    else
                    {
                        std::cout << "Not enough mana to cast " << spellName << ".\n";
                        delete spellToCast; // Clean up allocated spell
                    }
                }
            }
            else
            {
                std::cout << "Invalid SPELL command format. Coordinates out of bounds.\n";
            }
        }
        else
        {
            std::cout << "Invalid SPELL command format. Use: SPELL spellName X Y\n";
            std::cin.clear(); // Clear error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        }
    }
    else if (command == "pray")
    {
         int x, y;
         if (std::cin >> x >> y)
         {
             // Check if coordinates are within board bounds
              size_t boardWidth = board.size();
             size_t boardHeight = board[0].size();
             if (x >= 0 && static_cast<size_t>(x) < boardWidth &&
                 y >= 0 && static_cast<size_t>(y) < boardHeight)
             {
                 // Find a Priest unit controlled by the current player with Will > 0
                 Priest* castingPriest = nullptr;
                 // Iterate through the board to find the player's priests
                 for (size_t i = 0; i < boardWidth; ++i) {
                     for (size_t j = 0; j < boardHeight; ++j) {
                         Field* currentField = board[i][j];
                         Unit* unit = currentField->getUnit();
                         // Human player units have getPlayer() == true
                         if (unit && unit->getPlayer() && dynamic_cast<Priest*>(unit) && unit->getWill() > 0) {
                             castingPriest = dynamic_cast<Priest*>(unit);
                             break; // Found a priest, take the first one
                         }
                     }
                     if (castingPriest) break;
                 }

                 if (castingPriest) {
                      // Check if the target field is valid for praying (not a special field that cannot be shielded)
                      Field* targetField = board[x][y];
                       bool isSpecialField = dynamic_cast<ShieldedField*>(targetField) != nullptr ||
                                             dynamic_cast<Fortress*>(targetField) != nullptr ||
                                             dynamic_cast<Hill*>(targetField) != nullptr ||
                                             dynamic_cast<BurnedField*>(targetField) != nullptr ||
                                             dynamic_cast<BombedField*>(targetField) != nullptr ||
                                             dynamic_cast<HospitalField*>(targetField) != nullptr ||
                                             dynamic_cast<ManaMineField*>(targetField) != nullptr;

                      if (!isSpecialField) // Can pray on non-special fields
                      {
                         if (castingPriest->pray(board, x, y)) { // Priest::pray handles mana and will cost
                             std::cout << "Priest prayed at (" << x << "," << y << ").\n";
                             actionTaken = true;
                             continue;
                         } else {
                             std::cout << "Priest failed to pray at (" << x << "," << y << ").\n";
                         }
                      } else {
                          std::cout << "Invalid PRAY target: Cannot pray on this special field.\n";
                      }

                 } else {
                     std::cout << "No Priest unit with will available to pray.\n";
                 }

             } else {
                 std::cout << "Invalid PRAY command format. Coordinates out of bounds.\n";
             }
         } else {
             std::cout << "Invalid PRAY command format. Use: PRAY X Y\n";
             std::cin.clear(); // Clear error flags
             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
         }
    }
    else if (command == "build")
    {
        std::string buildType;
        int x, y;
        if (std::cin >> buildType >> x >> y)
        {
            // Convert buildType to lowercase
            std::transform(buildType.begin(), buildType.end(), buildType.begin(), ::tolower);

            // Check if coordinates are within board bounds
             size_t boardWidth = board.size();
            size_t boardHeight = board[0].size();
            if (x >= 0 && static_cast<size_t>(x) < boardWidth &&
                y >= 0 && static_cast<size_t>(y) < boardHeight)
            {
                // Find an Engineer unit controlled by the current player with Will > 0
                Engineer* buildingEngineer = nullptr;
                 // Iterate through the board to find the player's engineers
                 for (size_t i = 0; i < boardWidth; ++i) {
                     for (size_t j = 0; j < boardHeight; ++j) {
                         Field* currentField = board[i][j];
                         Unit* unit = currentField->getUnit();
                         // Human player units have getPlayer() == true
                         if (unit && unit->getPlayer() && dynamic_cast<Engineer*>(unit) && unit->getWill() > 0) {
                             buildingEngineer = dynamic_cast<Engineer*>(unit);
                             break; // Found an engineer, take the first one
                         }
                     }
                     if (buildingEngineer) break;
                 }


                if (buildingEngineer) {
                     Field* targetField = board[x][y];
                    // Check if the target field is empty and not a special field that blocks building
                    bool isSpecialField = dynamic_cast<ManaMineField*>(targetField) != nullptr ||
                                          dynamic_cast<BombedField*>(targetField) != nullptr ||
                                          dynamic_cast<Fortress*>(targetField) != nullptr ||
                                          dynamic_cast<Hill*>(targetField) != nullptr ||
                                          dynamic_cast<BurnedField*>(targetField) != nullptr ||
                                          dynamic_cast<HospitalField*>(targetField) != nullptr ||
                                          dynamic_cast<ShieldedField*>(targetField) != nullptr;

                    if (targetField->getUnit() == nullptr && !isSpecialField) // Corrected condition
                    {
                        int cost = 0;
                        Field* newField = nullptr;
                        // Unit* unitOnField = board[x][y]->getUnit(); // Removed unused variable

                        if (buildType == "fortress") {
                            cost = 3;
                            if (currentPlayer->subtractMana(cost)) {
                                newField = buildingEngineer->createFortress(x, y);
                            } else {
                                std::cout << "Not enough mana to build Fortress.\n";
                            }
                        } else if (buildType == "cannon") {
                            cost = 0; // Cannon build cost is 0
                            // Cannons are units, created directly.
                            // Check if the target field is valid for placing a unit.
                            if (targetField->getUnit() == nullptr && !isSpecialField) { // Re-check validity for unit placement
                                // Determine player status for the new cannon (should be human player)
                                bool cannonIsPlayer = !currentPlayer->getAI();
                                Unit* newCannon = new Cannon("Cannon", 0, 4, 4, 5, cannonIsPlayer);
                                board[x][y]->setUnit(newCannon);
                                buildingEngineer->setWill(buildingEngineer->getWill() - 1); // Consume engineer's will
                                std::cout << "Engineer built Cannon at (" << x << "," << y << ").\n";
                                actionTaken = true;
                                continue;
                            } else {
                                std::cout << "Invalid BUILD cannon location: Field is occupied or is a special field.\n";
                            }

                        } else if (buildType == "manamine") {
                            cost = 4;
                            if (currentPlayer->subtractMana(cost)) {
                                newField = buildingEngineer->createManaMine(x, y);
                            } else {
                                std::cout << "Not enough mana to build Mana Mine.\n";
                            }
                        } else if (buildType == "trap") {
                            cost = 2;
                             if (currentPlayer->subtractMana(cost)) {
                                newField = buildingEngineer->createTrap(x, y);
                            } else {
                                std::cout << "Not enough mana to build Trap.\n";
                            }
                        }
                        else {
                            std::cout << "Invalid build type: " << buildType << ".\n";
                        }

                        if (newField)
                        {
                             // Need to preserve the unit if there is one on the field when creating a special field
                            Unit* unitBeforeBuild = board[x][y]->getUnit(); // Should be null based on validation
                            delete board[x][y]; // Delete the old field object
                            board[x][y] = newField; // Place the new field
                             // Re-set the unit if it was there, as the new field constructor might not handle it
                            if(unitBeforeBuild && newField->getUnit() == nullptr) {
                                board[x][y]->setUnit(unitBeforeBuild);
                            }

                            buildingEngineer->setWill(buildingEngineer->getWill() - 1); // Consume engineer's will
                            std::cout << "Engineer built " << buildType << " at (" << x << "," << y << ") for " << cost << " mana.\n";
                            actionTaken = true;
                            continue;
                        }
                    }
                    else
                    {
                        std::cout << "Invalid BUILD location: Field is occupied or is a special field.\n";
                    }
                } else {
                    std::cout << "No Engineer unit with will available to build.\n";
                }
            }
            else
            {
                std::cout << "Invalid BUILD command format. Coordinates out of bounds.\n";
            }
        }
        else
        {
            std::cout << "Invalid BUILD command format. Use: BUILD buildType X Y\n";
            std::cin.clear(); // Clear error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        }
    }
    else if (command == "end")
    {
        std::cout << "Ending turn.\n";
        return actionTaken; // Return whether any action was taken this turn
    }
    else
    {
        std::cout << "Unknown command.\n";
        // Consume the rest of the line to prevent issues with the next input
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    return false; // No valid action was taken
}

// The getAICommands function seems to be defined in AI.cpp based on previous interactions.
// It is declared in getcommands.h, so no definition is needed here.

// Placeholder definitions for map functions if they are not defined elsewhere
// These might be defined in a separate display or utility file.
// Adding basic implementations to allow compilation if they are missing.

void unit_map(const std::vector<std::vector<Field*>>& board) {
    std::cout << "--- Unit Map ---\n";
    std::cout << "Legend: 1st letter - owner (M=Player, E=Enemy/AI), 2nd letter - unit type (I=Infantry, A=Archer, P=Priest, E=Engineer, C=Cannon), number - HP\n";
    size_t boardWidth = board.size();
    size_t boardHeight = boardWidth ? board[0].size() : 0;

    // Print column indices (now x axis)
    std::cout << "    ";
    for (size_t x = 0; x < boardWidth; ++x) std::cout << "   " << x << "   ";
    std::cout << "\n";
    // Print alignment bars under column numbers
    std::cout << "    ";
    for (size_t x = 0; x < boardWidth; ++x) std::cout << "   |   ";
    std::cout << "\n";

    // Print top border
    std::cout << "    +";
    for (size_t x = 0; x < boardWidth; ++x) std::cout << "------";
    std::cout << "---------+\n";

    for (size_t y = 0; y < boardHeight; ++y) {
        // Print each of the 3 lines for the 3x3 box
        for (int boxLine = 0; boxLine < 3; ++boxLine) {
            if (boxLine == 1) std::cout << std::setw(4) << (std::to_string(y) + ":") << "|";
            else std::cout << "    |";
            for (size_t x = 0; x < boardWidth; ++x) {
                Field* field = board[x][y];
                Unit* unit = field->getUnit();
                if (unit) {
                    char owner = unit->getPlayer() ? 'M' : 'E';
                    char type = unit->getName().empty() ? '?' : std::toupper(unit->getName()[0]);
                    int hp = unit->getCurrentHealth();
                    if (hp > 9) hp = 9;
                    std::string unitStr = std::string(1, owner) + type + std::to_string(hp);
                    if (boxLine == 1) std::cout << " " << unitStr << "  |";
                    else std::cout << "      |";
                } else {
                    std::cout << "      |";
                }
            }
            std::cout << "\n";
        }
        // Print row separator
        std::cout << "    +";
        for (size_t x = 0; x < boardWidth; ++x) std::cout << "------";
        std::cout << "---------+\n";
    }
}

void field_map(const std::vector<std::vector<Field*>>& board) {
    std::cout << "--- Field Map ---\n";
    std::cout << "Legend: Fortress-F, Hospital-H, Shielded-S, Mana Mine-M, Bombed-B, Burned-*, Hill-^, Normal-N\n";
    size_t boardWidth = board.size();
    size_t boardHeight = boardWidth ? board[0].size() : 0;
    // Print column indices
    std::cout << "   ";
    for (size_t y = 0; y < boardHeight; ++y) std::cout << y << " ";
    std::cout << "\n";
    for (size_t x = 0; x < boardWidth; ++x) {
        std::cout << x << ": ";
        for (size_t y = 0; y < boardHeight; ++y) {
            Field* field = board[x][y];
            if (dynamic_cast<Fortress*>(field)) std::cout << 'F';
            else if (dynamic_cast<HospitalField*>(field)) std::cout << 'H';
            else if (dynamic_cast<ShieldedField*>(field)) std::cout << 'S';
            else if (dynamic_cast<ManaMineField*>(field)) std::cout << 'M';
            else if (dynamic_cast<BombedField*>(field)) std::cout << 'B';
            else if (dynamic_cast<BurnedField*>(field)) std::cout << '*';
            else if (dynamic_cast<Hill*>(field)) std::cout << '^';
            else if (dynamic_cast<Field*>(field)) std::cout << 'N';
            else std::cout << '.';
            std::cout << " ";
        }
        std::cout << "\n";
    }
    std::cout << "-------------------\n";
}

void displayBoard(const std::vector<std::vector<Field*>>& board) {
    size_t width = board.size();
    if (width == 0) return;
    size_t height = board[0].size();

    std::cout << "   ";
    for (size_t y = 0; y < height; ++y) std::cout << y << " ";
    std::cout << "\n";
    for (size_t x = 0; x < width; ++x) {
        std::cout << x << ": ";
        for (size_t y = 0; y < height; ++y) {
            Field* field = board[x][y];
            if (field->getUnit())
                std::cout << field->getUnit()->getSymbol() << " ";
            else
                std::cout << field->getSymbol() << " ";
        }
        std::cout << "\n";
    }
}
