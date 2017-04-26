#pragma once
#include"abstractautosnakestrategy.h"
#include"flagcontroller.h"
#include"astarstrategyfactor.h"
class Map;

class AStarStrategy :public AbstractAutoSnakeStrategy
{
	struct Rank
	{
		double foodRank;
		double regionRank; 
		bool operator > (const Rank& rank)const;
		static 	AStarStrategyFactor factor; 
	}; 
public:
	AStarStrategy(Map* map);
	AStarStrategy(Map* map, const AStarStrategyFactor& factor);
	Action compute(const Position& head)override;
	void saveConfiguration(double rank)override;
	void loadConfiguration()override;
private:
	double getFoodRank(const Position& pos);
	double getRegionRank(const Position& pos);
	const Map*const _map;
	FlagController _flagController;
	AStarStrategyFactor _factor; 
	const static AStarStrategyFactor originFactor;
};