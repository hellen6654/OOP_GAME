
#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include <cstdlib>
#include <ctime>
#include "audio.h"
#include "gamelib.h"
#include "Station.h"
#include "Passenger.h"

namespace game_framework
{
	Passenger::Passenger()
		: passengerType(0), x(0), y(0)
	{ }

	Passenger::Passenger(int type, int start, int end, int x, int y)
		: passengerType(type),startStation(start),finalStation(end),x(x),y(y)
	{ }
	void Passenger::LoadBitmap()
	{
		//passengerAnimation.LoadBitmap(".\\RES\\passenger\\Passenger_Circle.bmp", RGB(255, 255, 255));
		if (passengerType == 0)
			passengerAnimation.LoadBitmap(".\\RES\\passenger\\Passenger_Circle.bmp", RGB(255, 255, 255));
		else if (passengerType == 1)
			passengerAnimation.LoadBitmap(".\\RES\\passenger\\Passenger_Triangle.bmp", RGB(255, 255, 255));
		else if (passengerType == 2)
			passengerAnimation.LoadBitmap(".\\RES\\passenger\\Passenger_Square.bmp", RGB(255, 255, 255));
		else if (passengerType == 3)
			passengerAnimation.LoadBitmap(".\\RES\\passenger\\Passenger_Diamond.bmp", RGB(255, 255, 255));
		else if (passengerType == 4)
			passengerAnimation.LoadBitmap(".\\RES\\passenger\\Passenger_Pentagon.bmp", RGB(255, 255, 255));
		else if (passengerType == 5)
			passengerAnimation.LoadBitmap(".\\RES\\passenger\\Passenger_Hexagon.bmp", RGB(255, 255, 255));
		else if (passengerType == 6)
			passengerAnimation.LoadBitmap(".\\RES\\passenger\\Passenger_Hexagon.bmp", RGB(255, 255, 255));
	}

	void Passenger::SetType(int type)
	{
		passengerType = type;
	}

	void Passenger::SetXY(int xP,int yP)
	{
		x = xP+27;
		y = yP;
	}

	int Passenger::GetStartStation()
	{
		return startStation;
	}

	int Passenger::GetFinalStation()
	{
		return finalStation;
	}

	void Passenger::RandomMadePassenger(vector<Passenger>& passengerList,vector<Station> stationList,int stationMaxium,int stationTypeNum,int totalPassenagerNum)
	{ 
		int start = -1;
		int end = -1;
		int x = -1;
		int y = -1;
		int type = -1;
		srand((unsigned)time(NULL));
		for (int i = 0; i < totalPassenagerNum; i++)
		{
			start = rand() % stationMaxium;
			if (stationList[start].GetPassenagerNum() < 5) {
				end = rand() % stationMaxium;
				//start = 0;
				//end = 3;
				//type = 0;

				type = rand() % stationTypeNum;

				stationList[start].SetAddPassenagerNum(1);
				x = stationList[start].GetX();
				y = stationList[start].GetY();
				int width = 15 * (stationList[start].GetPassenagerNum() - 1);
				Passenger buf(type, start, end, x + 27 + width, y);
				passengerList.push_back(buf);
			}
			else {
				i--;
			}
		}
	}




	void Passenger::OnShow()
	{
		passengerAnimation.SetTopLeft(x, y);
		passengerAnimation.ShowBitmap();
	}

	Passenger::~Passenger()
	{

	}
}