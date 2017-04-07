#pragma once
#include"timer.h"
class GameScene;

class GameControler
{
public:
	GameControler(int controlMillisceond,GameScene& scene);
	~GameControler();
private:
	void control();
	GameScene* _scene;
	Timer<decltype(&control),GameControler*> _timer;
};