#ifndef INICIALISATION_H
#define INICIALISATION_H

#include <vector>
#include "field.h"
#include "hill.h"
#include <cstdlib>
#include <ctime>
#include "player.h"
#include <string>

struct GameData
{
    std::vector<std::vector<Field*>> board;
    Player* player1;
    Player* player2;
};

GameData inicialisation(int width, int height, int numHills,
                        const std::string& name1, const std::string& name2,
                        int initialMana, bool player1Starts);

#endif