#include "pch.h"
#include "Worker.h"

char Worker::getClass()
{
    return 0;
}

int Worker::getHealth()
{
	return this->health;
}

int Worker::getMovementSpeed()
{
	return this->movementSpeed;
}

int Worker::getAttackRange()
{
	return this->attackRange;
}

int Worker::getBuildTime()
{
	return this->buildTime;
}

int Worker::getBuyPrice()
{
	return this->price;
}

int Worker::getEntityUniqueID()
{
	return this->uniqueID;
}

int Worker::getPosX()
{
	return 0;
}

int Worker::getPosY()
{
	return 0;
}

void Worker::setHealth(int health)
{
	this->health = health;
}

void Worker::setPosition(int posX, int posY)
{
	this->position.x = posX;
	this->position.y = posY;
}

void Worker::setEntityUniqueID(int ID)
{
	this->uniqueID = ID;
}

void Worker::takeDamage(int damage)
{
	this->health -= damage;
}

void Worker::attack(Entity* target)
{
	int targetIndex = m_unit_index.at(target->getClass());
	int attackerIndex = m_unit_index.at(this->getClass());
	target->takeDamage(m_damage_table[attackerIndex][targetIndex]);
}

bool Worker::isAlive()
{
	return health > 0;
}
