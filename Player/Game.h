#pragma once
#include "Entity.h"
#include "Archer.h"
#include "Base.h"
#include "Catapult.h"
#include "Knight.h"
#include "Pikeman.h"
#include "Ram.h"
#include "Swordsman.h"
#include "Worker.h"




class Game
{
public:
	Base playerBase;/**< Obiekt reprezentuj¹cy bazê gracza. */
	Base enemyBase;

	std::vector<std::vector<int>> map; /**< Mapa gry w postaci dwuwymiarowego wektora. */
	std::unordered_map<int, Entity*> PlayerEntities;
	std::unordered_map<int, Entity*> EnemyEntities;
	std::map<int, int> occupiedID;

	Game(std::string _mapa, std::string _status, std::string _rozkazy, std::string _playerNumber)
		: mapFile(_mapa), statusFile(_status), ordersFile(_rozkazy), playerNumberTurn(_playerNumber) {};

	/**
	 * @brief Wczytuje mapê gry z pliku.
	 * @param mapFile Œcie¿ka do pliku z map¹.
	 */
	void loadMap();

	/**
	 * @brief Wczytuje jednostki i bazê z pliku.
	 * @param entitiesFile Œcie¿ka do pliku z danymi jednostek.
	 * @param whichPlayer Numer gracza (1 lub 2).
	 */
	void loadEntities();

	/**
	 * @brief Wczytuje dane bazy z pliku i aktualizuje bazê.
	 * @param baseParameters Parametry bazy w postaci stringa.
	 */
	void loadBase(const std::string baseParameters);

	/**
	 * @brief Wczytuje dane jednostki z pliku i tworzy odpowiedni obiekt.
	 * @param entityParameters Parametry jednostki w postaci stringa.
	 */
	void loadEntity(const std::string entityParameters);

	/**
	 * @brief Tworzy obiekt jednostki na podstawie typu.
	 * @param entityType Typ jednostki.
	 * @return WskaŸnik do obiektu jednostki lub nullptr, jeœli niepowodzenie.
	 */
	Entity* createEntity(char entityType);

	/**
	 * @brief Ustawia parametry jednostki.
	 * @param emptyEntity WskaŸnik do obiektu jednostki.
	 * @param posX Wspó³rzêdna X pozycji jednostki.
	 * @param posY Wspó³rzêdna Y pozycji jednostki.
	 * @param health Zdrowie jednostki.
	 */
	void setEntityParameters(Entity* emptyEntity,int ID, int posX, int posY, int health);

	void setBaseParameters(char player,int ID, int posX, int posY, char entityBuildType);

	/**
	* @brief Generuje rozkazy w grze.
	*/
	void generateOrdersBase(char build_buy, char entityBuildType);

	/**
	 * @brief Generuje rozkazy w grze.
	 */
	void generateOrdersMove(int entityID, char action, int posX, int posY);

	void generateOrdersAttack(int playerEntityID, int enemyEntityID);

	/**
	 * @brief Ustawia numer gracza na podstawie parametru.
	 * @param whichPlayer Numer gracza (1 lub 2).
	 */
	void setPlayerChar();

	/**
	 * @brief Zwraca numer bazy gracza.
	 * @return Numer bazy gracza (P lub E).
	 */
	char getBaseNumber();

	/**
	 * @brief Zakupuje jednostkê w grze.
	 */
	void buyEntity(char typeBuyedEntity);

	/**
	 * @brief Buduje jednostkê w grze.
	 */
	void buildEntity(char typeBuildEntity);

	int creatorID();

	std::pair<int, int> maxDistancePoint(int startX, int startY, int maxMoves);
	
	int distaneBetweenBaseAndAttacker(Entity* attacker);

	void buildRandomEntity();
	

	void buyRandomEntity();
	

	void moveWithAllEntity();
	

	void attackWithAllEntity();

	/**
	* @brief Glowny algorytm odpowiadajacy za autonomiczne dzialanie programu.
	* Planowanie ruchu jednostek, budowa jednostek, atak na wroga.
	*/
	void mainAlgorithm();

private:

	char PlayerBaseChar=' ';
	char EnemyBaseChar=' ';
	int baseUniqueID=-1;

	std::string mapFile;
	std::string statusFile;
	std::string ordersFile;
	std::string playerNumberTurn;

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

	std::unordered_map<int, char> entityTypesForBuildOrBuy =
	{
		{0, 'K'},
		{1, 'S'},
		{2, 'A'},
		{3, 'P'},
		{4, 'C'},
		{5, 'C'},
		{6, 'W'},
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


	std::unordered_map<char, std::function<Entity* ()>> entityCreators =
	{
		{'K', [] { return new Knight; }},
		{'S', [] { return new Swordsman; }},
		{'A', [] { return new Archer; }},
		{'P', [] { return new Pikeman; }},
		{'R', [] { return new Ram; }},
		{'C', [] { return new Catapult; }},
		{'W', [] { return new Worker; }},
	};
};
