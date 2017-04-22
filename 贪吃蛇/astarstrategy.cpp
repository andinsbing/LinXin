#include"astarstrategy.h"
#include"map.h"

const AStarStrategy::Factor AStarStrategy::originFactor
{
	1.5,
	1.0,
	100000.0,
	0.0,
	300000.0,
	0.9,
	3,
	1.0
};

AStarStrategy::AStarStrategy(Map * map, const Factor & factor) :
	_map(map),
	_flagController(map),
	_factor{}
{
	ASSERT_NOT_NULLPTR(map, "map can not be nullptr");
}

AStarStrategy::AStarStrategy(Map * map):
	AStarStrategy(map,originFactor)
{

}

AbstractAutoSnakeStrategy::Action AStarStrategy::compute(const Position & head)
{
	int x = head.x;
	int y = head.y;
	Rank leftRank{ getFoodRank(Position{ x - 1,y }.standard()), getRegionRank(Position{ x - 1,y }.standard()) };
	Rank rightRank{ getFoodRank(Position{ x + 1,y }.standard()), getRegionRank(Position{ x + 1,y }.standard()) };
	Rank upRank{ getFoodRank(Position{ x  ,y - 1 }.standard()), getRegionRank(Position{ x  ,y - 1 }.standard()) };
	Rank downRank{ getFoodRank(Position{ x  ,y + 1 }.standard()), getRegionRank(Position{ x ,y + 1 }.standard()) };
	if (leftRank > rightRank&&leftRank > upRank&&leftRank > downRank)
	{
		return Action::toLeft;
	}
	else if (rightRank > upRank&&rightRank > downRank)
	{
		return Action::toRight;
	}
	else if (upRank > downRank)
	{
		return Action::toUp;
	}
	return Action::toDown;
}

double AStarStrategy::getFoodRank(const Position & pos)
{
	if (_map->getGameItem(pos) == Global::GameItem::Food)
	{
		return 100000;
	}
	if (_map->getGameItem(pos) != Global::GameItem::None)
	{
		return 0;
	}

	_flagController.updataFlagMap(); 
	_flagController.setFlagIf(pos, FlagController::up, FlagController::ready);

	auto foodSet = _map->getSet(Global::GameItem::Food);

	double rankIncrement = 30000;
	double ret = 1;
	int foodLeft = 3;

	while (foodLeft > 0 && _flagController.diffuse(FlagController::up))
	{
		rankIncrement *= 0.9;
		for (auto& pos : foodSet)
		{
			if (_flagController.getFlag(pos) == FlagController::up)
			{
				foodLeft--;
				ret += rankIncrement;
			}
		}
	}
	return ret;
}

double AStarStrategy::getRegionRank(const Position & pos)
{
	_flagController.updataFlagMap(); 
	_flagController.setFlagIf(pos, FlagController::up, FlagController::ready);

	while (_flagController.diffuse(FlagController::up));
	return std::sqrt(_flagController.count(FlagController::diffused));
}

bool AStarStrategy::Rank::operator>(const Rank & rank) const
{
	if (this->regionRank > rank.regionRank*1.5)
	{
		return true;
	}
	if (this->regionRank*1.5 < rank.regionRank)
	{
		return false;
	}
	return this->foodRank * this->regionRank > rank.foodRank * rank.regionRank;
}
