#include<iostream> 
#include<thread>
#include<vector>
#include"game.h"

using namespace std;
 
void fun(int val)
{
	cout << "fun called" << val << " ";
}  

void newGame()
{ 
	Game game;
	game.start();
	while (true)
	{
		while (!game.isGameOver())
		{
			Sleep(10000);
			this_thread::yield();
			game.end();
		}
		game.renew();
		//Sleep(3000);
		//game.renew();
	}
}
 
int main()  
{
	for (int i = 10; i < 999; i++ )
	{
		newGame();
	} 
	//Game game;
	//game.start();
	cin.get();//pause 
	return 0;
}