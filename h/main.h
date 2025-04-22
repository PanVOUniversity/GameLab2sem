#include <iostream>

#include "inicialisation.h"
#include <iostream>

int main()
{
    try
    {
        // Initialize game with:
        // - 10x10 board
        // - 5 hills
        // - Player names "Human" and "AI"
        // - Starting mana: 100
        // - Player 1 starts first
        GameData game = inicialisation(10, 10, 5, "my kingdom", "AI kingdom", 100, true);

        // Access game state
        std::cout << "Player 1 turn: " << game.player1->getMyTurn() << std::endl;
        std::cout << "Player 1 mana: " << game.player1->getMana() << std::endl;

    }
    catch (const std::exception& e)
    {
        std::cerr << "Initialization failed: " << e.what() << std::endl;
        return 1;
    }

    
    return 0;
}