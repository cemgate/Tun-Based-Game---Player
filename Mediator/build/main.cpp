#include <iostream>
#include <cstdlib>
#include <map>
#include <unordered_map>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

std::string program = "MIEJSCE PLIKU NA KOMPUTERZE";
std::string mapa = "MIEJSCE PLIKU NA KOMPUTERZE";
std::string status = "MIEJSCE PLIKU NA KOMPUTERZE";
std::string rozkazy = "MIEJSCE PLIKU NA KOMPUTERZE";
std::string player1 = "1"; //gracz pierwszy
std::string player2 = "2"; //gracz drugi

int goldPlayer1 = 2000;
int goldPlayer2 = 2000;

std::map<int, int> occupiedID;

std::pair<int, int> basePlayer1Position;
std::pair<int, int> basePlayer2Position;

std::pair<int, char> basePlayer1IDandCharType;
std::pair<int, char> basePlayer2IDandCharType;

std::pair<int, int> playersBuildTime;
std::pair<bool, bool> playerIsBuilding = { false,false };
std::pair<char, char> playersBuildingEntityType;
std::pair<int, int> playersBaseHp;


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


void addNewEntityToStatus(std::string newEntityLine);
void cleanOrdersOrStatus(const std::string& file);
void readOrders();
void generateFirstStatus();
void changeBuildStatus(int baseID, char buildEntityType);
void moveEntity(int ID, int posX, int posY);
void attackBase(int damage, int attackedBaseID);
bool checkWin(int damage, int IDbaseToLose);
int creatorID();
void updateBuilding();
void helpClean(int& baseID, char& actionType, char& entityTypeToBuildOrBuy, int& moveX, int& moveY, int& attackedBaseID, int& attackedEntityID);
void rewriteStatusToOppositePlayer(int goldLineToChange);
void all();


//Zrobione
void addNewEntityToStatus(std::string newEntityLine)
{
	std::ofstream outputFile(status, std::ios::app);

	if (!outputFile)
	{
		std::cerr << "Nie można otworzyć pliku." << std::endl;
		exit(0);
	}

	outputFile << newEntityLine << std::endl;

	outputFile.close();

}

//zrobione
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
				basePlayer1Position.first = rowCount;
				basePlayer1Position.second = columnCount;
			}

			if (c == '2')
			{
				basePlayer2Position.first = rowCount;
				basePlayer2Position.second = columnCount;
			}

			columnCount++;
		}

		columnCount = 0;
		rowCount++;
	}
}

//Zrobione
void generateFirstStatus()
{
	readMap();
	std::ofstream outputFile(status, std::ios::app);

	std::string firstBaseStatus = "P B 10 " + std::to_string(basePlayer1Position.first) + " " + std::to_string(basePlayer1Position.second) + " 100 0";
	std::string secondBaseStatus = "E B 12 " + std::to_string(basePlayer2Position.first) + " " + std::to_string(basePlayer2Position.second) + " 100 0";

	basePlayer1IDandCharType.first = 10;
	basePlayer1IDandCharType.second = 'P';

	basePlayer2IDandCharType.first = 12;
	basePlayer2IDandCharType.second = 'E';

	playersBaseHp.first = 100;
	playersBaseHp.second = 100;

	occupiedID[10] = 10;
	occupiedID[12] = 12;

	if (!outputFile)
	{
		std::cerr << "Nie można otworzyć pliku." << std::endl;
		exit(0);
	}

	outputFile << goldPlayer1 << std::endl;
	outputFile << firstBaseStatus << std::endl;
	outputFile << secondBaseStatus << std::endl;

	outputFile.close();
}

//ZROBIONE
void cleanOrdersOrStatus(const std::string& file)
{
	std::ofstream outputFile(file, std::ios::trunc); // Otwórz plik w trybie wyczyszczenia

	if (!outputFile.is_open())
	{
		std::cerr << "Could not open the file." << std::endl;
	}

	// Plik jest otwarty w trybie wyczyszczenia, więc zawartość zostanie usunięta

	outputFile.close();
}

//zrobione
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
	int attackedBaseID = 0;
	int totaldmg = 0;
	int damagedBase = 0;

	while (std::getline(ordersFile, line))
	{
		std::istringstream issMove(line);
		std::istringstream issBuyBuild(line);
		std::istringstream  issAttack(line);


		if (issMove >> baseID >> actionType >> moveX >> moveY) // poruszanie jednostka  
		{
			moveEntity(baseID, moveX, moveY);
			continue;
		}

		helpClean(baseID, actionType, entityTypeToBuildOrBuy, moveX, moveY, attackedBaseID, attackingEntityID);

		if (issBuyBuild >> baseID >> actionType >> entityTypeToBuildOrBuy) //Budowanie lub kupowanie jednostki
		{

			if (actionType == 'P')
			{
				std::string tmpStatusLine;
				int tmpID = creatorID();

				if (basePlayer1IDandCharType.first == baseID)
				{
					goldPlayer1 -= entityCost[entityTypeToBuildOrBuy];
					tmpStatusLine = std::string(1, basePlayer1IDandCharType.second) + " "
						+ std::string(1, entityTypeToBuildOrBuy) + " "
						+ std::to_string(tmpID) + " "
						+ std::to_string(basePlayer1Position.first) + " "
						+ std::to_string(basePlayer1Position.second) + " "
						+ std::to_string(entityBirthHealth[entityTypeToBuildOrBuy]);

					addNewEntityToStatus(tmpStatusLine);
					continue;
				}

				else
				{
					goldPlayer2 -= entityCost[entityTypeToBuildOrBuy];
					tmpStatusLine = std::string(1, basePlayer2IDandCharType.second) + " "
						+ std::string(1, entityTypeToBuildOrBuy) + " "
						+ std::to_string(tmpID) + " "
						+ std::to_string(basePlayer2Position.first) + " "
						+ std::to_string(basePlayer2Position.second) + " "
						+ std::to_string(entityBirthHealth[entityTypeToBuildOrBuy]);

					addNewEntityToStatus(tmpStatusLine);
					continue;
				}
			}

			if (actionType == 'B')
			{

				std::cout << "BUDUJEMY\n";
				if (basePlayer1IDandCharType.first == baseID)
				{
					changeBuildStatus(basePlayer1IDandCharType.first, entityTypeToBuildOrBuy);
					continue;
				}
				else
				{
					changeBuildStatus(basePlayer2IDandCharType.first, entityTypeToBuildOrBuy);
					continue;
				}
			}

		}

		helpClean(baseID, actionType, entityTypeToBuildOrBuy, moveX, moveY, attackedBaseID, attackingEntityID);

		if (issAttack >> attackingEntityID >> actionType >> attackedBaseID) //zadawanie dmg bazie
		{
			totaldmg += damageFromEntity[actionType];
			damagedBase = attackedBaseID;
		}

		else
		{
			// Niepowodzenie w odczycie, nieznany format linii
			std::cerr << "Nieznany format linii: " << line << std::endl;
		}
	}

	if (totaldmg > 0)
	{
		attackBase(totaldmg, attackedBaseID);
	}

	ordersFile.close();
}

//zrobione
void helpClean(int& baseID, char& actionType, char& entityTypeToBuildOrBuy, int& moveX, int& moveY, int& attackedBaseID, int& attackedEntityID)
{
	baseID = 0;
	actionType = ' ';
	entityTypeToBuildOrBuy = ' ';
	moveX = 0;
	moveY = 0;
	attackedBaseID = 0;
	attackedEntityID = 0;
}

//zrobione
void changeBuildStatus(int baseID, char buildEntityType)
{
	if (basePlayer1IDandCharType.first == baseID)
	{
		playersBuildTime.first = entityBuildTime[buildEntityType];
		playersBuildingEntityType.first = buildEntityType;

		if (buildEntityType != '0')
		{
			playerIsBuilding.first = true;
		}
		else
		{
			playerIsBuilding.first = false;
		}
	}
	else
	{
		playersBuildTime.second = entityBuildTime[buildEntityType];
		playersBuildingEntityType.second = buildEntityType;

		if (buildEntityType != '0')
		{
			playerIsBuilding.second = true;
		}
		else
		{
			playerIsBuilding.second = false;
		}
	}

	std::ifstream inputFile(status);
	std::vector<std::string> lines;

	if (!inputFile.is_open())
	{
		std::cerr << "Could not open the file." << std::endl;
		return exit(0);
	}

	// Wczytanie linii z pliku do wektora
	std::string line;
	while (getline(inputFile, line))
	{
		int tmpID, tmpposx, tmpposy, health;
		char whichPlayerbase, entityType, entityBuilding;
		std::istringstream iss(line);


		if (iss >> whichPlayerbase >> entityType >> tmpID >> tmpposx >> tmpposy >> health >> entityBuilding)
		{
			if (tmpID == baseID)
			{
				std::string baseLine = std::string(1, whichPlayerbase) + " "
					+ std::string(1, entityType) + " "
					+ std::to_string(tmpID) + " "
					+ std::to_string(tmpposx) + " "
					+ std::to_string(tmpposy) + " "
					+ std::to_string(health) + " "
					+ std::string(1, buildEntityType);
				lines.push_back(baseLine);
			}
			else
			{
				lines.push_back(line);
			}
		}
		else
		{
			lines.push_back(line);
		}
	}
	inputFile.close();



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

//zrobione
void moveEntity(int ID, int posX, int posY)
{
	std::ifstream inputFile(status);
	std::vector<std::string> lines;

	if (!inputFile.is_open())
	{
		std::cerr << "Could not open the file." << std::endl;
		return exit(0);
	}

	// Wczytanie linii z pliku do wektora
	std::string line;
	while (getline(inputFile, line))
	{
		int tmpID, tmpposx, tmpposy, health;
		char whichPlayerbase, entityType;
		std::istringstream iss(line);


		iss >> whichPlayerbase >> entityType >> tmpID >> tmpposx >> tmpposy >> health;

		if (tmpID == ID)
		{
			std::string movedEntity;
			movedEntity = std::string(1, whichPlayerbase) + " " + std::string(1, entityType) + " " + std::to_string(tmpID) + " " + std::to_string(posX) + " " + std::to_string(posY) + " " + std::to_string(health);
			lines.push_back(movedEntity);
		}

		else
		{
			lines.push_back(line);
		}
	}
	inputFile.close();




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

//zrobione
void attackBase(int damage, int attackedBaseID)
{
	if (basePlayer1IDandCharType.first == attackedBaseID)
	{
		playersBaseHp.first -= damage;
	}
	else
	{
		playersBaseHp.second -= damage;
	}

	std::ifstream inputFile(status);
	std::vector<std::string> lines;

	if (!inputFile.is_open())
	{
		std::cerr << "Could not open the file." << std::endl;
		return exit(0);
	}

	// Wczytanie linii z pliku do wektora
	std::string line;
	while (getline(inputFile, line))
	{
		int tmpID, tmpposx, tmpposy, health;
		char whichPlayerbase, entityType, entityBuilding;
		std::istringstream iss(line);

		if (iss >> whichPlayerbase >> entityType >> tmpID >> tmpposx >> tmpposy >> health >> entityBuilding)
		{
			if (tmpID == attackedBaseID)
			{
				std::string damageBase = std::string(1, whichPlayerbase) + " "
					+ std::string(1, entityType) + " "
					+ std::to_string(tmpID) + " "
					+ std::to_string(tmpposx) + " "
					+ std::to_string(tmpposy) + " "
					+ std::to_string(health - damage) + " "
					+ std::string(1, entityBuilding);
				lines.push_back(damageBase);
			}


			else
			{
				lines.push_back(line);
			}


		}
		else
		{
			lines.push_back(line);
		}
	}
	inputFile.close();


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

//zaraz zrobie xd
bool checkWin(int damage, int IDbaseToLose)
{
	if (basePlayer1IDandCharType.first == IDbaseToLose)
	{
		playersBaseHp.first -= damage;
		if (playersBaseHp.first < 0)
		{
			std::cout << "wygrywa gracz drugi";
			return true;
		}
	}

	else if (basePlayer1IDandCharType.first == IDbaseToLose)
	{
		playersBaseHp.second -= damage;
		if (playersBaseHp.second < 0)
		{
			std::cout << "wygrywa gracz pierwszy";
			return true;
		}
	}
	return false;
}

//zrobione
void updateBuilding()
{
	if (playerIsBuilding.first)
	{
		playersBuildTime.first = playersBuildTime.first - 1;

		if (playersBuildTime.first == 0)
		{
			std::string newEntity = std::string(1, basePlayer1IDandCharType.second) + " "
				+ std::string(1, playersBuildingEntityType.first) + " "
				+ std::to_string(creatorID()) + " "
				+ std::to_string(basePlayer1Position.first) + " "
				+ std::to_string(basePlayer1Position.second) + " "
				+ std::to_string(entityBirthHealth[playersBuildingEntityType.first]);

			addNewEntityToStatus(newEntity);
			changeBuildStatus(basePlayer1IDandCharType.first, '0');
			std::cout << "skonczone budowanie dla gracza 1\n";
			playerIsBuilding.first = false;
			playersBuildTime.first = 0;
			playersBuildingEntityType.first = '0';
		}
	}

	if (playerIsBuilding.second)
	{
		playersBuildTime.second = playersBuildTime.second - 1;

		if (playersBuildTime.second == 0)
		{
			std::string newEntity = std::string(1, basePlayer2IDandCharType.second) + " "
				+ std::string(1, playersBuildingEntityType.second) + " "
				+ std::to_string(creatorID()) + " "
				+ std::to_string(basePlayer2Position.first) + " "
				+ std::to_string(basePlayer2Position.second) + " "
				+ std::to_string(entityBirthHealth[playersBuildingEntityType.second]);

			addNewEntityToStatus(newEntity);
			changeBuildStatus(basePlayer2IDandCharType.first, '0');
			std::cout << "skonczone budowanie dla gracza 2\n";
			playerIsBuilding.second = false;
			playersBuildTime.second = 0;
			playersBuildingEntityType.second = '0';
		}
	}
}

//zrobione
void rewriteStatusToOppositePlayer(int goldLineToChange)
{
	std::ifstream inputFile(status);
	std::vector<std::string> lines;

	if (!inputFile.is_open())
	{
		std::cerr << "Could not open the file." << std::endl;
		return exit(0);
	}

	// Wczytanie linii z pliku do wektora
	std::string line;
	while (getline(inputFile, line))
	{
		int goldToChange;
		std::istringstream iss(line);


		if (iss >> goldToChange)
		{
			std::string goldLine = std::to_string(goldLineToChange);	
			lines.push_back(goldLine);
		}

		else
		{
			lines.push_back(line);
		}

	}
	inputFile.close();



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

//zrobione
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

void all(int whichPlayerTakesTurn)
{
	readOrders();
	cleanOrdersOrStatus(rozkazy);
	updateBuilding();

	if (whichPlayerTakesTurn == 1)
	{
		rewriteStatusToOppositePlayer(goldPlayer2);
	}
	else
	{
		rewriteStatusToOppositePlayer(goldPlayer1);
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


	while (turnCounter < 100)
	{
		std::cout << "RUCH PLAYER 1\n";
		system(commandPlayer1.c_str()); //odpalenie tury dla gracza pierwszego   
		all(1);
		system(commandPlayer2.c_str()); //odpalenie tury dla gracza drugiego 
		std::cout << "RUCH PLAYER 2\n";
		all(2);
		turnCounter++;
	}

}
