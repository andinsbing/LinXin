#pragma once  
#include"position.h"

class AbstractAutoSnakeStrategy
{  
public:
	enum Action
	{
		toLeft,
		toRight,
		toUp,
		toDown
	};
	AbstractAutoSnakeStrategy() = default;
	virtual ~AbstractAutoSnakeStrategy() = default;
	virtual Action compute(const Position& head) = 0; 
};



class SmartAutoSnakeStrategy
{
	struct Factor
	{
	}; 


};