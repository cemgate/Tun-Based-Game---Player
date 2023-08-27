#include <iostream>
#include <cstdlib>
#include <map>
#include <unordered_map>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

const int MAX_TURNS = 100;
long startedGold = 2000;

std::string program = "C:\\Users\\marci\\OneDrive\\Pulpit\\c++\\Player\\x64\\Debug\\Player.exe";
std::string mapa = "C:\\Users\\marci\\OneDrive\\Pulpit\\mapa.txt";
std::string status = "C:\\Users\\marci\\OneDrive\\Pulpit\\status.txt";
std::string rozkazy = "C:\\Users\\marci\\OneDrive\\Pulpit\\rozkazy.txt";
std::string player1 = "1"; //gracz pierwszy
std::string player2 = "2"; //gracz drugi


struct Entity
{
	int health = 0;
	int posX = 0;
	int posY = 0;
	int ID = 0;
	char entityClass = ' ';
	char playerChar = ' ';

	std::string returnEntityStringToStatus()
	{
		std::string newEntity = std::string(1, playerChar) + " "
			+ std::string(1, entityClass) + " "
			+ std::to_string(ID) + " "
			+ std::to_string(posX) + " "
			+ std::to_string(posY) + " "
			+ std::to_string(health);
		return newEntity;

	}
};

struct Base
{
	int health = 200;
	int posX = 0;
	int posY = 0;
	int ID = 0;
	long gold = startedGold;
	char entityClass = 'B';
	char playerChar = ' ';
	char buildingEntity = '0';
	bool isBuildingNow = false;
	int buildTime = 0;

	std::string returnBaseStringToStatus()
	{
		return std::string(1, playerChar) + " "
			+ std::string(1, entityClass) + " "
			+ std::to_string(ID) + " "
			+ std::to_string(posX) + " "
			+ std::to_string(posY) + " "
			+ std::to_string(health) + " "
			+ std::string(1, buildingEntity);
	}
};

std::unordered_map<int, Entity*> entitiesPlayer1;
std::unordered_map<int, Entity*> entitiesPlayer2;
std::pair<Base, Base> bases;
std::vector<std::pair<int, int>> mines;


std::map<int, int> occupiedID;
std::map<int, char> IDandCharEntity;


std::unordered_map<char, int> entityBirthHealth =
{
	{'K', 70},
	{'S', 60},
	{'A', 40},
	{'P', 50},
	{'R', 90},
	{'C', 50},
	{'W', 20},
};

std::unordered_map<char, int> damageFromEntity =
{
	{'K', 35},
	{'S', 30},
	{'A', 15},
	{'P', 10},
	{'R', 50},
	{'C', 50},
	{'W', 1},
};

std::unordered_map<char, int> entityBuildTime =
{
	{'K', 5},
	{'S', 3},
	{'A', 3},
	{'P', 3},
	{'R', 4},
	{'C', 6},
	{'W', 2},
};

std::unordered_map<char, int> entityCost =
{
	{'K', 400},
	{'S', 250},
	{'A', 250},
	{'P', 200},
	{'R', 500},
	{'C', 800},
	{'W', 100},
};

static constexpr int m_damage_table[7][8] =
{
	// K   S   A   P   C   R   W   B
	{ 35, 35, 35, 35, 35, 50, 35, 35 }, // K
	{ 30, 30, 30, 20, 20, 30, 30, 30 }, // S
	{ 15, 15, 15, 15, 10, 10, 15, 15 }, // A
	{ 35, 15, 15, 15, 10, 10, 15, 15 }, // P
	{ 40, 40, 40, 40 ,40, 40, 40, 50 }, // C
	{ 10, 10, 10, 10, 10, 10, 10, 50 }, // R
	{ 5,  5,  5,  5,  5,  5,  5,  1  }  // W
};

std::map<char, unsigned int> m_unit_index
{
	{ 'K', 0 },
	{ 'S', 1 },
	{ 'A', 2 },
	{ 'P', 3 },
	{ 'C', 4 },
	{ 'R', 5 },
	{ 'W', 6 },
	{ 'B', 7 }
};


void readMap();
void generateFirstStatus();
void cleanOrdersOrStatus(const std::string& file);
void readOrders();
void helpClean(int& baseID, char& actionType, char& entityTypeToBuildOrBuy, int& moveX, int& moveY, int& attackEntityID, int& attackingEntityID);
void changeBuildStatus(int baseID, char buildEntityType);
void moveEntity(int ID, int posX, int posY);
void attackEntity(int attackerID, int victimID);
void checkWin();
void updateBuilding(int whichPlayerTakesTurn);
void rewriteStatusToOppositePlayer(int whichPlayerTakesTurn);
int creatorID();
void allActions(int whichPlayerTakesTurn);
void checkWinAfterTurnsEnd();
void workerInMines(int whichPlayerTakesTurn);
void cleanMemory();


void readMap()
{
	std::ifstream mapFile(mapa);

	std::string line;
	int rowCount = 0;  // Licznik spacji
	int columnCount = 0;

	while (std::getline(mapFile, line))
	{
		for (char c : line)
		{
			if (c == '1')
			{
				bases.first.posX = rowCount;
				bases.first.posY = columnCount;
				bases.first.ID = 10;
				bases.first.playerChar = 'P';
			}

			if (c == '2')
			{
				bases.second.posX = rowCount;
				bases.second.posY = columnCount;
				bases.second.ID = 12;
				bases.second.playerChar = 'E';
			}

			if (c == '6')
			{
				mines.push_back(std::make_pair(rowCount, columnCount));
			}

			columnCount++;
		}

		columnCount = 0;
		rowCount++;
	}
}

void generateFirstStatus()
{
	readMap();

	std::ofstream outputFile(status, std::ios::app);

	std::string firstBaseStatus = bases.first.returnBaseStringToStatus();
	std::string secondBaseStatus = bases.second.returnBaseStringToStatus();

	occupiedID[10] = 10;
	occupiedID[12] = 12;

	if (!outputFile)
	{
		std::cerr << "Nie mo¿na otworzyæ pliku." << std::endl;
		exit(0);
	}

	outputFile << startedGold << std::endl;
	outputFile << firstBaseStatus << std::endl;
	outputFile << secondBaseStatus << std::endl;

	outputFile.close();
}

void cleanOrdersOrStatus(const std::string& file)
{
	std::ofstream outputFile(file, std::ios::trunc); // Otwórz plik w trybie wyczyszczenia

	if (!outputFile.is_open())
	{
		std::cerr << "Could not open the file." << std::endl;
	}

	// Plik jest otwarty w trybie wyczyszczenia, wiêc zawartoœæ zostanie usuniêta

	outputFile.close();
}

void readOrders()
{
	std::ifstream ordersFile(rozkazy);

	if (!ordersFile.is_open())
	{
		std::cout << "Unable to open the file" << '\n';
	}

	std::string line;
	std::string tmpOrderLine;


	int baseID = 0;
	char actionType = ' ', entityTypeToBuildOrBuy = ' ';
	int attackingEntityID = 0, moveX = 0, moveY = 0;
	int attackEntityID = 0;
	int totaldmg = 0;
	int damagedBase = 0;

	while (std::getline(ordersFile, line))
	{
		std::cout << "rozkaz -> " << line << "\n";
		std::istringstream issMove(line);
		std::istringstream issBuyBuild(line);
		std::istringstream  issAttack(line);


		if (issMove >> baseID >> actionType >> moveX >> moveY) // poruszanie jednostka  
		{

			moveEntity(baseID, moveX, moveY);
			continue;
		}

		helpClean(baseID, actionType, entityTypeToBuildOrBuy, moveX, moveY, attackEntityID, attackingEntityID);

		if (issBuyBuild >> baseID >> actionType >> entityTypeToBuildOrBuy) //Budowanie lub kupowanie jednostki
		{
			if (actionType == 'B')
			{
				changeBuildStatus(baseID, entityTypeToBuildOrBuy);
				continue;
			}

		}

		helpClean(baseID, actionType, entityTypeToBuildOrBuy, moveX, moveY, attackEntityID, attackingEntityID);

		if (issAttack >> attackingEntityID >> actionType >> attackEntityID) //zadawanie dmg bazie
		{
			attackEntity(attackingEntityID, attackEntityID);
		}

		else
		{
			// Niepowodzenie w odczycie, nieznany format linii
			std::cerr << "Nieznany format linii: " << line << std::endl;
		}
	}

	ordersFile.close();
}

void helpClean(int& baseID, char& actionType, char& entityTypeToBuildOrBuy, int& moveX, int& moveY, int& attackEntityID, int& attackingEntityID)
{
	baseID = 0;
	actionType = ' ';
	entityTypeToBuildOrBuy = ' ';
	moveX = 0;
	moveY = 0;
	attackEntityID = 0;
	attackingEntityID = 0;
}

void changeBuildStatus(int baseID, char buildEntityType)
{
	if (bases.first.ID == baseID)
	{
		bases.first.buildTime = entityBuildTime[buildEntityType];
		bases.first.gold -= entityCost[buildEntityType];
		bases.first.buildingEntity = buildEntityType;

		if (buildEntityType != '0')
		{
			bases.first.isBuildingNow = true;
		}
		else
		{
			bases.first.isBuildingNow = false;
		}
	}

	else
	{
		bases.second.buildTime = entityBuildTime[buildEntityType];
		bases.second.gold -= entityCost[buildEntityType];
		bases.second.buildingEntity = buildEntityType;

		if (buildEntityType != '0')
		{
			bases.second.isBuildingNow = true;
		}
		else
		{
			bases.second.isBuildingNow = false;
		}
	}
}

void moveEntity(int ID, int posX, int posY)
{
	auto it = entitiesPlayer1.find(ID);
	if (it != entitiesPlayer1.end())
	{
		it->second->posX = posX;
		it->second->posY = posY;
	}
	else
	{
		auto it2 = entitiesPlayer2.find(ID);

		if (it2 != entitiesPlayer2.end())
		{
			it2->second->posX = posX;
			it2->second->posY = posY;
		}
	}
}

void attackEntity(int attackerID, int victimID)
{
	if (bases.first.ID == victimID)
	{
		bases.first.health -= m_damage_table[m_unit_index[entitiesPlayer2[attackerID]->entityClass]][7];
	}
	else if (bases.second.ID == victimID)
	{
		bases.second.health -= m_damage_table[m_unit_index[entitiesPlayer1[attackerID]->entityClass]][7];;
	}

	else// odbieranie hp wszystkim innym entity
	{
		auto it = entitiesPlayer1.find(victimID);

		if (it != entitiesPlayer1.end())
		{

			it->second->health = it->second->health - m_damage_table[m_unit_index[IDandCharEntity[attackerID]]][m_unit_index[IDandCharEntity[victimID]]];

		}
		else if (it == entitiesPlayer1.end())
		{
			auto it2 = entitiesPlayer2.find(victimID);

			if (it2 != entitiesPlayer2.end())
			{

				it2->second->health = it2->second->health - m_damage_table[m_unit_index[IDandCharEntity[attackerID]]][m_unit_index[IDandCharEntity[victimID]]];

			}
		}

	}
}

void checkWin()
{
	if (bases.first.health < 0)
	{
		std::cout << "Wygrywa gracz drugi poprzez zniszczenie bazy przeciwnika'\n";
		cleanMemory();
		exit(0);
	}

	if (bases.second.health < 0)
	{
		std::cout << "Wygrywa gracz pierwszy poprzez zniszczenie bazy przeciwnika'\n";
		cleanMemory();
		exit(0);
	}
}

void updateBuilding(int whichPlayerTakesTurn)
{
	if (bases.first.isBuildingNow && whichPlayerTakesTurn==1)
	{
		bases.first.buildTime -= 1;

		if (bases.first.buildTime == 0)
		{
			int newID = creatorID();
			entitiesPlayer1[newID] = new Entity;
			entitiesPlayer1[newID]->ID = newID;
			entitiesPlayer1[newID]->entityClass = bases.first.buildingEntity;
			entitiesPlayer1[newID]->playerChar = bases.first.playerChar;
			entitiesPlayer1[newID]->posX = bases.first.posX;
			entitiesPlayer1[newID]->posY = bases.first.posY;
			entitiesPlayer1[newID]->health = entityBirthHealth[bases.first.buildingEntity];

			IDandCharEntity[newID] = entitiesPlayer1[newID]->entityClass;

			bases.first.isBuildingNow = false;
			bases.first.buildTime = 0;
			bases.first.buildingEntity = '0';
		}
	}

	if (bases.second.isBuildingNow && whichPlayerTakesTurn == 2)
	{
		bases.second.buildTime -= 1;

		if (bases.second.buildTime == 0)
		{
			int newID = creatorID();
			entitiesPlayer2[newID] = new Entity;
			entitiesPlayer2[newID]->ID = newID;
			entitiesPlayer2[newID]->entityClass = bases.second.buildingEntity;
			entitiesPlayer2[newID]->playerChar = bases.second.playerChar;
			entitiesPlayer2[newID]->posX = bases.second.posX;
			entitiesPlayer2[newID]->posY = bases.second.posY;
			entitiesPlayer2[newID]->health = entityBirthHealth[bases.second.buildingEntity];

			IDandCharEntity[newID] = entitiesPlayer2[newID]->entityClass;

			bases.second.isBuildingNow = false;
			bases.second.buildTime = 0;
			bases.second.buildingEntity = '0';
		}
	}
}

void rewriteStatusToOppositePlayer(int whichPlayerTakesTurn)
{
	cleanOrdersOrStatus(status);
	std::vector<std::string> lines;

	if (whichPlayerTakesTurn == 2)
	{
		lines.push_back(std::to_string(bases.first.gold));
		lines.push_back(bases.first.returnBaseStringToStatus());
		lines.push_back(bases.second.returnBaseStringToStatus());
	}

	else if (whichPlayerTakesTurn == 1)
	{
		lines.push_back(std::to_string(bases.second.gold));
		lines.push_back(bases.first.returnBaseStringToStatus());
		lines.push_back(bases.second.returnBaseStringToStatus());
	}

	for (const auto& p1 : entitiesPlayer1)
	{
		if (p1.second->health > 0)
		{
			lines.push_back(p1.second->returnEntityStringToStatus());
		}
	}

	for (const auto& p2 : entitiesPlayer2)
	{
		if (p2.second->health > 0)
		{
			lines.push_back(p2.second->returnEntityStringToStatus());
		}
	}

	// Zapisanie zmodyfikowanych linii z powrotem do pliku
	std::ofstream outputFile(status);
	if (!outputFile.is_open())
	{
		std::cerr << "Could not open the output file." << std::endl;
		exit(0);
	}

	for (const std::string& line : lines)
	{
		outputFile << line << std::endl;
	}
	outputFile.close();
}

int creatorID()
{
	int newID = 0;

	if (!occupiedID.empty()) // Check if
	{
		newID = occupiedID.rbegin()->second + 1; // Create ID one greater in size than the previously built/purchased unit

		while (occupiedID.find(newID) != occupiedID.end()) // Check if a unit with such an ID exists
		{
			newID++; // If yes, increase the counter
		}

		occupiedID[newID] = newID; // If not, set such ID as occupied
	}

	occupiedID[newID] = newID;
	return newID;
}

void workerInMines(int whichPlayerTakesTurn)
{
	if (whichPlayerTakesTurn == 1 && mines.size()!=0)
	{
		for (const auto& unit : entitiesPlayer1)
		{
			if (unit.second->entityClass == 'W')
			{
				for (const auto& minesPosition : mines)
				{
					if (unit.second->posX == minesPosition.first && unit.second->posY == minesPosition.second)
					{
						bases.first.gold += 50;
						break;
					}
				}
			}
		}
	}

	else if(whichPlayerTakesTurn == 2 && mines.size() != 0)
	{
		for (const auto& unit : entitiesPlayer2)
		{
			if (unit.second->entityClass == 'W')
			{
				for (const auto& minesPosition : mines)
				{
					if (unit.second->posX == minesPosition.first && unit.second->posY == minesPosition.second)
					{
						bases.second.gold += 50;
						break;
					}
				}
			}
		}
	}
}

void cleanMemory()
{
	for (const auto& clean : entitiesPlayer1)
	{
		delete clean.second;
	}

	for (const auto& clean : entitiesPlayer2)
	{
		delete clean.second;
	}

}

void allActions(int whichPlayerTakesTurn)
{
	readOrders();
	cleanOrdersOrStatus(rozkazy);
	updateBuilding(whichPlayerTakesTurn);
	workerInMines(whichPlayerTakesTurn);
	rewriteStatusToOppositePlayer(whichPlayerTakesTurn);
	checkWin();
}

void checkWinAfterTurnsEnd()
{
	cleanMemory();

	std::ifstream statusFile(status);
	std::string line;

	int numberOfEnemyOneUnits = 0;
	int numberOfEnemyTwoUnits = 0;

	while (std::getline(statusFile, line))
	{
		if (line[0] == 'P')
		{
			numberOfEnemyOneUnits++;
		}

		if (line[0] == 'E')
		{
			numberOfEnemyTwoUnits++;
		}
	}

	std::cout << "KONIEC ROZGRYWKI, WYGRA GRACZ Z WIEKSZA ILOSCIA WOJSK!!!!!'\n";

	if (numberOfEnemyOneUnits > numberOfEnemyTwoUnits)
	{
		std::cout << "Wygrywa gracz pierwszy ktory zgromadzil: " << numberOfEnemyOneUnits << " liczbe wojsk, gracz drugi posiada: " << numberOfEnemyTwoUnits << " jednostek.'\n";
		exit(0);
	}
	else if(numberOfEnemyOneUnits < numberOfEnemyTwoUnits)
	{
		std::cout << "Wygrywa gracz drugi ktory zgromadzil: " << numberOfEnemyTwoUnits << " liczbe wojsk, gracz pierwszy posiada: " << numberOfEnemyOneUnits << " jednostek.'\n";
		exit(0);
	}
	else if (numberOfEnemyOneUnits == numberOfEnemyTwoUnits)
	{
		std::cout << "REMIS!!!! gracz pierwszy ktory zgromadzil: " << numberOfEnemyOneUnits << " liczbe wojsk, gracz drugi posiada: " << numberOfEnemyTwoUnits << " jednostek.'\n";
		exit(0);
	}
}


int main()
{
	int turnCounter = 0;

	cleanOrdersOrStatus(rozkazy);
	cleanOrdersOrStatus(status);
	generateFirstStatus();

	std::string commandPlayer1 = program + " " + mapa + " " + status + " " + rozkazy + " " + player1;
	std::string commandPlayer2 = program + " " + mapa + " " + status + " " + rozkazy + " " + player2;


	while (turnCounter < MAX_TURNS)
	{
		std::cout << "ruch plaeyr 1\n";
		system(commandPlayer1.c_str()); //odpalenie tury dla gracza pierwszego   
		allActions(1);

		std::cout << "ruch plaeyr 2\n";
		system(commandPlayer2.c_str()); //odpalenie tury dla gracza drugiego 
		allActions(2);

		turnCounter++;
	}


	checkWinAfterTurnsEnd();

}
