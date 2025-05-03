#ifndef FIELD_H
#define FIELD_H

class Unit;

class Field
{
protected:
    int _x;
    int _y;
    Unit* _unit;

public:
    Field(int x, int y, Unit* unit = nullptr);
    virtual ~Field() = default;

    // Getters
    int getX() const;
    int getY() const;
    Unit* getUnit() const;

    // Setters
    void setUnit(Unit* unit);
};

#endif