// fireballspell.h
#ifndef FIREBALLSPELL_H
#define FIREBALLSPELL_H

#include "spell.h"

/**
 * @brief Spell that deals damage to a target unit (Fireball).
 */
class FireballSpell : public Spell
{

public:
    /**
     * @brief Constructs a FireballSpell.
     */
    FireballSpell();
    virtual ~FireballSpell() = default;

    /**
     * @brief Casts the Fireball spell at the given coordinates.
     * @param board The game board.
     * @param x X coordinate of the target.
     * @param y Y coordinate of the target.
     * @return True if the spell was cast successfully, false otherwise.
     */
    bool cast(std::vector<std::vector<Field*>>& board, int x, int y) override;
};

#endif
