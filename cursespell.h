// cursespell.h
#ifndef CURSESPELL_H
#define CURSESPELL_H

#include "spell.h"

class CurseSpell : public Spell
{
public:
    CurseSpell();
    bool cast(std::vector<std::vector<Field*>>& board, int x, int y) override;
};

#endif