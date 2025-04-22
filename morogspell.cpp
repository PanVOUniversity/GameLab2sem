// morogspell.cpp
#include "morogspell.h"

MorogSpell::MorogSpell() : Spell(5) {}

bool MorogSpell::cast(std::vector<std::vector<Field*>>& board, int x, int y)
{
    if (x >= 0 && x < static_cast<int>(board.size()) &&
            y >= 0 && y < static_cast<int>(board[0].size()))
    {
        Unit* unit = board[x][y]->getUnit();
        if (unit)
        {
            unit->setPlayer(!unit->getPlayer()); // Switch allegiance
            return true;
        }
    }
    return false;
}