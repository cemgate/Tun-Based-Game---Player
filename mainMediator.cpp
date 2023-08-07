#include <iostream>
#include <cstdlib>

int main()
{
	int turnCounter = 0;
	std::string program = "sciezka do pliku Player";
	std::string mapa = "sciezka do pliku mapa";
	std::string status = "sciezka do pliku status";
	std::string rozkazy = "sciezka do pliku rozkazy";
	std::string player1 = "1"; //gracz pierwszy
	std::string player2 = "2"; //gracz drugi


	std::string commandPlayer1 = program + " " + mapa + " " + status + " " + rozkazy + " " + player1;
	std::string commandPlayer2 = program + " " + mapa + " " + status + " " + rozkazy + " " + player2;
	while (turnCounter<2000)
	{
		system(commandPlayer1.c_str()); //odpalenie tury dla gracza pierwszego   
		//tutaj warunek sprawdzajacy wygrana albo przegrana 
		system(commandPlayer2.c_str()); //odpalenie tury dla gracza drugiego  
		//tutaj warunek sprawdzajacy wygrana przegrana
		turnCounter++;
	}	
}
