// shieldedfield.h
#ifndef SHIELDEDFIELD_H
#define SHIELDEDFIELD_H

#include "field.h"
#include "unit.h" // Include Unit header
#include "player.h" // Ensure Player is included
#include <string>

class Unit; // Forward declaration (already included, but good practice)
class Player; // Forward declaration (already included, but good practice)

/**
 * @brief Field that provides a temporary shield to units (Shielded Field).
 */
class ShieldedField : public Field
{
private:
    int duration; // Turns the shield lasts

public:
    /**
     * @brief Constructs a ShieldedField at the given coordinates.
     * @param fieldX X coordinate.
     * @param fieldY Y coordinate.
     * @param initialUnit Pointer to the initial unit on the field (default nullptr).
     * @param initialDuration Number of turns the shield lasts (default 3).
     */
    ShieldedField(int fieldX, int fieldY, Unit* initialUnit = nullptr, int initialDuration = 3);
    virtual ~ShieldedField() = default;

    /**
     * @brief Applies the shielded field's effect (ticks duration, provides shield).
     * @param owner The player whose turn it is.
     * @param board The game board.
     */
    void applyEffect(Player* owner, std::vector<std::vector<Field*>>& board) override;

    /**
     * @brief Gets the defense bonus provided by the shielded field.
     * @return The defense bonus value.
     */
    int getDefenseBonus() const override;

    /**
     * @brief Checks if a unit can enter the shielded field.
     * @param unit The unit to check.
     * @return True if the unit can enter, false otherwise.
     */
    bool canEnter(Unit* unit) const override;

    /**
     * @brief Gets the symbol representing the shielded field (for display).
     * @return 'S' character.
     */
    char getSymbol() const override { return 'S'; }
};

#endif
