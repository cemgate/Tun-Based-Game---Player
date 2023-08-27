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
        
        try
        {
            game.mainAlgorithm();  
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