#include "functions.h"

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
        static_cast<size_t>(y) >= board[0].size()) {
        return;
    }

    // Attempt to cast to Fortress
    Fortress* fortress = dynamic_cast<Fortress*>(board[x][y]);
    if (fortress) { // Check if cast succeeded
        if (fortress->setStrength(newStrength)) { // Strength ≤ 0?
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
) {
    // Check if coordinates are valid
    if (attackerX < 0 || attackerX >= static_cast<int>(board.size()) || 
        attackerY < 0 || attackerY >= static_cast<int>(board[0].size()) ||
        victimX < 0 || victimX >= static_cast<int>(board.size()) || 
        victimY < 0 || victimY >= static_cast<int>(board[0].size())) {
        return; // Invalid coordinates
    }

    Field* attackerField = board[attackerX][attackerY];
    Field* victimField = board[victimX][victimY];
    Unit* attacker = attackerField->getUnit();
    Unit* victim = victimField->getUnit();

    // Check if both units exist
    if (!attacker || !victim) return;

    // Check if attacker has enough Will to attack
    if (attacker->getWill() <= 0) {
        return; // Cannot attack if Will is <= 0
    }

    // Calculate Manhattan distance
    int distance = abs(attackerX - victimX) + abs(attackerY - victimY);

    // Check attack distance
    if (distance > attacker->getAttackDistance()) return;

    // Apply damage
    int damage = attacker->getDamage();
    victim->setHealth(victim->getHealth() - damage);

    // Decrease attacker's Will by 1
    attacker->setWill(attacker->getWill() - 1);  // Subtract 1 Will point

    // Check if victim is defeated
    if (victim->getHealth() <= 0) {
        victimField->setUnit(nullptr);
        delete victim;
    }
}