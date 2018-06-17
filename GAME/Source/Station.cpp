
#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include <cstdlib>
#include <ctime>
#include "audio.h"
#include "gamelib.h"
#include "Passenger.h"
#include "Station.h"

namespace game_framework
{
	Station::Station()
		:stationType(0), x(0), y(0), centerPositionX(0), centerPositionY(0)
	{ }

	Station::Station(int type, int set_x, int set_y)
		: stationType(type), x(set_x), y(set_y), centerPositionX(set_x + 13), centerPositionY(set_y + 13),passenagerNum(0)
	{ }

	void Station::LoadBitmap()
	{
		if (stationType == 0)
			stationAnimation.LoadBitmap(".\\RES\\Station\\Station_Circle.bmp", RGB(255, 255, 255));
		else if (stationType == 1)
			stationAnimation.LoadBitmap(".\\RES\\Station\\Station_Triangle.bmp", RGB(255, 255, 255));
		else if (stationType == 2)
			stationAnimation.LoadBitmap(".\\RES\\Station\\Station_Square.bmp", RGB(255, 255, 255));
		else if (stationType == 3)
			stationAnimation.LoadBitmap(".\\RES\\Station\\Station_Diamond.bmp", RGB(255, 255, 255));
		else if (stationType == 4)
			stationAnimation.LoadBitmap(".\\RES\\Station\\Station_Pentagon.bmp", RGB(255, 255, 255));
		else if (stationType == 5)
			stationAnimation.LoadBitmap(".\\RES\\Station\\Station_Hexagon.bmp", RGB(255, 255, 255));
	}

	void Station::SetXY(int set_x, int set_y)
	{
		x = set_x;
		y = set_y;
	}

	void Station::SetPassenagerNum(int num)
	{
		passenagerNum = num;
	}

	void Station::SetAddPassenagerNum(int num)
	{
		passenagerNum += num;
	}

	int Station::GetX()
	{
		return x;
	}

	int Station::GetY()
	{
		return y;
	}

	int Station::GetCenterPositionX()
	{
		return centerPositionX;
	}

	int Station::GetCenterPositionY()
	{
		return centerPositionY;
	}

	int Station::GetPassenagerNum()
	{
		return passenagerNum;
	}

	void Station::SetType(int type)
	{
		stationType = type;

	}

	void Station::RandomBuildStation(vector<Station> &stationList)
	{
		vector<Station> a;
		stationList.assign(a.begin(), a.end());
		int x = -1;
		int y = -1;
		int type = -1;
		srand((unsigned)time(NULL));
		for (int i = 0; i < MAXIUM_STATION; i++)
		{
			//type = rand() % MAXIUM_STATION_TYPE; //隨機選擇車站的形狀
			type = i; 
			x = MIN_GAME_MAP_SIDE_X + rand() % (MAX_GAME_MAP_SIDE_X - MIN_GAME_MAP_SIDE_X);// 隨機選車站的X位置
			y = MIN_GAME_MAP_SIDE_Y + rand() % (MAX_GAME_MAP_SIDE_Y - MIN_GAME_MAP_SIDE_Y);// 隨機選車站的Y位置
			Station buf(type, x, y);
			stationList.push_back(buf);
			stationList[i].LoadBitmap();
		}
		return;
	}

	void Station::CheckedOverLappingStation(vector<Station> &stationList)
	{
		for (int i = 1; i < MAXIUM_STATION; i++)
		{
			for (int j = 0; j < i; j++)
			{
				while (1)
				{
					if (stationList[j].GetX() >= stationList[i].GetX() - 50 && stationList[j].GetX() <= stationList[i].GetX() + 50 &&
						stationList[j].GetY() >= stationList[i].GetY() - 50 && stationList[j].GetY() <= stationList[i].GetY() + 50)
					{
						x = MIN_GAME_MAP_SIDE_X + rand() % (MAX_GAME_MAP_SIDE_X - MIN_GAME_MAP_SIDE_X);// 隨機選車站的X位置
						y = MIN_GAME_MAP_SIDE_Y + rand() % (MAX_GAME_MAP_SIDE_Y - MIN_GAME_MAP_SIDE_Y);// 隨機選車站的Y位置
						stationList[i].SetXY(x, y);
					}
					else break;
				}
			}
		}
	}

	void Station::SetPassengerToStationPosition(Passenger* p)
	{
		p->SetXY(x +25+(passenagerNum - 1)*10+passenagerNum*1, y);
		passengerInStationList.push_back(p);
	}

	void Station::RefreshPassengerPosition()
	{
		passenagerNum =(int)passengerInStationList.size();
		for (int i = 0; i < passenagerNum; i++)
		{
			passengerInStationList[i]->SetXY(x + 25 + i * 10 + i * 1,y);
		}
	}

	void Station::ErasePassenger(Passenger* p)
	{
		for (unsigned i = passengerInStationList.size()-1; i >=0 ; i--)
		{
			if (i >= 6)
			{
				break;
			}
			else if (passengerInStationList[i]->GetStartStation() == p->GetStartStation() &&
				passengerInStationList[i]->GetFinalStation() == p->GetFinalStation())
			{
				passengerInStationList.erase(passengerInStationList.begin() + i);
				return;
			}
			
			
		}
		passenagerNum = (int)passengerInStationList.size();
	}

	void Station::OnShowStation()
	{
		stationAnimation.SetTopLeft(x, y);
		stationAnimation.ShowBitmap();	
	}

	void Station::OnShowPassengerInStation()
	{
		
		for (unsigned i = 0; i < passengerInStationList.size(); i++)
		{
			passengerInStationList[i]->OnShow();
		}
	}

	Station::~Station()
	{

	}
}