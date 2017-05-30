#include <thread>
#include <mutex>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <time.h>
#include <vector>

using namespace std; 

int const m = 2;
mutex mtx[m][m];
thread watek[m];


//zwraca macierz zczytana z pliku
int** wczytaj_macierz()
{
	int rozmiar = m;
	int** macierz;
	
	

	ifstream plik;
	plik.open("tekst.txt", fstream::in);
	if (!plik.is_open()){
	  throw "Brak pliku z danymi";
	}
	
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
  int rozmiar = m;

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

void pomnoz_macierz(int const * const * A, int const * const * B,int** C,int row,int col, int i){
    mtx[row][col].lock();
    C[row][col] += A[row][i]*B[i][col];
    mtx[row][col].unlock();
}

//transparuj macierz
void transparuj_macierz(){
}

int main(int argc, char *argv[])
{
  srand(time(NULL));
 int **A,**B,**C;
 int i,j,k,s;




 A = wczytaj_macierz();
 B = losuj_macierz();



 C = new int * [m];
 for(int i = 0; i < m; i++)
 {
	C[i] = new int[m];
 }


 for(int row=0; row<m; row++){
        for(int col=0; col<m;col++){
            for(int i=0;i<m;i++){
                watek[i] = thread(pomnoz_macierz, A, B, C,row, col, i);
            }
        }
    }


      for(int i=0;i<2;i++){
         watek[i].join();
      }


  for(i = 0; i < m; i++)
  {
    for(j = 0; j < m; j++) cout << " " << C[i][j];
    cout << endl;
  }

  
  for(i = 0; i < m; i++)
  {
    delete [] A[i];
    delete [] B[i];
    delete [] C[i];
  }

  delete [] A;
  delete [] B;
  delete [] C; 

  return 0;
}
