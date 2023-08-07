#include "pch.h"
#include "Pikeman.h"

char Pikeman::getClass()
{
	return 'P';
}

int Pikeman::getHealth()
{
	return this->health;
}

int Pikeman::getMovementSpeed()
{
	return this->movementSpeed;
}

int Pikeman::getAttackRange()
{
	return this->attackRange;
}

int Pikeman::getBuildTime()
{
	return this->buildTime;
}

int Pikeman::getBuyPrice()
{
	return this->price;
}

void Pikeman::setHealth(int health)
{
	this->health = health;
}

void Pikeman::setPosition(int posX, int posY)
{
	this->position.x = posX;
	this->position.y = posY;
}

void Pikeman::takeDamage(int damage)
{
	this->health -= damage;
}

void Pikeman::attack(Entity* target)
{
	int targetIndex = m_unit_index.at(target->getClass());
	int attackerIndex = m_unit_index.at(this->getClass());
	target->takeDamage(m_damage_table[attackerIndex][targetIndex]);
}

bool Pikeman::isAlive()
{
	return health > 0;
}
