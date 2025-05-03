// fireballspell.h
#ifndef FIREBALLSPELL_H
#define FIREBALLSPELL_H

#include "spell.h"

class FireballSpell : public Spell
{

public:
    FireballSpell();
    virtual ~FireballSpell() = default;

    bool cast(std::vector<std::vector<Field*>>& board, int x, int y) override;
};

#endif