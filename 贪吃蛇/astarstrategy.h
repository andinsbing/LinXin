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
		std::pair<bool, double> regionRank;
		bool operator > (const Rank& rank)const;
		static 	AStarStrategyFactor factor; 
	}; 
public:
	AStarStrategy(Map* map);
	AStarStrategy(Map* map, const AStarStrategyFactor& factor);
	Action compute(const Position& head,const Position& tail)override;
	void saveConfiguration(double rank)override;
	void loadConfiguration()override;
private:
	double getFoodRank(const Position& pos);
	std::pair<bool,double> getRegionRank(const Position& pos,const Position& tail);
	const Map*const _map;
	FlagController _flagController;
	AStarStrategyFactor _factor; 
	const static AStarStrategyFactor originFactor;
};