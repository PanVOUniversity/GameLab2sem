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
#include "manaminefield.h" // Include for ManaMineField
#include "shieldedfield.h" // Include for ShieldedField
#include "hospitalfield.h" // Include for HospitalField
#include "infantry.h"
class Player; // Forward declaration for Player
class Unit; // Forward declaration for Unit
class Field; // Forward declaration for Field

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
 * Applies damage to a unit and handles unit removal if health drops to 0 or below.
 *
 * @param board The game board
 * @param x X coordinate of the unit's field
 * @param y Y coordinate of the unit's field
 * @param damage The amount of damage to apply
 * @param attackingUnit The unit performing the attack (can be null)
 */
void applyDamage(std::vector<std::vector<Field*>>& board, int x, int y, int damage, Unit* attackingUnit);

/**
 * Handles the attack logic between two units.
 *
 * @param board The game board
 * @param attackerX X coordinate of the attacking unit
 * @param attackerY Y coordinate of the attacking unit
 * @param targetX X coordinate of the target unit
 * @param targetY Y coordinate of the target unit
 */
void attack(std::vector<std::vector<Field*>>& board, int attackerX, int attackerY, int targetX, int targetY);

/**
 * Handles the movement logic for a unit.
 *
 * @param board The game board
 * @param startX X coordinate of the starting field
 * @param startY Y coordinate of the starting field
 * @param endX X coordinate of the destination field
 * @param endY Y coordinate of the destination field
 */
void move(std::vector<std::vector<Field*>>& board, int startX, int startY, int endX, int endY);


/**
 * Creates a ShieldedField at the specified coordinates.
 *
 * @param board The game board.
 * @param x The x-coordinate for the new field.
 * @param y The y-coordinate for the new field.
 * @param unitOnField The unit currently on the field (can be null).
 */
void createShieldedField(std::vector<std::vector<Field*>>& board, int x, int y, Unit* unitOnField);

/**
 * Creates a HospitalField at the specified coordinates.
 *
 * @param board The game board.
 * @param x The x-coordinate for the new field.
 * @param y The y-coordinate for the new field.
 * @param unitOnField The unit currently on the field (can be null).
 */
void createHospitalField(std::vector<std::vector<Field*>>& board, int x, int y, Unit* unitOnField);

void displayRules();

#endif
