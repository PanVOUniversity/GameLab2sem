#ifndef FIELD_H
#define FIELD_H

// Forward declaration for Unit
class Unit;

class Field {
private:
    int _x;
    int _y;
    int _damage;
    Unit* _unit;

public:
    Field(int xCoord, int yCoord, Unit* unit = nullptr);
    virtual ~Field();

    int getX() const;
    int getY() const;
    Unit* getUnit() const;
    void setUnit(Unit* unit);
};


#endif