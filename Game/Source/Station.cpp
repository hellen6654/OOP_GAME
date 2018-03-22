
#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Station.h"

namespace game_framework 
{
	Station::Station()
		:station_type(0), x(0), y(0)
	{ }
	Station::Station(int type,int set_x,int set_y)
		:station_type(type),x(set_x),y(set_y)
	{ }

	void Station::LoadBitmap()
	{
		
		if (station_type == 0)
			station_animation.LoadBitmap(IDB_STAT00_CIRCLE,   RGB(255, 255, 255));
		else if(station_type == 1)
			station_animation.LoadBitmap(IDB_STAT01_TRIANGLE, RGB(255, 255, 255));
		else if (station_type == 2)
			station_animation.LoadBitmap(IDB_STAT02_SQUARE,   RGB(255, 255, 255));
		else if (station_type == 3)
			station_animation.LoadBitmap(IDB_STAT03_DIAMOND,  RGB(255, 255, 255));
		else if (station_type == 4)
			station_animation.LoadBitmap(IDB_STAT04_RETANGLE, RGB(255, 255, 255));
		else if (station_type == 5)
			station_animation.LoadBitmap(IDB_STAT05_PENTAGON, RGB(255, 255, 255));
		else if (station_type == 6)
			station_animation.LoadBitmap(IDB_STAT06_HEXAGON,  RGB(255, 255, 255));
	}
	void Station::SetXY(int set_x, int set_y)
	{
		x = set_x;
		y = set_y;
	}
	void Station::SetType(int type)
	{
		station_type = type;
	}
	void Station::OnShow()
	{
		station_animation.SetTopLeft(x, y);
		station_animation.ShowBitmap();
	}
	Station::~Station()
	{

	}
}