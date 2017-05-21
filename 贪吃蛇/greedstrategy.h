#pragma once
#include"abstractautosnakestrategy.h"
#include"flagcontroller.h"
class Map;

class GreedStrategy :public AbstractAutoSnakeStrategy
{
public:
	GreedStrategy(Map* map);
	Action compute(const Position& head, const Position& tail)override;
	void saveConfiguration(double rank)override;
	void loadConfiguration()override;
private:
	Action translate(FlagController::FlagType flag)const;
	AbstractAutoSnakeStrategy::Action safeChoose(const Position& pos)const;
	Map*const _map;
	FlagController _flagController;
};
