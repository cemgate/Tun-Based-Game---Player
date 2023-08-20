#include "pch.h"
#include "Knight.h"

char Knight::getClass()
{
    return 'K';
}

int Knight::getHealth()
{
	return this->health;
}

int Knight::getMovementSpeed()
{
	return this->movementSpeed;
}

int Knight::getAttackRange()
{
	return this->attackRange;
}

int Knight::getBuildTime()
{
	return this->buildTime;
}

int Knight::getBuyPrice()
{
	return this->price;
}

int Knight::getEntityUniqueID()
{
	return this->uniqueID;
}

int Knight::getPosX()
{
	return this->position.x;
}

int Knight::getPosY()
{
	return this->position.y;
}

void Knight::setHealth(int health)
{
	this->health = health;
}

void Knight::setPosition(int posX, int posY)
{
	this->position.x = posX;
	this->position.y = posY;
}

void Knight::setEntityUniqueID(int ID)
{
	this->uniqueID = ID;
}

void Knight::takeDamage(int damage)
{
	this->health -= damage;
}

void Knight::attack(Entity* target)
{
	int targetIndex = m_unit_index.at(target->getClass());
	int attackerIndex = m_unit_index.at(this->getClass());
	target->takeDamage(m_damage_table[attackerIndex][targetIndex]);
}

bool Knight::isAlive()
{
	return health > 0;
}
