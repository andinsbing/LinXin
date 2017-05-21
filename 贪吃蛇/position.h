#pragma once
#include<Windows.h>
#include"macro.h"
#include"global.h"

#define ASSERT_POS_LEGAL(x,y) {ASSERT_TRUE(	 (x) >= 0 && (x) < ::Global::GameArea::WIDTH&&(y) >= 0 &&(y) < ::Global::GameArea::HEIGHT, "位置信息错误") }
#define ASSERT_NONE(gameItem) { ASSERT_EQUAL( (gameItem) ,::Global::GameItem::None, "gameItem必须为 NONE") }
#define ASSERT_NOT_NONE(gameItem) { ASSERT_NOT_EQUAL( (gameItem) ,::Global::GameItem::None, "gameItem不能为 NONE") }
#define ASSERT_REMOVEABLE(x,y) { ASSERT_NOT_NONE ( _map[(x)][(y)] ) } 

struct Position
{
	int x;
	int y;
	operator COORD()const
	{
		return{ static_cast<short>(x),static_cast<short>(y) };
	}
	bool operator ==(const Position& right)const
	{
		return this->x == right.x&&this->y == right.y;
	}
	bool operator !=(const Position& right)const
	{
		return this->x != right.x || this->y != right.y;
	}
	Position leftPos()const
	{
		return Position{ x - 1,y }.standard();
	}
	Position rightPos()const
	{
		return Position{ x + 1,y }.standard();
	}
	Position upPos()const
	{
		return Position{ x,y - 1 }.standard();
	}
	Position downPos()const
	{
		return Position{ x,y + 1 }.standard();
	}
	Position standard()const
	{
		return{ (x >= 0 ? x%Global::GameArea::WIDTH : x % Global::GameArea::WIDTH + Global::GameArea::WIDTH),
		(y >= 0 ? y%Global::GameArea::HEIGHT : y % Global::GameArea::HEIGHT + Global::GameArea::HEIGHT) };
	}
};

