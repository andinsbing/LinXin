#pragma once 
#include<list> 
#include"map.h"
#include"autosnake.h"

class GameScene
{  
public:
	GameScene();
	~GameScene(); 
	void advance(); 
	const Map& map()const;  
	void renew();
private:
	void adjustFood();
	void addAutoSnake(const Position& head, int snakeSize);
	void handleCollision(AutoSnake& snake);
	void removeAutoSnake(AutoSnake& snake);
	Map _map;
	int _foodLimit; 
	std::list<AutoSnake> _autoSnakeSet; 
};