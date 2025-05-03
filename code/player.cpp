// player.cpp
#include "player.h"
#include <iostream>

// Corrected constructor definition to match the declaration in player.h
Player::Player(std::string n, bool myTurn, bool ai, bool defeated, int initialMana)
    : name(n), mana(initialMana), isAI(ai), myTurn(myTurn), defeated(defeated), skippedTurns(0)
{
    // Constructor body if needed
}

// Removed the old constructor definition that didn't match the header
// Player::Player(std::string n, bool ai)
//     : name(n), mana(0), isAI(ai), myTurn(false)
// {
// }

std::string Player::getName() const
{
    return name;
}

int Player::getMana() const
{
    return mana;
}

void Player::setMana(int m)
{
    mana = m;
}

bool Player::getAI() const
{
    return isAI;
}

bool Player::getMyTurn() const
{
    return myTurn;
}

void Player::setMyTurn(bool turn)
{
    myTurn = turn;
}

// Getter for defeated
bool Player::getDefeated() const
{
    return defeated;
}

// Setter for defeated
void Player::setDefeated(bool d)
{
    defeated = d;
}

// Getter for skippedTurns
int Player::getSkippedTurns() const
{
    return skippedTurns;
}

// Setter for skippedTurns
void Player::setSkippedTurns(int turns)
{
    skippedTurns = turns;
}


void Player::addMana(int amount)
{
    mana += amount;
    if (mana < 0) mana = 0; // Prevent negative mana
}

bool Player::subtractMana(int amount)
{
    if (mana >= amount)
    {
        mana -= amount;
        return true;
    }
    return false; // Not enough mana
}

// Removed: Getter and setter for myUnits as unit ownership is board-managed
// std::vector<Unit*>& getMyUnits() {
//     // This implementation is problematic if units are not stored directly by the player
//     // Consider removing this getter or rethinking unit ownership.
//     // Returning a reference to an empty vector is a temporary workaround if needed,
//     // but it's better to fetch units from the board based on player ownership.
//     static std::vector<Unit*> emptyUnits;
//     return emptyUnits;
// }

// void Player::setMyUnits(const std::vector<Unit*>& units) {
//     // This setter is not needed if unit ownership is managed on the board.
//     // If needed, it would involve copying or managing unit pointers,
//     // which requires careful memory management.
// }
