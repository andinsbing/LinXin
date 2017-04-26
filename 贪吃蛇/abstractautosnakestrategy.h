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
	virtual void saveConfiguration(double rank)= 0;
	virtual void loadConfiguration() = 0;
}; 