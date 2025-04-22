// bombedfield.h
#ifndef BOMBEDFIELD_H
#define BOMBEDFIELD_H

#include "unit.h"
#include "field.h"

class BombedField : public Field {
private:
    int _timer;
public:
    BombedField(int x, int y, Unit* unit = nullptr);
    void unitEntered(Unit* unit);
    void endTurnEffect() ;
    bool shouldExplode() const;
};

#endif