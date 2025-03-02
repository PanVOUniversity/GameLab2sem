#ifndef INICIALISATION_H
#define INICIALISATION_H

#include <vector>
#include "field.h"

std::vector<std::vector<Field*>> createBoard(int width, int height);
void placeHills(std::vector<std::vector<Field*>>& board);
void createPlayers();
void inicialisation();

#endif