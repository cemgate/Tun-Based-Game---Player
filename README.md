# FINISH !!!!!
Wszystko zostalo ukonczone.

# Jak zbudować

Przed samym zbudowaniem prosilbym o zmienie paru linijek w kodzie w pliku main.cpp w folderze Mediator. (linijka 13-18)

Instrukcja jak zbudować:

1. Nalezy wejsc do folderu Player i wpisac komende ``````python ```````

```

3. Nastepnie wpisac komende "make"

4. Skopiować sciezke do pliku wykonawczego "./Player" i umiescic w linijce 10 pliku main.cpp w folderze Mediator.

3. Kolejne przejsc do folderu Mediator/build i wpisac komende "cmake .."

4. Nastepnie wpisac komende "make".

5. Odpalenie programu poprzez wpisanie "./Mediator"

## Player 

Wszystkie funkcje z programu player zostaly sprawdzone. Zastosowane zostało ułatwienie rozgrywki dotyczącego "autonomicznego grania". Komputer zamiast obmyslać optymalny ruch to przy kazdej turze, jesli moze, buduje jedna jednostek wybrana losowo, kupuje jedna jednostke wybrana losowa i nastepnie wszystkimi innymi jednostkami kieruje sie na baze przeciwnika. Potyczki pomiedzy jednostkami zostaly pominiete tak samo jak wydobywanie zlota przed górników. Do tego nie wiedziałem jak do końca ma wyglądać "kupowanie" jednostek więc zważająć na moją wiedzę z gier strategicznych, zakupione jednostki mogą używać punktów ruchów dopiero w kolejnej turze więc stworzyłem nowy tryb rozkazu dla bazy jakim jest 'P' - kupienie jednostki (np 11 P W - jednostka o id 11, w domysle baza, kupuje jednostke Worker). 

## Mediator

Program mediatora został ukończony. Mediator odpowiada za:
1. Zaktuzalizowanie poczatkowego pustego pliku status.txt (na podstawie odczytu z mapa.txt wpisuje to status.txt bazowe parametry bazy oraz poczatkowa wartosc golda dla gracza pierwszego = 2000)
2. Odczytywanie rozkazow i modyfikowanie pliku status.txt
3. Po kazdym odczytaniu rozkazow od programu Player i wykonaniu wszystkich czynnosci Mediator czysci plik rozkazy
4. Mediator przygotowuje nowy plik status.txt ktory tak naprawde rozni sie pierwsza linijka w ktorej jest zmieniona wartosc golda na golda gracza drugiego/pierwszego w zaleznosci kogo bedzie nastepna tura.
5. Mediator sprawdza po kazdym odczytaniu pliku rozkazy.txt oraz zmienieniu statusu czy nastapila wygrana (zycie przeciwnika < 0)
6. Mediator sprawdza po zakonczeniu maksymalnej ilosci tur (MAX_TURNS=1000) czy nastapila wygrana. Wygrana jest przydzielana na podstawie wiekszej liczby wojska.
