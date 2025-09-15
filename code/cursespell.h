// cursespell.h
#ifndef CURSESPELL_H
#define CURSESPELL_H

#include "spell.h"

/**
 * @brief Spell that reduces a unit's abilities (Curse). Damage to zero
 */
class CurseSpell : public Spell
{
public:
    /**
     * @brief Constructs a CurseSpell.
     */
    CurseSpell();
    /**
     * @brief Casts the Curse spell at the given coordinates.
     * @param board The game board.
     * @param x X coordinate of the target.
     * @param y Y coordinate of the target.
     * @return True if the spell was cast successfully, false otherwise.
     */
    bool cast(std::vector<std::vector<Field*>>& board, int x, int y) override;
};

#endif