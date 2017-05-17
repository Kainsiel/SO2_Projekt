#include <thread>
#include <iostream>
#include <stdlib.h>

using namespace std; 


void wczytaj_macierz()
{
int count = 0;
FILE *plik;

fPointer = fopen("tekst.txt", "r");

fclose(plik);

 /* int i;
  int j;

macierz
int** mat=malloc(4*sizeof(int));
for(i=0;i<4;++i)
mat[i]=malloc(4*sizeof(int));


  FILE *plik;
  plik=fopen("tekst.txt", "r");

 for(i = 0; i < 1000; i++)
  {
      for(j = 0; j < 4; j++) 
      {
       if (!fscanf(plik, " %c", &mat[i][j])) 
           break;
       mat[i][j] -= '0';
       printf("\n",mat[i][j]);
      }

  }
  fclose(plik);*/
}

void losuj_macierz()
{
  
}

int main()
{

  return 0;
}
