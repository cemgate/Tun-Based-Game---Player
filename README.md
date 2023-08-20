# Jak zbudować

Przed samym zbudowaniem prosilbym o zmienie paru linijek w kodzie w pliku main.cpp w folderze Mediator. (linijka 13-18)

Instrukcja jak zbudować:

1. Nalezy wejsc do folderu Player i wpisac komende ``` mdkir build && cd build ```

2. Wpisac komende ``` cmake .. ```

3. Nastepnie wpisac komende ``` make ```

4. Nastepnie wpisac ``` ./Player ``` i nalezy skopiować sciezke do pliku wykonawczego "./Player" i umiescic w linijce 10 pliku main.cpp w folderze Mediator.

3. Kolejne przejsc do folderu Mediator i wpisac komende ``` mkdir build && cd build ```

4. Nastepnie wpisac komende ``` cmake .. ```

5. Nastepnie wpisac komende ``` make ```

6. Odpalenie programu poprzez wpisanie ``` ./Mediator ``` (nalezy pamietac zeby dodac sciezki do plikow mapa.txt, status.txt, rozkazy.txt i sciezke do pliku wykonawcznego w pliku ./Mediator/main.cpp w liniach 13-16).

## Player 

Player odpowiada za:
-Przeczytanie pliku status.txt i wygenerowanie jednostek
-stworzenie planu dla kazdej jednostki
-zapisanie rozkazow do pliku rozkazy.txt po czym program konczy dzialanie

## Mediator

Mediator odpowiada za:
-Wygenerowanie podstawowego pliku status.txt
-Wlaczenie programu "Player"
-Po zakonczeniu dzialania programu "Player", Mediator obsluguje rozkazy (zmienia plik status.txt wzgledem rozkazow)
-Po wykonaniu rozkazow zalacza znowu program "Player" tylko dla drugiego gracza

