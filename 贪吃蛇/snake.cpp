#include<algorithm>
#include"global.h"
#include "snake.h"

using ::Global::GameArea::WIDTH;
using ::Global::GameArea::HEIGHT;


int Snake::_IDCount = 0;

Snake::Snake(const Position& head, int snakeSize):
	_shape(),
	_lastTail(head),
	_ID(_IDCount++)
{
	ASSERT_TRUE(snakeSize > 0, "size必须大于0"); 
	for (int i = 0; i < snakeSize; i++)
	{ 
		_shape.push_back(Position{ head.x - i,head.y }.standard());
	}
}

Snake::~Snake()
{
	this->die();
}

void Snake::append(const Position & newTail)
{
	ASSERT_TRUE(std::find(_shape.begin(), _shape.end(), newTail) == _shape.end(), "节点已存在");
	_shape.push_back(newTail);
}

void Snake::up()
{
	auto &head = _shape.front();
	_lastTail = _shape.back();
	this->_shape.push_front({ head.x,(head.y - 1 + HEIGHT) % HEIGHT });
	this->_shape.pop_back(); 
}

void Snake::down()
{
	auto &head = _shape.front();
	_lastTail = _shape.back();
	this->_shape.push_front({ head.x,(head.y + 1) % HEIGHT });
	this->_shape.pop_back(); 
}

void Snake::left()
{
	auto &head = _shape.front();
	_lastTail = _shape.back();
	this->_shape.push_front({ (head.x - 1 + WIDTH) % WIDTH,head.y });
	this->_shape.pop_back(); 
}

void Snake::right()
{
	auto &head = _shape.front();
	_lastTail = _shape.back();
	this->_shape.push_front({ (head.x + 1) % WIDTH ,head.y });
	this->_shape.pop_back(); 
} 

void Snake::die()
{
	this->_shape.clear();
}

Position Snake::head() const
{
	return this->_shape.front();
}

Position Snake::tail() const
{
	return this->_shape.back();
}

const std::deque<Position>& Snake::shape() const
{
	return this->_shape;
}

Position Snake::lastTail() const
{ 
	return this->_lastTail;
}

bool Snake::operator ==(const Snake& snake) const
{
	return this->_ID == snake._ID;
}
 