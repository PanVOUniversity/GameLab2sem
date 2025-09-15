// burnedfield.cpp
#include "burnedfield.h"
#include "field.h"
#include "unit.h"
#include "player.h"
#include "functions.h" // Include functions for applyDamage
#include <iostream>
#include <vector>

BurnedField::BurnedField(int fieldX, int fieldY, Unit* initialUnit, int initialDuration, int damage)
    : Field(fieldX, fieldY, "burned"), duration(initialDuration), damagePerTurn(damage)
{
    // Set the initial unit if there is one
    setUnit(initialUnit);
}

// Removed the explicit definition of the destructor.
// The "= default" in the header is sufficient.
// BurnedField::~BurnedField()
// {
//     // Destructor for BurnedField.
//     // No dynamic memory allocated within this class that needs explicit deletion here.
// }

void BurnedField::applyEffect(Player* /*owner*/, std::vector<std::vector<Field*>>& board)
{
    // Apply damage to the unit on the field if there is one
    if (unit)
    {
        std::cout << "Burned field at (" << getX() << "," << getY() << ") deals " << damagePerTurn << " damage to " << unit->getName() << ".\n";
        applyDamage(board, getX(), getY(), damagePerTurn, nullptr); // Use applyDamage, no attacking unit for field effect
    }

    // Decrease the duration
    duration--;
    std::cout << "Burned field at (" << getX() << "," << getY() << ") duration: " << duration << ".\n";

    // If duration reaches 0, revert to a plain field
    if (duration <= 0)
    {
        std::cout << "Burned field at (" << getX() << "," << getY() << ") fades away.\n";
        Unit* unitOnField = getUnit(); // Get unit before deleting the field
        // Create a new plain field at the same coordinates
        Field* plainField = new Field(getX(), getY(), "plain");
        plainField->setUnit(unitOnField); // Place the unit on the new plain field
        delete this; // Delete the burned field object
        board[getX()][getY()] = plainField; // Replace the pointer in the board
    }
}

int BurnedField::getDefenseBonus() const
{
    // Burned fields might offer no defense bonus or even a penalty
    return 0; // Or return a negative value for penalty
}

bool BurnedField::canEnter(Unit* /*unit*/) const
{
    // Units can enter burned fields, but will take damage
    return this->unit == nullptr; // Can enter if empty
}
