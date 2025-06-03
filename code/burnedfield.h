// burnedfield.h
#ifndef BURNEDFIELD_H
#define BURNEDFIELD_H

#include "field.h"
#include "unit.h" // Include Unit header
#include "player.h" // Include Player header
#include <string>
#include <vector> // Required for std::vector in applyEffect

class Unit; // Forward declaration (already included, but good practice)
class Player; // Forward declaration (already included, but good practice)

/**
 * @brief Field that deals damage to units each turn for a limited duration (Burned Field).
 */
class BurnedField : public Field
{
private:
    int duration; // Turns the field remains burned
    int damagePerTurn; // Damage dealt to units on the field each turn

public:
    /**
     * @brief Constructs a BurnedField at the given coordinates.
     * @param fieldX X coordinate.
     * @param fieldY Y coordinate.
     * @param initialUnit Pointer to the initial unit on the field (default nullptr).
     * @param initialDuration Number of turns the field remains burned (default 2).
     * @param damage Damage dealt per turn (default 2).
     */
    BurnedField(int fieldX, int fieldY, Unit* initialUnit = nullptr, int initialDuration = 2, int damage = 2);
    virtual ~BurnedField() = default; // Declared as default in header

    /**
     * @brief Applies the burned field's effect (ticks duration, deals damage).
     * @param owner The player whose turn it is.
     * @param board The game board.
     */
    void applyEffect(Player* owner, std::vector<std::vector<Field*>>& board) override;

    /**
     * @brief Gets the defense bonus provided by the burned field.
     * @return The defense bonus value.
     */
    int getDefenseBonus() const override;

    /**
     * @brief Checks if a unit can enter the burned field.
     * @param unit The unit to check.
     * @return True if the unit can enter, false otherwise.
     */
    bool canEnter(Unit* unit) const override;

    /**
     * @brief Gets the symbol representing the burned field (for display).
     * @return '*' character.
     */
    char getSymbol() const override { return '*'; }
};

#endif
