#include "gamecontroler.h"
#include"gamescene.h"
GameControler::GameControler(int controlMillisceond,GameScene & scene):
	_scene(&scene),
	_timer(controlMillisceond,&GameControler::control,std::move(const_cast<GameControler*>(this)))
{
	_timer.run();
}

GameControler::~GameControler()
{
}

void GameControler::control()
{
	_scene->advance();
}
