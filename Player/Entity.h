#pragma once

/**
 * @brief Abstrakcyjna klasa bazowa reprezentuj¹ca jednostki w grze.
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
     * @brief Zwraca prêdkoœæ ruchu jednostki.
     * @return Prêdkoœæ ruchu jednostki.
     */
    virtual int getMovementSpeed() = 0;

    /**
     * @brief Zwraca zasiêg ataku jednostki.
     * @return Zasiêg ataku jednostki.
     */
    virtual int getAttackRange() = 0;

    /**
     * @brief Zwraca czas budowy jednostki.
     * @return Czas budowy jednostki.
     */
    virtual int getBuildTime() = 0;

    /**
     * @brief Zwraca cenê zakupu jednostki.
     * @return Cena zakupu jednostki.
     */
    virtual int getBuyPrice() = 0;

    /**
     * @brief Ustawia zdrowie jednostki na podan¹ wartoœæ.
     * @param health Nowa wartoœæ zdrowia jednostki.
     */
    virtual void setHealth(int health) = 0;

    /**
     * @brief Ustawia pozycjê jednostki na podanych wspó³rzêdnych.
     * @param posX Wspó³rzêdna X pozycji jednostki.
     * @param posY Wspó³rzêdna Y pozycji jednostki.
     */
    virtual void setPosition(int posX, int posY) = 0;

    /**
     * @brief Atakuje wskazany cel.
     * @param target Cel ataku.
     */
    virtual void attack(Entity* target) = 0;

    /**
     * @brief Otrzymuje zadane obra¿enia.
     * @param damage Iloœæ obra¿eñ.
     */
    virtual void takeDamage(int damage) = 0;

    /**
     * @brief Sprawdza, czy jednostka jest wci¹¿ ¿ywa.
     * @return true, jeœli jednostka ¿yje; false, jeœli nie.
     */
    virtual bool isAlive() = 0;

    /**
     * @brief Wirtualny destruktor.
     */
    virtual ~Entity() {};

protected:
    /**
     * @brief Tablica obra¿eñ pomiêdzy ró¿nymi klasami jednostek.
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
     * @brief Mapa indeksów jednostek wed³ug ich typów.
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

