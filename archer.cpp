// archer.cpp
#include "archer.h"

Archer::Archer(bool player)
    : Unit("Archer", 2, 2, 5, 1, player, 2) {}

void Archer::updateAttackDistance(bool inFortress)
{
    setAttackDistance(inFortress ? 3 : 2);
}