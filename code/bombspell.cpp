// bombspell.cpp
#include "bombspell.h"
#include "spell.h"
#include "bombedfield.h" // Include for BombedField
#include "field.h"
#include <iostream>
#include <vector>

BombSpell::BombSpell()
    : Spell("Bomb Spell", 4) // Name, Mana Cost
{
}

// Removed the explicit definition of the destructor.
// The "= default" in the header is sufficient.
// BombSpell::~BombSpell()
// {
//     // Destructor for BombSpell.
//     // No dynamic memory allocated within this class that needs explicit deletion here.
// }

bool BombSpell::cast(std::vector<std::vector<Field*>>& board, int x, int y)
{
    // Check if coordinates are within board bounds
    if (x < 0 || static_cast<size_t>(x) >= board.size() || y < 0 || static_cast<size_t>(y) >= board[0].size())
    {
        std::cout << "Invalid target coordinates for Bomb Spell.\n";
        return false; // Invalid coordinates
    }

    Field* targetField = board[x][y];

    // Bomb spell replaces the target field with a BombedField
    // Need to handle the unit on the field before replacing it
    Unit* unitOnField = targetField->getUnit();

    // Create a new BombedField at the target coordinates
    // The BombedField constructor will handle setting the initial unit if it exists
    BombedField* bombedField = new BombedField(x, y, unitOnField);

    // Replace the old field with the new BombedField
    // Ensure to delete the old field object to prevent memory leaks
    delete targetField;
    board[x][y] = bombedField;

    std::cout << "Bomb Spell cast at (" << x << "," << y << "). The field is now unstable!\n";
    return true; // Spell cast successfully
}
