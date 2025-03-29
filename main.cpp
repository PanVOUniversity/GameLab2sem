#include "inicialisation.h"
#include <iostream>
#include <getcommands.h>

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
        GameData game = inicialisation(10, 10, 5, "Human", "AI", 100, true);

        // Access game state
        std::cout << "your turn: " << game.player1->getMyTurn() << std::endl;
        std::cout << "your mana: " << game.player1->getMana() << std::endl;

        while(game.player1->getDefeated()*game.player2->getDefeated() !=0)
        {
            if(game.player1->getMyTurn() == 1)
            {
                getPlayerCommands(game.player1, game.board);
            }
            else
            {
                AIact();
            }
        }

        if(game.player1->getDefeated = 0)

        }
    catch (const std::exception& e)
    {
        std::cerr << "Initialization failed: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}