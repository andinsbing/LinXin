#include "autosnakestrategy.h"
#include "map.h" 
 
 
FlagControler::FlagControler(Map * map):
	_map(map),
	_flagMap()
{
	ASSERT_NOT_NULLPTR(map,"map²»ÄÜÎª¿Õ");
}

void FlagControler::updataFlagMap()
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

void FlagControler::setFlagIf(const Position & pos, FlagType flag, const std::function<bool(FlagType)>& fun)
{
	if (fun(getFlag(pos)))
	{
		setFlag(pos, flag);
	}
}

void FlagControler::setFlag(const Position & pos, FlagType flag)
{
	_flagMap[pos.y][pos.x] = flag;
}

void FlagControler::setNearByFlagIf(const Position & pos, FlagType flag, const std::function<bool(FlagType)>& fun)
{
	int x = pos.x;
	int y = pos.y;
	setFlagIf(Position{ x - 1,y }.standard(), flag, fun);
	setFlagIf(Position{ x + 1,y }.standard(), flag, fun);
	setFlagIf(Position{ x,y - 1 }.standard(), flag, fun);
	setFlagIf(Position{ x,y + 1 }.standard(), flag, fun);
}

void FlagControler::setNearByFlag(const Position & pos, FlagType flag)
{
	int x = pos.x;
	int y = pos.y;
	setFlag(Position{ x - 1,y }.standard(), flag);
	setFlag(Position{ x + 1,y }.standard(), flag);
	setFlag(Position{ x,y - 1 }.standard(), flag);
	setFlag(Position{ x,y + 1 }.standard(), flag);
}

FlagControler::FlagType FlagControler::getFlag(const Position & pos)const
{
	return _flagMap[pos.y][pos.x];
}

bool FlagControler::diffuse(FlagType flag)
{
	bool diffuseble{};
	for (int i = 0; i < Global::GameArea::HEIGHT; i++)
	{
		for (int j = 0; j < Global::GameArea::WIDTH; j++)
		{
			if (_flagMap[i][j] == flag)
			{
				setNearByFlagIf({ j,i }, mark, [](FlagType flag) {return flag == ready; });
				setFlag({ j,i }, disable);
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

int FlagControler::count(FlagType flag)const
{
	int ret = 0; 
	std::for_each(&_flagMap[0][0], &_flagMap[Global::GameArea::HEIGHT - 1][Global::GameArea::WIDTH - 1 + 1],
		[&](FlagType f) {if (f == flag)++ret; });
	return ret;
}

std::vector<Position>&& FlagControler::getSet(FlagType flag) const
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
	_flagControler(map)
{
}

GreedStrategy::Action GreedStrategy::compute(const Position & head)
{
	_flagControler.updataFlagMap();
	int x = head.x;
	int y = head.y;
	auto isReady = [](FlagControler::FlagType flag) {return flag == FlagControler::ready; };
	_flagControler.setFlagIf(Position{ x - 1,y }.standard(), FlagControler::left, isReady);
	_flagControler.setFlagIf(Position{ x + 1,y }.standard(), FlagControler::right, isReady);
	_flagControler.setFlagIf(Position{ x,y - 1 }.standard(), FlagControler::up, isReady);
	_flagControler.setFlagIf(Position{ x,y + 1 }.standard(), FlagControler::down, isReady);

	bool leftAble = true;
	bool rightAble = true;
	bool upAble = true;
	bool downAble = true;

	auto foodSet = _map->getSet(Global::GameItem::Food);

	for (auto& pos : foodSet)
	{
		if (_flagControler.getFlag(pos) != FlagControler::ready)
		{
			return translate(_flagControler.getFlag(pos));
		}
	}

	while (leftAble || rightAble || upAble || downAble)
	{
		if (leftAble) leftAble = _flagControler.diffuse(FlagControler::left);
		if (rightAble) rightAble = _flagControler.diffuse(FlagControler::right);
		if (downAble) downAble = _flagControler.diffuse(FlagControler::down);
		if (upAble) upAble = _flagControler.diffuse(FlagControler::up);
		for (auto& pos : foodSet)
		{
			if (_flagControler.getFlag(pos) != FlagControler::ready)
			{
				return translate(_flagControler.getFlag(pos));
			}
		}
	}
	return safeChoose(head);
}

AbstractAutoSnakeStrategy::Action GreedStrategy::translate(FlagControler::FlagType flag) const
{
	switch (flag)
	{
	case FlagControler::up:
		return Action::toUp;
	case FlagControler::down:
		return Action::toDown;
	case FlagControler::left:
		return Action::toLeft;
	case FlagControler::right:
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
