// field.h
#ifndef FIELD_H
#define FIELD_H

#include <string>
#include <vector>
// Forward declaration for Unit to break circular dependency if needed, but unit.h includes field.h
class Unit;
// Include Player header for the applyEffect method signature
#include "player.h"

/**
 * @brief Represents a field (tile) on the game board. Base class for all field types.
 */
class Field
{
protected:
    Unit* unit; ///< Pointer to the unit on this field (if any)
    int x, y; ///< Coordinates of the field
    std::string type; ///< Type of the field (e.g., "plain", "fortress", "hill")

public:
    /**
     * @brief Constructs a Field at the given coordinates and type.
     * @param fieldX X coordinate.
     * @param fieldY Y coordinate.
     * @param fieldType Type of the field (default: "plain").
     */
    Field(int fieldX, int fieldY, const std::string& fieldType = "plain");
    /**
     * @brief Virtual destructor for Field.
     */
    virtual ~Field();

    /**
     * @brief Get the unit on this field.
     * @return Pointer to the unit, or nullptr if none.
     */
    Unit* getUnit() const;

    /**
     * @brief Set the unit on this field.
     * @param u Pointer to the unit to place.
     */
    void setUnit(Unit* u);

    /**
     * @brief Get the X coordinate of this field.
     * @return X coordinate.
     */
    int getX() const;
    /**
     * @brief Get the Y coordinate of this field.
     * @return Y coordinate.
     */
    int getY() const;

    /**
     * @brief Get the type of this field.
     * @return String representing the field type.
     */
    std::string getType() const;

    /**
     * @brief Apply the field's effect (e.g., mana generation, damage) to the board.
     * @param owner The player whose turn it is.
     * @param board The game board.
     */
    virtual void applyEffect(Player* owner, std::vector<std::vector<Field*>>& board);

    /**
     * @brief Get the defense bonus provided by this field.
     * @return The defense bonus value (default: 0).
     */
    virtual int getDefenseBonus() const;

    /**
     * @brief Check if a unit can enter this field.
     * @param unit The unit to check.
     * @return True if the unit can enter, false otherwise.
     */
    virtual bool canEnter(Unit* unit) const;

    /**
     * @brief Handle a unit entering this field.
     * @param unit The unit entering.
     */
    virtual void onEnter(Unit* unit);

    /**
     * @brief Handle a unit leaving this field.
     * @param unit The unit leaving.
     */
    virtual void onLeave(Unit* unit);

    /**
     * @brief Get the symbol representing this field (for display).
     * @return Character symbol (default: '+').
     */
    virtual char getSymbol() const { return '+'; }
};

#endif
