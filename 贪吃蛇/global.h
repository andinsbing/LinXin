#pragma once

namespace Global
{
	enum class GameItem
	{
		None,
		SnakeBody,
		Wall,
		Food
	}; 
	namespace GameArea
	{
		const int WIDTH = 40;
		const int HEIGHT = 20;
	}
}