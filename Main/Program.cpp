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

int **A;
int const M = 5;
int const N = 5;
queue <int> kolejka1;
mutex mx1;

queue <int> kolejka2;
mutex mx2;
int spr = 0;
condition_variable cv;


int getY(int size, int pos){
	int rows = pos/size;
	return rows;
}

int getX(int size, int pos){
	int rows = pos/size;
	return pos-rows*size;
}

void Producent(){

kolejka1.push_back(rand() % M);
kolejka2.push_back(rand() % N);



}

void Przetwarzacz()
{
  int var1 , var2;
  var1 = kolejka1.back();
  printw(" %d ", var1);
  kolejka1.pop_back();
  var2 = kolejka2.back();
  printw(" %d \n", var2);
  kolejka2.pop_back();

  A[var1][var2]=1;

  int temp = A[M-1][N-1];
  for (int i=M*N-1; i>0; i--){
  A[getY(M, i)][getX(N, i)] = A[getY(M, i-1)][getX(N, i-1)];
  }
  A[0][0] = temp;

  
}

void Wyswietl(){

this_thread::sleep_for(chrono::seconds(1));


for(int i = 0; i < M; i++){
	for (int j= 0; j < N; j++){
	  printw(" %d ", A[i][j]);
	}
     printw("\n");
}
   printw("\n");
   refresh();
}

int main()
{
  srand(time(NULL));
  initscr();
  vector<thread> thread_producent;
  vector<thread> thread_przetwarzacz;
  vector<thread> thread_wyswietl;

 A = new int * [M];
 for(int i = 0; i < M; i++)
 {
	A[i] = new int[N];
 }

 for(int i = 0; i < M; i++){
	for (int j= 0; j < N; j++){
	  A[i][j] = 0; 	
	}
}



  auto tProducent = thread(Producent);

  auto tPrzetwarzacz = thread(Przetwarzacz);

  auto tWyswietl = thread(Wyswietl);


  tProducent.join();

  tPrzetwarzacz.join();

  tWyswietl.join();

getch();
  
endwin();
return 0;
}
