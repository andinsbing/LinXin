#pragma once
#include"timer.h"
class GameScene;

class GameControler
{
public:
	GameControler(int controlMillisceond,GameScene& scene);
	~GameControler();
	void start();
	void pause();
	//释放控制权限，不再控制
	void release(); 
private:
	void control();
	GameScene*const _scene;
	Timer<decltype(&control),GameControler*> _timer;
};