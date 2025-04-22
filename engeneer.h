// engineer.h
#ifndef ENGINEER_H
#define ENGINEER_H

#include "unit.h"
#include "field.h"

class Engineer : public Unit
{
public:
    Engineer(bool player = false);
    virtual ~Engineer() = default;

    Field* createFortress(int x, int y);
    Field* createManaMine(int x, int y);
    Field* createTrap(int x, int y);
};

#endif