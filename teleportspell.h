// teleportspell.h
#ifndef TELEPORTSPELL_H
#define TELEPORTSPELL_H

#include "spell.h"

class TeleportSpell : public Spell
{
public:
    TeleportSpell();
    virtual ~TeleportSpell() = default;
    bool cast(std::vector<std::vector<Field*>>& board, int fromX, int fromY, int toX, int toY);
};

#endif