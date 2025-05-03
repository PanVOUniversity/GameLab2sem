#include "main.h"
#include <iostream> // Included for std::cout and std::cerr
#include "getcommands.h" // Include for displayBoard

int main()
{
    GameData game; // Declare game outside the try block

    try
    {
        // Initialize game with:
        // - 10x10 board
        // - 5 hills
        // - Player names "Human" and "AI"
        // - Starting mana: 50
        // - Player 1 starts first
        game = inicialisation(10, 10, 5, "Human", "AI", 50, true);

        int turnCount = 0; // Add turn counter

        // Access game state
        std::cout << "your turn: " << game.player1->getMyTurn() << std::endl;
        std::cout << "your mana: " << game.player1->getMana() << std::endl;

        // Game loop continues as long as neither player is defeated
        while(!game.player1->getDefeated() && !game.player2->getDefeated())
        {
            bool actionTakenThisTurn = false; // Flag to track if the current player took an action

            if(game.player1->getMyTurn())
            {
                // Human player's turn
                actionTakenThisTurn = getPlayerCommands(game.player1, game.board);
                checkBombExplosions(game.board); // Check for bomb explosions after player actions
                game.player1->setMyTurn(false);
                game.player2->setMyTurn(true); // Pass turn to AI

                // Update skipped turns for Player 1
                if (actionTakenThisTurn) {
                    game.player1->setSkippedTurns(0); // Reset skipped turns if action was taken
                } else {
                    game.player1->setSkippedTurns(game.player1->getSkippedTurns() + 1); // Increment skipped turns
                    std::cout << game.player1->getName() << " skipped a turn. Consecutive skipped turns: " << game.player1->getSkippedTurns() << std::endl;
                }
            }
            else
            {
                std::cout << "AI turn\n";
                std::cout << "[DEBUG] AI mana: " << game.player2->getMana() << "\n";
                // Print if AI has any units
                int aiUnitCount = 0;
                for (size_t x = 0; x < game.board.size(); ++x) {
                    for (size_t y = 0; y < game.board[x].size(); ++y) {
                        Field* f = game.board[x][y];
                        if (f && f->getUnit() && !f->getUnit()->getPlayer()) aiUnitCount++;
                    }
                }
                std::cout << "[DEBUG] AI units on board: " << aiUnitCount << "\n";
                // Print if AI has any valid creation spots
                int aiCreateSpots = 0;
                for (size_t y = 0; y <= 4 && y < game.board[0].size(); ++y) {
                    for (size_t x = 0; x < game.board.size(); ++x) {
                        Field* f = game.board[x][y];
                        if (f && !f->getUnit() && !dynamic_cast<Fortress*>(f) && !dynamic_cast<Hill*>(f) && !dynamic_cast<ManaMineField*>(f) && !dynamic_cast<BombedField*>(f) && !dynamic_cast<ShieldedField*>(f) && !dynamic_cast<BurnedField*>(f) && !dynamic_cast<HospitalField*>(f)) aiCreateSpots++;
                    }
                }
                std::cout << "[DEBUG] AI valid creation spots: " << aiCreateSpots << "\n";
                actionTakenThisTurn = getAICommands(game.player2, game.board);
                if (!actionTakenThisTurn) {
                    std::cout << "AI skipped its turn (no possible actions).\n";
                }
                checkBombExplosions(game.board);
                game.player1->setMyTurn(true);

                // Update skipped turns for Player 2
                if (actionTakenThisTurn) {
                    game.player2->setSkippedTurns(0); // Reset skipped turns if action was taken
                } else {
                    game.player2->setSkippedTurns(game.player2->getSkippedTurns() + 1); // Increment skipped turns
                    std::cout << game.player2->getName() << " skipped a turn. Consecutive skipped turns: " << game.player2->getSkippedTurns() << std::endl;
                }
            }

            

            // Check for victory/defeat/draw conditions after each turn
            checkVictory(game.player1, game.player2, game.board);

            // Add end-of-turn effects here if any (e.g., mana generation from manamines)
            for (size_t x = 0; x < game.board.size(); ++x) {
                for (size_t y = 0; y < game.board[x].size(); ++y) {
                    ManaMineField* manaMine = dynamic_cast<ManaMineField*>(game.board[x][y]);
                    if (manaMine) {
                        if (!game.player1->getMyTurn()) {
                             manaMine->generateMana(game.player1);
                             std::cout << game.player1->getName() << " gained 1 mana from a Mana Mine.\n";
                        } else {
                             manaMine->generateMana(game.player2);
                             std::cout << game.player2->getName() << " gained 1 mana from a Mana Mine.\n";
                        }
                    }
                }
            }

            // Increment turn counter after both players have played
            ++turnCount;
            if (game.player1->getSkippedTurns() >= 2) {
                std::cout << game.player1->getName() << " skipped 2 turns in a row. Game over!\n";
                break;
            }
            if (game.player2->getSkippedTurns() >= 2) {
                std::cout << game.player2->getName() << " skipped 2 turns in a row. Game over!\n";
                break;
            }
            if (turnCount >= 16) {
                std::cout << "16 turns have passed. Game over!\n";
                break;
            }
        }

        // Removed the redundant checkVictory call here.
        // The game outcome is already determined and printed inside the loop.

    }
    catch (const std::exception& e)
    {
        std::cerr << "Initialization failed: " << e.what() << std::endl;
        // No return here, proceed to cleanup if game was partially initialized
    }
     // Clean up allocated memory for the board and players
     // Check if the board was successfully created before attempting to delete
    if (!game.board.empty()) {
        for (size_t x = 0; x < game.board.size(); ++x) {
            // Check if the inner vector is not empty before accessing elements
            if (!game.board[x].empty()) {
                 for (size_t y = 0; y < game.board[x].size(); ++y) {
                    delete game.board[x][y]; // Deletes the field and the unit on it (if any)
                 }
            }
        }
    }
    delete game.player1;
    delete game.player2;

    return 0;
}
