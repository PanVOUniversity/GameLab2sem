#ifndef GETCOMMANDS_H
#define GETCOMMANDS_H

#include <vector>
#include "player.h"
#include "field.h"
#include <string>
#include <sstream>
#include "spell.h"
#include "teleportspell.h"
#include "morogspell.h"
#include "fireballspell.h"
#include "bombspell.h"
#include "functions.h"
#include "spells.h"
#include "archer.h"
#include "engeneer.h"
#include "infantry.h"
#include "priest.h"
#include "cannon.h"


void getPlayerCommands(
    Player* currentPlayer,
    std::vector<std::vector<Field*>>& board
);

#endif