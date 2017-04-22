#include "autosnakestrategyfactory.h"
#include"abstractautosnakestrategy.h"
#include"greedstrategy.h"
#include"astarstrategy.h"
#include"map.h"

AbstractAutoSnakeStrategy * AutoSnakeStrategyFactory::constractGreedStrategy(Map* map)
{
	return new AStarStrategy(map);
}

AbstractAutoSnakeStrategy * AutoSnakeStrategyFactory::constractAStartStrategy(Map* map)
{
	return new AStarStrategy(map);
}
