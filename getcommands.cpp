#include "getcommands.h"


void getPlayerCommands(Player* currentPlayer, std::vector<std::vector<Field*>>& board)
{
    // Only allow commands for non-AI players
    if (currentPlayer->getAI())
    {
        std::cout << "AI player's turn - no commands available\n";
        return;
    }

    
    std::string input;
    bool turnEnded = false;

    while (!turnEnded) {
        // Show mana at start of each command loop
        std::cout << "\n=== Your turn ===\n";
        std::cout << "Current mana: " << currentPlayer->getMana() << "\n";
        std::cout << "Available commands:\n";
        std::cout << "  move x1 y1 x2 y2 - Move unit\n";
        std::cout << "  attack x1 y1 x2 y2 - Attack\n";
        std::cout << "  create type x y - Create unit (archer:3, infantry:2, priest:5, engineer:5)\n";
        std::cout << "  morogspell x y - Switch unit (5 mana)\n";
        std::cout << "  fireball x y - Burn area (5 mana)\n";
        std::cout << "  cursespell x y - Disable enemy (3 mana)\n";
        std::cout << "  bombspell x y - Place bomb (4 mana)\n";
        std::cout << "  unit_map - Show unit positions (M=my, E=enemy)\n";
        std::cout << "  hill_map - show hill positions";
        std::cout << "  n - End turn\n";
        std::cout << "Enter command: ";

        std::getline(std::cin, input);

        if (input == "n")
        {
            turnEnded = true;
            std::cout << "Turn ended.\n";
            continue;
        }

        std::istringstream iss(input);
        std::string command;
        iss >> command;

        if (command == "move")
        {
            int x1, y1, x2, y2;
            if (iss >> x1 >> y1 >> x2 >> y2)
            {
                move(board, x1, y1, x2, y2);
            }
            else
            {
                std::cout << "Invalid move command format! Use: move x1 y1 x2 y2\n";
            }
        }
        else if (command == "attack")
        {
            int x1, y1, x2, y2;
            if (iss >> x1 >> y1 >> x2 >> y2)
            {
                attack(board, x1, y1, x2, y2);
            }
            else
            {
                std::cout << "Invalid attack command format! Use: attack x1 y1 x2 y2\n";
            }
        }
        else if (command == "create")
        {
            std::string unitType;
            int x, y;
            if (iss >> unitType >> x >> y)
            {
                // Validate coordinates
                if (x < 0 || x >= static_cast<int>(board.size()) || y < 0 || y >= static_cast<int>(board[0].size()))
                {
                    std::cout << "Coordinates out of bounds!\n";
                    continue;
                }
                Field* targetField = board[x][y];
                if (targetField->getUnit() != nullptr)
                {
                    std::cout << "Cannot create unit: Cell (" << x << "," << y << ") is occupied.\n";
                    continue;
                }
                // Create the unit
                bool isPlayerUnit = !currentPlayer->getAI(); // true for human player
                Unit* newUnit = nullptr;
                if (unitType == "archer")
                {
                    newUnit = new Archer(isPlayerUnit);
                }
                else if (unitType == "engineer")
                {
                    newUnit = new Engineer(isPlayerUnit);
                }
                else if (unitType == "infantry")
                {
                    newUnit = new Infantry(isPlayerUnit);
                }
                else if (unitType == "priest")
                {
                    newUnit = new Priest(isPlayerUnit);
                }
                else
                {
                    std::cout << "Invalid unit type. Valid types: archer, engineer, infantry, priest\n";
                    continue;
                }
                targetField->setUnit(newUnit);
                std::cout << "Created " << unitType << " at (" << x << "," << y << ")\n";
            }
            else
            {
                std::cout << "Invalid create command. Usage: create <type> x y\n";
            }
        }

        //spells
        else if (command == "morogspell")
        {
            int x,y;
            if (iss >> x >> y)
            {
                MorogSpell().cast(board, x, y);
            }
        }
        else if (command == "fireball")
        {
            int x,y;
            if (iss >> x >> y)
            {
                FireballSpell().cast(board, x, y);
            }
        }
        else if (command == "cursespell")
        {
            int x,y;
            if (iss >> x >>y)
            {
                CurseSpell().cast(board, x, y);
            }
        }
        else if (command == "bombspell")
        {
            int x, y;
            if (iss >> x >> y)
            {
                BombSpell().cast(board, x, y);
            }
        }

        //maps
        else if (command == "health_map") {
            std::cout << "M - mine, E - enemy's\n";
            std::cout << "Health map:\n";
            // Print column numbers
            std::cout << "   ";
            for (size_t x = 0; x < board.size(); ++x) {
                std::cout << std::setw(4) << x;
            }
            std::cout << "\n";
            
            for (size_t y = 0; y < board[0].size(); ++y) {
                std::cout << std::setw(2) << y << " ";
                for (size_t x = 0; x < board.size(); ++x) {
                    Unit* unit = board[x][y]->getUnit();
                    if (unit) {
                        std::string prefix = unit->getPlayer() ? "M" : "E"; // M=my, E=enemy
                        std::cout << std::setw(3) << (prefix + std::to_string(unit->getHealth()));
                    } else {
                        std::cout << std::setw(4) << "--";
                    }
                }
                std::cout << "\n";
            }
        }

        else if (command == "health_map") {
            std::cout << "Health map:\n";
            // Print column numbers...
            
            for (size_t y = 0; y < board[0].size(); ++y) {
                std::cout << std::setw(2) << y << " ";
                for (size_t x = 0; x < board.size(); ++x) {
                    Unit* unit = board[x][y]->getUnit();
                    if (unit) {
                        int health = unit->getHealth();
                        std::string color;
                        if (health > 6) color = "\033[32m";  // Green (healthy)
                        else if (health > 3) color = "\033[33m"; // Yellow (wounded)
                        else color = "\033[31m"; // Red (critical)
                        
                        std::string prefix = unit->getPlayer() ? "M" : "E";
                        std::cout << color << std::setw(3) 
                                << (prefix + std::to_string(health)) << "\033[0m";
                    } else {
                        std::cout << std::setw(4) << "--";
                    }
                }
                std::cout << "\n";
            }
        }

        // Add this new command handler:
        else if (command == "unit_map") {
            std::cout << "Unit map:\n";
            // Print column numbers
            std::cout << "   ";
            for (size_t x = 0; x < board.size(); ++x) {
                std::cout << std::setw(3) << x;
            }
            std::cout << "\n";
            
            for (size_t y = 0; y < board[0].size(); ++y) {
                std::cout << std::setw(2) << y << " ";
                for (size_t x = 0; x < board.size(); ++x) {
                    Unit* unit = board[x][y]->getUnit();
                    if (unit) {
                        std::string prefix = unit->getPlayer() ? "M" : "E"; // M=my, E=enemy
                        std::string type;
                        if (dynamic_cast<Archer*>(unit)) type = "A";
                        else if (dynamic_cast<Infantry*>(unit)) type = "I";
                        else if (dynamic_cast<Priest*>(unit)) type = "P";
                        else if (dynamic_cast<Engineer*>(unit)) type = "G"; // G for engineer
                        else if (dynamic_cast<Cannon*>(unit)) type = "C";
                        else type = "U"; // Unknown unit type
                        std::cout << std::setw(3) << (prefix + type);
                    } else {
                        std::cout << std::setw(3) << "--";
                    }
                }
                std::cout << "\n";
            }
        }
        else
        {
            std::cout << "Unknown command. Type 'n' to end your turn.\n";
        }

        // Reminder about ending turn
        if (!turnEnded)
        {
            std::cout << "\nRemember: you can end your turn with 'n'\n";
        }
    }

    // Switch turns after command loop ends
    currentPlayer->setMyTurn(false);
}

