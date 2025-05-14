#pragma once
#include "commons/constants.h"

class LevelMap
{
public:
	LevelMap(int map[MAP_HEIGHT][MAP_WIDTH]);
	~LevelMap();

	int GetTile(unsigned int x, unsigned int y);
	void SetTile(unsigned int x, unsigned int y, int tileValue);
	

private:
	int** m_map;
};
