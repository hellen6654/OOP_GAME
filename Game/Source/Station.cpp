
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
			station_animation.LoadBitmap(".\\RES\\Station\\Station_Circle.bmp",   RGB(255, 255, 255));
		else if(station_type == 1)
			station_animation.LoadBitmap(".\\RES\\Station\\Station_Triangle.bmp", RGB(255, 255, 255));
		else if (station_type == 2)
			station_animation.LoadBitmap(".\\RES\\Station\\Station_Square.bmp",   RGB(255, 255, 255));
		else if (station_type == 3)
			station_animation.LoadBitmap(".\\RES\\Station\\Station_Diamond.bmp",  RGB(255, 255, 255));
		else if (station_type == 4)
			station_animation.LoadBitmap(".\\RES\\Station\\Station_Rectangle.bmp", RGB(255, 255, 255));
		else if (station_type == 5)
			station_animation.LoadBitmap(".\\RES\\Station\\Station_Pentagon.bmp", RGB(255, 255, 255));
		else if (station_type == 6)
			station_animation.LoadBitmap(".\\RES\\Station\\Station_Hexagon.bmp",  RGB(255, 255, 255));
	}
	void Station::SetXY(int set_x, int set_y)
	{
		x = set_x;
		y = set_y;
	}
	int Station::GetX()
	{
		return x;
	}
	int Station::GetY()
	{
		return y;
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