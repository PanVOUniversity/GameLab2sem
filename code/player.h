// player.h
#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
// Removed: #include "field.h" // Include Field header - Use forward declaration instead
#include "unit.h" // Player needs to know about Units (e.g., for lists of units)

class Field; // Forward declaration for Field - Sufficient for pointer/reference types

/**
 * @brief Represents a player in the game (human or AI).
 */
class Player
{
private:
    std::string name;
    int mana;
    bool isAI;
    bool myTurn; // Added to track if it's this player's turn
    bool defeated; // Added to track if the player is defeated
    int skippedTurns; // Added to track consecutive skipped turns
    // Removed: std::vector<Unit*> myUnits; // Assuming unit ownership is managed elsewhere, e.g., on the board

public:
    /**
     * @brief Constructs a Player with the given parameters.
     * @param n Name of the player.
     * @param myTurn True if it's this player's turn.
     * @param ai True if this player is AI-controlled.
     * @param defeated True if the player is defeated.
     * @param initialMana Starting mana value.
     */
    Player(std::string n, bool myTurn = false, bool ai = false, bool defeated = false, int initialMana = 0);

    /** @brief Gets the player's name. */
    std::string getName() const;
    /** @brief Gets the player's current mana. */
    int getMana() const;
    /** @brief Sets the player's mana. */
    void setMana(int m);
    /** @brief Returns true if the player is AI-controlled. */
    bool getAI() const;
    /** @brief Returns true if it's this player's turn. */
    bool getMyTurn() const;
    /** @brief Sets whether it's this player's turn. */
    void setMyTurn(bool turn);
    /** @brief Returns true if the player is defeated. */
    bool getDefeated() const;
    /** @brief Sets whether the player is defeated. */
    void setDefeated(bool d);
    /** @brief Gets the number of consecutive skipped turns. */
    int getSkippedTurns() const;
    /** @brief Sets the number of consecutive skipped turns. */
    void setSkippedTurns(int turns);
    /**
     * @brief Adds mana to the player.
     * @param amount Amount of mana to add.
     */
    void addMana(int amount);
    /**
     * @brief Subtracts mana from the player if possible.
     * @param amount Amount of mana to subtract.
     * @return True if mana was subtracted, false if not enough mana.
     */
    bool subtractMana(int amount);

    // Removed: Getter and setter for myUnits as unit ownership is board-managed
    // std::vector<Unit*>& getMyUnits();
    // void setMyUnits(const std::vector<Unit*>& units);
};

#endif
