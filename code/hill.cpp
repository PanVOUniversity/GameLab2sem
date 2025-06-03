// hill.cpp
#include "hill.h"
#include "field.h"
#include "unit.h"
#include <iostream>

Hill::Hill(int fieldX, int fieldY, Unit* initialUnit)
    : Field(fieldX, fieldY, "hill")
{
    // Set the initial unit if there is one
    setUnit(initialUnit);
}

// Removed the explicit definition of the destructor.
// The "= default" in the header is sufficient.
// Hill::~Hill()
// {
//     // The unit on the field is not owned by the field.
// }

// Hill: symbol '^', defense bonus 3
// Ensure getDefenseBonus returns 3
int Hill::getDefenseBonus() const
{
    // Hills provide a defense bonus
    return 3; // Example defense bonus
}

// Corrected: Commented out unused 'unit' parameter
bool Hill::canEnter(Unit* /*unit*/) const
{
    // Units can enter hills if they are empty
    return this->unit == nullptr; // Can enter if empty
}

// Note: Hill does not override applyEffect, onEnter, or onLeave based on the provided headers.
// If hills had other effects, they would be implemented here.
