// spell.cpp
#include "spell.h"
#include "field.h" // Include Field header
#include <iostream>

Spell::Spell(const std::string& spellName, int cost)
    : name(spellName), manaCost(cost)
{
}

// Removed the explicit definition of the destructor.
// The "= default" in the header is sufficient.
// Spell::~Spell()
// {
//     // Destructor for Spell.
//     // No dynamic memory allocated within the base Spell class that needs explicit deletion here.
//     // Derived classes might need to implement their own destructors if they allocate memory.
// }

std::string Spell::getName() const
{
    return name;
}

int Spell::getManaCost() const
{
    return manaCost;
}

// Note: The pure virtual cast method is not implemented in the base class.
// It must be implemented in all derived spell classes.
