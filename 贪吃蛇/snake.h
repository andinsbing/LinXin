#pragma once
#include<Queue> 
#include"position.h"
#include"map.h"

class Snake
{
public:
	//蛇身由头开始向左展开为一排
	Snake(const Position& head, int snakeSize);
	~Snake();
	void append(const Position& newTail);
	void up();
	void down();
	void left();
	void right();  
	void die();
	Position head()const;
	Position tail()const;
	const std::deque<Position>& shape()const;
	Position lastTail()const;
	bool operator ==(const Snake& snake)const;
private: 
	std::deque<Position> _shape;
	Position _lastTail;
	const int _ID;
	static int _IDCount;
};