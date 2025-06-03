// infantry.cpp
#include "infantry.h"
#include "unit.h"
#include <iostream> // For debugging output

Infantry::Infantry(bool player)
    : Unit("Infantry", 2, 1, 10, 3, player, 2) // Name, Move, Attack, Health, Damage, isPlayer, Will
{
    // Infantry: Move 2, Attack 1, Health 10, Damage 3, Will 2, Symbol 'I'
}

void Infantry::counterAttack(Unit* attacker)
{
    if (attacker) {
        std::cout << getName() << " counter-attacks " << attacker->getName() << "!\n";
        // Infantry deals half their damage in a counter-attack (rounded down)
        int counterDamage = getDamage() / 2;
        attacker->takeDamage(counterDamage, this); // 'this' is the counter-attacking Infantry
    }
}

// Note: Infantry does not override useAbility based on the provided headers.
// If there were an Infantry-specific ability, it would be implemented here.
