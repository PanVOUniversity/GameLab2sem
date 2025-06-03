#ifndef INICIALISATION_H
#define INICIALISATION_H

#include <vector>
#include "field.h"
#include "hill.h"
#include <cstdlib>
#include <ctime>
#include "player.h" // Include Player header for GameData struct
#include <string>

/**
 * @brief Holds the main game data: board and players.
 */
struct GameData
{
    std::vector<std::vector<Field*>> board; ///< The game board
    Player* player1; ///< Pointer to player 1
    Player* player2; ///< Pointer to player 2
};

/**
 * @brief Initializes the game board and players.
 * @param width Board width.
 * @param height Board height.
 * @param numHills Number of hills to place on the board.
 * @param name1 Name of player 1.
 * @param name2 Name of player 2.
 * @param initialMana Starting mana for each player.
 * @param player1Starts True if player 1 starts the game.
 * @return GameData struct containing the initialized board and players.
 */
GameData inicialisation(int width, int height, int numHills,
                        const std::string& name1, const std::string& name2,
                        int initialMana, bool player1Starts);

#endif
