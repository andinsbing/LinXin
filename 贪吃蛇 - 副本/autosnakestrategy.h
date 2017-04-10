#pragma once
#include<functional>
#include<vector>
#include"position.h"  


class Map;

class FlagControler
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
		mark
	};
	FlagControler(Map* map);
	void updataFlagMap();
	void setFlagIf(const Position& pos, FlagType flag,const std::function<bool(FlagType)>& fun);
	void setFlag(const Position& pos, FlagType flag);
	void setNearByFlagIf(const Position& pos, FlagType flag, const std::function<bool(FlagType)>& fun); 
	void setNearByFlag(const Position& pos, FlagType flag);
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
	Action translate(FlagControler::FlagType flag)const;
	AbstractAutoSnakeStrategy::Action safeChoose(const Position& pos)const;
	Map*const _map;
	FlagControler _flagControler;
};

class AStarStrategy :public AbstractAutoSnakeStrategy
{
public:
	AStarStrategy(Map* map);
	Action compute(const Position& head)override;
private:
	Action translate(FlagControler::FlagType flag)const;
	AbstractAutoSnakeStrategy::Action safeChoose(const Position& pos)const;
	Map*const _map;
	FlagControler _flagControler;
};