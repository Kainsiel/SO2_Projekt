#include <thread>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <time.h>

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
int** losuj_macierz()
{
  int** macierz;
  int rozmiar = wczytaj_rozmiar();

  macierz = new int*[rozmiar];
  for(int i = 0; i < rozmiar; i++)
    macierz[i] = new int[rozmiar];

  for(int i = 0; i < rozmiar; i++){
  for (int j= 0; j < rozmiar; j++){
    macierz[i][j] = rand() % 100; 
  }	
  }	
  
  cout << "\n";
  for(int i = 0; i < rozmiar; i++){
	for (int j= 0; j < rozmiar; j++){
	 cout << macierz[i][j] << " "; 	
	}
	 cout << "\n";
	}
  cout << "\n";
  return macierz;
}

//transparuj macierz
void transparu_macierz(){
}

int main(int argc, char *argv[])
{
  srand(time(NULL));
 int **A,**B,**C,m;
 int i,j,k,s;

  m = wczytaj_rozmiar();
 cout << "\n" << m << "\n";

 C = new int * [m];
 for(i = 0; i < 3; i++)
  {
    
    C[i] = new int[m];
  }


 A = wczytaj_macierz();
 B = losuj_macierz();
 




for(i = 0; i < m; i++)
    for(j = 0; j < m; j++)
    {
      s = 0;
      for(k = 0; k < m; k++) s += A[i][k] * B[k][j];
      C[i][j] = s;
    }


  for(i = 0; i < m; i++)
  {
    for(j = 0; j < m; j++) cout << " " << C[i][j];
    cout << endl;
  }

  return 0;
}
