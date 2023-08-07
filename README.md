# Player

Projekt jest niedokonczony. Nie bylem dyspozycyjny przez caly tydzien i nie starczylo mi czasu. 

Glowny zarys:
 -Interfejs to klasa Entity
 -Klasy dziedziczace po Entity to wszystkie jednostki mozliwe do wybudowania w grze oprocz Base
 -Base nie dziedziczy po Entity

Dodatkowo glowna klasa ktora posiada w sobie vector<Entity*> (czyli cale nasze wojsko) jak i instacje klasy Base to klasa Game.
W niej sa zawarte wszystkie metody dotyczace wczytania mapy, wczytania statusu gry i generowania rozkazow.
Do zrobienia caly algorytm obliczajacy dzialanie programu (ruch jednostek, budowa, atak, ogolnie cala symulacja rozgrywki).
W klasie Game rowniez do dokonczenia funkcja generujaca plik z rozkazami.

Dodatkowo wrzucam plik mainMediator.cpp przez ktorego odpalalem program player do testow.
