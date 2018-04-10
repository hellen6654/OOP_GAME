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
		:mouseClickedPoint_X(0), mouseClickedPoint_Y(0),clickedStationNumA(-1), clickedStationNumB(-1)
		,isStation_A_Clicked(false), isStation_B_Clicked(false)
	{}

	Line::~Line()
	{

	}

	void Line::SetmouseClickedPointA(int x, int y)
	{
		mouseClickedPoint_X = x;
		mouseClickedPoint_Y = y;
	}

	void Line::SetisStation_A_Clicked(bool flag)
	{
		isStation_A_Clicked = flag;
	}

	void Line::SetisStation_B_Clicked(bool flag)
	{
		isStation_B_Clicked = flag;
	}

	void Line::SetclickedStationNumA(int num)
	{
		clickedStationNumA = num;
	}

	void Line::SetclickedStationNumB(int num)
	{
		clickedStationNumB = num;
	}

	int Line::GetclickedStationNumA()
	{
		return clickedStationNumA;
	}

	int Line::GetclickedStationNumB()
	{
		return clickedStationNumB;
	}

	int Line::GetmouseClickedPoint_X()
	{
		return mouseClickedPoint_X;
	}

	int Line::GetmouseClickedPoint_Y()
	{
		return mouseClickedPoint_Y;
	}

	bool Line::IsStation_A_Clicked()
	{
		return isStation_A_Clicked;
	}

	bool Line::IsStation_B_Clicked()
	{
		return isStation_B_Clicked;
	}

	bool Line::IsClickedOnStation(int x, int y, vector<Station> stationList, int currentStation)
	{
		for (int i = 0; i < currentStation; i++)
		{
			if (x >= stationList[i].GetX() && x <= stationList[i].GetX() + 25 && 
				y >= stationList[i].GetY() && y <= stationList[i].GetY() + 25)
				return true;
		}
		return false;
	}

}