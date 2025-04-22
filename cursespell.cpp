// cursespell.cpp
#include "cursespell.h"

CurseSpell::CurseSpell() : Spell(3) {}

bool CurseSpell::cast(std::vector<std::vector<Field*>>& board, int x, int y)
{
    if (x < 0 || y < 0 || x >= board.size() || y >= board[0].size())
    {
        return false;
    }
    Unit* unit = board[x][y]->getUnit();
    if (!unit || unit->getPlayer() == board[x][y]->getUnit()->getPlayer())
    {
        return false;
    }
    unit->setDamage(0);
    return true;
}