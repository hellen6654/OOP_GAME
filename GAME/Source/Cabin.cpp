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
		nextPoint = 1;
		prePoint = 0;
		leftTopX = setX;
		leftTopY = setY;
		nextStation = -1;
		counter_cabin_stop =0;
		isStop = false;
		isStopOnceInStation = false;
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
		updatelinePointX.assign(x.begin(), x.end());
		updatelinePointY.assign(y.begin(), y.end());

		if (linePointX.empty())linePointX.assign(x.begin(), x.end());
		if (linePointY.empty())linePointY.assign(y.begin(), y.end());

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
		if (!isStop)
		{
			int sizeVecX = linePointX.size();
			int sizeVecY = linePointY.size();
			int startX = linePointX[prePoint];
			int startY = linePointY[prePoint];
			int endX = linePointX[nextPoint];
			int endY = linePointY[nextPoint];
			int nowPointX = leftTopX;
			int nowPointY = leftTopY;
			// X座標相同 代表向上或向下移動
			// Y座標相同 代表向左或向右移動

			//================================
			//============設定移動方向==========
			//================================
			if (startX == endX)
			{
				if (startY > endY) //向上移動
				{
					movingDirection = "up";
				}
				else if (startY < endY) //向下移動
				{
					movingDirection = "down";
				}
			}
			else if (startY == endY)
			{
				if (startX > endX)// 向左移動
				{
					movingDirection = "left";
				}
				else if (startX < endX) //向右移動
				{
					movingDirection = "right";
				}
			}

			//================================
			//==============移動===============
			//================================
			if (movingDirection == "up")
			{
				if (nowPointY > endY)
					SetMovingCabin(movingDirection, velocity);
				else if (nowPointY <= endY)
				{
					if (IsInStation(endX,endY,totalStationList))
					{
						isStop = true;
					}
					
					//================================
					//============判斷起訖站===========
					//================================
					if (nextPoint == sizeVecX - 1)
					{
						goingDirection = "back";
					}
					else if (nextPoint == 0)
					{
						linePointX.assign(updatelinePointX.begin(), updatelinePointX.end());
						linePointY.assign(updatelinePointY.begin(), updatelinePointY.end());
						goingDirection = "head";
					}
					//================================
					//============移動到下一站==========
					//================================
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
					if (IsInStation(endX, endY, totalStationList))
					{
						isStop = true;
					}
					//================================
					//============判斷起訖站===========
					//================================
					if (nextPoint == sizeVecX - 1)
					{
						goingDirection = "back";
					}
					else if (nextPoint == 0)
					{
						goingDirection = "head";
						linePointX.assign(updatelinePointX.begin(), updatelinePointX.end());
						linePointY.assign(updatelinePointY.begin(), updatelinePointY.end());
					}
					//================================
					//============移動到下一站==========
					//================================
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
					if (IsInStation(endX, endY, totalStationList))
					{
						isStop = true;
					}
					//================================
					//============判斷起訖站===========
					//================================
					if (nextPoint == sizeVecX - 1)
					{
						goingDirection = "back";
					}
					else if (nextPoint == 0)
					{
						linePointX.assign(updatelinePointX.begin(), updatelinePointX.end());
						linePointY.assign(updatelinePointY.begin(), updatelinePointY.end());
						goingDirection = "head";
					}

					//================================
					//============移動到下一站==========
					//================================
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
					if (IsInStation(endX, endY, totalStationList))
					{
						isStop = true;
					}
					//================================
					//============判斷起訖站===========
					//================================
					if (nextPoint == sizeVecX - 1)
					{
						goingDirection = "back";
					}
					else if (nextPoint == 0)
					{
						goingDirection = "head";
						linePointX.assign(updatelinePointX.begin(), updatelinePointX.end());
						linePointY.assign(updatelinePointY.begin(), updatelinePointY.end());
					}
					//================================
					//============移動到下一站==========
					//================================

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
		SetPassengerPosition();
		for (unsigned i = 0; i < passengerOnCabinList.size(); i++)
		{
			passengerOnCabinList[i]->OnShow();
		}
	}

	bool Cabin::IsInStation(int endX, int endY,vector<Station> totalStationList)
	{
		int sizeVec = totalStationList.size();
		for (int i = 0; i < sizeVec; i++)
		{
			if (totalStationList[i].GetX() == endX && totalStationList[i].GetY() == endY)
			{
				nextStation = i;
				return true;
			}
		}
			
		return false;


	}

	void Cabin::GetNextPrePoint(int & pre, int & next)
	{
		pre = prePoint;
		next = nextPoint;
	}

	int Cabin::GetNextStation()
	{
		return nextStation;
	}

	void Cabin::SetLineStationNum(int num[6])
	{
		for (int i = 0; i < 6; i++)
		{
			lineStationNum[i] = num[i];
		}
	}

	void Cabin::GetLineStationNum(int(&num)[6])
	{
		for (int i = 0; i < 6; i++)
		{
			num[i] = lineStationNum[i];
		}
	}

	void Cabin::SetPassengerPosition()
	{
		if (movingDirection=="left"|| movingDirection =="right")
		{
			for (unsigned i = 0; i < passengerOnCabinList.size(); i++)
			{
				passengerOnCabinList[i]->SetXY(leftTopX + PASSENGERPOSITIONX_RIGHTLEFT[i], leftTopY + PASSENGERPOSITIONY_RIGHTLEFT[i]);
			}
		}
		else if (movingDirection == "down" || movingDirection == "up")
		{
			for (unsigned i = 0; i < passengerOnCabinList.size(); i++)
			{
				passengerOnCabinList[i]->SetXY(leftTopX + PASSENGERPOSITIONX_UPDOWN[i], leftTopY + PASSENGERPOSITIONY_UPDOWN[i]);
			}
		}
		
	}

	int Cabin::GetPassengerNum()
	{
		return passengerNum;
	}

	void Cabin::SetPassengerNum(int n)
	{
		passengerNum = n;
	}

	void Cabin::AddPassengerNum(int n)
	{
		passengerNum += n;
	}

	bool Cabin::IsCabinColorRepeat(vector<Cabin> cabinList, int R, int G, int B)
	{
		for (auto it = begin(cabinList); it != end(cabinList); it++)
		{
			int RR, GG, BB;
			it->GetRGB(RR, GG, BB);
			if (RR = R && GG == G && BB == B)
				return true;
		}

		return false;
	}

	int Cabin::GetCabinPointer(vector<Cabin> cabinList, int R, int G, int B)
	{
		for (unsigned i = 0; i < cabinList.size(); i++)
		{
			int RR, GG, BB;
			cabinList[i].GetRGB(RR, GG, BB);
			if (RR = R && GG == G && BB == B)
				return i;
		}
		return -1;
	}

	bool Cabin::IsCabinFull()
	{
		return (passengerNum >= 6); //看乘客有沒有超過6個
	}

	void Cabin::PassengerGetOn(Passenger* p,int nowStation)
	{
		passengerNum++;
		passengerOnCabinList.push_back(p);
		SetPassengerPosition();

		/*int vecSize = passengerList.size();
		for (int i = 0; i < vecSize; i++)
		{
			if (passengerList[i].GetStartStation() == nowStation)
			{
				passengerNum++;
				passengerOnCabinList.push_back(passengerList[i]);
				passengerList.erase(passengerList.begin() + i);
				vecSize--;
			}
		}*/
	}

	int Cabin::PassengerGetOut(int nowStation)
	{
		for (unsigned i = passengerOnCabinList.size()-1; i >=0 ; i--)
		{
			if (i > 6)
			{
				break;
			}
			else if (nowStation == passengerOnCabinList[i]->GetFinalStation())
			{
				passengerNum--;
				delete passengerOnCabinList[i];
				passengerOnCabinList.erase(passengerOnCabinList.begin()+i);
			}
			
			passengerNum = (int)passengerOnCabinList.size();
		}
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

	void Cabin::SetAddCounter(int n)
	{
		counter_cabin_stop += n;
	}

	void Cabin::SetCounter(int n)
	{
		counter_cabin_stop = n;
	}

	int Cabin::GetCounter()
	{
		return counter_cabin_stop;
	}

}