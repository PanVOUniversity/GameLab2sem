// archer.h
#ifndef ARCHER_H
#define ARCHER_H

#include "unit.h"

class Archer : public Unit {
public:
    Archer(bool player = false);
    virtual ~Archer() = default;
    
    void updateAttackDistance(bool inFortress);
};

#endif