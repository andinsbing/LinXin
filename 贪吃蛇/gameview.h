#pragma once
#include"console.h"
#include"map.h" 
#include"timer.h"
class GameScene;

class GameView
{
public:
	GameView(int refreshMillisecond,const GameScene& scene);
	GameView(const GameView&) = delete;
private: 
	void initializeWindow();
	void monitor();
	void update(const Position& pos, Global::GameItem item);
	char translate(Global::GameItem item)const;
	const Map *const _map; 
	Map _last_map_ver;
	Console _console; 
	Timer<decltype(&GameView::monitor),GameView*> _timer; 
};