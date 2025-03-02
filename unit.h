#ifndef UNIT_H
#define UNIT_H

#include <string>

// Forward declarations instead of full includes
class Player;
class Field;

class Unit {
private:
    std::string _name;
    int _move_distance;
    int _attack_distance;
    int _health;
    int _damage;
    bool _player;
    int _will;

public:
    Unit(
        std::string name,
        int move_distance,
        int attack_distance,
        int health,
        int damage,
        bool player = 0, // user
        int will = 2 //number of actions
    );
    ~Unit();

    int getMoveDistance() const;
    int getAttackDistance() const;
    void setAttackDistance(int attack_distance);
    int getHealth() const;
    void setHealth(int health);
    int getDamage() const;
    void setDamage(int damage);
    bool getPlayer() const;
    void setPlayer(bool player);
    std::string getName() const;
};

#endif