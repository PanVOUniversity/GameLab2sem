// engineer.h
#ifndef ENGINEER_H
#define ENGINEER_H

#include "unit.h"
#include "field.h"

/**
 * @brief Utility unit that can build special fields (Engineer).
 */
class Engineer : public Unit
{
public:
    /**
     * @brief Constructs an Engineer unit.
     * @param player True if controlled by player, false if AI (default: false).
     */
    Engineer(bool player = false);
    virtual ~Engineer() = default;

    /**
     * @brief Builds a fortress at the specified coordinates.
     * @param x X coordinate.
     * @param y Y coordinate.
     * @return Pointer to the new Fortress field.
     */
    Field* createFortress(int x, int y);
    /**
     * @brief Builds a mana mine at the specified coordinates.
     * @param x X coordinate.
     * @param y Y coordinate.
     * @return Pointer to the new ManaMineField.
     */
    Field* createManaMine(int x, int y);
    /**
     * @brief Builds a trap (bombed field) at the specified coordinates.
     * @param x X coordinate.
     * @param y Y coordinate.
     * @return Pointer to the new BombedField.
     */
    Field* createTrap(int x, int y);

    /**
     * @brief Gets the symbol representing the engineer (for display).
     * @return 'E' character.
     */
    char getSymbol() const { return 'E'; }
};

#endif