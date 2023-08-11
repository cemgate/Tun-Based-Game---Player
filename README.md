# Jak zbudować

Przed samym zbudowaniem prosilbym o zmienie paru linijek w kodzie w pliku main.cpp w folderze Mediator. (linijka 10-15)

Instrukcja jak zbudować:
1.Nalezy wejsc do folderu Player/build i wpisac komende "cmake .."
2.Nastepnie wpisac komende "make"
3.Skopiować sciezke do pliku wykonawczego "./Player" i umiescic w linijce 10 pliku main.cpp w folderze Mediator.
3.Kolejne przejsc do folderu Mediator/build i wpisac komende "cmake .."
4.Nastepnie wpisac komende "make".
5.Odpalenie programu poprzez wpisanie "./Mediator"

## Player 

Wszystkie funkcje z programu player zostaly sprawdzone. Zastosowane zostało ułatwienie rozgrywki dotyczącego "autonomicznego grania". Komputer zamiast obmyslać optymalny ruch to przy kazdej turze, jesli moze, buduje jedna jednostek wybrana losowo, kupuje jedna jednostke wybrana losowa i nastepnie wszystkimi innymi jednostkami kieruje sie na baze przeciwnika. Potyczki pomiedzy jednostkami zostaly pominiete tak samo jak wydobywanie zlota przed górników. Do tego nie wiedziałem jak do końca ma wyglądać "kupowanie" jednostek więc zważająć na moją wiedzę z gier strategicznych, zakupione jednostki mogą używać punktów ruchów dopiero w kolejnej turze więc stworzyłem nowy tryb rozkazu dla bazy jakim jest 'P' - kupienie jednostki (np 11 P W - jednostka o id 11, w domysle baza, kupuje jednostke Worker). 

## Mediator

Program mediator miał slużyć za odczytywanie rozkazów, aktualizacje zycia jednostek jak i sprawdzanie warunku wygranej/przegranej przez gracza/przeciwinika. Funkcje zostały zaimplementowane lecz jest tam jeszcze duzo bugów do poprawy. Nie udało mi się zrezalizować programu mediatora do końca. Program Mediatora odpala program gracza, zczytuje rozkazy, lecz przy probie przerobienia rozkazów na nowy status gry (linijki w pliku status.txt) nie moge znalezc na ten momentu bledu przy probie wczytywania linijek. Niezaleznie od danych wejsciowych program raz odczytuje linijke jako bledny format danych (np: poprawny [10,M,12,12] -> jednostka id 10, ruch do pola 12,12 w moim programie co jakis czas takie linijki są traktowane jako bledny format).
