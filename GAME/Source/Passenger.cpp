
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

Passenger::Passenger(int type, int set_x, int set_y)
    : passengerType(type), x(set_x), y(set_y)
{ }

void Passenger::LoadBitmap()
{
    if (passengerType == 0)
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

void Passenger::SetXY(int set_x, int set_y)
{
    x = set_x;
    y = set_y;
}

int Passenger::GetX()
{
    return x;
}

int Passenger::GetY()
{
    return y;
}



void Passenger::SetType(int type)
{
    passengerType = type;
}

void Passenger::RandomBuildPassenger(vector< Passenger>& passengerList, int stationx, int stationy, int passenger, int type)
{
    int x = -1;
    int y = -1;
    x = stationx + (passenger + 1) * 25; // 隨機選乘客的X位置 passenger=乘客數量
    y = stationy - 5; // 隨機選乘客的Y位置
    Passenger buf(type, x, y);
    passengerList.push_back(buf);
    return;
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