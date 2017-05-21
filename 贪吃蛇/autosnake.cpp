#include<cstdlib>
#include"autosnake.h"
#include"abstractautosnakestrategy.h"
#include"map.h"
#include"autosnakestrategyfactory.h"

using ::Global::GameArea::HEIGHT;
using ::Global::GameArea::WIDTH;
using ::Global::GameItem;

int AutoSnake::snakeAmount = 0;

AutoSnake::AutoSnake(Map* map, const Position& head, int snakeSize) :
	_snake(head,snakeSize),
	_map(map),
	_lastCollisionItem(GameItem::None), 
	_strategy(AutoSnakeStrategyFactory::constractAStartStrategy(map))
{
	for (auto& node : _snake.shape())
	{
		ASSERT_NONE(_map->getGameItem(node));// check if snake shape is legal
		_map->setGameItem(node, Global::GameItem::SnakeBody);
	}
	ASSERT_NOT_NULLPTR(map, "map不能为空指针"); 
	ASSERT_NOT_NULLPTR(_strategy.get(), "strategy不能为空");
	_strategy->loadConfiguration();
	snakeAmount++;
}

AutoSnake::~AutoSnake()
{
	if (--snakeAmount == 0)
	{
		_strategy.get()->saveConfiguration(_map->count(Global::GameItem::SnakeBody));
	}
	this->die();
}

void AutoSnake::advance()
{   
	auto action = _strategy.get()->compute(_snake.head(),_snake.tail());
	_map->removeGameItem(_snake.tail());
	switch (action)
	{ 
	case AbstractAutoSnakeStrategy::toLeft:
		_snake.left();
		break;
	case AbstractAutoSnakeStrategy::toRight:
		_snake.right();
		break;
	case AbstractAutoSnakeStrategy::toUp:
		_snake.up();
		break;
	case AbstractAutoSnakeStrategy::toDown:
		_snake.down();
		break;
	default:
		ASSERT_TRUE(false, "error case");
		break;
	}
	_lastCollisionItem = _map->getGameItem(_snake.head());
	_map->setGameItem(_snake.head(), GameItem::SnakeBody);
}

void AutoSnake::defaultMove()
{
	enum Des
	{
		left,
		right,
		up,
		down
	};
	int x = _snake.head().x;
	int y = _snake.head().y;
	int des[4];
	int count = 0; 
	auto tryPush = [&](Des d, int x, int y)
	{
		if (_map->getGameItem({ x,y }) == GameItem::None)
		{
			des[count++] = d;
		}
	};
	tryPush(left, (x - 1 + WIDTH) % WIDTH, y);
	tryPush(right, (x + 1) % WIDTH, y);
	tryPush(up, x, (y - 1 + HEIGHT) % HEIGHT);
	tryPush(down, x, (y + 1) % HEIGHT);
	 
	if (count == 0)
	{// no legal desicion, choose illegal one 
		_snake.right();
		return;
	}
	 
	switch (des[std::rand() % count])
	{
	case up:
		_snake.up();
		break;
	case down:
		_snake.down();
		break;
	case left:
		_snake.left();
		break;
	case right:
		_snake.right();
		break;
	default:
		ASSERT_LOG("wrong case");
		break;
	}
}

GameItem AutoSnake::collisionItem() const
{
	return _lastCollisionItem;
}

void AutoSnake::appendTail()
{
	_snake.append(_snake.lastTail());
	_map->setGameItem(_snake.tail(), Global::GameItem::SnakeBody);
}

void AutoSnake::append(const Position & pos)
{
	_snake.append(pos);
}

bool AutoSnake::accessible(const Position & pos)
{
	enum Flag
	{
		ready,
		disable,
		mark
	};
	static Flag map[HEIGHT][WIDTH];
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			auto item = _map->getGameItem({ j,i });
			map[i][j] = (item == GameItem::None || item == GameItem::Food) ? ready : disable;
		}
	}
	map[_snake.head().y][_snake.head().x] = mark;

	auto trySetFlag = [&](int x, int y, Flag flag) {
		if (x >= 0 && x < WIDTH&&y >= 0 && y < HEIGHT \
			&&map[y][x] == ready)
		{
			map[y][x] = flag;
			return true;
		}
		return false;
	};
	bool ended{};
	while (!ended)
	{
		ended=true;
		for (int i = 1; i < HEIGHT; i++)
		{
			for (int j = 1; j < WIDTH; j++)
			{
				if (map[i][j] == mark)
				{
					if (pos.x == j&&pos.y == i)
					{
						return true; // the pos is accessible
					}
					map[i][j] = disable; // searched,so do not search this pos again
					ended = trySetFlag(j - 1, i, mark) ? false : ended;
					ended = trySetFlag(j + 1, i, mark) ? false : ended;
					ended = trySetFlag(j, i - 1, mark) ? false : ended;
					ended = trySetFlag(j, i + 1, mark) ? false : ended;
				}
			}
		}
	}
	return false; //the pos is not accessible
}

void AutoSnake::die()
{
	//死亡的时候，头部不会变为食物
	for(auto i=++_snake.shape().begin();i!=_snake.shape().end();i++)
	{
		_map->setGameItem(*i, GameItem::Food);
	}
	_snake.die();
}

bool AutoSnake::operator==(const AutoSnake & snake) const
{
	return this->_snake == snake._snake;
} 