#include "player.h"
#include "unit.h"

Player::Player(bool my_turn, bool AI, bool defeated, int mana)
    : _my_turn(my_turn), _AI(AI), _defeated(defeated), _mana(mana) {}

bool Player::getMyTurn() const { return _my_turn; }
bool Player::getAI() const { return _AI; }
bool Player::getDefeated() const { return _defeated; }
int Player::getMana() const { return _mana; }
std::vector<Unit*> Player::getMyUnits() const { return _my_units; }

void Player::setMyTurn(bool my_turn) { _my_turn = my_turn; }
void Player::setAI(bool AI) { _AI = AI; }
void Player::setDefeated(bool defeated) { _defeated = defeated; }
void Player::setMana(int mana) { _mana = mana; }
void Player::setMyUnits(const std::vector<Unit*>& my_units) { _my_units = my_units; }