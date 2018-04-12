#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include <vector>
#include "audio.h"
#include "gamelib.h"
#include "Station.h"
#include "Line.h"
namespace game_framework
{
	Line::Line()
		: clickedStationNumA(-1), clickedStationNumB(-1),lineColor{0,0,0}
	{}
	
	Line::~Line()
	{}

	void Line::SetLineColor(int r, int g, int b)
	{
		lineColor[0] = r;
		lineColor[1] = g;
		lineColor[2] = b;
	}
	
	bool Line::IsClickedStation(int x, int y, vector<Station> stationList, int currentStation)
	{
		for (int i = 0; i < currentStation; i++)
		{
			if (x >= stationList[i].GetX() && x <= stationList[i].GetX() + 25 &&
					y >= stationList[i].GetY() && y <= stationList[i].GetY() + 25)
			{
				if (clickedStationNumA == -1 && clickedStationNumB == -1) clickedStationNumA = i;
				else if (clickedStationNumA != -1 && clickedStationNumB == -1) clickedStationNumB = i;
				return true;
			}
		}

		return false;
	}
	bool Line::IsClickedTwoStation()
	{
		if (clickedStationNumA != -1 && clickedStationNumB != -1 && clickedStationNumA!= clickedStationNumB)
			return true;
		return false;
	}

	int Line::GetclickedTwoNumA()
	{
		return clickedStationNumA;
	}

	int Line::GetclickedTwoNumB()
	{
		return clickedStationNumB;
	}

	void Line::SetclickedTwoNumA(int num)
	{
		clickedStationNumA = num;
	}

	void Line::SetclickedTwoNumB(int num)
	{
		clickedStationNumB = num;
	}

	void Line::LoadBitmap()
	{
		//red(255.0.0),orang(255.144.0),yellow(255.255.0),green(0.255.0),blue(0.138.255),bblue(0.6.255),puple(144.0.255)
		if (lineColor[0]==255 && lineColor[1] == 0 && lineColor[2] == 0)
			lineColorBMP.LoadBitmap(".\\RES\\color\\red.bmp", RGB(255, 255, 255));
		else if (lineColor[0] == 255 && lineColor[1] == 144 && lineColor[2] == 0)
			lineColorBMP.LoadBitmap(".\\RES\\color\\orang.bmp", RGB(255, 255, 255));
		else if (lineColor[0] == 255 && lineColor[1] == 255 && lineColor[2] == 0)
			lineColorBMP.LoadBitmap(".\\RES\\color\\yellow.bmp", RGB(255, 255, 255));
		else if (lineColor[0] == 0 && lineColor[1] == 255 && lineColor[2] == 0)
			lineColorBMP.LoadBitmap(".\\RES\\color\\green.bmp", RGB(255, 255, 255));
		else if (lineColor[0] == 0 && lineColor[1] == 138 && lineColor[2] == 255)
			lineColorBMP.LoadBitmap(".\\RES\\color\\blue.bmp", RGB(255, 255, 255));
		else if (lineColor[0] == 0 && lineColor[1] == 6 && lineColor[2] == 255)
			lineColorBMP.LoadBitmap(".\\RES\\color\\bblue.bmp", RGB(255, 255, 255));
		else if (lineColor[0] == 144 && lineColor[1] == 0 && lineColor[2] == 255)
			lineColorBMP.LoadBitmap(".\\RES\\color\\purple.bmp", RGB(255, 255, 255));
		else if (lineColor[0] == 0 && lineColor[1] == 0 && lineColor[2] == 0)
			lineColorBMP.LoadBitmap(".\\RES\\color\\purple.bmp", RGB(255, 255, 255));
	}

	void Line::ShowBitmap()
	{
		if (lineColor[0] == 255 && lineColor[1] == 0 && lineColor[2] == 0)
			lineColorBMP.SetTopLeft(240, 565);
		else if (lineColor[0] == 255 && lineColor[1] == 144 && lineColor[2] == 0)
			lineColorBMP.SetTopLeft(285, 565);
		else if (lineColor[0] == 255 && lineColor[1] == 255 && lineColor[2] == 0)
			lineColorBMP.SetTopLeft(330, 565);
		else if (lineColor[0] == 0 && lineColor[1] == 255 && lineColor[2] == 0)
			lineColorBMP.SetTopLeft(375, 565);
		else if (lineColor[0] == 0 && lineColor[1] == 138 && lineColor[2] == 255)
			lineColorBMP.SetTopLeft(420, 565);
		else if (lineColor[0] == 0 && lineColor[1] == 6 && lineColor[2] == 255)
			lineColorBMP.SetTopLeft(465, 565);
		else if (lineColor[0] == 144 && lineColor[1] == 0 && lineColor[2] == 255)
			lineColorBMP.SetTopLeft(510, 565);

		lineColorBMP.ShowBitmap();
	}

	void Line::DrawRailway(int startX, int startY, int endX, int endY)
	{
		const int BORDERSIZE = 15;
		//const int rectHeight = 20;
		CDC* pDC = CDDraw::GetBackCDC();
		CPen* pp, p(PS_NULL, 0, RGB(0, 0, 0));
		pp = pDC->SelectObject(&p);
		
		//比對start 跟 end 去判斷怎麼畫出線來

		CBrush b1(RGB(lineColor[0], lineColor[1], lineColor[2]));
		pDC->SelectObject(&b1);
		CBrush b2(RGB(lineColor[0], lineColor[1], lineColor[2]));
		pDC->SelectObject(&b2);

		if (endX >= startX && endY >= startY)  //結束點在右下
		{
			
			pDC->Rectangle(startX, startY, endX + BORDERSIZE, startY + BORDERSIZE);
			pDC->Rectangle(endX, startY, endX + BORDERSIZE, endY+BORDERSIZE);
		}
		else if (endX < startX && endY > startY) //結束點在左下
		{
			
			pDC->Rectangle(startX, startY, startX + BORDERSIZE, endY + BORDERSIZE);
			pDC->Rectangle(startX + BORDERSIZE, endY , endX , endY + BORDERSIZE);
		}
		else if (endX <= startX && endY <= startY) //結束點在左上
		{
			pDC->Rectangle(startX, startY, endX , startY + BORDERSIZE);
			pDC->Rectangle(endX ,endY ,endX+BORDERSIZE, startY + BORDERSIZE);
		}
		else if(endX > startX && endY < startY) //結束點在右上
		{
			
			pDC->Rectangle(startX, endY, startX + BORDERSIZE, startY);
			pDC->Rectangle(startX, endY, endX, endY + BORDERSIZE);
		}
		//釋放 pen brush、Back、Plain的CDC
		pDC->SelectObject(pp);
		//pDC->SelectObject(pb);
		CDDraw::ReleaseBackCDC();
	}
}