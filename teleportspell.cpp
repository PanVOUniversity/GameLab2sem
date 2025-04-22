// teleportspell.cpp
#include "teleportspell.h"

TeleportSpell::TeleportSpell() : Spell(6) {}

bool TeleportSpell::cast(std::vector<std::vector<Field*>>& board, int fromX, int fromY, int toX, int toY)
{
    if (fromX < 0 || fromY < 0 || fromX >= board.size() || fromY >= board[0].size() || toX < 0|| toY<0 || toX>=board.size() || toY >= board[0].size())
    {
        return false;
    }
    Unit* unit = board[fromX][fromY]->getUnit();
    if (!unit || unit->getPlayer() != board[toX][toY]->getUnit()->getPlayer())
    {
        return false;
    }
    board[toX][toY]->setUnit(unit);
    board[fromX][fromY]->setUnit(nullptr);
    return true;
}