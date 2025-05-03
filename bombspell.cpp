#include "bombspell.h"
#include "bombedfield.h"

BombSpell::BombSpell() : Spell(4) {}

bool BombSpell::cast(std::vector<std::vector<Field*>>& board, int x, int y)
{
    // Check if coordinates are out of bounds
    if (x < 0 || y < 0 || x >= board.size() || y >= board[0].size())
    {
        return false;
    }

    // Check if the field is a Hill, Fortress, or ManaMineField
    if (dynamic_cast<Hill*>(board[x][y]) ||
            dynamic_cast<Fortress*>(board[x][y]) ||
            dynamic_cast<ManaMineField*>(board[x][y]))
    {
        return false;
    }

    // Check if the field already has a unit
    if (board[x][y]->getUnit() != nullptr)
    {
        return false;
    }

    // Replace the field with a BombedField
    delete board[x][y];
    board[x][y] = new BombedField(x, y, nullptr); // No unit is passed
    return true;
}