#include"greedstrategy.h"
#include"map.h"

GreedStrategy::GreedStrategy(Map * map) :
	_map(map),
	_flagController(map)
{
}

AbstractAutoSnakeStrategy::Action GreedStrategy::compute(const Position& head, const Position& tail)
{
	_flagController.updataFlagMap();
	int x = head.x;
	int y = head.y; 
	_flagController.setFlagIf(Position{ x - 1,y }.standard(), FlagController::left, FlagController::ready);
	_flagController.setFlagIf(Position{ x + 1,y }.standard(), FlagController::right, FlagController::ready);
	_flagController.setFlagIf(Position{ x,y - 1 }.standard(), FlagController::up, FlagController::ready);
	_flagController.setFlagIf(Position{ x,y + 1 }.standard(), FlagController::down, FlagController::ready);

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

void GreedStrategy::saveConfiguration(double rank)
{
	// not need ,do nothing
}

void GreedStrategy::loadConfiguration()
{
	// not need ,do nothing
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
