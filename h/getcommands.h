#ifndef GETCOMMANDS_H
#define GETCOMMANDS_H

#include <vector>
#include "player.h"
#include "field.h"
#include <string>
#include "spell.h"
#include "teleportspell.h"
#include "morogspell.h"
#include "fireballspell.h"
#include "bombspell.h"


void getPlayerCommands(
    Player* currentPlayer,
    std::vector<std::vector<Field*>>& board
);

#endif