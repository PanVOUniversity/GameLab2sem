// bombedfield.h
#ifndef BOMBEDFIELD_H
#define BOMBEDFIELD_H

#include "field.h"
#include "unit.h"
#include "player.h" // Ensure Player is included
#include <string>
#include <vector> // Required for std::vector in explode method

class Unit; // Forward declaration
class Player; // Forward declaration (already included, but good practice)

/**
 * @brief Field that acts as a trap and explodes after a timer or when triggered by a unit (Bombed Field).
 */
class BombedField : public Field
{
private:
    int timer; // Turns until explosion
    int explosionDamage; // Damage dealt on explosion

public:
    /**
     * @brief Constructs a BombedField at the given coordinates.
     * @param fieldX X coordinate.
     * @param fieldY Y coordinate.
     * @param initialUnit Pointer to the initial unit on the field (default nullptr).
     * @param initialTimer Number of turns until explosion (default 3).
     * @param damage Damage dealt on explosion (default 10).
     */
    BombedField(int fieldX, int fieldY, Unit* initialUnit = nullptr, int initialTimer = 3, int damage = 10);
    virtual ~BombedField() = default;

    /**
     * @brief Applies the bombed field's effect (ticks timer, may explode).
     * @param owner The player whose turn it is.
     * @param board The game board.
     */
    void applyEffect(Player* owner, std::vector<std::vector<Field*>>& board) override;

    /**
     * @brief Checks if a unit can enter the bombed field.
     * @param unit The unit to check.
     * @return True if the unit can enter, false otherwise.
     */
    bool canEnter(Unit* unit) const override;

    /**
     * @brief Handles a unit entering the bombed field (may trigger explosion).
     * @param unit The unit entering.
     */
    void onEnter(Unit* unit) override;

    /**
     * @brief Checks if the bomb should explode.
     * @return True if the bomb should explode, false otherwise.
     */
    bool shouldExplode() const;

    /**
     * @brief Triggers the explosion effect.
     * @param board The game board.
     */
    void explode(std::vector<std::vector<Field*>>& board);

    /**
     * @brief Gets the symbol representing the bombed field (for display).
     * @return 'B' character.
     */
    char getSymbol() const override { return 'B'; }
};

#endif
