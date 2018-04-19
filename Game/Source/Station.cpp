
#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include <cstdlib>
#include <ctime>
#include "audio.h"
#include "gamelib.h"
#include "Station.h"

namespace game_framework
{
Station::Station()
    : stationType(0), x(0), y(0), centerPositionX(0), centerPositionY(0), currentPassengerNum(0)
{ }

Station::Station(int type, int set_x, int set_y, int a)
    : stationType(type), x(set_x), y(set_y), centerPositionX(set_x + 13), centerPositionY(set_y + 13), currentPassengerNum(a)
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
        stationAnimation.LoadBitmap(".\\RES\\Station\\Station_Rectangle.bmp", RGB(255, 255, 255));
    else if (stationType == 5)
        stationAnimation.LoadBitmap(".\\RES\\Station\\Station_Pentagon.bmp", RGB(255, 255, 255));
    else if (stationType == 6)
        stationAnimation.LoadBitmap(".\\RES\\Station\\Station_Hexagon.bmp", RGB(255, 255, 255));
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
int Station::Getpassenger()
{
    return currentPassengerNum;
}
void Station::Setpassenger()
{
    currentPassengerNum++;
}
int Station::GetCenterPositionX()
{
    return centerPositionX;
}

int Station::GetCenterPositionY()
{
    return centerPositionY;
}

void Station::SetType(int type)
{
    stationType = type;
}

void Station::RandomBuildStation(vector<Station>& stationList)
{
    int x = -1;
    int y = -1;
    int type = -1;
    srand((unsigned)time(NULL));

    for (int i = 0; i < MAXIUM_STATION; i++)
    {
        type = rand() % MAXIUM_STATION_TYPE; //隨機選擇車站的形狀
        x = MIN_GAME_MAP_SIDE_X + rand() % (MAX_GAME_MAP_SIDE_X - MIN_GAME_MAP_SIDE_X);// 隨機選車站的X位置
        y = MIN_GAME_MAP_SIDE_Y + rand() % (MAX_GAME_MAP_SIDE_Y - MIN_GAME_MAP_SIDE_Y);// 隨機選車站的Y位置
        Station buf(type, x, y, 0);
        stationList.push_back(buf);
    }

    return;
}
void Station::CheckedOverLappingStation(vector<Station>& stationList)
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

void Station::OnShow()
{
    stationAnimation.SetTopLeft(x, y);
    stationAnimation.ShowBitmap();
}

Station::~Station()
{
}
}