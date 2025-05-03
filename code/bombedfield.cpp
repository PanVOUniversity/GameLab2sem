// bombedfield.cpp
#include "bombedfield.h"
#include "field.h"
#include "unit.h"
#include "player.h"
#include "functions.h" // Include functions for applyDamage
#include <iostream>
#include <vector>
#include <algorithm> // For std::max

BombedField::BombedField(int fieldX, int fieldY, Unit* initialUnit, int initialTimer, int damage)
    : Field(fieldX, fieldY, "bombed"), timer(initialTimer), explosionDamage(damage)
{
    // Set the initial unit if there is one
    setUnit(initialUnit);
}

// Removed the explicit definition of the destructor.
// The "= default" in the header is sufficient.
// BombedField::~BombedField() = default; // This line is not needed here

void BombedField::applyEffect(Player* /*owner*/, std::vector<std::vector<Field*>>& board)
{
    // Decrease the timer
    timer--;
    std::cout << "Bombed field at (" << getX() << "," << getY() << ") timer: " << timer << ".\n";

    // If timer reaches 0 or a unit is on the field, explode
    if (shouldExplode())
    {
        explode(board);
    }
}

bool BombedField::canEnter(Unit* /*unit*/) const
{
    // Units can enter bombed fields
    return this->unit == nullptr; // Can enter if empty
}

void BombedField::onEnter(Unit* unit)
{
    // Handle actions when a unit enters the bombed field (might trigger explosion)
    std::cout << unit->getName() << " entered the Bombed Field at (" << getX() << "," << getY() << ").\n";
    // If a unit enters, the bomb should explode immediately
    if (unit) {
        // Set timer to 0 to trigger explosion in applyEffect
        timer = 0;
    }
}

bool BombedField::shouldExplode() const
{
    // Explode if timer is 0 or less, or if a unit is on the field
    return timer <= 0 || unit != nullptr;
}

void BombedField::explode(std::vector<std::vector<Field*>>& board)
{
    std::cout << "Bombed field at (" << getX() << "," << getY() << ") explodes!\n";

    // Apply explosion damage to adjacent units and the unit on the field
    size_t boardWidth = board.size();
    size_t boardHeight = board[0].size();

    // Check the field itself
    if (unit) {
        std::cout << "Unit " << unit->getName() << " on the field takes " << explosionDamage << " damage from explosion.\n";
        // applyDamage needs board, x, y, damage, attackingUnit
        applyDamage(board, getX(), getY(), explosionDamage, nullptr); // Use applyDamage
    }

    // Check adjacent fields (including diagonals)
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue; // Skip the center field

            int targetX = getX() + dx;
            int targetY = getY() + dy;

            if (targetX >= 0 && static_cast<size_t>(targetX) < boardWidth &&
                targetY >= 0 && static_cast<size_t>(targetY) < boardHeight)
            {
                Field* adjacentField = board[targetX][targetY];
                if (adjacentField && adjacentField->getUnit()) {
                    std::cout << "Adjacent unit " << adjacentField->getUnit()->getName() << " at (" << targetX << "," << targetY << ") takes " << explosionDamage << " damage from explosion.\n";
                    // applyDamage needs board, x, y, damage, attackingUnit
                    applyDamage(board, targetX, targetY, explosionDamage, nullptr); // Use applyDamage
                }
            }
        }
    }

    // After explosion, revert to a plain field
    Unit* unitAfterExplosion = getUnit(); // Get unit again in case it survived damage
    // Create a new plain field at the same coordinates
    Field* plainField = new Field(getX(), getY(), "plain");
    plainField->setUnit(unitAfterExplosion); // Place the unit (if it survived) on the new plain field
    delete this; // Delete the bombed field object
    board[getX()][getY()] = plainField; // Replace the pointer in the board
}
