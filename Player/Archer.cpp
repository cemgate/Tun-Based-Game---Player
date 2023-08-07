#include "pch.h"
#include "Archer.h"

char Archer::getClass()
{
	return 'A';
}

int Archer::getHealth()
{
	return this->health;
}

int Archer::getMovementSpeed()
{
	return this->movementSpeed;
}

int Archer::getAttackRange()
{
	return this->attackRange;
}

int Archer::getBuildTime()
{
	return this->buildTime;
}

int Archer::getBuyPrice()
{
	return this->price;
}

void Archer::setHealth(int health)
{
	this->health = health;
}

void Archer::setPosition(int posX, int posY)
{
	this->position.x = posX;
	this->position.y = posY;
}

void Archer::takeDamage(int damage)
{
	this->health -= damage;
}

void Archer::attack(Entity* target)
{
	int targetIndex = m_unit_index.at(target->getClass());
	int attackerIndex = m_unit_index.at(this->getClass());
	target->takeDamage(m_damage_table[attackerIndex][targetIndex]);
}

bool Archer::isAlive()
{
	return health > 0;
}
