#pragma once
#include "Commons/ACE_Constants.h"

class ACE_LevelMap
{
public:
	ACE_LevelMap(int map[MAP_HEIGHT][MAP_WIDTH]);
	~ACE_LevelMap();

	int GetTile(unsigned int x, unsigned int y);
	void SetTile(unsigned int x, unsigned int y, int tileValue);

	int GetMapWidth() const { return MAP_WIDTH; }
	int GetMapHeight() const { return MAP_HEIGHT; }

private:
	int** m_map;
};
