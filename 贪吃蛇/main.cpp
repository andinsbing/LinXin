#include<iostream> 
#include<thread>
#include<vector>
#include"game.h"

using namespace std; 

//void newGame()
//{ 
//	Game game;
//	game.start();
//	int timesLimit;
//	while (true)
//	{
//		timesLimit = 100;
//		while (!game.isGameOver())
//		{
//			Sleep(5000);
//			this_thread::yield(); 
//			if (--timesLimit == 0)
//			{
//				break;
//			}
//		}
//		game.renew(); 
//	}
//}
 
int main()  
{
	Game game;
	game.start();
	system("pause");
	return 0;
}