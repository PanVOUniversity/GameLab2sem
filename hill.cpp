#include "hill.h"

Hill::Hill(int x, int y, int height, Unit* unit)
    : Field(x, y, unit), _height(height) {}

int Hill::getHeight() const { return _height; }
void Hill::setHeight(int height) { _height = height; }