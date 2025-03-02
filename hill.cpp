#include "hill.h"

// Constructor for Hill, initializing Field and height
Hill::Hill(int x, int y, int height, Unit* unit)
    : Field(x, y, unit), _height(height) {}

// Destructor
Hill::~Hill() = default;

// Getter for height
int Hill::getHeight() const {
    return _height;
}

// Setter for height
void Hill::setHeight(int height) {
    _height = height;
}