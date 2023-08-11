#include <iostream>
#include <cstdlib>
#include <map>
#include <unordered_map>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

std::string program = "C:\\Users\\marci\\OneDrive\\Pulpit\\c++\\Player\\x64\\Debug\\Player.exe";
std::string mapa = "C:\\Users\\marci\\OneDrive\\Pulpit\\mapa.txt";
std::string status = "C:\\Users\\marci\\OneDrive\\Pulpit\\status.txt";
std::string rozkazy = "C:\\Users\\marci\\OneDrive\\Pulpit\\rozkazy.txt";
std::string player1 = "1"; //gracz pierwszy
std::string player2 = "2"; //gracz drugi






std::map<int, int> occupiedID;
std::pair<int, int> basePlayer1Position;
std::pair<int, int> basePlayer2Position;
std::pair<int, char> basePlayer1IDandCharType;
std::pair<int, char> basePlayer2IDandCharType;
std::pair<int, int> playersBuildTime;
std::pair<int, int> playersBuilingEntityType;
std::pair<int, int> playersBaseHp = { 100,100 };
std::pair<int, int> playerStartedGold = { 2000,2000 };

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

void addNewEntityToStatus(std::string newEntityLine);
void cleanOrders();
void firstReadFile();
void readOrders();
void changeBuildStatus(int baseID, char buildEntityType);
void moveEntity(int ID, int posX, int posY);
void attackBase(int damage, int attackedBaseID);
bool checkWin(int damage, int IDbaseToLose);
int creatorID();
void all();





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

void firstReadFile()
{
	std::ifstream statusFile(status);
	
	if (!statusFile.is_open())
	{
		std::cout << "Unable to open the file" << '\n';
	}

	std::string line;
	std::string tmpOrderLine;


	int ID=0;
	char charTypePlayer, charBase,buildingEntity;
	int intValue1, intValue2,intValue3,intValue4;
	int counter = 0;

	while (std::getline(statusFile, line) && counter<=2)
	{
		std::string tmpline;
		std::istringstream iss(line);
		if(counter==1)
		{
			iss >> charTypePlayer >> charBase >> intValue1 >> intValue2 >> intValue3 >> intValue4 >>buildingEntity;
			basePlayer1IDandCharType.first = intValue1;
			basePlayer1IDandCharType.second = charTypePlayer;
			occupiedID[basePlayer1IDandCharType.first] = basePlayer1IDandCharType.first;
		}
		if (counter == 2)
		{
			iss >> charTypePlayer >> charBase >> intValue1 >> intValue2 >> intValue3 >> intValue4;
			basePlayer2IDandCharType.first = intValue1;
			basePlayer2IDandCharType.second = charTypePlayer;
			occupiedID[basePlayer2IDandCharType.first] = basePlayer2IDandCharType.first;
		}

		counter++;
	}

	statusFile.close();
}

void cleanOrders()
{
	std::ofstream outputFile(rozkazy, std::ios::trunc); // Otwórz plik w trybie wyczyszczenia

	if (!outputFile.is_open()) 
	{
		std::cerr << "Could not open the file." << std::endl;
	}

	// Plik jest otwarty w trybie wyczyszczenia, więc zawartość zostanie usunięta

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


	int ID;
	char charValue1, charValue2=0;
	int int1Value, int2Value;

	while (std::getline(ordersFile, line))
	{
		int totaldmg=0;
		int damagedBase = 0;
		std::istringstream iss(line);
		

		if(sscanf_s(line.c_str(), "%d %c %d %d", &ID, &charValue1, &int1Value,&int2Value)==4)//poruszanie jednostka
		{
			moveEntity(ID, int1Value, int2Value);
		}

		else if (iss >> ID >> charValue1 >> charValue2) //Budowanie lub kupowanie jednostki
		{
			std::cout << charValue1;
			if (charValue1 == 'P')
			{
				std::cout << "siemanko" << '\n';
				std::string tmpStatusLine;
				int tmpID = creatorID();
			
				if (basePlayer1IDandCharType.first == ID)
				{
					tmpStatusLine = basePlayer1IDandCharType.second;
					

					std::cout << tmpStatusLine;
					addNewEntityToStatus(tmpStatusLine);
				}
				else
				{
					tmpStatusLine = basePlayer2IDandCharType.second + " "
						+ std::to_string(charValue2) + " "
						+ std::to_string(tmpID) + " "
						+ std::to_string(basePlayer2Position.first) + " "
						+ std::to_string(basePlayer2Position.second) + " "
						+ std::to_string(entityBirthHealth[charValue2]);
					
					addNewEntityToStatus(tmpStatusLine);
				}
			}

			else if (charValue1 == 'B')
			{
				
				if (basePlayer1IDandCharType.first == ID)
				{
					changeBuildStatus(basePlayer1IDandCharType.first, charValue2);
				}
				else
				{
					changeBuildStatus(basePlayer1IDandCharType.second, charValue2);
				}
			}
		}
		else if(sscanf_s(line.c_str(), "%d %c %d", &ID, &charValue1, &int1Value) == 3) //zadawanie dmg bazie
		{
			
			totaldmg += damageFromEntity[charValue1];
			damagedBase = ID;
		}

		else
		{
			// Niepowodzenie w odczycie, nieznany format linii
			std::cerr << "Nieznany format linii: " << line << std::endl;
		}


		if (totaldmg > 0)
		{
			checkWin(totaldmg, damagedBase);
			attackBase(totaldmg, damagedBase);
		}


	}

	ordersFile.close();
}

void changeBuildStatus(int baseID, char buildEntityType)
{
	std::ifstream inputFile(status);
	std::vector<std::string> lines;

	if (!inputFile.is_open()) {
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
		iss >> whichPlayerbase >> entityType >> tmpID >> tmpposx >> tmpposy >> health >> entityBuilding;

		if ((iss >> whichPlayerbase >> entityType >> tmpID >> tmpposx >> tmpposy >> health >> entityBuilding) && tmpID == baseID)
		{
			std::string damageBase = std::to_string(whichPlayerbase) + " " + std::to_string(entityType) + " " + std::to_string(tmpID) + " " + std::to_string(tmpposx) + " " + std::to_string(tmpposy) + " " + std::to_string(health) + " " + std::to_string(buildEntityType);
			lines.push_back(damageBase);
		}
		else
		{
			lines.push_back(line);
		}
	}
	inputFile.close();



	// Zapisanie zmodyfikowanych linii z powrotem do pliku
	std::ofstream outputFile("output.txt");
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

void moveEntity(int ID, int posX, int posY)
{
	std::ifstream inputFile(status);
	std::vector<std::string> lines;

	if (!inputFile.is_open()) {
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

		if (tmpID = ID)
		{
			std::string movedEntity;
			movedEntity = std::to_string(whichPlayerbase) + " " + std::to_string(entityType) + " "  + std::to_string(tmpID) + " " + std::to_string(posX) + " " + std::to_string(posY) + " " + std::to_string(health);
			lines.push_back(movedEntity);
		}
		else
		{
			lines.push_back(line);
		}
	}
	inputFile.close();

	

	// Zapisanie zmodyfikowanych linii z powrotem do pliku
	std::ofstream outputFile("output.txt");
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

void attackBase(int damage, int attackedBaseID)
{
	std::ifstream inputFile(status);
	std::vector<std::string> lines;

	if (!inputFile.is_open()) {
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
		iss >> whichPlayerbase >> entityType >> tmpID >> tmpposx >> tmpposy >> health >> entityBuilding;

		if ((iss >> whichPlayerbase >> entityType >> tmpID >> tmpposx >> tmpposy >> health >> entityBuilding) && tmpID == attackedBaseID)
		{
			std::string damageBase = std::to_string(whichPlayerbase) + " " + std::to_string(entityType) + " " + std::to_string(tmpID) + " " + std::to_string(tmpposx) + " " + std::to_string(tmpposy) + " " + std::to_string(health - damage) + " " + std::to_string(entityBuilding);
			lines.push_back(damageBase);
		}
		else
		{
			lines.push_back(line);
		}
	}
	inputFile.close();

	checkWin(damage, attackedBaseID);



	// Zapisanie zmodyfikowanych linii z powrotem do pliku
	std::ofstream outputFile("output.txt");
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

bool checkWin(int damage, int IDbaseToLose)
{
	if (basePlayer1IDandCharType.first== IDbaseToLose)
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

void all()
{
	readOrders();
	cleanOrders();
}





int main()
{
	int turnCounter = 0;


	firstReadFile();
	std::string commandPlayer1 = program + " " + mapa + " " + status + " " + rozkazy + " " + player1;
	std::string commandPlayer2 = program + " " + mapa + " " + status + " " + rozkazy + " " + player2;


	while (turnCounter < 2)
	{
		system(commandPlayer1.c_str()); //odpalenie tury dla gracza pierwszego   
		all();
		system(commandPlayer2.c_str()); //odpalenie tury dla gracza drugiego  
		all();
		turnCounter++;
	}
}
