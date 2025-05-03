// infantry.cpp
#include "infantry.h"

Infantry::Infantry(bool player)
    : Unit("Infantry", 2, 1, 8, 2, player, 2) {}

void Infantry::counterAttack(Unit* attacker)
{
    if (attacker && dynamic_cast<Infantry*>(attacker))
    {
        attacker->setHealth(attacker->getHealth() - 1);
    }
}