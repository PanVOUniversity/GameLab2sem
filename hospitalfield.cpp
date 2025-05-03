// hospitalfield.cpp
#include "hospitalfield.h"

HospitalField::HospitalField(int x, int y, Unit* unit)
    : Field(x, y, unit) {}

void HospitalField::applyHospitalEffect(Unit* unit)
{
    if (unit)
    {
        unit->setHealth(unit->getHealth() + 3);
    }
}