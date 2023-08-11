#include <iostream>
#include <cstdlib>
#include<map>

void readOrders()
{

}


int main()
{
	int turnCounter = 0;
	std::string program = "C:\\Users\\marci\\OneDrive\\Pulpit\\c++\\Player\\x64\\Debug\\Player.exe";
	std::string mapa = "C:\\Users\\marci\\OneDrive\\Pulpit\\mapa.txt";
	std::string status = "C:\\Users\\marci\\OneDrive\\Pulpit\\status.txt";
	std::string rozkazy = "C:\\Users\\marci\\OneDrive\\Pulpit\\rozkazy.txt";
	std::string player1 = "1"; //gracz pierwszy
	std::string player2 = "2"; //gracz drugi


	std::string commandPlayer1 = program + " " + mapa + " " + status + " " + rozkazy + " " + player1;
	std::string commandPlayer2 = program + " " + mapa + " " + status + " " + rozkazy + " " + player2;
	while (turnCounter<1)
	{
		system(commandPlayer1.c_str()); //odpalenie tury dla gracza pierwszego   
		//tutaj warunek sprawdzajacy wygrana albo przegrana 
		system(commandPlayer2.c_str()); //odpalenie tury dla gracza drugiego  
		//tutaj warunek sprawdzajacy wygrana przegrana
		turnCounter++;
	}	
}
