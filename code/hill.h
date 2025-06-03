// hill.h
#ifndef HILL_H
#define HILL_H

#include "field.h"
#include <string>

/**
 * @brief Represents a Hill field on the board, which provides a defense bonus.
 */
class Hill : public Field
{
public:
    /**
     * @brief Constructs a Hill at the given coordinates, optionally with a unit.
     * @param fieldX X coordinate.
     * @param fieldY Y coordinate.
     * @param initialUnit Pointer to the initial unit on the hill (default nullptr).
     */
    Hill(int fieldX, int fieldY, Unit* initialUnit = nullptr);
    virtual ~Hill() = default;

    /**
     * @brief Gets the defense bonus provided by the hill.
     * @return The defense bonus value.
     */
    int getDefenseBonus() const override;

    /**
     * @brief Checks if a unit can enter the hill.
     * @param unit The unit to check.
     * @return True if the unit can enter, false otherwise.
     */
    bool canEnter(Unit* unit) const override;

    /**
     * @brief Gets the symbol representing the hill (for display).
     * @return '^' character.
     */
    char getSymbol() const override { return '^'; }
};

#endif
