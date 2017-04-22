#include"flagcontroller.h"
#include"map.h"

FlagController::FlagController(Map * map) :
	_map(map),
	_flagMap()
{
	ASSERT_NOT_NULLPTR(map, "map²»ÄÜÎª¿Õ");
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

void FlagController::setFlagIf(const Position & pos, FlagType newFlag, FlagType oldFlag)
{
	if (_flagMap[pos.y][pos.x]==oldFlag)
	{
		setFlag(pos, newFlag);
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

void FlagController::setNearbyFlagIf(const Position & pos, FlagType newFlag, FlagType oldFlag)
{
	int x = pos.x;
	int y = pos.y;
	setFlagIf(Position{ x - 1,y }.standard(), newFlag, oldFlag);
	setFlagIf(Position{ x + 1,y }.standard(), newFlag, oldFlag);
	setFlagIf(Position{ x,y - 1 }.standard(), newFlag, oldFlag);
	setFlagIf(Position{ x,y + 1 }.standard(), newFlag, oldFlag);
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
				setNearbyFlagIf({ j,i }, mark,ready);
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
	for (int i = 0; i < Global::GameArea::HEIGHT; i++)
	{
		for (int j = 0; j < Global::GameArea::WIDTH; j++)
		{
			if (_flagMap[i][j] == flag)
			{
				ret++;
			}
		}
	}
	return ret;
}

std::vector<Position> FlagController::getSet(FlagType flag) const
{
	std::vector<Position> set;
	for (int i = 0; i < Global::GameArea::HEIGHT; i++)
	{
		for (int j = 0; j < Global::GameArea::WIDTH; j++)
		{
			if (_flagMap[i][j] == flag)
			{
				set.push_back({ j,i });
			}
		}
	}
	return std::move(set);
}