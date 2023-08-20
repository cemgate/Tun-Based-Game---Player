#include "pch.h"
#include "Base.h"

long Base::getGold()
{
    return this->gold;
}

int Base::getHealth()
{
    return this->health;
}

int Base::getBaseUniqueID()
{
    return this->baseUniqueID;
}

int Base::getBasePosX()
{
    return this->position.x;
}

int Base::getBasePosY()
{
    return this->position.y;
}

void Base::setGold(long goldFromFile)
{
    this->gold=goldFromFile;
}

void Base::setHealth(int health)
{
    this->health=health;
}

void Base::setPosition(int x, int y)
{
    this->position.x = x;
    this->position.y = y;
}

void Base::setBuildStatus(char entityType)
{
    this->buildingEntity = entityType;
    if (entityType != '0')
    {
        this->isReadyToBuildEntity = false;
    }
}

void Base::setBaseUniqueID(int ID)
{
    this->baseUniqueID = ID;
}

void Base::takeDamage(int damage)
{
    this->health -= damage;
}

void Base::entityCostOfPurchase(int cost)
{
    this->gold -= cost;
}

bool Base::isReadyToBuy(int cost)
{
    return this->gold - cost >= 0;
}

bool Base::isReadyToBuild()
{
    return this->isReadyToBuildEntity;
}

bool Base::isAlive()
{
    return this->health>0;
}


