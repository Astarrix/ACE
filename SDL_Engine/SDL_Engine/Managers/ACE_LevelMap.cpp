#include "ACE_LevelMap.h"

#include <iostream>
#include <ostream>

/**
 * 0 = empty;
 * 1 = blocked;
 * 2 = coin;
 * 3 = ???;
 */

ACE_LevelMap::ACE_LevelMap(int map[MAP_HEIGHT][MAP_WIDTH])
{
	m_map = new int* [MAP_HEIGHT];
	//alloc array
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		m_map[i] = new int[MAP_WIDTH];
	}
	//populate array
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			m_map[i][j] = map[i][j];
		}
	}
}

ACE_LevelMap::~ACE_LevelMap()
{
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		delete[] m_map[i];
	}
	delete[] m_map;
}

int ACE_LevelMap::GetTile(unsigned int x, unsigned int y)
{
	if (x < MAP_WIDTH && y < MAP_HEIGHT)
	{
		return m_map[y][x];
	}

	return 0;
}

void ACE_LevelMap::SetTile(unsigned int x, unsigned int y, int tileValue)
{
	if (x < MAP_WIDTH && y < MAP_HEIGHT)
	{
		m_map[y][x] = tileValue;
	}
}
