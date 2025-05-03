// spell.cpp
#include "spell.h"

Spell::Spell(int manaCost) : _manaCost(manaCost) {}

int Spell::getManaCost() const
{
    return _manaCost;
}