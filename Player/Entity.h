#pragma once

/**
 * @brief Abstrakcyjna klasa bazowa reprezentuj�ca jednostki w grze.
 */
class Entity
{
public:
    /**
     * @brief Zwraca identyfikator klasy jednostki.
     * @return Identyfikator klasy (typ) jednostki.
     */
    virtual char getClass() = 0;

    /**
     * @brief Zwraca aktualne zdrowie jednostki.
     * @return Aktualne zdrowie jednostki.
     */
    virtual int getHealth() = 0;

    /**
     * @brief Zwraca pr�dko�� ruchu jednostki.
     * @return Pr�dko�� ruchu jednostki.
     */
    virtual int getMovementSpeed() = 0;

    /**
     * @brief Zwraca zasi�g ataku jednostki.
     * @return Zasi�g ataku jednostki.
     */
    virtual int getAttackRange() = 0;

    /**
     * @brief Zwraca czas budowy jednostki.
     * @return Czas budowy jednostki.
     */
    virtual int getBuildTime() = 0;

    /**
     * @brief Zwraca cen� zakupu jednostki.
     * @return Cena zakupu jednostki.
     */
    virtual int getBuyPrice() = 0;

    /**
     * @brief Ustawia zdrowie jednostki na podan� warto��.
     * @param health Nowa warto�� zdrowia jednostki.
     */
    virtual void setHealth(int health) = 0;

    /**
     * @brief Ustawia pozycj� jednostki na podanych wsp�rz�dnych.
     * @param posX Wsp�rz�dna X pozycji jednostki.
     * @param posY Wsp�rz�dna Y pozycji jednostki.
     */
    virtual void setPosition(int posX, int posY) = 0;

    /**
     * @brief Atakuje wskazany cel.
     * @param target Cel ataku.
     */
    virtual void attack(Entity* target) = 0;

    /**
     * @brief Otrzymuje zadane obra�enia.
     * @param damage Ilo�� obra�e�.
     */
    virtual void takeDamage(int damage) = 0;

    /**
     * @brief Sprawdza, czy jednostka jest wci�� �ywa.
     * @return true, je�li jednostka �yje; false, je�li nie.
     */
    virtual bool isAlive() = 0;

    /**
     * @brief Wirtualny destruktor.
     */
    virtual ~Entity() {};

protected:
    /**
     * @brief Tablica obra�e� pomi�dzy r�nymi klasami jednostek.
     */
    static constexpr int m_damage_table[7][8] = {
        // K   S   A   P   C   R   W   B
        { 35, 35, 35, 35, 35, 50, 35, 35 }, // K
        { 30, 30, 30, 20, 20, 30, 30, 30 }, // S
        { 15, 15, 15, 15, 10, 10, 15, 15 }, // A
        { 35, 15, 15, 15, 10, 10, 15, 15 }, // P
        { 40, 40, 40, 40 ,40, 40, 40, 50 }, // C
        { 10, 10, 10, 10, 10, 10, 10, 50 }, // R
        { 5,  5,  5,  5,  5,  5,  5,  1  }  // W
    };

    /**
     * @brief Mapa indeks�w jednostek wed�ug ich typ�w.
     */
    const std::map<char, unsigned int> m_unit_index{
        { 'K', 0 },
        { 'S', 1 },
        { 'A', 2 },
        { 'P', 3 },
        { 'C', 4 },
        { 'R', 5 },
        { 'W', 6 },
        { 'B', 7 }
    };
};

