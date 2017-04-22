#pragma once
#include<vector>
#include<functional>
#include<algorithm>
#include"position.h"
#include"global.h"
 
class Map
{ 
public:
	Map();
	~Map();
	Map(const Map&) = default;
	Map& operator =(const Map&) = default;
 
	//back to initial state
	void renew();

	void setGameItem(const Position& pos, Global::GameItem gameItem);

	void removeGameItem(const Position& pos);

	Global::GameItem getGameItem(const Position& pos)const;

	std::vector<Position> getSet(const Global::GameItem gameItem)const;

	void forEach(const std::function<void(Global::GameItem)>& fun)const;

	Position const firsOf(Global::GameItem gameItem)const;

	static bool isInLegalRange(const Position& pos);

	int count(Global::GameItem gameItem)const;

private:
	Global::GameItem _map[Global::GameArea::HEIGHT][Global::GameArea::WIDTH];
};