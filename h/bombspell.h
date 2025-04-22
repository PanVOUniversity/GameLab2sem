// bombspell.h
#ifndef BOMBSPELL_H
#define BOMBSPELL_H

#include "spell.h"

class BombSpell : public Spell {
public:
    BombSpell();
    bool cast(std::vector<std::vector<Field*>>& board, int x, int y) override;
};

#endif