#pragma once

/**
 * @brief Abstract base class representing units in the game.
 */
class Entity
{
public:
    /**
     * @brief Get the class identifier of the unit.
     * @return Class identifier (type) of the unit.
     */
    virtual char getClass() = 0;

    /**
     * @brief Get the current health of the unit.
     * @return Current health of the unit.
     */
    virtual int getHealth() = 0;

    /**
     * @brief Get the movement speed of the unit.
     * @return Movement speed of the unit.
     */
    virtual int getMovementSpeed() = 0;

    /**
     * @brief Get the attack range of the unit.
     * @return Attack range of the unit.
     */
    virtual int getAttackRange() = 0;

    /**
     * @brief Get the build time of the unit.
     * @return Build time of the unit.
     */
    virtual int getBuildTime() = 0;

    /**
     * @brief Get the purchase price of the unit.
     * @return Purchase price of the unit.
     */
    virtual int getBuyPrice() = 0;

    /**
     * @brief Get the unique ID of the unit.
     * @return Unique ID of the unit.
     */
    virtual int getEntityUniqueID() = 0;

    /**
     * @brief Get the X position of the unit.
     * @return X position of the unit.
     */
    virtual int getPosX() = 0;

    /**
     * @brief Get the Y position of the unit.
     * @return Y position of the unit.
     */
    virtual int getPosY() = 0;

    /**
     * @brief Set the health of the unit to the given value.
     * @param health New health value for the unit.
     */
    virtual void setHealth(int health) = 0;

    /**
     * @brief Set the position of the unit to the given coordinates.
     * @param posX X coordinate of the unit's position.
     * @param posY Y coordinate of the unit's position.
     */
    virtual void setPosition(int posX, int posY) = 0;

    /**
     * @brief Set the unique ID of the unit.
     * @param ID Unique ID to set for the unit.
     */
    virtual void setEntityUniqueID(int ID) = 0;

    /**
     * @brief Attack the specified target.
     * @param target Target of the attack.
     */
    virtual void attack(Entity* target) = 0;

    /**
     * @brief Receive the given amount of damage.
     * @param damage Amount of damage to receive.
     */
    virtual void takeDamage(int damage) = 0;

    /**
     * @brief Check if the unit is still alive.
     * @return true if the unit is alive; false if not.
     */
    virtual bool isAlive() = 0;

    /**
     * @brief Virtual destructor.
     */
    virtual ~Entity() {};

protected:
    /**
     * @brief Damage table array between different unit classes.
     */
    static constexpr int m_damage_table[7][8] = {
        // K   S   A   P   C   R   W   B
        { 35, 35, 35, 35, 35, 50, 35, 35 }, // K
        { 30, 30, 30, 20, 20, 30, 30, 30 }, // S
        { 15, 15, 15, 15, 10, 10, 15, 15 }, // A
        { 35, 15, 15, 15, 10, 10, 15, 15 }, // P
        { 40, 40, 40, 40 ,40, 40, 40, 50 }, // C
        { 10, 10, 10, 10, 10, 10, 10, 50 }, // R
        { 5,  5,  5,  5,  5,  5,  5,  1  }  // W
    };

    /**
     * @brief Map of unit indexes by their types.
     */
    const std::map<char, unsigned int> m_unit_index{
        { 'K', 0 },
        { 'S', 1 },
        { 'A', 2 },
        { 'P', 3 },
        { 'C', 4 },
        { 'R', 5 },
        { 'W', 6 },
        { 'B', 7 }
    };
};

