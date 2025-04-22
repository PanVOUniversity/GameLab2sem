// bombedfield.cpp
#include "bombedfield.h"

BombedField::BombedField(int x, int y, Unit* unit) :
    Field(x, y, unit), _timer(0) {}

void BombedField::unitEntered(Unit* unit)
{
    if (unit)
    {
        unit->setHealth(unit->getHealth() - 2 * (_timer + 1));
    }
}

void BombedField::endTurnEffect()
{
    _timer++;
    if (_unit)
    {
        _unit->setHealth(_unit->getHealth() - 2 * _timer);
    }
}


bool BombedField::shouldExplode() const
{
    return _timer >= 3;
}