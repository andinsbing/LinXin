#pragma once
#include"snake.h"
#include"autosnakestrategy.h"

class Map; 

class AutoSnake
{
	enum Action
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
	void defaultMove();
	Global::GameItem collisionItem()const;
	void appendTail();
	void append(const Position& pos);
	bool accessible(const Position & pos);
	void die();
	bool operator ==(const AutoSnake& snake)const;
private: 
	Snake _snake;
	Map*const _map;
	Global::GameItem _lastCollisionItem;
	GreedStrategy _greedStrategy;
	AStarStrategy _aStarStrategy;
};
