#include "autosnakestrategy.h"
#include "map.h" 
 
 
FlagController::FlagController(Map * map):
	_map(map),
	_flagMap()
{
	ASSERT_NOT_NULLPTR(map,"map不能为空");
}

void FlagController::updataFlagMap()
{
	for (int i = 0; i < Global::GameArea::HEIGHT; i++)
	{
		for (int j = 0; j < Global::GameArea::WIDTH; j++)
		{
			switch (_map->getGameItem({ j,i }))
			{
			case Global::GameItem::Food: 
			case Global::GameItem::None:
				_flagMap[i][j] = ready;
				break;
			case Global::GameItem::SnakeBody:
			case Global::GameItem::Wall:
				_flagMap[i][j] = disable;
				break;
			default:
				ASSERT_LOG("wrong case");
				break;
			}
		}
	}
}

void FlagController::setFlagIf(const Position & pos, FlagType flag, const std::function<bool(FlagType)>& fun)
{
	if (fun(getFlag(pos)))
	{
		setFlag(pos, flag);
	}
}

void FlagController::setFlag(const Position & pos, FlagType flag)
{
	_flagMap[pos.y][pos.x] = flag;
}

void FlagController::setNearbyFlagIf(const Position & pos, FlagType flag, const std::function<bool(FlagType)>& fun)
{
	int x = pos.x;
	int y = pos.y;
	setFlagIf(Position{ x - 1,y }.standard(), flag, fun);
	setFlagIf(Position{ x + 1,y }.standard(), flag, fun);
	setFlagIf(Position{ x,y - 1 }.standard(), flag, fun);
	setFlagIf(Position{ x,y + 1 }.standard(), flag, fun);
}

void FlagController::setNearbyFlag(const Position & pos, FlagType flag)
{
	int x = pos.x;
	int y = pos.y;
	setFlag(Position{ x - 1,y }.standard(), flag);
	setFlag(Position{ x + 1,y }.standard(), flag);
	setFlag(Position{ x,y - 1 }.standard(), flag);
	setFlag(Position{ x,y + 1 }.standard(), flag);
}

FlagController::FlagType FlagController::getFlag(const Position & pos)const
{
	return _flagMap[pos.y][pos.x];
}

bool FlagController::diffuse(FlagType flag)
{
	bool diffuseble{};
	for (int i = 0; i < Global::GameArea::HEIGHT; i++)
	{
		for (int j = 0; j < Global::GameArea::WIDTH; j++)
		{
			if (_flagMap[i][j] == flag)
			{
				setNearbyFlagIf({ j,i }, mark, [](FlagType flag) {return flag == ready; });
				setFlag({ j,i }, diffused);
				diffuseble = true;
			}
		}
	}
	if (!diffuseble)
	{
		return diffuseble;
	}
	for (int i = 0; i < Global::GameArea::HEIGHT; i++)
	{
		for (int j = 0; j < Global::GameArea::WIDTH; j++)
		{
			if (_flagMap[i][j] == mark)
			{ 
				_flagMap[i][j] = flag;
			}
		}
	} 
	return diffuseble;
}

int FlagController::count(FlagType flag)const
{
	int ret = 0; 
	std::for_each(&_flagMap[0][0], &_flagMap[Global::GameArea::HEIGHT - 1][Global::GameArea::WIDTH - 1 + 1],
		[&](FlagType f) {if (f == flag)++ret; });
	return ret;
}

std::vector<Position>&& FlagController::getSet(FlagType flag) const
{
	auto* set = new std::vector<Position>();
	for (int i = 0; i < Global::GameArea::HEIGHT; i++)
	{
		for (int j = 0; j < Global::GameArea::WIDTH; j++)
		{
			if (_flagMap[i][j] == flag)
			{
				set->push_back({ j,i });
			}
		}
	}
	return std::move(*set);
}

GreedStrategy::GreedStrategy(Map * map):
	_map(map),
	_flagController(map)
{
}

GreedStrategy::Action GreedStrategy::compute(const Position & head)
{
	_flagController.updataFlagMap();
	int x = head.x;
	int y = head.y;
	auto isReady = [](FlagController::FlagType flag) {return flag == FlagController::ready; };
	_flagController.setFlagIf(Position{ x - 1,y }.standard(), FlagController::left, isReady);
	_flagController.setFlagIf(Position{ x + 1,y }.standard(), FlagController::right, isReady);
	_flagController.setFlagIf(Position{ x,y - 1 }.standard(), FlagController::up, isReady);
	_flagController.setFlagIf(Position{ x,y + 1 }.standard(), FlagController::down, isReady);

	bool leftable = true;
	bool rightable = true;
	bool upable = true;
	bool downable = true;

	auto foodSet = _map->getSet(Global::GameItem::Food);

	for (auto& pos : foodSet)
	{
		if (_flagController.getFlag(pos) != FlagController::ready)
		{
			return translate(_flagController.getFlag(pos));
		}
	}

	while (leftable || rightable || upable || downable)
	{
		if (leftable) leftable = _flagController.diffuse(FlagController::left);
		if (rightable) rightable = _flagController.diffuse(FlagController::right);
		if (downable) downable = _flagController.diffuse(FlagController::down);
		if (upable) upable = _flagController.diffuse(FlagController::up);
		for (auto& pos : foodSet)
		{
			if (_flagController.getFlag(pos) != FlagController::ready)
			{
				return translate(_flagController.getFlag(pos));
			}
		}
	}
	return safeChoose(head);
}

AbstractAutoSnakeStrategy::Action GreedStrategy::translate(FlagController::FlagType flag) const
{
	switch (flag)
	{
	case FlagController::up:
		return Action::toUp;
	case FlagController::down:
		return Action::toDown;
	case FlagController::left:
		return Action::toLeft;
	case FlagController::right:
		return Action::toRight;
	default:
		ASSERT_LOG("wrong case");
		break;
	}
	ASSERT_LOG("wrong case");
	return Action();
}

AbstractAutoSnakeStrategy::Action GreedStrategy::safeChoose(const Position& pos) const
{
	auto isNone = [&](const Position& pos) {return _map->getGameItem(pos) == Global::GameItem::None; };
	int x = pos.x;
	int y = pos.y;
	AbstractAutoSnakeStrategy::Action actionSet[4];
	int actionSetSize = 0;
	if (isNone(Position{ x - 1,y }.standard())) actionSet[actionSetSize++] = AbstractAutoSnakeStrategy::Action::toLeft;
	if (isNone(Position{ x + 1,y }.standard())) actionSet[actionSetSize++] = AbstractAutoSnakeStrategy::Action::toRight;
	if (isNone(Position{ x,y - 1 }.standard())) actionSet[actionSetSize++] = AbstractAutoSnakeStrategy::Action::toUp;
	if (isNone(Position{ x,y + 1 }.standard())) actionSet[actionSetSize++] = AbstractAutoSnakeStrategy::Action::toDown;

	if (actionSetSize == 0)
	{//  no ans, just return illegal one 
		return AbstractAutoSnakeStrategy::Action::toLeft;
	}
	return actionSet[rand() % actionSetSize];
}

AStarStrategy::AStarStrategy(Map * map):
	_map(map),
	_flagController(map)
{
	ASSERT_NOT_NULLPTR(map, "map不能为空");
}

AStarStrategy::Action AStarStrategy::compute(const Position & head)
{
	int x = head.x;
	int y = head.y;
	Rank leftRank{ getFoodRank(Position{ x - 1,y }.standard()), getRegionRank(Position{ x - 1,y }.standard()) };
	Rank rightRank{ getFoodRank(Position{ x + 1,y }.standard()), getRegionRank(Position{ x + 1,y }.standard()) };
	Rank upRank{ getFoodRank(Position{ x  ,y - 1 }.standard()), getRegionRank(Position{ x  ,y - 1 }.standard()) };
	Rank downRank{ getFoodRank(Position{ x  ,y + 1 }.standard()), getRegionRank(Position{ x ,y + 1}.standard()) };
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
	auto isReady = [](FlagController::FlagType flag) {return flag == FlagController::ready; };
	_flagController.setFlagIf(pos, FlagController::up, isReady);

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
	auto isReady = [](FlagController::FlagType flag) {return flag == FlagController::ready; };
	_flagController.setFlagIf(pos, FlagController::up, isReady);
	  
	while (_flagController.diffuse(FlagController::up));
	return std::sqrt(_flagController.count(FlagController::diffused));
}

bool AStarStrategy::Rank::operator>(const Rank & rank) const
{
	if (this->regionRank > rank.regionRank*1.5)
	{
		return true;
	}
	else if (this->regionRank*1.5 < rank.regionRank)
	{
		return false;
	}
	return this->foodRank * this->regionRank > rank.foodRank * rank.regionRank;
}
