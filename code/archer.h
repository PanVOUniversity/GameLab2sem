// archer.h
#ifndef ARCHER_H
#define ARCHER_H

#include "unit.h"

/**
 * @brief Ranged unit with variable attack distance (Archer).
 */
class Archer : public Unit
{
public:
    /**
     * @brief Constructs an Archer unit.
     * @param player True if controlled by player, false if AI (default: false).
     */
    Archer(bool player = false);
    virtual ~Archer() = default;

    /**
     * @brief Updates the attack distance based on whether the archer is in a fortress.
     * @param inFortress True if the archer is in a fortress, false otherwise.
     */
    void updateAttackDistance(bool inFortress);

    /**
     * @brief Gets the symbol representing the archer (for display).
     * @return 'A' character.
     */
    char getSymbol() const { return 'A'; }
};

#endif
