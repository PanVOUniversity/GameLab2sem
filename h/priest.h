// priest.h
#ifndef PRIEST_H
#define PRIEST_H

#include "unit.h"
#include <vector>
#include "field.h"

class Priest : public Unit {
public:
    Priest(bool player = false);
    virtual ~Priest() = default;
    
    void protectFromSpells(std::vector<std::vector<Field*>>& board, int x, int y);
};

#endif