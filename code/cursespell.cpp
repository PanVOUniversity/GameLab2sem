// cursespell.cpp
#include "cursespell.h"
#include "spell.h"
#include "field.h" // Include Field header
#include "unit.h" // Include Unit header
#include <iostream>
#include <vector>

CurseSpell::CurseSpell()
    : Spell("Curse", 3) // Name, Mana Cost
{
}

bool CurseSpell::cast(std::vector<std::vector<Field*>>& board, int x, int y)
{
    // Check if target coordinates are valid
    size_t boardWidth = board.size();
    size_t boardHeight = board[0].size();
    if (x >= 0 && static_cast<size_t>(x) < boardWidth &&
        y >= 0 && static_cast<size_t>(y) < boardHeight)
    {
        Field* targetField = board[x][y];
        Unit* targetUnit = targetField->getUnit();

        // Curse spell reduces a unit's will
        if (targetUnit)
        {
            std::cout << "Casting Curse on unit at (" << x << "," << y << ").\n";
            int currentWill = targetUnit->getWill();
            targetUnit->setWill(std::max(0, currentWill - 1)); // Reduce will by 1, minimum 0
            std::cout << targetUnit->getName() << "'s will reduced to " << targetUnit->getWill() << ".\n";
            return true; // Spell cast successfully
        }
        else
        {
            std::cout << "Curse spell failed: No unit at target location.\n";
        }
    }
    else
    {
        std::cout << "Curse spell failed: Target coordinates out of bounds.\n";
    }
    return false; // Spell cast failed
}
