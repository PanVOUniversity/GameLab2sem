// cannon.cpp
#include "cannon.h"
#include "unit.h"
#include "field.h"
#include "fortress.h" // Include Fortress header
#include "functions.h" // Include functions for attack
#include <iostream>
#include <vector>
#include <cmath>
#include <utility> // For std::pair
#include <random> // For std::default_random_engine
#include <chrono> // For std::chrono::steady_clock
#include <algorithm> // Required for std::shuffle - Added this line

// Cannon constructor - Cannons are static (moveDistance 0)
// Corrected: Added Direction parameter to match declaration
Cannon::Cannon(const std::string& unitName, int moveD, int attackD, int health, int dmg, bool isPlayer, int will, Direction dir)
    : Unit(unitName, moveD, attackD, health, dmg, isPlayer, will), _direction(dir) // Initialize direction
{
    // Cannon: Move 0, Attack 4, Health 4, Damage 5, Will 1, Symbol 'C'
}

// Removed the explicit definition of the destructor.
// The "= default" in the header is sufficient.
// Cannon::~Cannon()
// {
//     // Destructor for Cannon.
//     // No dynamic memory allocated within this class that needs explicit deletion here.
// }

// Method to set the cannon's direction
void Cannon::setDirection(Direction dir) {
    _direction = dir;
}

// Method to get the cannon's direction
Direction Cannon::getDirection() const {
    return _direction;
}

// Cannon's fire ability
// Assumes targetX and targetY are relative to the cannon's position
// This implementation assumes the 'fire' ability is a direct attack,
// potentially with a different range or cost than a normal attack.
// If it's just a wrapper for the normal attack, this method might be redundant
// or need more specific logic (e.g., firing in a line).
bool Cannon::fire(std::vector<std::vector<Field*>>& board, int targetX, int targetY) {
    // Cannons use 1 Will point to fire
    if (getWill() <= 0) {
        std::cout << getName() << " has no Will to fire.\n";
        return false;
    }

    // Check if the target is within attack distance (using Manhattan distance as per AI logic)
    // This assumes targetX and targetY are absolute board coordinates, not relative
    // Need the cannon's current position to calculate distance
    int cannonX = -1, cannonY = -1;
    bool foundCannon = false;
    size_t boardWidth = board.size();
    size_t boardHeight = board[0].size();

    // Find the cannon's position
    for (size_t x = 0; x < boardWidth; ++x) {
        for (size_t y = 0; y < boardHeight; ++y) {
            if (board[x][y]->getUnit() == this) {
                cannonX = static_cast<int>(x);
                cannonY = static_cast<int>(y);
                foundCannon = true;
                break;
            }
        }
        if (foundCannon) break;
    }

    if (!foundCannon) {
        std::cerr << "Error: Cannon unit not found on the board.\n";
        return false; // Cannon not on board?
    }

    int distance = std::abs(targetX - cannonX) + std::abs(targetY - cannonY);
    if (distance > getAttackDistance()) {
        std::cout << getName() << " target (" << targetX << "," << targetY << ") is out of range.\n";
        return false; // Target out of range
    }

    // Check if the target field exists and has a unit
    if (targetX < 0 || static_cast<size_t>(targetX) >= boardWidth || targetY < 0 || static_cast<size_t>(targetY) >= boardHeight) {
        std::cout << getName() << " target coordinates (" << targetX << "," << targetY << ") are out of bounds.\n";
        return false; // Target out of bounds
    }

    Field* targetField = board[targetX][targetY];
    if (!targetField || !targetField->getUnit()) {
        std::cout << getName() << " target field (" << targetX << "," << targetY << ") is empty.\n";
        return false; // Target field is empty
    }

    Unit* target = targetField->getUnit();
    if (target->getPlayer() == getPlayer()) {
        std::cout << getName() << " cannot attack a friendly unit.\n";
        return false; // Cannot attack friendly unit
    }

    std::cout << getName() << " fires at " << target->getName() << "!\n";

    // Apply damage to the target unit
    target->setHealth(target->getCurrentHealth() - getDamage());

    // Check if the target unit is defeated
    if (target->getCurrentHealth() <= 0) {
        std::cout << target->getName() << " has been defeated!\n";
        // Remove the defeated unit from the board
        targetField->setUnit(nullptr);
        // Note: The actual deletion of the Unit object should be handled by
        // the game's unit management logic (e.g., the Player class or a central
        // unit manager) to avoid memory leaks or double deletions.
        // For simplicity here, we are just removing the pointer from the field.
    }

    // Consume Will point for firing
    setWill(getWill() - 1);
    std::cout << getName() << " Will remaining: " << getWill() << ".\n";

    return true; // Fire successful
}


// Override useAbility if Cannon has a general ability (e.g., fire)
// This method is called by the game loop when a unit's ability is used.
// It should delegate to the specific ability method (like fire).
bool Cannon::useAbility(std::vector<std::vector<Field*>>& board, int targetX, int targetY) {
    // Assuming useAbility is used to trigger the Cannon's fire action
    // The targetX and targetY here are the coordinates of the target field.
    return fire(board, targetX, targetY);
}

// Helper function to find a friendly unit within a certain range
std::pair<int, int> Cannon::_findFriendlyNearby(const std::vector<std::vector<Field*>>& board, int x, int y) const {
    size_t boardWidth = board.size();
    size_t boardHeight = board[0].size();
    int searchRange = 2; // Example search range for nearby friendly units

    for (int dx = -searchRange; dx <= searchRange; ++dx) {
        for (int dy = -searchRange; dy <= searchRange; ++dy) {
            if (dx == 0 && dy == 0) continue;
            int targetX = x + dx;
            int targetY = y + dy;
            if (targetX >= 0 && static_cast<size_t>(targetX) < boardWidth &&
                targetY >= 0 && static_cast<size_t>(targetY) < boardHeight)
            {
                Field* targetField = board[targetX][targetY];
                if (targetField && targetField->getUnit() && targetField->getUnit()->getPlayer() == getPlayer()) {
                    return {targetX, targetY}; // Found a friendly unit
                }
            }
        }
    }
    return {-1, -1}; // No friendly unit found nearby
}

// Helper function to find an enemy unit within attack range
std::pair<int, int> Cannon::_findEnemyInRange(const std::vector<std::vector<Field*>>& board, int x, int y) const {
    size_t boardWidth = board.size();
    size_t boardHeight = board[0].size();
    int attackRange = getAttackDistance();

    for (int dx = -attackRange; dx <= attackRange; ++dx) {
        for (int dy = -attackRange; dy <= attackRange; ++dy) {
            if (dx == 0 && dy == 0) continue;
            int targetX = x + dx;
            int targetY = y + dy;
            if (targetX >= 0 && static_cast<size_t>(targetX) < boardWidth &&
                targetY >= 0 && static_cast<size_t>(targetY) < boardHeight)
            {
                Field* targetField = board[targetX][targetY];
                if (targetField && targetField->getUnit() && targetField->getUnit()->getPlayer() != getPlayer()) {
                    // Use Manhattan distance for attack range check
                    if (std::abs(dx) + std::abs(dy) <= attackRange) {
                        return {targetX, targetY}; // Found an enemy unit in range
                    }
                }
            }
        }
    }
    return {-1, -1}; // No enemy unit found in range
}

// Helper function to find an empty field within movement range
std::pair<int, int> Cannon::_findEmptyFieldInRange(const std::vector<std::vector<Field*>>& board, int x, int y) const {
     size_t boardWidth = board.size();
    size_t boardHeight = board[0].size();
    int moveRange = getMoveDistance(); // For Cannon, this is 0

    // Since Cannon moveDistance is 0, it can only "move" to its current empty field if it somehow became empty
    // This function might not be relevant for a static unit like Cannon unless its moveDistance can change.
    // However, implementing it for completeness based on the base Unit class.
    std::vector<std::pair<int, int>> possibleMoves;
    for (int dx = -moveRange; dx <= moveRange; ++dx) {
        for (int dy = -moveRange; dy <= moveRange; ++dy) {
             if (std::abs(dx) + std::abs(dy) > moveRange || (dx == 0 && dy == 0)) {
                continue;
             }
            int newX = x + dx;
            int newY = y + dy;
            if (newX >= 0 && static_cast<size_t>(newX) < boardWidth &&
                newY >= 0 && static_cast<size_t>(newY) < boardHeight)
            {
                 Field* targetField = board[newX][newY];
                 if(targetField && !targetField->getUnit()) {
                     possibleMoves.push_back({newX, newY});
                 }
            }
        }
    }

    if (!possibleMoves.empty()) {
        unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
        std::default_random_engine rng(seed);
        std::shuffle(possibleMoves.begin(), possibleMoves.end(), rng);
        return possibleMoves[0];
    }
    return {-1, -1}; // No empty field found in range
}

// Helper function to find a friendly fortress within a certain range
std::pair<int, int> Cannon::_findFriendlyFortressNearby(const std::vector<std::vector<Field*>>& board, int x, int y) const {
    size_t boardWidth = board.size();
    size_t boardHeight = board[0].size();
    int searchRange = 3; // Example search range for nearby friendly fortresses

    for (int dx = -searchRange; dx <= searchRange; ++dx) {
        for (int dy = -searchRange; dy <= searchRange; ++dy) {
            if (dx == 0 && dy == 0) continue;
            int targetX = x + dx;
            int targetY = y + dy;
            if (targetX >= 0 && static_cast<size_t>(targetX) < boardWidth &&
                targetY >= 0 && static_cast<size_t>(targetY) < boardHeight)
            {
                Field* targetField = board[targetX][targetY];
                // Check if it's a Fortress and if it's occupied by a friendly unit
                if (targetField && dynamic_cast<Fortress*>(targetField) && targetField->getUnit() && targetField->getUnit()->getPlayer() == getPlayer()) {
                    return {targetX, targetY}; // Found a friendly fortress
                }
            }
        }
    }
    return {-1, -1}; // No friendly fortress found nearby
}
