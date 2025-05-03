// fireballspell.cpp
#include "fireballspell.h"
#include "burnedfield.h"

FireballSpell::FireballSpell() : Spell(5) {}

bool FireballSpell::cast(std::vector<std::vector<Field*>>& board, int x, int y)
{
    if (x >= 0 && x < static_cast<int>(board.size()) &&
            y >= 0 && y < static_cast<int>(board[0].size()))
    {
        Unit* unit = board[x][y]->getUnit();
        delete board[x][y];
        board[x][y] = new BurnedField(x, y, 3, unit); // Burns for 3 turns
        return true;
    }
    return false;
}