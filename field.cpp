#include "field.h"

Field::Field(int x, int y, Unit* unit)
    : _x(x), _y(y), _unit(unit) {}

int Field::getX() const { return _x; }
int Field::getY() const { return _y; }
Unit* Field::getUnit() const { return _unit; }
void Field::setUnit(Unit* unit) { _unit = unit; }