#include "cannon.h"

Cannon::Cannon(
    const std::string& name,
    int move_distance,
    int attack_distance,
    int health,
    int damage,
    bool player,
    int will,
    Direction direction
) : Unit(name, move_distance, attack_distance, health, damage, player, will),
    _direction(direction) {}

std::pair<int, int> Cannon::_findFriendlyNearby(const std::vector<std::vector<Field*>>& board, int x, int y) const
{
    for (int dx = -1; dx <= 1; ++dx)
    {
        for (int dy = -1; dy <= 1; ++dy)
        {
            if (dx == 0 && dy == 0) continue;

            int nx = x + dx;
            int ny = y + dy;

            if (nx >= 0 && nx < static_cast<int>(board.size()) &&
                    ny >= 0 && ny < static_cast<int>(board[0].size()))
            {
                Unit* unit = board[nx][ny]->getUnit();
                if (unit && unit->getPlayer() == this->getPlayer() &&
                        unit->getWill() > 0 && dynamic_cast<const Cannon*>(unit) == nullptr)
                {
                    return {nx, ny};
                }
            }
        }
    }
    return {-1, -1};
}

std::pair<int, int> Cannon::_findFriendlyBehind(const std::vector<std::vector<Field*>>& board, int x, int y) const
{
    int bx = x, by = y;
    switch(_direction)
    {
    case Direction::FRONT:
        bx--;
        break;
    case Direction::BACK:
        bx++;
        break;
    case Direction::LEFT:
        by++;
        break;
    case Direction::RIGHT:
        by--;
        break;
    case Direction::FRONT_LEFT:
        bx--;
        by++;
        break;
    case Direction::FRONT_RIGHT:
        bx--;
        by--;
        break;
    case Direction::BACK_LEFT:
        bx++;
        by++;
        break;
    case Direction::BACK_RIGHT:
        bx++;
        by--;
        break;
    }

    if (bx >= 0 && bx < static_cast<int>(board.size()) &&
            by >= 0 && by < static_cast<int>(board[0].size()))
    {
        Unit* unit = board[bx][by]->getUnit();
        if (unit && unit->getPlayer() == this->getPlayer() &&
                unit->getWill() > 0 && dynamic_cast<const Cannon*>(unit) == nullptr)
        {
            return {bx, by};
        }
    }
    return {-1, -1};
}

bool Cannon::_isPathClear(const std::vector<std::vector<Field*>>& board, int x, int y, int distance) const
{
    int cx = x, cy = y;
    for (int i = 0; i < distance; ++i)
    {
        switch(_direction)
        {
        case Direction::FRONT:
            cx--;
            break;
        case Direction::BACK:
            cx++;
            break;
        case Direction::LEFT:
            cy--;
            break;
        case Direction::RIGHT:
            cy++;
            break;
        case Direction::FRONT_LEFT:
            cx--;
            cy--;
            break;
        case Direction::FRONT_RIGHT:
            cx--;
            cy++;
            break;
        case Direction::BACK_LEFT:
            cx++;
            cy--;
            break;
        case Direction::BACK_RIGHT:
            cx++;
            cy++;
            break;
        }

        if (cx < 0 || cx >= static_cast<int>(board.size()) ||
                cy < 0 || cy >= static_cast<int>(board[0].size()))
        {
            return false;
        }

        if (dynamic_cast<Fortress*>(board[cx][cy]))
        {
            return false;
        }
    }
    return true;
}

bool Cannon::canFire(const std::vector<std::vector<Field*>>& board, int x, int y) const
{
    auto [fx, fy] = _findFriendlyNearby(board, x, y);
    return fx != -1 && getWill() > 0 && _isPathClear(board, x, y, getAttackDistance());
}

bool Cannon::fire(std::vector<std::vector<Field*>>& board, int x, int y)
{
    auto [fx, fy] = _findFriendlyNearby(board, x, y);
    if (fx == -1)
    {
        std::cout << getName() << " needs a friendly unit with Will nearby to fire!\n";
        return false;
    }

    if (getWill() <= 0)
    {
        std::cout << getName() << " doesn't have enough Will to fire!\n";
        return false;
    }

    if (!_isPathClear(board, x, y, getAttackDistance()))
    {
        std::cout << getName() << " can't fire - path is blocked!\n";
        return false;
    }

    Unit* helper = board[fx][fy]->getUnit();
    std::cout << getName() << " is being loaded by " << helper->getName() << " and is firing ";

    int tx = x, ty = y;
    for (int i = 0; i < getAttackDistance(); ++i)
    {
        switch(_direction)
        {
        case Direction::FRONT:
            tx--;
            break;
        case Direction::BACK:
            tx++;
            break;
        case Direction::LEFT:
            ty--;
            break;
        case Direction::RIGHT:
            ty++;
            break;
        case Direction::FRONT_LEFT:
            tx--;
            ty--;
            break;
        case Direction::FRONT_RIGHT:
            tx--;
            ty++;
            break;
        case Direction::BACK_LEFT:
            tx++;
            ty--;
            break;
        case Direction::BACK_RIGHT:
            tx++;
            ty++;
            break;
        }
    }

    setWill(getWill() - 1);
    helper->setWill(helper->getWill() - 1);

    if (tx >= 0 && tx < static_cast<int>(board.size()) &&
            ty >= 0 && ty < static_cast<int>(board[0].size()))
    {
        Unit* target = board[tx][ty]->getUnit();
        if (target && target->getPlayer() != this->getPlayer())
        {
            std::cout << "at " << target->getName() << "!\n";
            target->setHealth(target->getHealth() - getDamage());
            if (target->getHealth() <= 0)
            {
                std::cout << target->getName() << " was destroyed!\n";
                delete target;
                board[tx][ty]->setUnit(nullptr);
            }
        }
        else
        {
            std::cout << "but hit nothing!\n";
        }
    }
    else
    {
        std::cout << "but shot out of bounds!\n";
    }

    return true;
}

bool Cannon::changeDirection(std::vector<std::vector<Field*>>& board, int x, int y, Direction newDirection)
{
    auto [bx, by] = _findFriendlyBehind(board, x, y);
    if (bx == -1)
    {
        std::cout << "No willing friendly unit behind " << getName() << " to help change direction!\n";
        return false;
    }

    if (getWill() <= 0)
    {
        std::cout << getName() << " doesn't have enough Will to change direction!\n";
        return false;
    }

    Unit* helper = board[bx][by]->getUnit();
    _direction = newDirection;
    setWill(getWill() - 1);
    helper->setWill(helper->getWill() - 1);
    std::cout << helper->getName() << " helped " << getName() << " change direction to face new target!\n";
    return true;
}

Direction Cannon::getDirection() const
{
    return _direction;
}