#pragma once
#include "Entity.h"

class Base
{
public:

	long getGold();
	long setGold(long gold);
	int getHealth();
	int setHealth(int health);
	void takeDamage(int damage);
	void setPosition(int x,int y);
	void setBuildStatus(char entityType);
	void buildEntity(char entityType);
	bool isAlive();
	~Base() {};

private:

	long gold;
	int health;	
	Vector2f position;
	bool isBuildingEntity=false;
	char buildingEntity;
};

