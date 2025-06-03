// manaminefield.cpp
#include "manaminefield.h"
#include "field.h"
#include "player.h"
#include "unit.h" // Include Unit header
#include <iostream>
#include <vector> // Required for std::vector in applyEffect

ManaMineField::ManaMineField(int fieldX, int fieldY, Unit* initialUnit)
    : Field(fieldX, fieldY, "mana_mine"), manaPerTurn(2) // Example mana per turn
{
    // Set the initial unit if there is one
    setUnit(initialUnit);
}

// Removed the explicit definition of the destructor.
// The "= default" in the header is sufficient.
// ManaMineField::~ManaMineField()
// {
//     // The unit on the field is not owned by the field.
// }

// Corrected: Commented out unused 'board' parameter
void ManaMineField::applyEffect(Player* owner, std::vector<std::vector<Field*>>& /*board*/)
{
    // Generate mana for the owner of the mana mine (the player who controls the unit on it, or the player who built it)
    // Assuming the mana is generated for the player whose turn it is, if they control the unit on the mine
    if (owner && unit && unit->getPlayer() == !owner->getAI()) // Assuming human player is !getAI() for human player control
    {
        std::cout << "Mana mine at (" << getX() << "," << getY() << ") generates " << manaPerTurn << " mana for " << owner->getName() << ".\n";
        owner->addMana(manaPerTurn);
    }
    // Note: Mana mines don't have a duration based on the header,
    // so they persist unless replaced by another field.
}

// Corrected: Commented out unused 'unit' parameter
bool ManaMineField::canEnter(Unit* /*unit*/) const
{
    // Units can enter mana mine fields
    return this->unit == nullptr; // Can enter if empty
}

// Added generateMana method as used in main.cpp
void ManaMineField::generateMana(Player* player) {
    if (player) {
         std::cout << "Mana mine at (" << getX() << "," << getY() << ") generates " << manaPerTurn << " mana for " << player->getName() << ".\n";
         player->addMana(manaPerTurn);
    }
}
