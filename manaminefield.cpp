// manaminefield.cpp
#include "manaminefield.h"

ManaMineField::ManaMineField(int x, int y, Unit* unit)
    : Field(x, y, unit) {}

void ManaMineField::generateMana(Player* player)
{
    if (player)
    {
        player->setMana(player->getMana() + 1);
    }
}