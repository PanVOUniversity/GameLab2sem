// field.cpp
#include "field.h"
#include "unit.h"
#include "player.h"
#include <iostream>
#include <vector>

Field::Field(int fieldX, int fieldY, const std::string& fieldType)
    : unit(nullptr), x(fieldX), y(fieldY), type(fieldType)
{
}

Field::~Field()
{
    // The unit on the field is owned by the player, not the field.
    // So, the field should not delete the unit here.
    // The player's destructor or game logic should handle unit deletion.
}

Unit* Field::getUnit() const
{
    return unit;
}

void Field::setUnit(Unit* u)
{
    unit = u;
}

int Field::getX() const
{
    return x;
}

int Field::getY() const
{
    return y;
}

std::string Field::getType() const
{
    return type;
}

// Default implementation for applyEffect (does nothing)
// Corrected: Commented out unused 'owner' and 'board' parameters
void Field::applyEffect(Player* /*owner*/, std::vector<std::vector<Field*>>& /*board*/)
{
    // Default fields have no special effects
}

// Default implementation for getDefenseBonus (no bonus)
int Field::getDefenseBonus() const
{
    return 0;
}

// Default implementation for canEnter (most units can enter plain fields)
// Corrected: Commented out unused 'unit' parameter
bool Field::canEnter(Unit* /*unit*/) const
{
    // Plain fields can be entered if they are empty
    return this->unit == nullptr;
}

// Default implementation for onEnter (does nothing)
// Corrected: Commented out unused 'unit' parameter
void Field::onEnter(Unit* /*unit*/)
{
    // No special action when a unit enters a plain field
}

// Default implementation for onLeave(does nothing)
// Corrected: Commented out unused 'unit' parameter
void Field::onLeave(Unit* /*unit*/)
{
    // No special action when a unit leaves a plain field
}
