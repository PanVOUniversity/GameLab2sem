// burnedfield.cpp
#include "burnedfield.h"

BurnedField::BurnedField(int x, int y, int burnTime, Unit* unit)
    : Field(x, y, unit), _burnTime(burnTime) {}

void BurnedField::burnUnit(Unit* unit)
{
    if (unit)
    {
        unit->setHealth(unit->getHealth() - 2); // 2 damage per turn
    }
}

bool BurnedField::updateBurnTime()
{
    return --_burnTime <= 0;
}