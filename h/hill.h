#ifndef HILL_H
#define HILL_H

#include "field.h"

class Hill : public Field
{
private:
    int _height;

public:
    Hill(int x, int y, int height, Unit* unit = nullptr);
    ~Hill() override = default;

    int getHeight() const;
    void setHeight(int height);
};

#endif