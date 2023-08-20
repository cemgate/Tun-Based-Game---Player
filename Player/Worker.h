#pragma once
#include "Entity.h"

class Worker : public Entity
{
public:
	char getClass() override;
	int getHealth() override;
	int getMovementSpeed() override;
	int getAttackRange() override;
	int getBuildTime() override;
	int getBuyPrice() override;
	int getEntityUniqueID() override;
	int getPosX() override;
	int getPosY() override;

	void setHealth(int health) override;
	void setPosition(int posX, int posY) override;
	void setEntityUniqueID(int ID) override;

	void attack(Entity* target) override;
	void takeDamage(int damage) override;
	bool isAlive() override;
	virtual ~Worker() {};

private:

	int uniqueID;
	int health;
	Vector2f position;
	const int movementSpeed = 2;
	const int attackRange = 1;
	const int price = 100;
	const int buildTime = 2;
};
