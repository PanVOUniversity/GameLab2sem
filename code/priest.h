// priest.h
#ifndef PRIEST_H
#define PRIEST_H

#include "unit.h"
#include <vector> // Required for std::vector
#include "field.h" // Include Field header
#include "shieldedfield.h" // Include ShieldedField header
#include "functions.h" // Include functions for helper function (createShieldedField)
#include <cmath> // For std::abs
#include <iostream> // For std::cout
#include "burnedfield.h"
#include "hospitalfield.h"

class Field; // Forward declaration for Field

/**
 * @brief Support unit that can create shielded fields (Priest).
 */
class Priest : public Unit
{
public:
    /**
     * @brief Constructs a Priest unit.
     * @param player True if controlled by player, false if AI (default: false).
     */
    Priest(bool player = false);
    virtual ~Priest() = default;

    /**
     * @brief Uses the pray ability to create a ShieldedField at the target location.
     * @param board The game board.
     * @param targetX X coordinate of the target.
     * @param targetY Y coordinate of the target.
     * @return True if the ability was used successfully.
     */
    bool pray(std::vector<std::vector<Field*>>& board, int targetX, int targetY);

    // Override useAbility if Priest has a general ability (e.g., heal)
    // virtual bool useAbility(std::vector<std::vector<Field*>>& board, int targetX, int targetY) override;

    /**
     * @brief Gets the symbol representing the priest (for display).
     * @return 'P' character.
     */
    char getSymbol() const { return 'P'; }
};

#endif
