#pragma once
#include"gamescene.h"
#include"gameview.h"
#include"gamecontroler.h"

class Game
{
public:
	enum State
	{
		started,
		paused,
		over
	};
public:
	Game();
	~Game(); 
	void start(); 
	void pause(); 
	void end();
	void renew();
	bool isGameOver()const;
private:
	GameScene _scene;
	GameView _view;
	GameControler _controler;
	State _state;
};