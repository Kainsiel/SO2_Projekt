#include <thread>
#include <mutex>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <ncurses.h>
#include <chrono>
#include <queue>

using namespace std;


int const M = 5;
int const N = 5;
queue <int> kolejka1;
mutex mx1;

queue <int> kolejka2;
mutex mx2;
mutex mx3;

int A[M][N];
mutex mtx;



int getY(int size, int pos){
	int rows = pos/size;
	return rows;
}

int getX(int size, int pos){
	int rows = pos/size;
	return pos-rows*size;
}

void Wyczysc_macierz(){

 while(1){
   mtx.lock();
   for(int i=0; i<M; i++){
	 for(int j = 0; j<N; j++){
	   A[i][j] = 0;
	   }    		
   }
   mtx.unlock();
 }
 
 this_thread::sleep_for(std::chrono::seconds(30));
}

void Producent(){
srand(time(NULL));
while(1){
  mx1.lock();
  kolejka1.push(rand() % M);
  mx1.unlock();
  mx2.lock();
  kolejka2.push(rand() % N);
  mx2.unlock();
  this_thread::sleep_for (std::chrono::milliseconds(100)); 
}


}

void Przetwarzacz()
{
  int var1 , var2;
  mx1.lock();
  if(int spr = kolejka1.back())
    var1 = kolejka1.back();
  mx1.unlock();
   
  mx2.lock();
  if(int spr = kolejka2.back())
    var2 = kolejka2.back();
  mx2.unlock();

  A[var1][var2]=1;

/*  int temp = A[M-1][N-1];
  for (int i=M*N-1; i>0; i--){
  A[getY(M, i)][getX(N, i)] = A[getY(M, i-1)][getX(N, i-1)];
  }
  A[0][0] = temp;
  
*/
  
}

void Wyswietl(){

this_thread::sleep_for(chrono::milliseconds(500));

while(1){
clear();
mtx.lock();
for(int i = 0; i < M; i++){
	for (int j= 0; j < N; j++){
	  printw(" %d ", A[i][j]);
	}
     printw("\n");
}
printw("\n");

mtx.unlock();
refresh();
this_thread::sleep_for(chrono::milliseconds(500)); 
}

}

int main()
{
  
  initscr();

auto tWyczysc = thread(Wyczysc_macierz);
  
auto tWyswietl = thread(Wyswietl);

auto tProducent = thread(Producent);

auto tPrzetwarzacz = thread(Przetwarzacz);


tWyczysc.join();

tWyswietl.join();

tProducent.join();

tPrzetwarzacz.join();



getch();
  
endwin();
return 0;
}
