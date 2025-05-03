#include "functions.h"

void checkBombExplosions(std::vector<std::vector<Field*>>& board)
{
    for (size_t x = 0; x < board.size(); ++x)
    {
        for (size_t y = 0; y < board[x].size(); ++y)
        {
            BombedField* bomb = dynamic_cast<BombedField*>(board[x][y]);
            if (bomb)
            {
                // Check if bomb should explode (has unit or timer expired)
                if (bomb->getUnit() != nullptr || bomb->shouldExplode())
                {
                    // Damage unit if present
                    if (bomb->getUnit())
                    {
                        bomb->getUnit()->setHealth(bomb->getUnit()->getHealth() - 4); // Fixed damage
                    }

                    // Replace with regular field
                    delete board[x][y];
                    board[x][y] = new Field(x, y, nullptr);

                    std::cout << "Bomb exploded at (" << x << "," << y << ")!\n";
                }
                else
                {
                    // Increment timer if not exploding this turn
                    bomb->endTurnEffect();
                }
            }
        }
    }
}

void updateFortressStrength(
    std::vector<std::vector<Field*>>& board,
    int x,
    int y,
    int newStrength
)
// Check if coordinates are valid
{
    if (x < 0 || y < 0 ||
            static_cast<size_t>(x) >= board.size() ||
            static_cast<size_t>(y) >= board[0].size())
    {
        return;
    }

    // Attempt to cast to Fortress
    Fortress* fortress = dynamic_cast<Fortress*>(board[x][y]);

    if (fortress)   // Check if cast succeeded
    {
        if (fortress->setStrength(newStrength))   // Strength ≤ 0?
        {
            delete board[x][y]; // Delete the fortress
            board[x][y] = new Field(x, y); // Replace with a plain field
        }
    }
}


void attack(
    std::vector<std::vector<Field*>>& board,
    int attackerX,
    int attackerY,
    int victimX,
    int victimY
)
{
    // Check if coordinates are valid
    if (attackerX < 0 || attackerX >= static_cast<int>(board.size()) ||
            attackerY < 0 || attackerY >= static_cast<int>(board[0].size()) ||
            victimX < 0 || victimX >= static_cast<int>(board.size()) ||
            victimY < 0 || victimY >= static_cast<int>(board[0].size()))
    {
        return; // Invalid coordinates
    }

    Field* attackerField = board[attackerX][attackerY];
    Field* victimField = board[victimX][victimY];
    Unit* attacker = attackerField->getUnit();
    Unit* victim = victimField->getUnit();

    // Check if both units exist
    if (!attacker || !victim)
    {
        return;
    }

    // Check if attacker has enough Will to attack
    if (attacker->getWill() <= 0)
    {
        return; // Cannot attack if Will is <= 0
    }

    // Calculate distance
    int distance = sqrt(pow((attackerX - victimX), 2) + pow((attackerY - victimY), 2));

    // Check attack distance
    if (distance > attacker->getAttackDistance())
    {
        return;
    }

    // Apply damage
    int damage = attacker->getDamage();
    victim->setHealth(victim->getHealth() - damage);

    // Decrease attacker's Will by 1
    attacker->setWill(attacker->getWill() - 1);  // Subtract 1 Will point

    // Check if victim is defeated
    if (victim->getHealth() <= 0)
    {
        victimField->setUnit(nullptr);
        delete victim;
    }
}

void move(
    std::vector<std::vector<Field*>>& board,
    int fromX,
    int fromY,
    int toX,
    int toY
)
{
    // Check if coordinates are valid
    if (fromX < 0 || fromX >= static_cast<int>(board.size()) ||
            fromY < 0 || fromY >= static_cast<int>(board[0].size()) ||
            toX < 0 || toX >= static_cast<int>(board.size()) ||
            toY < 0 || toY >= static_cast<int>(board[0].size()))
    {
        std::cout << "Invalid coordinates for movement!\n";
        return;
    }

    Field* sourceField = board[fromX][fromY];
    Field* targetField = board[toX][toY];
    Unit* unit = sourceField->getUnit();

    // Check if there's a unit to move
    if (!unit)
    {
        std::cout << "No unit to move at (" << fromX << "," << fromY << ")!\n";
        return;
    }

    // Check if target is occupied
    if (targetField->getUnit())
    {
        std::cout << "Target field (" << toX << "," << toY << ") is already occupied!\n";
        return;
    }

    // Calculate Manhattan distance
    int distance = abs(fromX - toX) + abs(fromY - toY);

    // Check movement range
    if (distance > unit->getMoveDistance())
    {
        std::cout << unit->getName() << " cannot move that far! (Max range: "
                  << unit->getMoveDistance() << ")\n";
        return;
    }

    // Check Will points
    if (unit->getWill() <= 0)
    {
        std::cout << unit->getName() << " doesn't have enough Will points to move!\n";
        return;
    }

    // Perform the move
    targetField->setUnit(unit);
    sourceField->setUnit(nullptr);
    unit->setWill(unit->getWill() - 1);

    // Prepare terrain information
    std::string terrainType = "plain field";
    if (dynamic_cast<Hill*>(targetField))
    {
        terrainType = "hill";
    }
    else if (dynamic_cast<Fortress*>(targetField))
    {
        terrainType = "fortress";
    }

    std::cout << unit->getName() << " moved from (" << fromX << "," << fromY
              << ") to (" << toX << "," << toY << ") - now on " << terrainType << "\n";
}

bool checkVictory(Player* player1, Player* player2)
{
    if(player2->getDefeated())
    {
        // Player 1 wins - congratulatory message
        std::cout << "\n\n";
        std::cout << "  ╔══════════════════════════════════════╗\n";
        std::cout << "  ║                                      ║\n";
        std::cout << "  ║   CONGRATULATIONS, " << std::left << std::setw(19) << player1->getName() << "!   ║\n";
        std::cout << "  ║                                      ║\n";
        std::cout << "  ║   You have defeated " << std::left << std::setw(18) << player2->getName() << "!   ║\n";
        std::cout << "  ║                                      ║\n";
        std::cout << "  ║        (\\_/)                        ║\n";
        std::cout << "  ║        (•ᴗ•)                        ║\n";
        std::cout << "  ║       c(\")(\")                       ║\n";
        std::cout << "  ║                                      ║\n";
        std::cout << "  ╚══════════════════════════════════════╝\n";
        return false;
    }
    else if(player1->getDefeated())
    {
        // Player 2 wins - sarcastic message
        std::cout << "\n\n";
        std::cout << "  ╔══════════════════════════════════════╗\n";
        std::cout << "  ║                                      ║\n";
        std::cout << "  ║    WOW. JUST... WOW.                ║\n";
        std::cout << "  ║                                      ║\n";
        std::cout << "  ║   " << std::left << std::setw(36) << (player2->getName() + " beat you. How?") << "║\n";
        std::cout << "  ║   It was barely sentient!           ║\n";
        std::cout << "  ║                                      ║\n";
        std::cout << "  ║        (╯°□°)╯︵ ┻━┻                ║\n";
        std::cout << "  ║                                      ║\n";
        std::cout << "  ╚══════════════════════════════════════╝\n";
        return false;
    }
    return true;
}