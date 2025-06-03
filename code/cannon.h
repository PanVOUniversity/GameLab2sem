// cannon.h
#ifndef CANNON_H
#define CANNON_H

#include "unit.h"
#include <vector>
#include "field.h"
#include "fortress.h"
#include <iostream>
#include <cmath>
#include <utility> // For std::pair
#include <string> // For std::string

// Forward declarations
class Field;
class Unit;

// Enum for Cannon direction
enum class Direction { FRONT, BACK, LEFT, RIGHT, FRONT_LEFT, FRONT_RIGHT, BACK_LEFT, BACK_RIGHT };

/**
 * @brief Stationary ranged unit with directional fire ability (Cannon).
 */
class Cannon : public Unit
{
private:
    Direction _direction;

    // Helper functions (declared here as they are used internally)
    std::pair<int, int> _findFriendlyNearby(const std::vector<std::vector<Field*>>& board, int x, int y) const;
    std::pair<int, int> _findEnemyInRange(const std::vector<std::vector<Field*>>& board, int x, int y) const;
    std::pair<int, int> _findEmptyFieldInRange(const std::vector<std::vector<Field*>>& board, int x, int y) const;
    std::pair<int, int> _findFriendlyFortressNearby(const std::vector<std::vector<Field*>>& board, int x, int y) const;

public:
    /**
     * @brief Constructs a Cannon unit.
     * @param unitName Name of the unit (default: "Cannon").
     * @param moveD Move distance (default: 0).
     * @param attackD Attack distance (default: 4).
     * @param health Health value (default: 4).
     * @param dmg Damage value (default: 5).
     * @param isPlayer True if controlled by player, false if AI (default: false).
     * @param will Will points (default: 1).
     * @param dir Initial direction (default: FRONT).
     */
    Cannon(const std::string& unitName = "Cannon", int moveD = 0, int attackD = 4, int health = 4, int dmg = 5, bool isPlayer = false, int will = 1, Direction dir = Direction::FRONT);
    virtual ~Cannon() = default; // Declared as default in header

    /**
     * @brief Sets the cannon's direction.
     * @param dir The new direction.
     */
    void setDirection(Direction dir);

    /**
     * @brief Gets the cannon's direction.
     * @return The current direction.
     */
    Direction getDirection() const;

    /**
     * @brief Fires at the specified target coordinates.
     * @param board The game board.
     * @param targetX X coordinate of the target.
     * @param targetY Y coordinate of the target.
     * @return True if the fire action was successful.
     */
    bool fire(std::vector<std::vector<Field*>>& board, int targetX, int targetY);

    /**
     * @brief Uses the cannon's special ability (fire).
     * @param board The game board.
     * @param targetX X coordinate of the target.
     * @param targetY Y coordinate of the target.
     * @return True if the ability was used successfully.
     */
    bool useAbility(std::vector<std::vector<Field*>>& board, int targetX, int targetY) override;

    /**
     * @brief Gets the symbol representing the cannon (for display).
     * @return 'C' character.
     */
    char getSymbol() const { return 'C'; }
};

#endif
