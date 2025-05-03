// fortress.cpp
#include "fortress.h"
#include "field.h"
#include "unit.h"
#include "player.h"
#include "archer.h" // Include Archer header for dynamic_cast
#include <iostream>

Fortress::Fortress(int fieldX, int fieldY, int initialStrength, int maxStrength, Player* owner)
    : Field(fieldX, fieldY, "fortress"), strength(initialStrength), maxStrength(maxStrength), owner(owner)
{
    // Ensure strength doesn't exceed max strength on creation
    if (strength > maxStrength) {
        strength = maxStrength;
    }
}

// Destructor is defaulted in header, no dynamic memory owned by Fortress itself.

int Fortress::getStrength() const
{
    return strength;
}

// Setter for strength - Returns true if destroyed
// Corrected: Changed return type to bool to match declaration
bool Fortress::setStrength(int s)
{
    strength = s;
    if (strength < 0) strength = 0; // Strength cannot go below 0
    return strength <= 0; // Return true if strength is 0 or less
}

int Fortress::getMaxStrength() const
{
    return maxStrength;
}

// Corrected: Commented out unused 'board' parameter
void Fortress::applyEffect(Player* owner, std::vector<std::vector<Field*>>& /*board*/)
{
    // Fortresses could potentially heal units on them each turn
    if (unit)
    {
        // Assuming the unit on the fortress belongs to the owner whose turn it is
        // This logic might need refinement based on actual game rules for fortress ownership
        // For now, let's assume it heals the unit if it's a player unit (human or AI)
        // Check if the unit belongs to the current player before healing
        if (owner && ((owner->getAI() && !unit->getPlayer()) || (!owner->getAI() && unit->getPlayer()))) {
             int healAmount = 2; // Example heal amount per turn
             std::cout << "Fortress at (" << getX() << "," << getY() << ") heals " << unit->getName() << " for " << healAmount << " health.\n";
             unit->restoreHealth(healAmount);
        }
    }
}

int Fortress::getDefenseBonus() const
{
    // Fortresses provide a significant defense bonus
    return 10; // Example defense bonus
}

// Corrected: Commented out unused 'unit' parameter
bool Fortress::canEnter(Unit* /*unit*/) const
{
    // Units can enter a fortress, but typically only one unit can occupy a fortress field.
    // Also, check if the unit belongs to the player who controls the fortress (if applicable).
    // For simplicity, let's assume any unit can enter if the fortress is empty.
     return this->unit == nullptr; // Can enter if empty
}

void Fortress::onEnter(Unit* unit)
{
    // Handle actions when a unit enters the fortress (e.g., update unit stats)
    std::cout << unit->getName() << " entered the Fortress at (" << getX() << "," << getY() << ").\n";
    // Example: If the unit is an Archer, update its attack distance
    Archer* archer = dynamic_cast<Archer*>(unit);
    if (archer) {
        archer->updateAttackDistance(true); // Indicate it's in a fortress
    }
}

void Fortress::onLeave(Unit* unit)
{
    // Handle actions when a unit leaves the fortress (e.g., revert unit stats)
    std::cout << unit->getName() << " left the Fortress at (" << getX() << "," << getY() << ").\n";
    // Example: If the unit is an Archer, revert its attack distance
    Archer* archer = dynamic_cast<Archer*>(unit);
    if (archer) {
        archer->updateAttackDistance(false); // Indicate it left the fortress
    }
}
