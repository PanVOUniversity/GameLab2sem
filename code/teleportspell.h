// teleportspell.h
#ifndef TELEPORTSPELL_H
#define TELEPORTSPELL_H

#include "spell.h"
#include "unit.h" // Include Unit header
#include <vector> // Required for std::vector
#include "field.h" // Include Field header

class Unit; // Forward declaration
class Field; // Forward declaration

/**
 * @brief Spell that teleports a unit to a new location (Teleport).
 */
class TeleportSpell : public Spell
{
public:
    /**
     * @brief Constructs a TeleportSpell.
     */
    TeleportSpell();
    virtual ~TeleportSpell() = default;

    /**
     * @brief Casts the Teleport spell at the given coordinates.
     * @param board The game board.
     * @param x X coordinate of the target.
     * @param y Y coordinate of the target.
     * @return True if the spell was cast successfully, false otherwise.
     */
    bool cast(std::vector<std::vector<Field*>>& board, int x, int y) override;
};

#endif
