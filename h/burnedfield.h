// burnedfield.h
#ifndef BURNEDFIELD_H
#define BURNEDFIELD_H

#include "field.h"
#include "unit.h"

class BurnedField : public Field {
private:
    int _burnTime;
public:
    BurnedField(int x, int y, int burnTime, Unit* unit = nullptr);
    virtual ~BurnedField() = default;
    
    void burnUnit(Unit* unit);
    bool updateBurnTime();
};

#endif