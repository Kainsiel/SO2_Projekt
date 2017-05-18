#include <thread>
#include <iostream>
#include <stdlib.h>
#include <fstream>

using namespace std; 

int wczytaj_rozmiar()
{
	int rozmiar;
	
	ifstream plik;
	plik.open("tekst.txt", fstream::in);
	if (!plik.is_open()){
	  throw "Brak pliku z danymi";
	}

	plik >> rozmiar;
	
	plik.close();
	return rozmiar;
}

//zwraca macierz zczytana z pliku
int** wczytaj_macierz()
{
	int rozmiar;
	int** macierz;
	
	

	ifstream plik;
	plik.open("tekst.txt", fstream::in);
	if (!plik.is_open()){
	  throw "Brak pliku z danymi";
	}
	plik >> rozmiar;
	
	macierz = new int*[rozmiar];
	for(int i = 0; i < rozmiar; i++)
		macierz[i] = new int[rozmiar];

	for(int i = 0; i < rozmiar; i++){
	for (int j= 0; j < rozmiar; j++){
	 plik >> macierz[i][j]; 
	}	
	}
	
	for(int i = 0; i < rozmiar; i++){
	for (int j= 0; j < rozmiar; j++){
	 cout << macierz[i][j] << " "; 	
	}
	 cout << "\n";
	}

	plik.close();
	return macierz;	
}

//tworzy macierz z wylosowanymi wartosciami
void losuj_macierz()
{
  
}

//transparuj macierz
void transparu_macierz(){
}

int main(int argc, char *argv[])
{
  wczytaj_macierz();
  return 0;
}
