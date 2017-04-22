#pragma once

class AbstractAutoSnakeStrategy;
class Map;

class AutoSnakeStrategyFactory
{
public:
	AutoSnakeStrategyFactory() = delete;
	static AbstractAutoSnakeStrategy* constractGreedStrategy(Map* map);
	static AbstractAutoSnakeStrategy* constractAStartStrategy(Map* map);
};