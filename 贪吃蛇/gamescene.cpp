#include<ctime>
#include "gamescene.h"

using ::Global::GameArea::WIDTH;
using ::Global::GameArea::HEIGHT;
using ::Global::GameItem;
 

GameScene::GameScene():
	_map(), 
	_foodLimit(4),
	_autoSnakeSet()
{ 
	srand(static_cast<unsigned int>(std::time(NULL))); 
	renew();
}

GameScene::~GameScene()
{
}

void GameScene::advance()
{ 
	auto temp = _autoSnakeSet.begin();
	for (auto& it=_autoSnakeSet.begin();it!=_autoSnakeSet.end();)
	{// removeble traversal 
		temp = it;
		it++;
		temp->advance();
		handleCollision(*temp); 
	}
}

const Map & GameScene::map() const
{
	return _map;
}

void GameScene::renew()
{
	_autoSnakeSet.clear();
	_map.renew();
	addAutoSnake({ 2,2 }, 5);
	addAutoSnake({ 0,10 }, 5);
	addAutoSnake({ 12,12 }, 5);
	//addAutoSnake({ 15,15 }, 5);
	//addAutoSnake({ 18,18 }, 1);
	//addAutoSnake({ 19,0 }, 1);
	adjustFood();
}

void GameScene::adjustFood()
{
	int x = 0;
	int y = 0;
	for (int i = _map.count(GameItem::Food); i < _foodLimit; i++)
	{
		do
		{
			x = std::rand() % WIDTH;
			y = std::rand() % HEIGHT;
		} while (_map.getGameItem({ x,y }) != GameItem::None); 
		_map.setGameItem({ x,y }, GameItem::Food);
	}
}

void GameScene::addAutoSnake(const Position& head, int snakeSize)
{
	_autoSnakeSet.emplace_back(&_map,head, snakeSize);
	_map.setGameItem(head, GameItem::SnakeBody);
}

void GameScene::handleCollision(AutoSnake& snake)
{
	auto collisionItem = snake.collisionItem();
	switch (collisionItem)
	{
	case GameItem::None:
		break;  
	case GameItem::Wall:
		break;
	case GameItem::Food:
		snake.appendTail();
  		adjustFood(); 
		break;
	case GameItem::SnakeBody:
		removeAutoSnake(snake);
		break;
	default: 
		ASSERT_TRUE(false, "error case");
		break;
	}
}

void GameScene::removeAutoSnake(AutoSnake& snake)
{
	auto it = std::find(_autoSnakeSet.begin(), _autoSnakeSet.end(), snake);
	ASSERT_TRUE(it != _autoSnakeSet.end(), "snake not exist");
	_autoSnakeSet.erase(it);
}

