#include "unit.h"

Unit::Unit(
    const std::string& name,
    int move_distance,
    int attack_distance,
    int health,
    int damage,
    bool player,
    int will
) : _name(name),
    _move_distance(move_distance),
    _attack_distance(attack_distance),
    _health(health),
    _damage(damage),
    _player(player),
    _will(will) {}

Unit::~Unit() = default;

// Getters
int Unit::getMoveDistance() const { return _move_distance; }
int Unit::getAttackDistance() const { return _attack_distance; }
int Unit::getHealth() const { return _health; }
int Unit::getDamage() const { return _damage; }
bool Unit::getPlayer() const { return _player; }
std::string Unit::getName() const { return _name; }

// Setters
void Unit::setAttackDistance(int attack_distance) { _attack_distance = attack_distance; }
void Unit::setHealth(int health) { _health = health; }
void Unit::setDamage(int damage) { _damage = damage; }
void Unit::setPlayer(bool player) { _player = player; }