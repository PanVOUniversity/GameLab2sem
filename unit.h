#ifndef UNIT_H
#define UNIT_H

#include <string>

class Unit
{
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
        const std::string& name,
        int move_distance,
        int attack_distance,
        int health,
        int damage,
        bool player = false,
        int will = 2
    );
    virtual ~Unit();

    // Getters and setters
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
    int getWill() const;
    void setWill(int will);
};

#endif