#include "pch.h"
#include "Ram.h"

char Ram::getClass()
{
    return 'R';
}

int Ram::getHealth()
{
	return this->health;
}

int Ram::getMovementSpeed()
{
	return this->movementSpeed;
}

int Ram::getAttackRange()
{
	return this->attackRange;
}

int Ram::getBuildTime()
{
	return this->buildTime;
}

int Ram::getBuyPrice()
{
	return this->price;
}

int Ram::getEntityUniqueID()
{
	return this->uniqueID;
}

int Ram::getPosX()
{
	return this->position.x;
}

int Ram::getPosY()
{
	return this->position.y;
}

void Ram::setHealth(int health)
{
	this->health = health;
}

void Ram::setPosition(int posX, int posY)
{
	this->position.x = posX;
	this->position.y = posY;
}

void Ram::setEntityUniqueID(int ID)
{
	this->uniqueID = ID;
}

void Ram::takeDamage(int damage)
{
	this->health -= damage;
}

void Ram::attack(Entity* target)
{
	int targetIndex = m_unit_index.at(target->getClass());
	int attackerIndex = m_unit_index.at(this->getClass());
	target->takeDamage(m_damage_table[attackerIndex][targetIndex]);
}

bool Ram::isAlive()
{
	return health > 0;
}
