#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
class Unit;

class Player {
private:
    bool _my_turn;
    std::vector<Unit*> _my_units;
    bool _AI;
    bool _defeated;
    int _mana;

public:
    Player(bool my_turn = false, bool AI = false, bool defeated = false, int mana = 0);
    ~Player() = default;

    // Only declarations here
    bool getMyTurn() const;
    void setMyTurn(bool my_turn);
    std::vector<Unit*> getMyUnits() const;
    void setMyUnits(const std::vector<Unit*>& my_units);
    bool getAI() const;
    void setAI(bool AI);
    bool getDefeated() const;
    void setDefeated(bool defeated);
    int getMana() const;
    void setMana(int mana);
};

#endif