// bombspell.h
#ifndef BOMBSPELL_H
#define BOMBSPELL_H

#include "spell.h"
#include "bombedfield.h" // Include for BombedField

class BombedField; // Forward declaration

/**
 * @brief Spell that creates a bombed field (trap) at a target location (Bomb).
 */
class BombSpell : public Spell
{
public:
    /**
     * @brief Constructs a BombSpell.
     */
    BombSpell();
    virtual ~BombSpell() = default;

    /**
     * @brief Casts the Bomb spell at the given coordinates.
     * @param board The game board.
     * @param x X coordinate of the target.
     * @param y Y coordinate of the target.
     * @return True if the spell was cast successfully, false otherwise.
     */
    bool cast(std::vector<std::vector<Field*>>& board, int x, int y) override;
};

#endif
