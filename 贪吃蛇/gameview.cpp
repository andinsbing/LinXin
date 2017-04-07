#include<iostream>
#include "gameview.h"
#include"gamescene.h"
 
using ::Global::GameArea::WIDTH;
using ::Global::GameArea::HEIGHT;
using ::Global::GameItem;

GameView::GameView(int refreshMillisecond,const Map& map) :
	_map(&map),
	_last_map_ver(),
	_console(),
	_timer(refreshMillisecond,&GameView::monitor, std::move(const_cast<GameView*>(this)))
{
	ASSERT_NOT_NULLPTR(_map, "_map²»ÄÜÎª¿Õ"); 
	_timer.run();
} 

void GameView::monitor()
{
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			Position pos{ j, i };
			auto item = _map->getGameItem(pos);
			if (item != _last_map_ver.getGameItem(pos))
			{
				update(pos, item);
			}
		}
	}
}

void GameView::update(const Position & pos, GameItem item)
{
	_last_map_ver.setGameItem(pos, item);
	_console.putElement(static_cast<COORD>(pos), mapToSymbol(item)); 
}

char GameView::mapToSymbol(GameItem item)
{
	char ret = 0;
	switch (item)
	{
	case GameItem::None:
		ret = ' ';
		break;
	case GameItem::SnakeBody:
		ret = '*';
		break;
	case GameItem::Wall:
		ret = '+';
		break;
	case GameItem::Food:
		ret = '@';
		break;
	default:
		ASSERT_TRUE(false, "error case");
		break;
	}
	return ret;
}


