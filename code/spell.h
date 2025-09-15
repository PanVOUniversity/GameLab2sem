// spell.h
#ifndef SPELL_H
#define SPELL_H

#include <string>
#include <vector>
#include "field.h" // Include Field header

class Field; // Forward declaration

/**
 * @brief Abstract base class for all spells in the game.
 */
class Spell
{
protected:
    std::string name;
    int manaCost;

public:
    /**
     * @brief Constructs a Spell with the given name and mana cost.
     * @param spellName Name of the spell.
     * @param cost Mana cost to cast the spell.
     */
    Spell(const std::string& spellName, int cost);
    /** @brief Virtual destructor for Spell. */
    virtual ~Spell() = default;

    /** @brief Gets the name of the spell. */
    std::string getName() const;
    /** @brief Gets the mana cost of the spell. */
    int getManaCost() const;

    /**
     * @brief Casts the spell on the board at the given coordinates.
     * @param board The game board.
     * @param x X coordinate of the target.
     * @param y Y coordinate of the target.
     * @return True if the spell was cast successfully, false otherwise.
     */
    virtual bool cast(std::vector<std::vector<Field*>>& board, int x, int y) = 0; // Pure virtual
};

#endif
