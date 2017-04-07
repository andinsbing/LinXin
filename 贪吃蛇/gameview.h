#pragma once
#include"console.h"
#include"map.h" 
#include"timer.h"

class GameView
{
public:
	GameView(int refreshMillisecond,const Map& map);
	GameView(const GameView&) = delete;
private: 
	void monitor();
	void update(const Position& pos, Global::GameItem item);
	char mapToSymbol(Global::GameItem item);
	const Map *const _map; 
	Map _last_map_ver;
	Console _console; 
	Timer<decltype(&GameView::monitor),GameView*> _timer; 
};