#ifndef GETCOMMANDS_H
#define GETCOMMANDS_H

#include <vector>
#include <string>
#include <iostream>
#include <sstream> // For std::istringstream
#include <iomanip> // For std::setw
#include <random> // For random number generation
#include <chrono> // For seeding the random number generator
#include <algorithm> // For std::shuffle

#include "player.h"
#include "field.h"
#include "functions.h" // For move, attack, checkBombExplosions, createShieldedField
#include "spells.h"    // For spell classes
#include "unit.h"      // For Unit and derived classes
#include "hill.h"      // For Hill
#include "burnedfield.h" // For BurnedField
#include "bombedfield.h" // For BombedField
#include "hospitalfield.h" // For HospitalField
#include "fortress.h" // For Fortress
#include "shieldedfield.h" // For ShieldedField
#include "archer.h" // Include specific unit types for dynamic_cast
#include "infantry.h"
#include "priest.h" // Include Priest for the pray command
#include "engineer.h"
#include "cannon.h"
#include "manaminefield.h"


/**
 * @brief Handles player commands during their turn.
 *
 * @param currentPlayer The current player.
 * @param board The game board.
 * @return true if a resource-consuming action was taken, false otherwise.
 */
bool getPlayerCommands(Player* currentPlayer, std::vector<std::vector<Field*>>& board);

/**
 * @brief Handles AI commands during its turn.
 *
 * @param currentPlayer The current AI player.
 * @param board The game board.
 * @return true if a resource-consuming action was taken, false otherwise.
 */
bool getAICommands(Player* currentPlayer, std::vector<std::vector<Field*>>& board);


/**
 * @brief Displays a map showing the locations of hills.
 *
 * @param board The game board.
 */
void hill_map(const std::vector<std::vector<Field*>>& board);

/**
 * @brief Displays a map showing burned fields.
 *
 * @param board The game board.
 */
void burned_map(const std::vector<std::vector<Field*>>& board);

/**
 * @brief Displays a map showing bombed fields.
 *
 * @param board The game board.
 */
void bomb_map(const std::vector<std::vector<Field*>>& board);

/**
 * @brief Displays a map showing hospital fields.
 *
 * @param board The game board.
 */
void hospital_map(const std::vector<std::vector<Field*>>& board);

/**
 * @brief Displays a map showing fortresses.
 *
 * @param board The game board.
 */
void fortress_map(const std::vector<std::vector<Field*>>& board);

/**
 * @brief Displays a map showing shielded fields.
 *
 * @param board The game board.
 */
void shield_map(const std::vector<std::vector<Field*>>& board);

/**
 * @brief Displays a map showing mana mine positions.
 *
 * @param board The game board.
 */
void manamine_map(const std::vector<std::vector<Field*>>& board);

/**
 * @brief Displays a map showing trap positions (bombed fields).
 *
 * @param board The game board.
 */
void trap_map(const std::vector<std::vector<Field*>>& board);

void displayBoard(const std::vector<std::vector<Field*>>& board);

void unit_map(const std::vector<std::vector<Field*>>& board);
void field_map(const std::vector<std::vector<Field*>>& board);

#endif // GETCOMMANDS_H
