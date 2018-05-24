#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "audio.h"
#include "gamelib.h"
#include "Cabin.h"
#include "Passenger.h"
#include "Station.h"
namespace game_framework
{
Cabin::Cabin()
{ }
Cabin::Cabin(int setX, int setY, int R, int G, int B)
{
    nextPoint = 0;
    prePoint = 1;
    leftTopX = setX;
    leftTopY = setY;
    rightDownX = setX + 42;
    rightDownY = setY + 28;
    movingDirection = "up";
    goingDirection = "head";
    velocity = BASIC_VELOCITY;
    color[0] = R;
    color[1] = G;
    color[2] = B;
}
Cabin::~Cabin()
{ }
void Cabin::SetXY(int setX, int setY)
{
    leftTopX = setX;
    leftTopY = setY;
    rightDownX = setX + 42;
    rightDownY = setY + 28;
}
void Cabin::SetVelocity(int v)
{
    velocity = v;
}

void Cabin::SetMovingCabin(string movingDirection, int num)
{
    if (movingDirection == "up")
    {
        leftTopY -= num;
        rightDownX = leftTopX + 28;
        rightDownY = leftTopY + 42;
    }
    else if (movingDirection == "down")
    {
        leftTopY += num;
        rightDownX = leftTopX + 28;
        rightDownY = leftTopY + 42;
    }
    else if (movingDirection == "right")
    {
        leftTopX += num;
        rightDownX = leftTopX + 42;
        rightDownY = leftTopY + 28;
    }
    else if (movingDirection == "left")
    {
        leftTopX -= num;
        rightDownX = leftTopX + 42;
        rightDownY = leftTopY + 28;
    }
}

void Cabin::SetRGB(int R, int G, int B)
{
    color[0] = R;
    color[1] = G;
    color[2] = B;
}
void Cabin::SetGoingDirection(string s)
{
    goingDirection = s;
}
void Cabin::SetMovingDirection(string s)
{
    movingDirection = s;
}
void Cabin::SetLinePoint(vector<int> x, vector<int> y)
{
    updateLinePointX.assign(x.begin(), x.end());
    updateLinePointY.assign(y.begin(), y.end());

    if (linePointX.empty() && linePointY.empty())
    {
        linePointX.assign(x.begin(), x.end());
        linePointY.assign(y.begin(), y.end());
    }
}
void Cabin::SetPassedStation(vector<int> station)
{
    passedStation.assign(station.begin(), station.end());
}
int Cabin::GetX()
{
    return leftTopX;
}
int Cabin::GetY()
{
    return leftTopY;
}
int Cabin::GetVelocity()
{
    return velocity;
}
int Cabin::GetNextPoint()
{
    return nextPoint;
}
void Cabin::GetRGB(int& R, int& G, int& B)
{
    R = color[0];
    G = color[1];
    B = color[2];
}
void Cabin::OnMove(vector<Station> totalStationList)
{
    int sizeVecX = linePointX.size();
    int sizeVecY = linePointY.size();
    int startX = linePointX[prePoint];
    //int startX = totalStationList[passedStation[prePoint]].GetX();
    int startY = linePointY[prePoint];
    int endX = linePointX[nextPoint];
    int endY = linePointY[nextPoint];
    int nowPointX = leftTopX;
    int nowPointY = leftTopY;
    // X�y�ЬۦP �N��V�W�ΦV�U����
    // Y�y�ЬۦP �N��V���ΦV�k����

    if (startX == endX)
    {
        if (startY > endY) //�V�W����
        {
            movingDirection = "up";
        }
        else if (startY < endY) //�V�U����
        {
            movingDirection = "down";
        }
    }
    else if (startY == endY)
    {
        if (startX > endX)// �V������
        {
            movingDirection = "left";
        }
        else if (startX < endX) //�V�k����
        {
            movingDirection = "right";
        }
    }

    if (movingDirection == "up")
    {
        if (nowPointY > endY)
            SetMovingCabin(movingDirection, velocity);
        else if (nowPointY <= endY)
        {
            if (nextPoint >= sizeVecX - 1)
            {
                goingDirection = "back";
            }
            else if (nextPoint == 0)
            {
                goingDirection = "head";
            }

            if (goingDirection == "head")
            {
                prePoint = nextPoint;
                nextPoint++;
            }
            else if (goingDirection == "back")
            {
                prePoint = nextPoint;
                nextPoint--;
            }
        }
    }
    else if (movingDirection == "down")
    {
        if (nowPointY < endY)
            SetMovingCabin(movingDirection, velocity);
        else if (nowPointY >= endY)
        {
            if (nextPoint >= sizeVecX - 1)
            {
                goingDirection = "back";
            }
            else if (nextPoint == 0)
            {
                goingDirection = "head";
            }

            if (goingDirection == "head")
            {
                prePoint = nextPoint;
                nextPoint++;
            }
            else if (goingDirection == "back")
            {
                prePoint = nextPoint;
                nextPoint--;
            }
        }
    }
    else if (movingDirection == "left")
    {
        if (nowPointX > endX)
            SetMovingCabin(movingDirection, velocity);
        else if (nowPointX <= endX)
        {
            if (nextPoint >= sizeVecX - 1)
            {
                goingDirection = "back";
            }
            else if (nextPoint == 0)
            {
                goingDirection = "head";
            }

            if (goingDirection == "head")
            {
                prePoint = nextPoint;
                nextPoint++;
            }
            else if (goingDirection == "back")
            {
                prePoint = nextPoint;
                nextPoint--;
            }
        }
    }
    else if (movingDirection == "right")
    {
        if (nowPointX < endX)
            SetMovingCabin(movingDirection, velocity);
        else if (nowPointX >= endX)
        {
            if (nextPoint >= sizeVecX - 1)
            {
                goingDirection = "back";
            }
            else if (nextPoint == 0)
            {
                goingDirection = "head";
            }

            if (goingDirection == "head")
            {
                prePoint = nextPoint;
                nextPoint++;
            }
            else if (goingDirection == "back")
            {
                prePoint = nextPoint;
                nextPoint--;
            }
        }
    }
}
void Cabin::OnShow()
{
    CDC* pDC = CDDraw::GetBackCDC();
    CPen* pp, p(PS_NULL, 0, RGB(0, 0, 0));
    pp = pDC->SelectObject(&p);
    CBrush b(RGB(color[0], color[1], color[2]));
    pDC->SelectObject(&b);
    pDC->Rectangle(leftTopX, leftTopY, rightDownX, rightDownY);
    pDC->SelectObject(pp);
    //pDC->SelectObject(pb);
    CDDraw::ReleaseBackCDC();
}



void Cabin::SetPassengerPosition()
{
    int vecSize = passengerOnCabinList.size();

    if (movingDirection == "right" || movingDirection == "left")
    {
        for (int i = 0; i < vecSize; i++)
        {
            passengerOnCabinList[i].SetXY(leftTopX + PASSENGERPOSITIONX_RIGHTLEFT[i], leftTopY + PASSENGERPOSITIONY_RIGHTLEFT[i]);
        }
    }
    else if (movingDirection == "up" || movingDirection == "down")
    {
        for (int i = 0; i < vecSize; i++)
        {
            passengerOnCabinList[i].SetXY(leftTopX + PASSENGERPOSITIONX_UPDOWN[i], leftTopY + PASSENGERPOSITIONY_UPDOWN[i]);
        }
    }
}
bool Cabin::IsCabinFull()
{
    return (passengerOnCabinList.size() >= 6); //�ݭ��Ȧ��S���W�L6��
}

void Cabin::PassengerGetOn(vector<Passenger>& passengerList, int nowStation)
{
    int vecSize = passengerList.size();

    for (int i = 0; i < vecSize; i++)
    {
        if (passengerList[i].GetStartStation() == nowStation )
        {
            passengerOnCabinList.push_back(passengerList[i]);
            passengerList.erase(passengerList.begin() + i);
            vecSize = passengerList.size();
        }
    }
}

bool Cabin::IsPassengerGetOut(int nowStation)
{
    int vecSize = passengerOnCabinList.size();

    if (vecSize >= MAXPASSENGERNUM) return false;

    for (int i = 0; i < vecSize; i++)
        if (passengerOnCabinList[i].GetFinalStation() == nowStation) return true;

    return false;
}
int Cabin::PassengerGetOut(int nowStation)
{
    int vecSize = passengerOnCabinList.size();

    for (int i = 0; i < vecSize; i++)
        if (passengerOnCabinList[i].GetFinalStation() == nowStation)
            passengerOnCabinList.erase(passengerOnCabinList.begin() + i);

    return 1;
}

bool Cabin::IsStop()
{
    return isStop;
}

void Cabin::SetIsStop(bool b)
{
    isStop = b;
}

}