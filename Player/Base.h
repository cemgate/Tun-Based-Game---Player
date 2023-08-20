#pragma once
#include "Entity.h"

/**
 * @class Base
 * @brief Represents a base in the game.
 *
 * This class encapsulates attributes and behavior of a base in the game.
 * It includes information about gold, health, position, build status, and more.
 */
class Base
{
public:
    /**
     * @brief Get the amount of gold the base has.
     * @return The current gold amount.
     */
    long getGold();

    /**
     * @brief Get the health of the base.
     * @return The current health of the base.
     */
    int getHealth();

    /**
     * @brief Get the unique ID of the base.
     * @return The unique ID of the base.
     */
    int getBaseUniqueID();

    /**
     * @brief Get the X position of the base.
     * @return The X position of the base.
     */
    int getBasePosX();

    /**
     * @brief Get the Y position of the base.
     * @return The Y position of the base.
     */
    int getBasePosY();

    /**
     * @brief Set the amount of gold for the base.
     * @param gold The amount of gold to set.
     */
    void setGold(long gold);

    /**
     * @brief Set the health of the base.
     * @param health The health value to set.
     */
    void setHealth(int health);

    /**
     * @brief Set the position of the base.
     * @param x The X position to set.
     * @param y The Y position to set.
     */
    void setPosition(int x, int y);

    /**
     * @brief Set the build status of the base.
     * @param entityType The type of entity being built.
     */
    void setBuildStatus(char entityType);

    /**
     * @brief Set the unique ID of the base.
     * @param ID The unique ID to set.
     */
    void setBaseUniqueID(int ID);

    /**
     * @brief Apply damage to the base.
     * @param damage The amount of damage to apply.
     */
    void takeDamage(int damage);

    /**
     * @brief Deduct the cost of an entity from the base's gold.
     * @param cost The cost of the entity to deduct.
     */
    void entityCostOfPurchase(int cost);

    /**
     * @brief Check if the base is still alive.
     * @return True if the base's health is above 0, otherwise false.
     */
    bool isAlive();

    /**
     * @brief Check if the base is ready to buy an entity.
     * @param cost The cost of the entity to check against.
     * @return True if the base's gold is enough for the cost, otherwise false.
     */
    bool isReadyToBuy(int cost);

    /**
     * @brief Check if the base is ready to build an entity.
     * @return True if the base is ready to build, otherwise false.
     */
    bool isReadyToBuild();

    /**
     * @brief Destructor for the Base class.
     */
    ~Base() {};

private:
    int baseUniqueID = -1; ///< The unique ID of the base.
    long gold; ///< The amount of gold the base has.
    int health; ///< The health of the base.
    Vector2f position; ///< The position of the base.
    bool isReadyToBuildEntity = true; ///< Flag indicating if the base is ready to build an entity.
    char buildingEntity; ///< The type of entity currently being built.
};

