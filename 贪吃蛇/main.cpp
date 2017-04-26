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
	int timesLimit;
	while (true)
	{
		timesLimit = 100;
		while (!game.isGameOver())
		{
			Sleep(5000);
			this_thread::yield(); 
			if (--timesLimit == 0)
			{
				break;
			}
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