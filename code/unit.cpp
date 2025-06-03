// unit.cpp
#include "unit.h"
#include "field.h" // Include Field header
#include "functions.h" // Include functions for applyDamage
#include <iostream>
#include <algorithm> // For std::max

Unit::Unit(const std::string& unitName, int moveD, int attackD, int health, int dmg, bool isPlayer, int will)
    : name(unitName), moveDistance(moveD), attackDistance(attackD),
      currentHealth(health), maxHealth(health), damage(dmg), isPlayerUnit(isPlayer),
      currentWill(will), maxWill(will)
{
}

Unit::~Unit()
{
    // Destructor for Unit.
    // No dynamic memory allocated within the base Unit class that needs explicit deletion here.
    // Derived classes might need to implement their own destructors if they allocate memory.
}

std::string Unit::getName() const
{
    return name;
}

int Unit::getMoveDistance() const
{
    return moveDistance;
}

int Unit::getAttackDistance() const
{
    return attackDistance;
}

int Unit::getCurrentHealth() const
{
    return currentHealth;
}

int Unit::getMaxHealth() const
{
    return maxHealth;
}

int Unit::getDamage() const
{
    return damage;
}

bool Unit::getPlayer() const
{
    return isPlayerUnit;
}

int Unit::getWill() const
{
    return currentWill;
}

int Unit::getMaxWill() const
{
    return maxWill;
}


void Unit::setCurrentHealth(int health)
{
    currentHealth = health;
}

void Unit::setWill(int will)
{
    currentWill = will;
}

void Unit::takeDamage(int damage, Unit* attacker)
{
    (void)attacker; // Suppress unused parameter warning
    std::cout << getName() << " takes " << damage << " damage.\n";
    currentHealth -= damage;
    if (currentHealth < 0) currentHealth = 0; // Health cannot go below 0
    std::cout << getName() << " health: " << currentHealth << "/" << maxHealth << ".\n";

    // Note: Unit removal logic is handled in the applyDamage function, not here.
}

void Unit::restoreHealth(int amount)
{
    currentHealth += amount;
    if (currentHealth > maxHealth) currentHealth = maxHealth; // Health cannot exceed max
    std::cout << getName() << " health restored by " << amount << ". Current health: " << currentHealth << "/" << maxHealth << ".\n";
}

void Unit::restoreWill(int amount)
{
    currentWill += amount;
    if (currentWill > maxWill) currentWill = maxWill; // Will cannot exceed max
    std::cout << getName() << " will restored by " << amount << ". Current will: " << currentWill << "/" << maxWill << ".\n";
}

void Unit::setHealth(int health)
{
    currentHealth = std::max(0, std::min(health, maxHealth));
}

// Default implementation for useAbility (does nothing)
bool Unit::useAbility(std::vector<std::vector<Field*>>& board, int targetX, int targetY)
{
    (void)board; (void)targetX; (void)targetY; // Suppress unused parameter warnings
    // Base units have no special abilities
    std::cout << getName() << " has no special ability.\n";
    return false; // Ability not used
}
