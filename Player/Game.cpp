#include "pch.h"
#include "Game.h"

void Game::loadMap()
{
	std::ifstream inputFile(this->mapFile);

	if (!inputFile.is_open())
	{
		std::cout << "Nie mo¿na otworzyæ pliku." << std::endl;
		throw std::runtime_error("Nie udalo sie wczytac mapy");
	}

	unsigned int lineCounter = 0; //Zmienna pomocnicza do iterowania po vectorze
	std::string line;

	while (std::getline(inputFile, line))
	{
		this->map.push_back({}); //Dodanie pustego vectora do naszego vectora vectorow

		for (char c : line)
		{
			if (!std::isdigit(c)) //Sprawdzenie czy wczytana wartosc jest liczba, jezeli nie jest to wystapi blad
			{
				throw std::runtime_error("w pliku mapy znaleziono niedozwolony znak");
			}

			this->map[lineCounter].push_back(c - '0'); //Dodanie wartosci do naszego pustego vectora
		}

		lineCounter++;
	}

	inputFile.close();

}

void Game::loadEntities()
{
	setPlayerChar(); //Ustawienie czy gra gracz 'P' czy 'E'.

	std::ifstream inputFile(this->statusFile);

	if (!inputFile.is_open())
	{
		std::cout << "Nie mo¿na otworzyæ pliku." << std::endl;
		throw std::runtime_error("Nie udalo sie odtworzyc pliku status.txt");
	}

	std::string goldLine; //Zmienna pomocnicza do wczytania ilosci golda.
	long gold = 0; //Zmienna pomocnicza do przekonwertowania stringa na longa .

	if (std::getline(inputFile, goldLine))
	{
		try
		{
			gold = std::stol(goldLine); //Proba konwertowania.
		}
		catch (const std::invalid_argument& e)
		{
			throw std::runtime_error("Blad, nieprawidlowy argument. Wartosc wczytana to nie liczba");
		}
		catch (const std::out_of_range& e)
		{
			throw std::runtime_error("Blad, przekroczono zasieg dla wartosci typu long");
		}

		playerBase.setGold(gold); //Ustawiamy ile posiadamy golda.
		
	}

	std::string line;
	int baseLine = 0; //Zmienna pomocnicza ktora bedzie nam mowic czy wczytalismy juz baze.


	while (std::getline(inputFile, line))
	{
		if (baseLine < 2) //Linia w ktorej wczytamy baze.
		{
			loadBase(line);
			baseLine++;
		}
		else  //Linie w ktorych wczytamy wszystkie inne jednostki.
		{
			loadEntity(line);
		}
	}
	inputFile.close();
}

void Game::loadBase(const std::string baseParameters)
{
	//Ponizej zmienne pomocnicze ktore wczytamy z lini.
		//Wiemy ze dane z pliku wygladaja w ten sposob : P B 10 0 0 98 A 
		// P lub E na pierwszym miejscu - baza nasza lub przeciwnika 
		// B - obiekt typu 'baza'
		// 10 - unikalne ID jednostki 
		// 0 0 - polozenie x y
		// 98 - wytrzymalosc bazy 
		// A - w trakcie budowania jednostki 'A' (do wyboru budowanie innych jednostek np:'S', 'W', 'P' itd)

	std::istringstream iss(baseParameters);
	char tmpPlayer = '-';
	char tmpBase = '-';
	int uniqueID = 0;
	int posX = 0;
	int posY = 0;
	int health = 0;
	char entityBuildType = '-';

	iss >> tmpPlayer >> tmpBase >> uniqueID >> posX >> posY >> health >> entityBuildType;

	setBaseParameters(tmpPlayer,uniqueID, posX, posY, entityBuildType);
	occupiedID[uniqueID] = uniqueID;
}

void Game::loadEntity(const std::string entityParameters)
{
	//Ponizej zmienne pomocnicze ktore wczytamy z lini.
		//Wiemy ze dane z pliku wygladaja w ten sposob : P K 13 20 10 5  
		// P lub E na pierwszym miejscu - jednostka nasza lub przeciwnika 
		// K - obiekt typu 'knight' (jeszcze do wyboru inne typy np: 'S', 'W', 'P' itd)
		// 13 - unikalne ID jednostki 
		// 20 10 - polozenie x y
		// 5 - wytrzymalosc jednostki 

	std::istringstream iss(entityParameters);
	char tmpPlayer = '-';
	char entityType = '-';
	int uniqueID = 0;
	int posX = 0;
	int posY = 0;
	int health = 0;
	iss >> tmpPlayer >> entityType >> uniqueID >> posX >> posY >> health;

	if (entityParameters[0] == PlayerBaseChar) //Srawdzamy czy wczytalismy linie z nasza jednostka.
	{
		Entity* emptyEntity = createEntity(entityType);

		if (emptyEntity)
		{
			setEntityParameters(emptyEntity, uniqueID, posX, posY, health);
			PlayerEntities[emptyEntity->getEntityUniqueID()] = emptyEntity;
			occupiedID[uniqueID] = uniqueID;
		}
	}

	else //Wczytanie jednostki wroga
	{
		Entity* emptyEntity = createEntity(entityType);

		if (emptyEntity)
		{
			setEntityParameters(emptyEntity,uniqueID, posX, posY, health);
			EnemyEntities[emptyEntity->getEntityUniqueID()] = emptyEntity;
			occupiedID[uniqueID] = uniqueID;
		}
	}
}

Entity* Game::createEntity(char entityType)
{
	if (entityCreators.find(entityType) != entityCreators.end()) //Sprawdzenie czy mozemy stworzyc jednostke o danym typie.
	{
		return entityCreators[entityType](); //Tworzenie danej jednostki.
	}
	return nullptr;

}

void Game::setEntityParameters(Entity* emptyEntity,int ID, int posX, int posY, int health)
{
	emptyEntity->setEntityUniqueID(ID);
	emptyEntity->setPosition(posX, posY);
	emptyEntity->setHealth(health);
}

void Game::setBaseParameters(char Player,int ID, int posX, int posY, char entityBuildType)
{
	if (Player == PlayerBaseChar)
	{
		playerBase.setBaseUniqueID(ID);
		playerBase.setPosition(posX, posY);
		playerBase.setBuildStatus(entityBuildType);
	}
	else if (Player == EnemyBaseChar)
	{
		enemyBase.setBaseUniqueID(ID);
		enemyBase.setPosition(posX, posY);
		enemyBase.setBuildStatus(entityBuildType);
	}
	
}

void Game::generateOrdersBase(char build_pay, char entityBuildType)
{
	std::ofstream ordersFile(this->ordersFile, std::ios::app);

	if (!ordersFile)
	{
		std::cerr << "Nie mozna odtworzyc pliku" << '\n';
	}

	std::string newOrders = std::to_string(playerBase.getBaseUniqueID()) + " " + build_pay + " " + entityBuildType;

	ordersFile << newOrders << '\n';

	ordersFile.close();
}

void Game::generateOrdersMove(int entityID, char action, int posX, int posY)
{
	std::ofstream ordersFile(this->ordersFile, std::ios::app);

	if (!ordersFile)
	{
		std::cerr << "Nie mozna odtworzyc pliku" << '\n';
	}

	std::string newOrders = std::to_string(entityID) + " " + action + " " + std::to_string(posX) + " " + std::to_string(posY);

	ordersFile << newOrders << '\n';

	ordersFile.close();
}

void Game::generateOrdersAttack(int playerEntityID, int enemyEntityID)
{
	std::ofstream ordersFile(this->ordersFile, std::ios::app);

	if (!ordersFile)
	{
		std::cerr << "Nie mozna odtworzyc pliku" << '\n';
	}

	std::string newOrders = std::to_string(playerEntityID) + " " + 'A' + " " + std::to_string(enemyEntityID);

	ordersFile << newOrders << '\n';

	ordersFile.close();
}

void Game::setPlayerChar()
{
	if (playerNumberTurn == "1") //Jesli jestesmy graczem 1 to nasze jednostki beda zaczynaly sie od litery 'P'.
	{
		PlayerBaseChar = 'P';
		EnemyBaseChar = 'E';
	}

	else if (playerNumberTurn == "2") //Jesli jestesmy graczem 2 to nasze jednostki beda zaczynaly sie od litery 'E'.
	{
		PlayerBaseChar = 'E';
		EnemyBaseChar = 'P';
	}
}

void Game::buyEntity(char typeBuyedEntity)
{
	Entity* newEntity = createEntity(typeBuyedEntity);
	setEntityParameters(newEntity, creatorID(), playerBase.getBasePosX(), playerBase.getBasePosY(), entityBirthHealth[typeBuyedEntity]);
	PlayerEntities[creatorID()] = newEntity;
	playerBase.entityCostOfPurchase(entityCost[typeBuyedEntity]);

	generateOrdersBase( 'P', newEntity->getClass());
}

char Game::getBaseNumber()
{
	return this->PlayerBaseChar;
}

void Game::buildEntity(char typeBuildEntity)
{
	playerBase.setBuildStatus(typeBuildEntity);
	generateOrdersBase('B', typeBuildEntity);
}

int Game::creatorID()
{
	int newID = 0;

	if (!occupiedID.empty())
	{
		newID = occupiedID.rbegin()->second + 1;

		while (occupiedID.find(newID) != occupiedID.end())
		{
			newID++;
		}

		occupiedID[newID] = newID;
	}

	return newID;
}

std::pair<int, int> Game::maxDistancePoint(int startX, int startY, int maxMoves) 
{
	int rows = map.size();
	int cols = map[0].size();

	int dx[] = { -1, 1, 0, 0 }; // Przesuniêcia w pionie
	int dy[] = { 0, 0, -1, 1 }; // Przesuniêcia w poziomie

	std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
	std::queue<std::pair<int, int>> q;

	q.push({ startX, startY });
	visited[startX][startY] = true;

	std::pair<int, int> currentPoint = { startX, startY };

	while (!q.empty() && maxMoves >= 0) 
	{
		int levelSize = q.size();

		for (int i = 0; i < levelSize; ++i) 
		{
			int x = q.front().first;
			int y = q.front().second;
			q.pop();

			currentPoint = { x, y };

			if (x == enemyBase.getBasePosX() && y == enemyBase.getBasePosY()) 
			{
				return currentPoint;
			}

			for (int dir = 0; dir < 4; ++dir) 
			{
				int nx = x + dx[dir];
				int ny = y + dy[dir];

				if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && map[nx][ny] != 9 && !visited[nx][ny]) {
					q.push({ nx, ny });
					visited[nx][ny] = true;
				}
			}
		}

		--maxMoves; // Zmniejsz liczbê ruchów
	}

	return currentPoint;
}

void Game::buildRandomEntity()
{
	if (playerBase.isReadyToBuild())
	{
		std::random_device rd;
		std::mt19937 gen(rd()); 
		std::uniform_int_distribution<int> distribution(0, 6); 

		int random_number = distribution(gen); 

		playerBase.setBuildStatus(entityTypesForBuildOrBuy[random_number]);

		generateOrdersBase('B', entityTypesForBuildOrBuy[random_number]);
	}
}

void Game::buyRandomEntity()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distribution(0, 6);

	int random_number = distribution(gen);

	int counter = 0;
	while (counter < 7)
	{
		if (playerBase.isReadyToBuy(entityCost[entityTypesForBuildOrBuy[random_number]]))
		{
			playerBase.entityCostOfPurchase(entityCost[entityTypesForBuildOrBuy[random_number]]);
			generateOrdersBase('P', entityTypesForBuildOrBuy[random_number]);
			break;
		}
		else
		{
			random_number++;

			if (random_number == 7)
			{
				random_number = 0;
			}
		}

		counter++;
	}
}

int Game::distaneBetweenBaseAndAttacker(Entity* attacker)
{
	return std::abs(attacker->getPosX() - enemyBase.getBasePosX()) + std::abs(attacker->getPosY() - enemyBase.getBasePosY());
}

void Game::moveWithAllEntity()
{
	for (const auto& unit : PlayerEntities)
	{
		std::pair<int, int> newPosition;
		newPosition = maxDistancePoint(unit.second->getPosX(), unit.second->getPosY(),unit.second->getMovementSpeed());
		if (newPosition.first != enemyBase.getBasePosX() && newPosition.second != enemyBase.getBasePosY())
		{
			unit.second->setPosition(newPosition.first, newPosition.second);
			generateOrdersMove(unit.second->getEntityUniqueID(), 'M', newPosition.first, newPosition.second);
		}
	}
}

void Game::attackWithAllEntity()
{
	for (const auto& unit : PlayerEntities)
	{
		int distanceFromEnemyBase;
		distanceFromEnemyBase = distaneBetweenBaseAndAttacker(unit.second);
		if (distanceFromEnemyBase<=unit.second->getAttackRange())
		{
			enemyBase.takeDamage(damageFromEntity[unit.second->getClass()]);
			generateOrdersAttack(unit.second->getEntityUniqueID(),enemyBase.getBaseUniqueID());
		}
	}
}

void Game::mainAlgorithm()
{
	loadMap();
	loadEntities();
	buildRandomEntity();
	buyRandomEntity();
	moveWithAllEntity();
	attackWithAllEntity();
}




