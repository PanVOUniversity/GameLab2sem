// unit.h
#ifndef UNIT_H
#define UNIT_H

#include <string>
#include <vector>
// Removed: #include "field.h" // Include Field header

// Forward declaration for Field to break circular dependency
class Field;

/**
 * @brief Represents a unit in the game (base class for all units).
 */
class Unit
{
protected:
    std::string name;
    int moveDistance;
    int attackDistance;
    int currentHealth;
    int maxHealth;
    int damage;
    bool isPlayerUnit; // true if controlled by human player, false if AI
    int currentWill; // Will points for actions
    int maxWill; // Maximum Will points

public:
    /**
     * @brief Constructs a Unit with the given parameters.
     * @param unitName Name of the unit.
     * @param moveD Move distance.
     * @param attackD Attack distance.
     * @param health Initial and max health.
     * @param dmg Damage value.
     * @param isPlayer True if controlled by player, false if AI.
     * @param will Initial and max will points.
     */
    Unit(const std::string& unitName, int moveD, int attackD, int health, int dmg, bool isPlayer, int will);
    /**
     * @brief Virtual destructor for Unit.
     */
    virtual ~Unit();

    /** @brief Gets the unit's name. */
    std::string getName() const;
    /** @brief Gets the unit's move distance. */
    int getMoveDistance() const;
    /** @brief Gets the unit's attack distance. */
    int getAttackDistance() const;
    /** @brief Gets the unit's current health. */
    int getCurrentHealth() const;
    /** @brief Gets the unit's max health. */
    int getMaxHealth() const;
    /** @brief Gets the unit's damage value. */
    int getDamage() const;
    /** @brief Returns true if the unit is controlled by the player. */
    bool getPlayer() const;
    /** @brief Gets the unit's current will points. */
    int getWill() const;
    /** @brief Gets the unit's max will points. */
    int getMaxWill() const;

    /** @brief Sets the unit's current health. */
    void setCurrentHealth(int health);
    /** @brief Sets the unit's will points. */
    void setWill(int will);
    /** @brief Sets the unit's health (alias for setCurrentHealth). */
    void setHealth(int health);

    /**
     * @brief Applies damage to the unit.
     * @param damage Amount of damage to apply.
     * @param attacker The attacking unit (optional).
     */
    virtual void takeDamage(int damage, Unit* attacker = nullptr);

    /**
     * @brief Restores health to the unit.
     * @param amount Amount of health to restore.
     */
    void restoreHealth(int amount);

    /**
     * @brief Restores will points to the unit.
     * @param amount Amount of will to restore.
     */
    void restoreWill(int amount);

    /**
     * @brief Virtual method for special unit abilities (to be overridden by derived classes).
     * @param board The game board.
     * @param targetX X coordinate of the target.
     * @param targetY Y coordinate of the target.
     * @return True if the ability was used successfully.
     */
    virtual bool useAbility(std::vector<std::vector<Field*>>& board, int targetX, int targetY);

    /**
     * @brief Gets the symbol representing the unit (for display).
     * @return Character symbol.
     */
    virtual char getSymbol() const { return '?'; }
};

#endif
