#include<algorithm>
#include"map.h" 

using ::Global::GameArea::WIDTH;
using ::Global::GameArea::HEIGHT;
using ::Global::GameItem;


Map::Map()
{
	std::fill(&_map[0][0], &_map[HEIGHT - 1][WIDTH - 1 + 1], Global::GameItem::None);
}

Map::~Map()
{
}

void Map::setGameItem(const Position & pos, GameItem gameItem)
{
	ASSERT_POS_LEGAL(pos.x, pos.y);
	_map[pos.y][pos.x] = gameItem;
}

void Map::removeGameItem(const Position & pos) 
{
	ASSERT_POS_LEGAL(pos.x, pos.y);
	_map[pos.y][pos.x] = GameItem::None;
}

GameItem Map::getGameItem(const Position & pos) const
{
	ASSERT_POS_LEGAL(pos.x, pos.y);
	return _map[pos.y][pos.x];
}

std::vector<Position>&& Map::getSet(const GameItem gameItem) const
{
	auto set = new std::vector<Position>();
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (_map[i][j] == gameItem)
			{
				set->push_back({ j,i });
			}
		}
	}
	return std::move(*set);
}

void Map::forEach(const std::function<void(GameItem)>& fun) const
{
	std::for_each(&_map[0][0], &_map[HEIGHT - 1][WIDTH - 1 + 1], fun);
}

Position const Map::firsOf(GameItem gameItem) const
{
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (_map[i][j] == gameItem)
			{
				return{ j,i };
			}
		}
	}
	//not found
	return{ WIDTH,HEIGHT };
}

int Map::count(Global::GameItem gameItem) const
{
	int amout = 0;
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (_map[i][j] == gameItem)
			{
				amout++;
			}
		}
	}
	return amout;
}

bool Map::isInLegalRange(const Position & pos) 
{
	return false;
}
