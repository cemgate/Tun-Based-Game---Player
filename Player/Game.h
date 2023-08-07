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
    Base base; /**< Obiekt reprezentuj�cy baz� gracza. */
    std::vector<std::vector<int>> map; /**< Mapa gry w postaci dwuwymiarowego wektora. */
    std::vector<Entity*> Entities; /**< Wektor przechowuj�cy wska�niki do jednostek w grze. */

    /**
     * @brief Wczytuje map� gry z pliku.
     * @param mapFile �cie�ka do pliku z map�.
     */
    void loadMap(const std::string& mapFile);

    /**
     * @brief Wczytuje jednostki i baz� z pliku.
     * @param entitiesFile �cie�ka do pliku z danymi jednostek.
     * @param whichPlayer Numer gracza (1 lub 2).
     */
    void loadEntities(const std::string& entitiesFile, const std::string playerNumber);

    /**
     * @brief Wczytuje dane bazy z pliku i aktualizuje baz�.
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
     * @return Wska�nik do obiektu jednostki lub nullptr, je�li niepowodzenie.
     */
    Entity* createEntity(char entityType);

    /**
     * @brief Ustawia parametry jednostki.
     * @param emptyEntity Wska�nik do obiektu jednostki.
     * @param posX Wsp�rz�dna X pozycji jednostki.
     * @param posY Wsp�rz�dna Y pozycji jednostki.
     * @param health Zdrowie jednostki.
     */
    void setEntityParameters(Entity* emptyEntity, int posX, int posY, int health);

    /**
     * @brief Generuje rozkazy w grze.
     */
    void generateOrders();

    /**
     * @brief Ustawia numer gracza na podstawie parametru.
     * @param whichPlayer Numer gracza (1 lub 2).
     */
    void setPlayerNumber(std::string whichPlayer);

    /**
     * @brief Zwraca numer bazy gracza.
     * @return Numer bazy gracza (P lub E).
     */
    char getBaseNumber();

    /**
     * @brief Zakupuje jednostk� w grze.
     */
    void buyEntity();

    /**
     * @brief Buduje jednostk� w grze.
     */
    void buildEntity();

    /**
    * @brief Glowny algorytm odpowiadajacy za autonomiczne dzialanie programu.
    * Planowanie ruchu jednostek, budowa jednostek, atak na wroga.
    */
    void mainAlgorithm();

private:
    char baseNumber; /**< Numer bazy gracza. */

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
