#include<cstdlib>
#include"autosnake.h"
#include"map.h"

using ::Global::GameArea::HEIGHT;
using ::Global::GameArea::WIDTH;
using ::Global::GameItem;

AutoSnake::AutoSnake(Map* map, const Position& head, int snakeSize) :
	_snake(head,snakeSize),
	_map(map),
	_lastCollisionItem(GameItem::None),
	_strategy(map)
{
	ASSERT_NOT_NULLPTR(map, "map不能为空指针"); 
}

AutoSnake::~AutoSnake()
{
	this->die();
}

void AutoSnake::advance()
{
	//Action action = breadthFisrtSearch();
	auto action = _strategy.compute(_snake.head());
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
	for (auto&i : _snake.shape())
	{
		_map->setGameItem(i, GameItem::Food);
	}
	_snake.die();
}

bool AutoSnake::operator==(const AutoSnake & snake) const
{
	return this->_snake == snake._snake;
}
 
 
AutoSnake::Action AutoSnake::breadthFisrtSearch()
{
	enum Flag
	{
		ready, // ready for setting
		mark,  // temp flag for marking
		disable, //disable setting
		left,
		right,
		up,
		down
	};

	// hash table
	static Flag des[HEIGHT][WIDTH]; 
	auto head = _snake.head();
	auto foodSet = _map->getSet(GameItem::Food);

	if (foodSet.empty())
	{   // not found food,do nothing
		return none;
	}
	// init des with ready flag or disable flag,init food pos with ready
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			des[i][j] = (_map->getGameItem({ j,i }) == GameItem::None ? ready : disable);
		}
	}
	for (auto& i : foodSet)
	{
		des[i.y][i.x] = ready;
	}

	// set the flag if Position {x,y} is legal and map[y][x] is NONE or Head,  and des[y][x] is ready
	// reutrn if had set flag
	auto trySetFlag = [&](int x, int y, Flag flag) {
		x = (x + WIDTH) % WIDTH;
		y = (y + HEIGHT) % HEIGHT;
		if (des[y][x] == ready\
			&& (_map->getGameItem({ x,y }) == GameItem::None|| _map->getGameItem({ x,y }) == GameItem::Food))
		{
			des[y][x] = flag;
			return true;
		}
		return false;
	};

	// replace with new flag if des[y][x] is old flag
	// reutrn if had replaced flag 
	auto tryReplaceFlag = [&](int x, int y, Flag oldFlag, Flag newFlag) {
		ASSERT_POS_LEGAL(x,y);
		if (des[y][x] == oldFlag)
		{
			des[y][x] = newFlag;
			return true;
		}
		return false;
	};

	// set flag if position is leagl , and nearby {x,y} and corresponding oldval is ready
	// reutrn if had set flag
	auto trySetNearbyFlag = [&](int x, int y, Flag flag) {
		bool leftFlag = trySetFlag(x - 1, y, flag);
		bool rightFlag = trySetFlag(x + 1, y, flag);
		bool upFlag = trySetFlag(x, y - 1, flag);
		bool downFlag = trySetFlag(x, y + 1, flag);
		return leftFlag || rightFlag || upFlag || downFlag;
	};

	// diffuse flag
	// return if had diffused flag
	auto tryDiffuseFlag = [&](Flag flag) {
		bool diffused{};
		for (int i = 0; i < HEIGHT; i++)
		{
			for (int j = 0; j <WIDTH; j++)
			{
				if (des[i][j] == flag)
				{
					diffused = (trySetNearbyFlag(j, i, mark) ? true : diffused);
				}
			}
		}
		if (diffused)
		{
			for (int i = 0; i < HEIGHT; i++)
			{
				for (int j = 0; j < WIDTH; j++)
				{
					tryReplaceFlag(j, i, mark, flag);
				}
			}
		}
		return diffused;
	};

	//init state
	trySetFlag(head.x - 1+WIDTH, head.y, left);
	trySetFlag(head.x + 1, head.y, right);
	trySetFlag(head.x, head.y - 1, up);
	trySetFlag(head.x, head.y + 1, down);

	//init action possible 
	bool leftAble = true;
	bool rightAble = true;
	bool downAble = true;
	bool upAble = true;


	//breadth first serach
	while (leftAble || rightAble || downAble || upAble)
	{
		if (leftAble)
		{
			leftAble = tryDiffuseFlag(left);
		}
		if (rightAble)
		{
			rightAble = tryDiffuseFlag(right);
		}
		if (downAble)
		{
			downAble = tryDiffuseFlag(down);
		}
		if (upAble)
		{
			upAble = tryDiffuseFlag(up);
		}
		for (auto& i : foodSet)
		{
			if(des[i.y][i.x] != ready)
			{
				switch (des[i.y][i.x])
				{
				case left:
					return toLeft;
					break;
				case right:
					return toRight;
					break;
				case up:
					return toUp;
					break;
				case down:
					return toDown;
					break;
				default:
					ASSERT_TRUE(false, "wrong case");
					break;
				}
			} 
		} 
	}
	//ASSERT_LOG("none action");
	return none;
} 
