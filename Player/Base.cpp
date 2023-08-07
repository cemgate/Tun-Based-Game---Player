#include "pch.h"
#include "Base.h"

long Base::getGold()
{
    return this->gold;
}

long Base::setGold(long goldFromFile)
{
    return this->gold=goldFromFile;
}

int Base::getHealth()
{
    return this->health;
}

int Base::setHealth(int health)
{
    return this->health=health;
}

void Base::takeDamage(int damage)
{
    this->health -= damage;
}

void Base::setPosition(int x, int y)
{
    this->position.x = x;
    this->position.y = y;
}

void Base::setBuildStatus(char entityType)
{
    this->buildingEntity = entityType;
    this->isBuildingEntity = true;
}

void Base::buildEntity(char entityType)
{
    if (!isBuildingEntity)
    {
        this->isBuildingEntity = entityType;
    }
}

bool Base::isAlive()
{
    return this->health>0;
}

