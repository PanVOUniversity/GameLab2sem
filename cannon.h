#ifndef CANNON_H
#define CANNON_H

#include "unit.h"
#include <vector>
#include "field.h"
#include "fortress.h"
#include <iostream>
#include <cmath>
#include <utility>

enum class Direction { FRONT, BACK, LEFT, RIGHT, FRONT_LEFT, FRONT_RIGHT, BACK_LEFT, BACK_RIGHT };

class Cannon : public Unit
{
private:
    Direction _direction;
    std::pair<int, int> _findFriendlyNearby(const std::vector<std::vector<Field*>>& board, int x, int y) const;
    std::pair<int, int> _findFriendlyBehind(const std::vector<std::vector<Field*>>& board, int x, int y) const;
    bool _isPathClear(const std::vector<std::vector<Field*>>& board, int x, int y, int distance) const;

public:
    Cannon(
        const std::string& name,
        int move_distance,
        int attack_distance,
        int health,
        int damage,
        bool player = false,
        int will = 0,
        Direction direction = Direction::FRONT
    );

    bool canFire(const std::vector<std::vector<Field*>>& board, int x, int y) const;
    bool fire(std::vector<std::vector<Field*>>& board, int x, int y);
    bool changeDirection(std::vector<std::vector<Field*>>& board, int x, int y, Direction newDirection);
    Direction getDirection() const;
};

#endif