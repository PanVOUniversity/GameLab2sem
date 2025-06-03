// shieldedfield.cpp
#include "shieldedfield.h"
#include "field.h"
#include "unit.h"
#include "player.h" // Include Player header for applyEffect signature
#include <iostream>
#include <vector> // Required for std::vector in applyEffect

ShieldedField::ShieldedField(int fieldX, int fieldY, Unit* initialUnit, int initialDuration)
    : Field(fieldX, fieldY, "shielded"), duration(initialDuration)
{
    // Set the initial unit if there is one
    setUnit(initialUnit);
}

// Removed the explicit definition of the destructor.
// The "= default" in the header is sufficient.
// ShieldedField::~ShieldedField()
// {
//     // The unit on the field is not owned by the field.
// }

// Corrected: Commented out unused 'owner' parameter
void ShieldedField::applyEffect(Player* /*owner*/, std::vector<std::vector<Field*>>& board)
{
    // Decrease the duration
    duration--;
    std::cout << "Shielded field at (" << getX() << "," << getY() << ") duration: " << duration << ".\n";

    // If duration reaches 0, revert to a plain field
    if (duration <= 0)
    {
        std::cout << "Shielded field at (" << getX() << "," << getY() << ") fades away.\n";
        Unit* unitOnField = getUnit(); // Get unit before deleting the field
        // Create a new plain field at the same coordinates
        Field* plainField = new Field(getX(), getY(), "plain");
        plainField->setUnit(unitOnField); // Place the unit on the new plain field
        delete this; // Delete the shielded field object
        board[getX()][getY()] = plainField; // Replace the pointer in the board
    }
    // Note: ShieldedField itself doesn't directly interact with the board in applyEffect
    // beyond potentially deleting itself and replacing the field pointer.
    // The board parameter is kept to match the base class signature.
}

int ShieldedField::getDefenseBonus() const
{
    // Shielded fields provide a significant defense bonus
    return 5; // Example defense bonus
}

// Corrected: Commented out unused 'unit' parameter
bool ShieldedField::canEnter(Unit* /*unit*/) const
{
    // Units can enter shielded fields
    return this->unit == nullptr; // Can enter if empty
}
