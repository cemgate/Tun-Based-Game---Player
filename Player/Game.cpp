#include "pch.h"
#include "Game.h"

void Game::loadMap(const std::string& mapFile)
{
	std::ifstream inputFile(mapFile);

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

void Game::loadEntities(const std::string& entitiesFile, const std::string playerNumber)
{
	setPlayerNumber(playerNumber); //Ustawienie czy gra gracz 'P' czy 'E'.

	std::ifstream inputFile(entitiesFile); 

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

		base.setGold(gold); //Ustawiamy ile posiadamy golda.
	}

	std::string line;
	bool baseLine = true; //Zmienna pomocnicza ktora bedzie nam mowic czy wczytalismy juz baze.


	while (std::getline(inputFile, line))
	{
		if (line[0] == baseNumber && baseLine) //Linia w ktorej wczytamy baze.
		{
			loadMap(entitiesFile);
		}
		else if (line[0] == baseNumber) //Linie w ktorych wczytamy wszystkie inne jednostki.
		{
			loadEntities(entitiesFile,playerNumber);
		}
	}

	inputFile.close();
}

void Game::loadBase(const std::string baseParameters)
{
	if (baseParameters[0] == baseNumber) // sprawdzenie czy wczytalismy linie z nasza baza.
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

		base.setHealth(health);
		base.setPosition(posX, posY);
		base.setBuildStatus(entityBuildType);
	}
}

void Game::loadEntity(const std::string entityParameters)
{
	if (entityParameters[0] == baseNumber) //Srawdzamy czy wczytalismy linie z nasza jednostka.
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

		Entity* emptyEntity = createEntity(entityType);

		if (emptyEntity)
		{
			setEntityParameters(emptyEntity, posX,posY,health);
			Entities.push_back(emptyEntity);
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

void Game::setEntityParameters(Entity* emptyEntity, int posX, int posY, int health)
{
	emptyEntity->setPosition(posX, posY);
	emptyEntity->setHealth(health);
}

void Game::setPlayerNumber(std::string playerNumber)
{
	if (playerNumber == "1") //Jesli jestesmy graczem 1 to nasze jednostki beda zaczynaly sie od litery 'P'.
	{
		baseNumber = 'P';
	}

	else if (playerNumber == "2") //Jesli jestesmy graczem 2 to nasze jednostki beda zaczynaly sie od litery 'E'.
	{
		baseNumber = 'E';
	}
}


//todo
void Game::generateOrders()
{
	// to do -> Wygenerowania ruchow na podstawie algorytmu i zapisanie ich do pliku tekstowego. 
}


//todo
void Game::buyEntity() 
{
	//Funkcja pomocnicza do algorytmu ktory bedzie decydowal co zrobic na planszy.
}

char Game::getBaseNumber()
{
	return this->baseNumber;
}


//todo
void Game::buildEntity() 
{
	//Funkcja pomocnicza do algorytmu ktory bedzie decydowal co zrobic na planszy.
}


//todo
void Game::mainAlgorithm() 
{
	//Glowny algorytm do zrobienia
}




