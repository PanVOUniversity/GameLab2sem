// manaminefield.h
#ifndef MANAMINEFIELD_H
#define MANAMINEFIELD_H

#include "field.h"
#include "player.h"

class ManaMineField : public Field {
public:
    ManaMineField(int x, int y, Unit* unit = nullptr);
    virtual ~ManaMineField() = default;
    
    void generateMana(Player* player);
};

#endif