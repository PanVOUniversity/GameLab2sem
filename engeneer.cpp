#include "engeneer.h"
#include "fortress.h"
#include "manaminefield.h"
#include "bombedfield.h"

Engineer::Engineer(bool player)
    : Unit("Engineer", 1, 1, 6, 1, player, 3) {}

Field* Engineer::createFortress(int x, int y)
{
    return new Fortress(x, y, 3, 5); // height=3, strength=5
}

Field* Engineer::createManaMine(int x, int y)
{
    return new ManaMineField(x, y);
}

Field* Engineer::createTrap(int x, int y)
{
    return new BombedField(x, y);
}