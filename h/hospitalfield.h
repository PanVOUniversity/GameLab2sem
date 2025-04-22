// hospitalfield.h
#ifndef HOSPITALFIELD_H
#define HOSPITALFIELD_H

#include "field.h"
#include "unit.h"

class HospitalField : public Field {
public:
    HospitalField(int x, int y, Unit* unit = nullptr);
    virtual ~HospitalField() = default;
    
    void applyHospitalEffect(Unit* unit);
};

#endif