#include <thread>
#include <iostream>
#include <stdlib.h>
#include <fstream>

using namespace std; 

//zwraca macierz zczytana z pliku
void wczytaj_macierz()
{
	ifstream plik;
	plik.open("tekst.txt", fstream::in);
	if (!plik.is_open()){
	  throw "Brak pliku z danymi";
	}
	plik.close();
}
//tworzy macierz z wylosowanymi wartosciami
void losuj_macierz()
{
  
}

//transparuj macierz
void transparu_macierz(){
}

int main()
{

  return 0;
}
