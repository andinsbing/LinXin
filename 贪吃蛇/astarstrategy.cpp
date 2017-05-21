#include"astarstrategy.h"
#include"map.h"

const AStarStrategyFactor AStarStrategy::originFactor{};
AStarStrategyFactor AStarStrategy::Rank::factor{};

AStarStrategy::AStarStrategy(Map * map, const AStarStrategyFactor & factor) :
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

AbstractAutoSnakeStrategy::Action AStarStrategy::compute(const Position& head, const Position& tail)
{
	int x = head.x;
	int y = head.y;
	Rank leftRank{ getFoodRank(Position{ x - 1,y }.standard()), getRegionRank(Position{ x - 1,y }.standard(),tail) };
	Rank rightRank{ getFoodRank(Position{ x + 1,y }.standard()), getRegionRank(Position{ x + 1,y }.standard(),tail) };
	Rank upRank{ getFoodRank(Position{ x  ,y - 1 }.standard()), getRegionRank(Position{ x  ,y - 1 }.standard(),tail) };
	Rank downRank{ getFoodRank(Position{ x  ,y + 1 }.standard()), getRegionRank(Position{ x ,y + 1 }.standard(),tail) };
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

void AStarStrategy::saveConfiguration(double rank) 
{
	_factor.setFactorRank(rank);
	_factor.save();
}

void AStarStrategy::loadConfiguration()
{
	_factor.load();
}

double AStarStrategy::getFoodRank(const Position & pos)
{
	if (_map->getGameItem(pos) == Global::GameItem::Food)
	{
		return _factor.foodMaxRank();
	}
	if (_map->getGameItem(pos) != Global::GameItem::None)
	{
		return _factor.foodMinRank();
	}

	_flagController.updataFlagMap(); 
	_flagController.setFlagIf(pos, FlagController::up, FlagController::ready);

	auto foodSet = _map->getSet(Global::GameItem::Food);

	double ret = _factor.foodMinRank() + 1;
	int foodCountLeft = _factor.foodAmountCalculated();
	double foodDecreasementProportion = _factor.foodRankDecreseProportion();
	double rankIncrement = _factor.foodMinRank() + _factor.foodMaxRank() / foodCountLeft;

	while (foodCountLeft > 0 && _flagController.diffuse(FlagController::up))
	{
		rankIncrement *= foodDecreasementProportion;
		for (auto& pos : foodSet)
		{
			if (_flagController.getFlag(pos) == FlagController::up)
			{
				foodCountLeft--;
				ret += rankIncrement;
			}
		}
	}
	return ret;
}

std::pair<bool, double> AStarStrategy::getRegionRank(const Position & pos, const Position& tail)
{
	std::pair<bool, double> ret{ false,0.0 };
	_flagController.updataFlagMap();
	_flagController.setFlagIf(pos, FlagController::up, FlagController::ready);
	while (_flagController.diffuse(FlagController::up));
	ret.second = _flagController.count(FlagController::diffused);

	if (pos == tail)
	{
		ret.first = true;
	}
	else if (_flagController.getFlag(tail.leftPos()) == FlagController::diffused ||
		_flagController.getFlag(tail.rightPos()) == FlagController::diffused ||
		_flagController.getFlag(tail.upPos()) == FlagController::diffused ||
		_flagController.getFlag(tail.downPos()) == FlagController::diffused
		)
	{
		ret.first = true;
	}
	return  ret;
}

bool AStarStrategy::Rank::operator>(const Rank & rank) const
{
	if (this->regionRank.first && !rank.regionRank.first)
	{
		return true;
	}
	if (!this->regionRank.first&&rank.regionRank.first)
	{
		return false;
	}
	if (this->regionRank.second > rank.regionRank.second*factor.regionComparingFactor())
	{
		return true;
	}
	if (this->regionRank.second*factor.regionComparingFactor() < rank.regionRank.second)
	{
		return false;
	}
	return this->foodRank * this->regionRank.second > rank.foodRank * rank.regionRank.second;
}
