// infantry.h
#ifndef INFANTRY_H
#define INFANTRY_H

#include "unit.h"

/**
 * @brief Melee unit with counter-attack ability (Infantry).
 */
class Infantry : public Unit
{
public:
    /**
     * @brief Constructs an Infantry unit.
     * @param player True if controlled by player, false if AI (default: false).
     */
    Infantry(bool player = false);
    virtual ~Infantry() = default;

    /**
     * @brief Performs a counter-attack against an attacker.
     * @param attacker The attacking unit.
     */
    void counterAttack(Unit* attacker);

    /**
     * @brief Gets the symbol representing the infantry (for display).
     * @return 'I' character.
     */
    char getSymbol() const { return 'I'; }
};

#endif
