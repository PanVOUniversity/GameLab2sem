#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>
#include "field.h"
#include "fortress.h"
#include "hill.h"
#include "unit.h"
#include <iostream>
#include <cmath>
#include "player.h"
#include <iomanip>
#include "bombedfield.h"

/**
 * Updates the strength of a fortress at given coordinates
 * If strength drops to 0 or below, replaces fortress with a plain field
 *
 * @param board The game board
 * @param x X coordinate of fortress
 * @param y Y coordinate of fortress
 * @param newStrength New strength value to set
 */
void updateFortressStrength(
    std::vector<std::vector<Field*>>& board,
    int x,
    int y,
    int newStrength
);

/**
 * Checks all bombed fields on the board and explodes them if:
 * 1. They have a unit standing on them, OR
 * 2. Their timer has expired
 *
 * @param board The game board
 */
void checkBombExplosions(std::vector<std::vector<Field*>>& board);

/**
 * Handles attack between two units
 *
 * @param board The game board
 * @param attackerX X coordinate of attacking unit
 * @param attackerY Y coordinate of attacking unit
 * @param victimX X coordinate of victim unit
 * @param victimY Y coordinate of victim unit
 */
void attack(
    std::vector<std::vector<Field*>>& board,
    int attackerX,
    int attackerY,
    int victimX,
    int victimY
);

/**
 * Moves a unit from one position to another if valid
 *
 * @param board The game board
 * @param fromX Starting X coordinate
 * @param fromY Starting Y coordinate
 * @param toX Destination X coordinate
 * @param toY Destination Y coordinate
 */
void move(
    std::vector<std::vector<Field*>>& board,
    int fromX,
    int fromY,
    int toX,
    int toY
);

/**
 * @param player1 the player
 * @param player2 the AI
 */
bool checkVictory(
    Player* player1,
    Player* player2);

#endif