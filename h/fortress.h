#ifndef FORTRESS_H
#define FORTRESS_H

#include "hill.h"

class Fortress : public Hill
{
private:
    int _strength;

public:
    Fortress(int x, int y, int height, int strength, Unit* unit = nullptr);
    ~Fortress() override = default;

    int getStrength() const;
    bool setStrength(int strength); // Returns true if fortress should be destroyed
};

#endif