#include "fortress.h"

Fortress::Fortress(int x, int y, int height, int strength, Unit* unit)
    : Hill(x, y, height, unit), _strength(strength) {}

int Fortress::getStrength() const {
    return _strength;
}

bool Fortress::setStrength(int strength) {
    _strength = strength;
    return (_strength <= 0);
}