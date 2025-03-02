#include "unit.h"

Unit::Unit(
    std::string name,
    int move_distance,
    int attack_distance,
    int health,
    int damage,
    bool player,
    int will
) :
    _name(name),
    _move_distance(move_distance),
    _attack_distance(attack_distance),
    _health(health),
    _damage(damage),
    _player(player),
    _will(will)
{}

Unit::~Unit() = default;

int Unit::getMoveDistance() const {
    return _move_distance;
}

int Unit::getAttackDistance() const {
    return _attack_distance;
}

void Unit::setAttackDistance(int attack_distance) {
    _attack_distance = attack_distance;
}

int Unit::getHealth() const {
    return _health;
}

void Unit::setHealth(int health) {
    _health = health;
}

int Unit::getDamage() const {
    return _damage;
}

void Unit::setDamage(int damage) {
    _damage = damage;
}

bool Unit::getPlayer() const {
    return _player;
}

void Unit::setPlayer(bool player) {
    _player = player;
}

std::string Unit::getName() const {
    return _name;
}


