// teleportspell.cpp
#include "teleportspell.h"
#include "unit.h" // Include for Unit
#include "field.h" // Include for Field
#include "player.h" // Include for Player (needed to find player's units)
#include <iostream>
#include <vector>
#include <random> // For std::default_random_engine, std::shuffle
#include <chrono> // For std::chrono::steady_clock
#include <algorithm> // For std::shuffle

// Corrected constructor to call base Spell constructor with name and cost
TeleportSpell::TeleportSpell() : Spell("Teleport Spell", 6) // Name, Mana Cost (example cost)
{
    // Constructor body if needed
}

// Destructor is defaulted in header, no dynamic memory owned by TeleportSpell itself.

// Cast method for TeleportSpell - Takes target destination (x, y)
bool TeleportSpell::cast(std::vector<std::vector<Field*>>& board, int targetX, int targetY)
{
    // Check if target coordinates are within board bounds
    size_t boardWidth = board.size();
    size_t boardHeight = board[0].size();
    if (targetX < 0 || static_cast<size_t>(targetX) >= boardWidth || targetY < 0 || static_cast<size_t>(targetY) >= boardHeight)
    {
        std::cout << "TeleportSpell: Target coordinates out of bounds!\n";
        return false;
    }

    Field* targetField = board[targetX][targetY];

    // Check if the destination is empty
    if (targetField->getUnit() != nullptr)
    {
        std::cout << "TeleportSpell: Destination (" << targetX << "," << targetY << ") is occupied!\n";
        return false;
    }

    // Find a random friendly unit (assuming the spell is cast by the human player)
    // A more robust implementation would pass the casting player to the spell.
    // For now, let's assume the spell is cast by the player whose turn it is and is human.
    // This requires finding the human player. This might need access to the game state or player list.
    // Since the spell doesn't have direct access to the Player objects,
    // the calling code (e.g., getPlayerCommands) needs to handle finding the unit to teleport
    // and then potentially call a different version of cast or pass the unit.

    // Given the current structure, let's iterate the board to find a human player unit.
    // This is not ideal as it doesn't guarantee finding the *intended* unit,
    // but it fits the cast(board, x, y) signature by using x,y as the destination.
    Unit* unitToTeleport = nullptr;
    int unitCurrentX = -1, unitCurrentY = -1;
    std::vector<std::pair<int, int>> humanUnitCoords;

    // Find all human player units
    for (size_t y = 0; y < boardHeight; ++y) {
        for (size_t x = 0; x < boardWidth; ++x) {
            Field* currentField = board[x][y];
            Unit* unit = currentField->getUnit();
            // Assuming human player units have getPlayer() == true
            if (unit && unit->getPlayer()) {
                humanUnitCoords.push_back({static_cast<int>(x), static_cast<int>(y)});
            }
        }
    }

    if (humanUnitCoords.empty()) {
        std::cout << "TeleportSpell: No human units found to teleport!\n";
        return false;
    }

    // Pick a random human unit to teleport
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    std::default_random_engine rng(seed);
    std::shuffle(humanUnitCoords.begin(), humanUnitCoords.end(), rng);

    unitCurrentX = humanUnitCoords[0].first;
    unitCurrentY = humanUnitCoords[0].second;
    unitToTeleport = board[unitCurrentX][unitCurrentY]->getUnit();

    if (!unitToTeleport) {
        // Should not happen if humanUnitCoords was not empty, but as a safeguard
        std::cerr << "TeleportSpell Error: Selected unit is null.\n";
        return false;
    }

    // Perform the teleportation
    // Handle onLeave effect for the starting field
    board[unitCurrentX][unitCurrentY]->onLeave(unitToTeleport);

    targetField->setUnit(unitToTeleport); // Move the unit to the destination
    board[unitCurrentX][unitCurrentY]->setUnit(nullptr); // Remove the unit from the source

    // Handle onEnter effect for the target field
    targetField->onEnter(unitToTeleport);

    std::cout << "TeleportSpell: " << unitToTeleport->getName() << " teleported from (" << unitCurrentX << "," << unitCurrentY << ") to (" << targetX << "," << targetY << ").\n";

    return true; // Spell cast successfully
}
