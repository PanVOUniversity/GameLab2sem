#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>
#include "field.h"
#include "fortress.h"
#include "unit.h"
#include <cstddef>

void updateFortressStrength(
    std::vector<std::vector<Field*>>& board,
    int x,
    int y,
    int newStrength
);


void attack(
    std::vector<std::vector<Field*>>& board,
    int attackerX,
    int attackerY,
    int victimX,
    int victimY
);

#endif