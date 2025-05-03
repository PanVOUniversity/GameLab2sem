// shieldedfield.h
#ifndef SHIELDEDFIELD_H
#define SHIELDEDFIELD_H

#include "field.h"

class ShieldedField : public Field {
public:
    ShieldedField(int x, int y, Unit* unit = nullptr);
    virtual ~ShieldedField() = default;
    
    bool isSpellProtected() const { return true; }
};

#endif