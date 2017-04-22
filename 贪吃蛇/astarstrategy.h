#pragma once
#include"abstractautosnakestrategy.h"
#include"flagcontroller.h"
class Map;

class AStarStrategy :public AbstractAutoSnakeStrategy
{
	struct Rank
	{
		double foodRank;
		double regionRank;
		bool operator > (const Rank& rank)const;
	};
public:
	struct Factor
	{
		double regionComparingFactory;
		double regionRankProportion;
		double foodMaxRank;
		double foodMinRank;
		double foodBaseRank;
		double foodRankDecreseProportion;
		int foodAmountCalculated;
		double foodRankProportion;
	};
public:
	AStarStrategy(Map* map);
	AStarStrategy(Map* map, const Factor& factor);
	Action compute(const Position& head)override;
private:
	double getFoodRank(const Position& pos);
	double getRegionRank(const Position& pos);
	const Map*const _map;
	FlagController _flagController;
	Factor _factor;
	const static Factor originFactor;
};