#pragma once
#include<functional>
#include<vector>
#include"position.h"  


class Map;

class FlagController
{
public:
	enum FlagType
	{
		ready,
		disable,
		left,
		right,
		up,
		down,
		mark, // temp for diffusion
		diffused,
	};
	FlagController(Map* map);
	void updataFlagMap();
	void setFlagIf(const Position& pos, FlagType flag,const std::function<bool(FlagType)>& fun);
	void setFlag(const Position& pos, FlagType flag);
	void setNearbyFlagIf(const Position& pos, FlagType flag, const std::function<bool(FlagType)>& fun); 
	void setNearbyFlag(const Position& pos, FlagType flag);
	FlagType getFlag(const Position& pos)const; 
	bool diffuse(FlagType flag);
	int count(FlagType flag)const;
 
	std::vector<Position>&& getSet(FlagType flag)const; 
	
private:
	Map *const _map;
	FlagType _flagMap[Global::GameArea::HEIGHT][Global::GameArea::WIDTH];
};

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
	virtual ~AbstractAutoSnakeStrategy() = default;
	virtual Action compute(const Position& head) = 0; 
};

class GreedStrategy :public AbstractAutoSnakeStrategy
{ 
public: 
	GreedStrategy(Map* map);
	Action compute(const Position& head)override;
private: 
	Action translate(FlagController::FlagType flag)const;
	AbstractAutoSnakeStrategy::Action safeChoose(const Position& pos)const;
	Map*const _map;
	FlagController _flagController;
};

class AStarStrategy :public AbstractAutoSnakeStrategy
{
	struct Rank
	{
		double foodRank;
		double regionRank;
		bool operator > (const Rank& rank)const;
	};
public:
	AStarStrategy(Map* map);
	Action compute(const Position& head)override;
private: 
	double getFoodRank(const Position& pos);
	double getRegionRank(const Position& pos);
	Map*const _map;
	FlagController _flagController;
};