#include "pch.h"
#include "Game.h"
#include "Entity.h"
#include "Knight.h"
#include "Archer.h"

int main(int argc, char* argv[])
{
    //Game game; //stworzenie obiektu game, nim bedziemy sterowac
    
    if (argc >= 2) 
    {
        Game game(argv[1], argv[2], argv[3], argv[4]);
        std::string mapa = argv[1]; //string ze sciezka do pliku mapa.txt
        std::string status = argv[2]; //string ze sciezka do pliku status.txt
        std::string rozkazy = argv[3]; //string ze sciezka do pliku rozkazy.txt
        std::string playerNumber = argv[4]; //string z informacja ktorym jestesmy graczem
        try
        {
            //std::cout << game.playerBase.getGold() << '\n';
            game.mainAlgorithm();
            //std::cout << game.playerBase.getGold() << '\n';
        }
        catch (const std::exception& e)
        {
            std::cout << "Wystapil wyjatek:" << e.what() << '\n';
            return 1;
        }
    }

    else 
    {
        std::cout << "Brak przekazanego argumentu." << std::endl;
    }
}