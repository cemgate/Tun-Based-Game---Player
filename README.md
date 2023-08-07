# Player

Projekt jest niedokonczony. Nie bylem dyspozycyjny przez caly tydzien i nie starczylo mi czasu. 

## Glowny zarys: 
 - interfejsem jest klasa Entity. Dziedzicza po niej wszystkie klasy stworzone na podobienstwo typu jednostki oprocz Bazy
 - Baza nie dziedziczy po Entity 
 - Glowna klasa dowodzącą jest klasa Game
 - W klasie game wczytujemy mape z pliku
 - W klasie game na podstawie pliku status.txt tworzymy jednostki
 - W klasie game tworzymy plik rozkazy.txt
 - W klasie game posiadamy instancje klasy "Base" oraz vector<Entity*> (wszystkie jednostki w jednym vectorze)
 
## Do zrobienia
Do zrobienia caly algorytm obliczajacy dzialanie programu (ruch jednostek, budowa, atak, ogolnie cala symulacja rozgrywki).
W klasie Game rowniez do dokonczenia funkcja generujaca plik z rozkazami.

## Mediator
Dodatkowo wrzucam plik mainMediator.cpp przez ktorego odpalalem program player do testow.
