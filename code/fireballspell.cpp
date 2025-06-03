// fireballspell.cpp
#include "fireballspell.h"
#include "spell.h"
#include "field.h" // Include Field header
#include "unit.h" // Include Unit header
#include "functions.h" // Include functions for applyDamage
#include <iostream>
#include <vector>
#include <cmath> // For std::abs

FireballSpell::FireballSpell()
    : Spell("Fireball", 2) // Name, Mana Cost
{
}

bool FireballSpell::cast(std::vector<std::vector<Field*>>& board, int x, int y)
{
    // Check if target coordinates are valid
    size_t boardWidth = board.size();
    size_t boardHeight = board[0].size();
    if (x >= 0 && static_cast<size_t>(x) < boardWidth &&
        y >= 0 && static_cast<size_t>(y) < boardHeight)
    {
        Field* targetField = board[x][y];
        Unit* targetUnit = targetField->getUnit();

        // Fireball deals damage to a unit
        if (targetUnit)
        {
            std::cout << "Casting Fireball on unit at (" << x << "," << y << ").\n";
            int damageToDeal = 5; // Example damage for Fireball
            applyDamage(board, x, y, damageToDeal, nullptr); // Use applyDamage function, no attacking unit for spell
            return true; // Spell cast successfully
        }
        else
        {
            std::cout << "Fireball spell failed: No unit at target location.\n";
        }
    }
    else
    {
        std::cout << "Fireball spell failed: Target coordinates out of bounds.\n";
    }
    return false; // Spell cast failed
}
