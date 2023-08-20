#include "pch.h"
#include "Swordsman.h"

char Swordsman::getClass()
{
    return 'S';
}

int Swordsman::getHealth()
{
	return this->health;
}

int Swordsman::getMovementSpeed()
{
	return this->movementSpeed;
}

int Swordsman::getAttackRange()
{
	return this ->attackRange;
}

int Swordsman::getBuildTime()
{
	return this->buildTime;
}

int Swordsman::getBuyPrice()
{
	return this->price;
}

int Swordsman::getEntityUniqueID()
{
	return this->uniqueID;
}

int Swordsman::getPosX()
{
	return this->position.x;
}

int Swordsman::getPosY()
{
	return this->position.y;
}

void Swordsman::setHealth(int health)
{
	this->health = health;
}

void Swordsman::setPosition(int posX, int posY)
{
	this->position.x = posX;
	this->position.y = posY;
}

void Swordsman::setEntityUniqueID(int ID)
{
	this->uniqueID = ID;
}

void Swordsman::takeDamage(int damage)
{
	this->health -= damage;
}

void Swordsman::attack(Entity* target)
{
	int targetIndex = m_unit_index.at(target->getClass());
	int attackerIndex = m_unit_index.at(this->getClass());
	target->takeDamage(m_damage_table[attackerIndex][targetIndex]);
}

bool Swordsman::isAlive()
{
	return health > 0;
}
