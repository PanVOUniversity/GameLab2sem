// archer.cpp
#include "archer.h"
#include "unit.h"
#include <iostream> // For debugging output

Archer::Archer(bool player)
    : Unit("Archer", 2, 2, 7, 2, player, 2) // Name, Move, Attack, Health, Damage, isPlayer, Will
{
    // Archer: Move 2, Attack 2 (default), Health 7, Damage 2, Will 2, Symbol 'A'
}

void Archer::updateAttackDistance(bool inFortress)
{
    if (inFortress) {
        attackDistance = 3; // Increased range in a fortress
        std::cout << getName() << " gains increased attack range in fortress.\n";
    } else {
        attackDistance = 2; // Default range
    }
}

// Note: Archer does not override useAbility based on the provided headers.
// If there were an Archer-specific ability, it would be implemented here.
