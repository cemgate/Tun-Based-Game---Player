#pragma once
#include "Entity.h"

class Base
{
public:

	long getGold();
	int getHealth();
	int getBaseUniqueID();
	int getBasePosX();
	int getBasePosY();

	void setGold(long gold);
	void setHealth(int health);
	void setPosition(int x, int y);
	void setBuildStatus(char entityType);
	void setBaseUniqueID(int ID);

	void takeDamage(int damage);
	void entityCostOfPurchase(int cost);
	bool isAlive();
	bool isReadyToBuy(int cost);
	bool isReadyToBuild();
	~Base() {};

private:

	int baseUniqueID=-1;
	long gold;
	int health;	
	Vector2f position;
	bool isReadyToBuildEntity=true;
	char buildingEntity;
};

