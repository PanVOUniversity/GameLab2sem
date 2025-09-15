// AI.h
#ifndef AI_H
#define AI_H

// Use forward declarations to avoid including full headers if not necessary
class Player;
class Field;
class Unit; // Forward declaration needed for function declarations below

#include <vector>

// Function declarations
/**
 * @brief Performs the main AI logic for the AI player's turn.
 * @param aiPlayer Pointer to the AI player.
 * @param board The game board.
 * @return True if the AI performed a resource-consuming action, false otherwise.
 */
bool AIact(Player* aiPlayer, std::vector<std::vector<Field*>>& board);

/**
 * @brief Handles AI commands during its turn.
 * @param currentPlayer The current AI player.
 * @param board The game board.
 * @return True if a resource-consuming action was taken, false otherwise.
 */
bool getAICommands(Player* currentPlayer, std::vector<std::vector<Field*>>& board);

// Declarations for helper functions used in AI.cpp
/**
 * @brief Attempts to make the AI attack with the given unit.
 * @param unit The unit to attack with.
 * @param x The unit's x coordinate.
 * @param y The unit's y coordinate.
 * @param board The game board.
 * @return True if an attack was performed, false otherwise.
 */
bool tryAIAttack(Unit* unit, int x, int y, std::vector<std::vector<Field*>>& board);

/**
 * @brief Attempts to move the given AI unit.
 * @param unit The unit to move.
 * @param x The unit's x coordinate.
 * @param y The unit's y coordinate.
 * @param board The game board.
 */
void tryAIMove(Unit* unit, int x, int y, std::vector<std::vector<Field*>>& board);

#endif
