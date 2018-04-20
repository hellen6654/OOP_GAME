
#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include <cstdlib>
#include <ctime>
#include "audio.h"
#include "gamelib.h"
#include "Passenger.h"

namespace game_framework
{
	Passenger::Passenger()
		: passengerType(0), x(0), y(0)
	{ }


	void Passenger::LoadBitmap()
	{
		passengerAnimation.LoadBitmap(".\\RES\\passenger\\Passenger_Circle.bmp", RGB(255, 255, 255));

		/*if (passengerType == 0)
			passengerAnimation.LoadBitmap(".\\RES\\passenger\\Passenger_Circle.bmp", RGB(255, 255, 255));
		else if (passengerType == 1)
			passengerAnimation.LoadBitmap(".\\RES\\passenger\\Passenger_Triangle.bmp", RGB(255, 255, 255));
		else if (passengerType == 2)
			passengerAnimation.LoadBitmap(".\\RES\\passenger\\Passenger_Square.bmp", RGB(255, 255, 255));

		/*else if (passengerType == 3)
		passengerAnimation.LoadBitmap(".\\RES\\passenger\\Passenger_Diamond.bmp", RGB(255, 255, 255));
		else if (passengerType == 4)
		passengerAnimation.LoadBitmap(".\\RES\\passenger\\Passenger_Rectangle.bmp", RGB(255, 255, 255));
		else if (passengerType == 5)
		passengerAnimation.LoadBitmap(".\\RES\\passenger\\Passenger_Pentagon.bmp", RGB(255, 255, 255));
		else if (passengerType == 6)
		passengerAnimation.LoadBitmap(".\\RES\\passenger\\Passenger_Hexagon.bmp", RGB(255, 255, 255));*/
	}
	void Passenger::SetType(int type)
	{
		passengerType = type;
	}

	void Passenger::SetX(int xP)
	{
		x = xP;
	}

	void Passenger::SetY(int yP)
	{
		y = yP;
	}

	int Passenger::GetStartStation()
	{
		return startStation;
	}

	void Passenger::RandomMadePassenger(vector<Passenger>& passengerList,int stationMaxium,int stationTypeNum)
	{ 
		srand((unsigned)time(NULL));
		for (int i = 0; i < stationMaxium; i++)
		{
			startStation = rand() % stationTypeNum;
		}
	}

	void Passenger::RandomMadePassenger(int stationTypeNum)
	{
		srand((unsigned)time(NULL));
		startStation = rand() % stationTypeNum;
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