#include "pch.h"
#include "Catapult.h"

char Catapult::getClass()
{
    return 'C';
}

int Catapult::getHealth()
{
	return this->health;
}

int Catapult::getMovementSpeed()
{
	return this->movementSpeed;
}

int Catapult::getAttackRange()
{
	return this->attackRange;
}

int Catapult::getBuildTime()
{
	return this->buildTime;
}

int Catapult::getBuyPrice()
{
	return this->price;
}

int Catapult::getEntityUniqueID()
{
	return this->uniqueID;
}

int Catapult::getPosX()
{
	return this->position.x;
}

int Catapult::getPosY()
{
	return this->position.y;
}

void Catapult::setHealth(int health)
{
	this->health = health;
}

void Catapult::setPosition(int posX, int posY)
{
	this->position.x = posX;
	this->position.y = posY;
}

void Catapult::setEntityUniqueID(int ID)
{
	this->uniqueID = ID;
}

void Catapult::takeDamage(int damage)
{
	this->health -= damage;
}

void Catapult::attack(Entity* target)
{
	int targetIndex = m_unit_index.at(target->getClass());
	int attackerIndex = m_unit_index.at(this->getClass());
	target->takeDamage(m_damage_table[attackerIndex][targetIndex]);
}

bool Catapult::isAlive()
{
	return health > 0;
}
