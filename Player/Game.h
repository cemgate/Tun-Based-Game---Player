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

/**
 * @brief Class representing the game.
 */
class Game
{
public:
	/**
	 * @brief Object representing the player's base.
	 */
	Base playerBase;

	/**
	 * @brief Object representing the enemy's base.
	 */
	Base enemyBase;

	/**
	 * @brief Game map in the form of a two-dimensional vector.
	 */
	std::vector<std::vector<int>> map;

	/**
	 * @brief Hash map storing player's entities by ID.
	 */
	std::unordered_map<int, Entity*> PlayerEntities;

	/**
	 * @brief Hash map storing enemy's entities by ID.
	 */
	std::unordered_map<int, Entity*> EnemyEntities;

	/**
	 * @brief Map storing occupied IDs.
	 */
	std::map<int, int> occupiedID;

	/**
	 * @brief Constructor for the Game class.
	 * @param _mapa Path to the map file.
	 * @param _status Path to the status file.
	 * @param _rozkazy Path to the orders file.
	 * @param _playerNumber Player's number (1 or 2).
	 */
	Game(std::string _mapa, std::string _status, std::string _rozkazy, std::string _playerNumber)
		: mapFile(_mapa), statusFile(_status), ordersFile(_rozkazy), playerNumberTurn(_playerNumber) {};

	/**
	 * @brief Loads the game map from a file.
	 */
	void loadMap();

	/**
	 * @brief Loads entities and bases from a file.
	 */
	void loadEntities();

	/**
	 * @brief Loads base data from a file and updates the base.
	 * @param baseParameters Parameters of the base as a string.
	 */
	void loadBase(const std::string baseParameters);

	/**
	 * @brief Loads entity data from a file and creates the corresponding object.
	 * @param entityParameters Parameters of the entity as a string.
	 */
	void loadEntity(const std::string entityParameters);

	/**
	 * @brief Creates an entity object based on the given entity type.
	 * @param entityType Type of the entity.
	 * @return Pointer to the created entity object, or nullptr on failure.
	 */
	Entity* createEntity(char entityType);

	/**
	 * @brief Sets parameters for an entity.
	 * @param emptyEntity Pointer to the entity object.
	 * @param ID Entity ID.
	 * @param posX X-coordinate of the entity's position.
	 * @param posY Y-coordinate of the entity's position.
	 * @param health Entity's health.
	 */
	void setEntityParameters(Entity* emptyEntity, int ID, int posX, int posY, int health);

	/**
	 * @brief Sets parameters for a base.
	 * @param player Player identifier ('P' or 'E').
	 * @param ID Base ID.
	 * @param posX X-coordinate of the base's position.
	 * @param posY Y-coordinate of the base's position.
	 * @param entityBuildType Type of the entity being built.
	 */
	void setBaseParameters(char player, int ID, int posX, int posY, char entityBuildType);

	/**
	 * @brief Generates build or buy orders for bases.
	 * @param build_buy Action to build or buy ('B' or 'P').
	 * @param entityBuildType Type of the entity to build or buy.
	 */
	void generateOrdersBase(char build_buy, char entityBuildType);

	/**
	 * @brief Generates movement orders for entities.
	 * @param entityID ID of the entity to be moved.
	 * @param action Movement action ('M').
	 * @param posX Target X-coordinate for movement.
	 * @param posY Target Y-coordinate for movement.
	 */
	void generateOrdersMove(int entityID, char action, int posX, int posY);

	/**
	 * @brief Generates attack orders for entities.
	 * @param playerEntityID ID of the attacking entity.
	 * @param enemyEntityID ID of the target enemy entity.
	 */
	void generateOrdersAttack(int playerEntityID, int enemyEntityID);

	/**
	 * @brief Sets the player character based on the player number.
	 */
	void setPlayerChar();

	/**
	 * @brief Returns the base number for the current player.
	 * @return Player's base number ('P' or 'E').
	 */
	char getBaseNumber();

	/**
	 * @brief Purchases an entity in the game.
	 * @param typeBuyedEntity Type of entity to buy.
	 */
	void buyEntity(char typeBuyedEntity);

	/**
	 * @brief Builds an entity in the game.
	 * @param typeBuildEntity Type of entity to build.
	 */
	void buildEntity(char typeBuildEntity);

	/**
	 * @brief Generates a unique creator ID for entities.
	 * @return Unique creator ID.
	 */
	int creatorID();

	/**
	 * @brief Calculates the maximum point reachable from a starting point.
	 * @param startX Starting X-coordinate.
	 * @param startY Starting Y-coordinate.
	 * @param maxMoves Maximum number of moves.
	 * @return Pair of X and Y coordinates representing the reachable point.
	 */
	std::pair<int, int> maxDistancePoint(int startX, int startY, int maxMoves);

	/**
	 * @brief Calculates the distance between the enemys's base and an attacking entity.
	 * @param attacker Pointer to the attacking entity.
	 * @return Distance between the enemy's base and the attacker.
	 */
	int distaneBetweenBaseAndAttacker(Entity* attacker);

	/**
	 * @brief Builds a random entity based on predefined probabilities.
	 */
	void buildRandomEntity();

	/**
	 * @brief Purchases a random entity based on predefined probabilities.
	 */
	void buyRandomEntity();

	/**
	 * @brief Moves all entities on the map.
	 */
	void moveWithAllEntity();

	/**
	 * @brief Initiates attacks with all player's entities.
	 */
	void attackWithAllEntity();

	/**
	 * @brief Main algorithm responsible for autonomous game behavior.
	 *        It handles movement planning, entity building, and enemy attack.
	 */
	void mainAlgorithm();

private:
	/**
	* @brief Character representing the player's base.
	*/
	char PlayerBaseChar = ' ';

	/**
	 * @brief Character representing the enemy's base.
	 */
	char EnemyBaseChar = ' ';

	/**
	 * @brief Unique identifier for the bases.
	 */
	int baseUniqueID = -1;

	/**
	 * @brief Path to the file containing the game's map.
	 */
	std::string mapFile;

	/**
	 * @brief Path to the file containing the game's status.
	 */
	std::string statusFile;

	/**
	 * @brief Path to the file containing the game's orders.
	 */
	std::string ordersFile;

	/**
	 * @brief Player number turn ('1' or '2').
	 */
	std::string playerNumberTurn;

	/**
	 * @brief Mapping of damage dealt by different entities.
	 */
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

	/**
	 * @brief Mapping of entity types for build or buy actions.
	 */
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

	/**
	 * @brief Mapping of entity costs.
	 */
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

	/**
	 * @brief Mapping of entity birth health.
	 */
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

	/**
	 * @brief Mapping of entity creators for different types.
	 */
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


