// infantry.h
#ifndef INFANTRY_H
#define INFANTRY_H

#include "unit.h"

class Infantry : public Unit
{
public:
    Infantry(bool player = false);
    virtual ~Infantry() = default;

    void counterAttack(Unit* attacker);
};

#endif