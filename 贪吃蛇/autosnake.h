#pragma once
#include<memory>
#include"snake.h" 

class AbstractAutoSnakeStrategy;

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
	static int snakeAmount;
	Snake _snake;
	Map*const _map;
	Global::GameItem _lastCollisionItem; 
	std::unique_ptr<AbstractAutoSnakeStrategy> _strategy;
};
