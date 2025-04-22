// spell.h
#ifndef SPELL_H
#define SPELL_H

#include <vector>
#include "field.h"
#include "unit.h"
#include "fortress.h"

class Spell {
protected:
    int _manaCost;
public:
    Spell(int manaCost = 5);
    virtual ~Spell() = default;
    
    int getManaCost() const;
    virtual bool cast(std::vector<std::vector<Field*>>& board, int x, int y) = 0;
};

#endif