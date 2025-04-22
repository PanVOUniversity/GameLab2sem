#include "AI.h"


// Forward declarations
bool tryAIAttack(Unit* unit, int x, int y, std::vector<std::vector<Field*>>& board);
void tryAIMove(Unit* unit, int x, int y, std::vector<std::vector<Field*>>& board);
void tryAICreateUnits(Unit* unit, int x, int y, std::vector<std::vector<Field*>>& board, Player* aiPlayer);

void AIact(Player* aiPlayer, std::vector<std::vector<Field*>>& board) {
    if (!aiPlayer || !aiPlayer->getAI() || !aiPlayer->getMyTurn()) {
        return;
    }

    std::cout << "\n=== AI's turn ===\n";

    // Collect all AI units (owned by AI player)
    std::vector<std::pair<int, int>> aiUnits;
    for (size_t x = 0; x < board.size(); ++x) {
        for (size_t y = 0; y < board[x].size(); ++y) {
            Unit* unit = board[x][y]->getUnit();
            if (unit && !unit->getPlayer()) {  // Check if unit belongs to AI (getPlayer() == false)
                aiUnits.emplace_back(x, y);
            }
        }
    }

    // Shuffle units for random order
    std::srand(static_cast<unsigned>(std::time(0)));
    std::random_shuffle(aiUnits.begin(), aiUnits.end());

    // Process each unit
    for (auto& [x, y] : aiUnits) {
        Unit* unit = board[x][y]->getUnit();
        if (!unit || unit->getWill() <= 0) continue;

        if (tryAIAttack(unit, x, y, board)) continue;
        tryAIMove(unit, x, y, board);
        tryAICreateUnits(unit, x, y, board, aiPlayer);
    }

    // End AI turn
    aiPlayer->setMyTurn(false);
    std::cout << "AI turn ended.\n";
}

// Helper function implementations
bool tryAIAttack(Unit* unit, int x, int y, std::vector<std::vector<Field*>>& board) {
    if (!unit) return false;

    for (int dx = -unit->getAttackDistance(); dx <= unit->getAttackDistance(); ++dx) {
        for (int dy = -unit->getAttackDistance(); dy <= unit->getAttackDistance(); ++dy) {
            int nx = x + dx;
            int ny = y + dy;

            if (nx >= 0 && nx < static_cast<int>(board.size()) &&
                ny >= 0 && ny < static_cast<int>(board[0].size())) {
                Unit* target = board[nx][ny]->getUnit();
                if (target && target->getPlayer()) {  // Attack human units (getPlayer() == true)
                    if (abs(dx) + abs(dy) <= unit->getAttackDistance()) {
                        std::cout << "AI " << unit->getName() << " attacks (" << nx << "," << ny << ")\n";
                        attack(board, x, y, nx, ny);
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

void tryAIMove(Unit* unit, int x, int y, std::vector<std::vector<Field*>>& board) {
    if (!unit || unit->getWill() <= 0) return;

    for (int attempt = 0; attempt < 5; ++attempt) {
        int dx = (std::rand() % (unit->getMoveDistance() * 2 + 1)) - unit->getMoveDistance();
        int dy = (std::rand() % (unit->getMoveDistance() * 2 + 1)) - unit->getMoveDistance();
        
        int nx = x + dx;
        int ny = y + dy;

        if (nx >= 0 && nx < static_cast<int>(board.size()) &&
            ny >= 0 && ny < static_cast<int>(board[0].size()) &&
            abs(dx) + abs(dy) <= unit->getMoveDistance() &&
            !board[nx][ny]->getUnit()) {
            
            std::cout << "AI " << unit->getName() << " moves to (" << nx << "," << ny << ")\n";
            move(board, x, y, nx, ny);
            break;
        }
    }
}

void tryAICreateUnits(Unit* unit, int x, int y, std::vector<std::vector<Field*>>& board, Player* aiPlayer) {
    if (!unit || !aiPlayer) return;

    Engineer* engineer = dynamic_cast<Engineer*>(unit);
    if (!engineer || aiPlayer->getMana() < 3) return;

    int middleRow = board[0].size() / 2;

    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue;
            
            int nx = x + dx;
            int ny = y + dy;

            bool inUpperHalf = ny < middleRow;

            if (nx >= 0 && nx < static_cast<int>(board.size()) &&
                ny >= 0 && ny < static_cast<int>(board[0].size()) &&
                inUpperHalf &&
                !board[nx][ny]->getUnit()) {
                
                int unitType = std::rand() % 4;
                std::string type;
                int cost = 0;

                switch (unitType) {
                    case 0: type = "archer"; cost = 3; break;
                    case 1: type = "infantry"; cost = 2; break;
                    case 2: type = "priest"; cost = 5; break;
                    case 3: type = "engineer"; cost = 5; break;
                }

                if (aiPlayer->getMana() >= cost) {
                    Unit* newUnit = nullptr;
                    if (type == "archer") newUnit = new Archer(false);  // AI owns the unit (getPlayer() == false)
                    else if (type == "infantry") newUnit = new Infantry(false);
                    else if (type == "priest") newUnit = new Priest(false);
                    else if (type == "engineer") newUnit = new Engineer(false);

                    if (newUnit) {
                        board[nx][ny]->setUnit(newUnit);
                        aiPlayer->setMana(aiPlayer->getMana() - cost);
                        std::cout << "AI created " << type << " at (" << nx << "," << ny << ")\n";
                        return;
                    }
                }
            }
        }
    }
}