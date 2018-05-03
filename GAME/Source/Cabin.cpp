#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include <cstdlib>
#include <ctime>
#include "audio.h"
#include "gamelib.h"
#include "Cabin.h"
#include "Passenger.h"
namespace game_framework 
{
	Cabin::Cabin()
	{
		const int BASIC_VELOCITY = 5;
		direction = 'U';
		velocity = BASIC_VELOCITY;
		x = 300;
		y = 0;
		head = x + 42;
		isTurn = false;
		color[0] = 255;
		color[1] = 0;
		color[2] = 0;
	}
	Cabin::~Cabin()
	{}
	void Cabin::SetXY(int setX, int setY)
	{
		x = setX;
		y = setY;
	}
	void Cabin::SetVelocity(int v)
	{
		velocity = v;
	}
	void Cabin::SetDirection(char d)
	{
		direction = d;
	}
	int Cabin::GetX()
	{
		return x;
	}
	int Cabin::GetY()
	{
		return y;
	}
	int Cabin::GetVelocity()
	{
		return velocity;
	}
	void Cabin::OnMove()
	{
		if (!isTurn) //如果不是轉彎
		{
			if (direction == 'U'&& y<=500) //UP
			{
				SetXY(x, y + velocity);
			}
			else if (direction == 'D')//Down
			{
				SetXY(x, y - velocity);
			}
			else if (direction == 'R')//Right
			{
				SetXY(x + velocity, y);
			}
			else if (direction == 'L')//Left
			{
				SetXY(x - velocity, y);
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
		if (isTurn) //轉彎的狀態
		{
			if (direction == 'U') //UP
			{
				
			}
			else if (direction == 'D')//Down
			{
				
			}
			else if (direction == 'R')//Right
			{
				
			}
			else if (direction == 'L')//Left
			{
				
			}
			isTurn = !isTurn;
		}
		else //不用轉彎
		{
			pDC->Rectangle(x, y, x+28,y+42);
		}
		//pDC->Rectangle(startX, startY, endX + BORDERSIZE, startY + BORDERSIZE);
		pDC->SelectObject(pp);
		//pDC->SelectObject(pb);
		CDDraw::ReleaseBackCDC();
	}
}