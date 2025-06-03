// hospitalfield.cpp
#include "hospitalfield.h"
#include "field.h"
#include "unit.h"
#include "player.h"
#include <iostream>

HospitalField::HospitalField(int fieldX, int fieldY, Unit* initialUnit, int healAmount)
    : Field(fieldX, fieldY, "hospital"), healPerTurn(healAmount)
{
    // Set the initial unit if there is one
    setUnit(initialUnit);
}

// Removed the explicit definition of the destructor.
// The "= default" in the header is sufficient.
// HospitalField::~HospitalField()
// {
//     // The unit on the field is not owned by the field.
// }

// Corrected: Commented out unused 'board' parameter
void HospitalField::applyEffect(Player* owner, std::vector<std::vector<Field*>>& /*board*/)
{
    // Heal the unit on the field if there is one and it belongs to the owner
    if (unit && owner && unit->getPlayer() == !owner->getAI()) // Assuming human player is !getAI()
    {
        std::cout << "Hospital field at (" << getX() << "," << getY() << ") heals " << unit->getName() << " for " << healPerTurn << " health.\n";
        unit->restoreHealth(healPerTurn);
    }
    // Note: Hospital fields don't have a duration based on the header,
    // so they persist unless replaced by another field.
}

// Corrected: Commented out unused 'unit' parameter
bool HospitalField::canEnter(Unit* /*unit*/) const
{
    // Units can enter hospital fields
    return this->unit == nullptr; // Can enter if empty
}
