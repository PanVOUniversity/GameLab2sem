#include "engineer.h"
#include "fortress.h"
#include "manaminefield.h"
#include "bombedfield.h"

Engineer::Engineer(bool player)
    : Unit("Engineer", 1, 1, 6, 1, player, 3) // Name, Move, Attack, Health, Damage, isPlayer, Will
{
    // Engineer: Move 1, Attack 1, Health 6, Damage 1, Will 3, Symbol 'E'
}

Field* Engineer::createFortress(int x, int y)
{
    // Create fortress with owner set based on engineer's player status
    Fortress* fortress = new Fortress(x, y, 3, 5, nullptr);
    fortress->setOwner(this->getPlayer() ? nullptr : nullptr); // Set owner based on player status
    return fortress;
}

Field* Engineer::createManaMine(int x, int y)
{
    return new ManaMineField(x, y);
}

Field* Engineer::createTrap(int x, int y)
{
    return new BombedField(x, y);
}