#pragma once
#include"snake.h"

class Map; 

class AutoSnake
{
	enum Decision
	{
		none,
		toLeft,
		toRight,
		toUp,
		toDown
	};
public:
	explicit AutoSnake(Map* map,const Position& head,int snakeSize);
	~AutoSnake();
	void advance();
	Global::GameItem collisionItem()const;
	void appendTail();
	void append(const Position& pos);
	bool accessible(const Position & pos);
	void die();
	bool operator ==(const AutoSnake& snake)const;
private:
	Decision breadthFisrtSearch();
	Snake _snake;
	Map*const _map;
	Global::GameItem _lastCollisionItem;
};
