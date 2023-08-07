#pragma once
#include "Entity.h"


class Archer : public Entity
{
public:
	char getClass() override;
	int getHealth() override;
	int getMovementSpeed() override;
	int getAttackRange() override;
	int getBuildTime() override;
	int getBuyPrice() override;

	void setHealth(int health) override;
	void setPosition(int posX, int posY) override;

	void attack(Entity* target) override;
	void takeDamage(int damage) override;
	bool isAlive() override;
	virtual ~Archer() {};

private:

	int health;
	Vector2f position;
	const int movementSpeed = 2;
	const int attackRange = 1;
	const int price = 250;
	const int buildTime = 3;
	
};

