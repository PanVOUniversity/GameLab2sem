// morogspell.cpp
#include "morogspell.h"
#include "spell.h"
#include "field.h" // Include Field header
#include "unit.h" // Include Unit header
#include "functions.h" // Include functions for applyDamage
#include <iostream>
#include <vector>

MorogSpell::MorogSpell()
    : Spell("Morog", 5) // Name, Mana Cost
{
}

bool MorogSpell::cast(std::vector<std::vector<Field*>>& board, int x, int y)
{
    // Check if target coordinates are valid
    size_t boardWidth = board.size();
    size_t boardHeight = board[0].size();
    if (x >= 0 && static_cast<size_t>(x) < boardWidth &&
        y >= 0 && static_cast<size_t>(y) < boardHeight)
    {
        Field* targetField = board[x][y];
        Unit* targetUnit = targetField->getUnit();

        // Morog spell deals significant damage to a single unit
        if (targetUnit)
        {
            std::cout << "Casting Morog spell on unit at (" << x << "," << y << ").\n";
            int damageToDeal = 15; // Example significant damage for Morog
            applyDamage(board, x, y, damageToDeal, nullptr); // Use applyDamage function, no attacking unit for spell
            return true; // Spell cast successfully
        }
        else
        {
            std::cout << "Morog spell failed: No unit at target location.\n";
        }
    }
    else
    {
        std::cout << "Morog spell failed: Target coordinates out of bounds.\n";
    }
    return false; // Spell cast failed
}
