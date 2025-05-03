// priest.cpp
#include "priest.h"
#include "shieldedfield.h"

Priest::Priest(bool player)
    : Unit("Priest", 1, 1, 5, 0, player, 3) {}

void Priest::protectFromSpells(std::vector<std::vector<Field*>>& board, int x, int y)
{
    for (int dx = -1; dx <= 1; ++dx)
    {
        for (int dy = -1; dy <= 1; ++dy)
        {
            int nx = x + dx;
            int ny = y + dy;
            if (nx >= 0 && nx < static_cast<int>(board.size()) &&
                    ny >= 0 && ny < static_cast<int>(board[0].size()))
            {
                delete board[nx][ny];
                board[nx][ny] = new ShieldedField(nx, ny, board[nx][ny]->getUnit());
            }
        }
    }
}