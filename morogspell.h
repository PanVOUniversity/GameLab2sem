// morogspell.h
#ifndef MOROGSPELL_H
#define MOROGSPELL_H

#include "spell.h"

class MorogSpell : public Spell
{
public:
    MorogSpell();
    virtual ~MorogSpell() = default;

    bool cast(std::vector<std::vector<Field*>>& board, int x, int y) override;
};

#endif