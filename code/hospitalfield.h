// hospitalfield.h
#ifndef HOSPITALFIELD_H
#define HOSPITALFIELD_H

#include "field.h"
#include "unit.h" // Include Unit header
#include "player.h" // Ensure Player is included
#include <string>

class Unit; // Forward declaration (already included, but good practice)
class Player; // Forward declaration (already included, but good practice)

/**
 * @brief Field that heals units each turn (Hospital Field).
 */
class HospitalField : public Field
{
private:
    int healPerTurn; // Amount of health healed per turn

public:
    /**
     * @brief Constructs a HospitalField at the given coordinates.
     * @param fieldX X coordinate.
     * @param fieldY Y coordinate.
     * @param initialUnit Pointer to the initial unit on the field (default nullptr).
     * @param healAmount Amount of health healed per turn (default 3).
     */
    HospitalField(int fieldX, int fieldY, Unit* initialUnit = nullptr, int healAmount = 3);
    virtual ~HospitalField() = default;

    /**
     * @brief Applies the hospital field's effect (heals unit).
     * @param owner The player whose turn it is.
     * @param board The game board.
     */
    void applyEffect(Player* owner, std::vector<std::vector<Field*>>& board) override;

    /**
     * @brief Checks if a unit can enter the hospital field.
     * @param unit The unit to check.
     * @return True if the unit can enter, false otherwise.
     */
    bool canEnter(Unit* unit) const override;

    /**
     * @brief Gets the symbol representing the hospital field (for display).
     * @return 'H' character.
     */
    char getSymbol() const override { return 'H'; }
};

#endif
