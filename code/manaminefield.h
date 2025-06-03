// manaminefield.h
#ifndef MANAMINEFIELD_H
#define MANAMINEFIELD_H

#include "field.h"
#include "player.h" // Include Player header
#include "unit.h" // Include Unit header for initialUnit parameter
#include <string>

class Player; // Forward declaration (already included, but good practice)
class Unit; // Forward declaration (already included, but good practice)

/**
 * @brief Field that generates mana for the owner each turn (Mana Mine Field).
 */
class ManaMineField : public Field
{
private:
    int manaPerTurn; // Amount of mana generated per turn

public:
    /**
     * @brief Constructs a ManaMineField at the given coordinates.
     * @param fieldX X coordinate.
     * @param fieldY Y coordinate.
     * @param initialUnit Pointer to the initial unit on the field (default nullptr).
     */
    ManaMineField(int fieldX, int fieldY, Unit* initialUnit = nullptr);
    virtual ~ManaMineField() = default;

    /**
     * @brief Applies the mana mine field's effect (generates mana).
     * @param owner The player whose turn it is.
     * @param board The game board.
     */
    void applyEffect(Player* owner, std::vector<std::vector<Field*>>& board) override;

    /**
     * @brief Checks if a unit can enter the mana mine field.
     * @param unit The unit to check.
     * @return True if the unit can enter, false otherwise.
     */
    bool canEnter(Unit* unit) const override;

    /**
     * @brief Generates mana for the given player.
     * @param player The player to receive mana.
     */
    void generateMana(Player* player);

    /**
     * @brief Gets the symbol representing the mana mine field (for display).
     * @return 'M' character.
     */
    char getSymbol() const override { return 'M'; }
};

#endif
