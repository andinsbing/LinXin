#pragma once

#include<vector>
#include<functional>
#include"position.h"
class Map;

class FlagController
{
public:
	enum FlagType
	{
		ready,
		disable,
		left,
		right,
		up,
		down,
		mark, // temp for diffusion
		diffused,
	};
	FlagController(Map* map);
	void updataFlagMap();
	void setFlagIf(const Position& pos, FlagType flag, const std::function<bool(FlagType)>& fun);
	void setFlagIf(const Position& pos, FlagType newFlag, FlagType oldFlag);
	void setFlag(const Position& pos, FlagType flag);
	void setNearbyFlagIf(const Position& pos, FlagType flag, const std::function<bool(FlagType)>& fun);
	void setNearbyFlagIf(const Position& pos, FlagType newFlag, FlagType oldFlag);
	void setNearbyFlag(const Position& pos, FlagType flag);
	FlagType getFlag(const Position& pos)const;
	bool diffuse(FlagType flag);
	int count(FlagType flag)const;

	std::vector<Position> getSet(FlagType flag)const;

private:
	Map *const _map;
	FlagType _flagMap[Global::GameArea::HEIGHT][Global::GameArea::WIDTH];
};