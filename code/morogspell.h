// morogspell.h
#ifndef MOROGSPELL_H
#define MOROGSPELL_H

#include "spell.h"

/**
 * @brief Spell that changes owner of unit on the field
 */
class MorogSpell : public Spell
{
public:
    /**
     * @brief Constructs a MorogSpell.
     */
    MorogSpell();
    virtual ~MorogSpell() = default;

    /**
     * @brief Casts the Morog spell at the given coordinates.
     * @param board The game board.
     * @param x X coordinate of the target.
     * @param y Y coordinate of the target.
     * @return True if the spell was cast successfully, false otherwise.
     */
    bool cast(std::vector<std::vector<Field*>>& board, int x, int y) override;
};

#endif
