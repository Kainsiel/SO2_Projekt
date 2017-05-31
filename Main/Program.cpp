#include <thread>
#include <mutex>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <ncurses.h>
#include <chrono>
#include <condition_variable>

using namespace std;

int **A;
int const M = 5;
int const N = 5;
vector<int> kolejka1;
mutex mx;
vector<int> kolejka2;
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

unique_lock<mutex> lock(mx);

kolejka1.push_back(rand() % M);
kolejka2.push_back(rand() % N);

cv.wait(lock,[]{return spr == 1;});

}

void Przetwarzacz()
{
  int var1 , var2;
  lock_guard<mutex> lock(mx);
  var1 = kolejka1.back();
  //printw(" %d ", var1);
  kolejka1.pop_back();
  var2 = kolejka2.back();
  //printw(" %d \n", var2);
  kolejka2.pop_back();

  A[var1][var2]=1;

  int temp = A[M-1][N-1];
  for (int i=M*N-1; i>0; i--){
  A[getY(M, i)][getX(N, i)] = A[getY(M, i-1)][getX(N, i-1)];
  }
  A[0][0] = temp;


   spr=1;
  cv.notify_one();
}

void Wyswietl()
{

   for(int i = 0; i < M; i++){
	for (int j= 0; j < N; j++){
	  printw(" %d ", A[i][j]);
	}
     printw("\n");
}
   printw("\n");
  
   
  
}

//transparuj macierz

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


printw("\n");
for (int i = 0; i < 10; i++){
  thread_producent.push_back(thread(Producent));
    

}

for (int i = 0; i < 10; i++){
  thread_przetwarzacz.push_back(thread(Przetwarzacz));
    

}

for (int i = 0; i < 10; i++){
  thread_wyswietl.push_back(thread(Wyswietl));
    
}

for(auto& thread : thread_wyswietl)
  thread.join();

for(auto& thread : thread_przetwarzacz)
  thread.join();

for(auto& thread : thread_producent)
  thread.join();	

getch();
  
endwin();
return 0;
}