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
		: clickedStartStationNum(-1), clickedEndStationNum(-1),lineColor{0,0,0}
	{}
	
	Line::~Line()
	{}

	void Line::DrawRailway(int startX, int startY, int endX, int endY)
	{
		const int BORDERSIZE = 14;
		//const int rectHeight = 20;
		CDC* pDC = CDDraw::GetBackCDC();
		CPen* pp, p(PS_NULL, 0, RGB(0, 0, 0));
		pp = pDC->SelectObject(&p);

		//比對start 跟 end 去判斷怎麼畫出線來

		CBrush b1(RGB(lineColor[0], lineColor[1], lineColor[2]));
		pDC->SelectObject(&b1);
		

		if (endX >= startX && endY >= startY)  //結束點在右下
		{
			pDC->Rectangle(startX, startY, endX + BORDERSIZE, startY + BORDERSIZE);
			pDC->Rectangle(endX, startY, endX + BORDERSIZE, endY + BORDERSIZE);
		}
		else if (endX < startX && endY > startY) //結束點在左下
		{

			pDC->Rectangle(startX, startY, startX + BORDERSIZE, endY + BORDERSIZE);
			pDC->Rectangle(startX + BORDERSIZE, endY, endX, endY + BORDERSIZE);
		}
		else if (endX <= startX && endY <= startY) //結束點在左上
		{
			pDC->Rectangle(startX, startY, endX, startY + BORDERSIZE);
			pDC->Rectangle(endX, endY, endX + BORDERSIZE, startY + BORDERSIZE);
		}
		else if (endX > startX && endY < startY) //結束點在右上
		{
			pDC->Rectangle(startX, endY, startX + BORDERSIZE, startY);
			pDC->Rectangle(startX, endY, endX, endY + BORDERSIZE);
		}
		//釋放 pen brush、Back、Plain的CDC
		pDC->SelectObject(pp);
		//pDC->SelectObject(pb);
		CDDraw::ReleaseBackCDC();
	}

	void Line::SetLineColor(int r, int g, int b)
	{
		lineColor[0] = r;
		lineColor[1] = g;
		lineColor[2] = b;
	}
	
	void Line::SetClickedStartStationNum(int num)
	{
		clickedStartStationNum = num;
	}

	void Line::SetClickedEndStationNum(int num)
	{
		clickedEndStationNum = num;
	}

	void Line::SetPassedStation(int start,int end)
	{
		if (passedStation.empty()) //從來沒有拉過線路
		{
			passedStation.push_back(start);
			passedStation.push_back(end);
		}
		else 
		{
			if (passedStation.front()==start)//從頭拉線路出去
			{
				passedStation.insert(passedStation.begin(), end);
			}
			else if (passedStation.back()==start)//從尾巴拉線路出去
			{
				passedStation.push_back(end);
			} 
		}
		
	}

	void Line::SetTurnedPointXY(vector<Station> stationList)
	{
		int vecSize = passedStation.size();
		for (int i = 0; i < vecSize - 1; i++)
		{
			int stationStartNum = passedStation[i];
			int stationEndNum = passedStation[i+1];
			int startX = stationList[stationStartNum].GetX()+5;
			int startY = stationList[stationStartNum].GetY()+5;
			int endX = stationList[stationEndNum].GetX()+5;
			int endY = stationList[stationEndNum].GetY()+5;
			if (endX >= startX && endY >= startY)  //結束點在右下
			{
				turnedPointX.push_back(endX+14);
				turnedPointY.push_back(startY);
			}
			else if (endX < startX && endY > startY) //結束點在左下
			{
				turnedPointX.push_back(startX + 14);
				turnedPointY.push_back(endY + 14);
			}
			else if (endX <= startX && endY <= startY) //結束點在左上
			{
				turnedPointX.push_back(endX);
				turnedPointY.push_back(startY + 14);
			}
			else if (endX > startX && endY < startY) //結束點在右上
			{
				turnedPointX.push_back(startX);
				turnedPointY.push_back(endY);
			}
		}
		
		
		
	}
	
	int Line::GetClickedStartStationNum()
	{
		return clickedStartStationNum;
	}

	int Line::GetClickedEndStationNum()
	{
		return clickedEndStationNum;
	}

	int Line::GetMouseClickedStationNum(int x, int y, vector<Station> stationList, int currentStation)
	{
		for (int i = 0; i < currentStation; i++)
			if (x >= stationList[i].GetX() && x <= stationList[i].GetX() + 25 && y >= stationList[i].GetY() && y <= stationList[i].GetY() + 25)
				return i;
		return -1;
	}

	int Line::GetLineColorNum()
	{
		if (lineColor[0] == 255 && lineColor[1] == 0 && lineColor[2] == 0)
			return 0;
		else if (lineColor[0] == 255 && lineColor[1] == 144 && lineColor[2] == 0)
			return 1;
		else if (lineColor[0] == 255 && lineColor[1] == 255 && lineColor[2] == 0)
			return 2;
		else if (lineColor[0] == 0 && lineColor[1] == 255 && lineColor[2] == 0)
			return 3;
		else if (lineColor[0] == 0 && lineColor[1] == 138 && lineColor[2] == 255)
			return 4;
		else if (lineColor[0] == 0 && lineColor[1] == 6 && lineColor[2] == 255)
			return 5;
		else if (lineColor[0] == 144 && lineColor[1] == 0 && lineColor[2] == 255)
			return 6;
		else
			return 0;
	}

	int Line::GetClickedFirstStation()
	{
		return passedStation.empty() ? -1 : passedStation.front();
	}

	int Line::GetClickedLastStation()
	{
		return passedStation.empty() ? -1 : passedStation.back();
	}

	bool Line::IsClickedStation(int x, int y, vector<Station> stationList, int currentStation)
	{
		for (int i = 0; i < currentStation; i++)
			if (x >= stationList[i].GetX() && x <= stationList[i].GetX() + 25 && y >= stationList[i].GetY() && y <= stationList[i].GetY() + 25)
				return true;
		return false;
	}

	bool Line::IsClickedTwoStation()
	{
		if (clickedStartStationNum != -1 && clickedEndStationNum != -1 && clickedStartStationNum != clickedEndStationNum)
			return true;
		return false;
	}

	bool Line::IsMouseClickedLineColorBMP(int mouseX, int mouseY)
	{
		if (mouseX > lineColorBMP.Left() && mouseX < lineColorBMP.Left() + lineColorBMP.Width() &&
			mouseY > lineColorBMP.Top() && mouseY < lineColorBMP.Top() + lineColorBMP.Height())
			return true;
		return false;
	}

	bool Line::IsPassedStationEmpty()
	{
		return passedStation.empty();
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
		/*else if (lineColor[0] == 0 && lineColor[1] == 0 && lineColor[2] == 0)
			lineColorBMP.LoadBitmap(".\\RES\\color\\purple.bmp", RGB(255, 255, 255));*/
	}

	void Line::ShowLineIconBitmap()
	{
		if (lineColor[0] == 255 && lineColor[1] == 0 && lineColor[2] == 0)
			lineColorBMP.SetTopLeft(240, 570);
		else if (lineColor[0] == 255 && lineColor[1] == 144 && lineColor[2] == 0)
			lineColorBMP.SetTopLeft(285, 570);
		else if (lineColor[0] == 255 && lineColor[1] == 255 && lineColor[2] == 0)
			lineColorBMP.SetTopLeft(330, 570);
		else if (lineColor[0] == 0 && lineColor[1] == 255 && lineColor[2] == 0)
			lineColorBMP.SetTopLeft(375, 570);
		else if (lineColor[0] == 0 && lineColor[1] == 138 && lineColor[2] == 255)
			lineColorBMP.SetTopLeft(420, 570);
		else if (lineColor[0] == 0 && lineColor[1] == 6 && lineColor[2] == 255)
			lineColorBMP.SetTopLeft(465, 570);
		else if (lineColor[0] == 144 && lineColor[1] == 0 && lineColor[2] == 255)
			lineColorBMP.SetTopLeft(510, 570);

		lineColorBMP.ShowBitmap();
	}

	void Line::ShowRailway(vector<Station> stationList,int currentStation)
	{
		int vecSize = passedStation.size();
		for (int i = 0; i < vecSize-1; i++)
		{
			int stationA = passedStation[i];
			int stationB = passedStation[i + 1];
			DrawRailway(stationList[stationA].GetX() + 5, stationList[stationA].GetY() + 5, stationList[stationB].GetX() + 5, stationList[stationB].GetY() + 5);
		}
	}

	
}