// fortress.h
#ifndef FORTRESS_H
#define FORTRESS_H

#include "field.h"
#include "unit.h"
#include "player.h" // Ensure Player is included
#include <string>

class Unit; // Forward declaration

/**
 * @brief Represents a Fortress field on the board, which provides defense and can be captured or destroyed.
 */
class Fortress : public Field
{
private:
    int strength;
    int maxStrength; // Added max strength
    Player* owner; // Add owner field

public:
    /**
     * @brief Constructs a Fortress at the given coordinates.
     * @param fieldX X coordinate.
     * @param fieldY Y coordinate.
     * @param initialStrength Initial strength value.
     * @param maxStrength Maximum strength value.
     * @param owner Pointer to the owning player (default nullptr).
     */
    Fortress(int fieldX, int fieldY, int initialStrength, int maxStrength, Player* owner = nullptr);
    virtual ~Fortress() = default;

    /** @brief Gets the current strength of the fortress. */
    int getStrength() const;
    /**
     * @brief Sets the strength of the fortress.
     * @param s The new strength value.
     * @return True if the fortress is destroyed (strength <= 0), false otherwise.
     */
    bool setStrength(int s);
    /** @brief Gets the maximum strength of the fortress. */
    int getMaxStrength() const;

    /**
     * @brief Applies the fortress's effect (e.g., healing, defense) to the board.
     * @param owner The owning player.
     * @param board The game board.
     */
    void applyEffect(Player* owner, std::vector<std::vector<Field*>>& board) override;

    /**
     * @brief Gets the defense bonus provided by the fortress.
     * @return The defense bonus value.
     */
    int getDefenseBonus() const override;

    /**
     * @brief Checks if a unit can enter the fortress.
     * @param unit The unit to check.
     * @return True if the unit can enter, false otherwise.
     */
    bool canEnter(Unit* unit) const override;

    /**
     * @brief Handles a unit entering the fortress.
     * @param unit The unit entering.
     */
    void onEnter(Unit* unit) override;

    /**
     * @brief Handles a unit leaving the fortress.
     * @param unit The unit leaving.
     */
    void onLeave(Unit* unit) override;

    /** @brief Gets the owner of the fortress. */
    Player* getOwner() const { return owner; }
    /** @brief Sets the owner of the fortress. */
    void setOwner(Player* p) { owner = p; }

    /**
     * @brief Gets the symbol representing the fortress (for display).
     * @return 'F' character.
     */
    char getSymbol() const override { return 'F'; }

    // Fortress: symbol 'F', defense bonus 10, heals 2 per turn, can be destroyed, turns into Plain field
};

#endif
