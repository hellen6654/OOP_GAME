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
    : clickedStationNumA(-1), clickedStationNumB(-1)
{}
Line::~Line()
{
}
bool Line::IsClickedStation(int x, int y, vector<Station> stationList, int currentStation)
{
    for (int i = 0; i < currentStation; i++)
    {
        if (x >= stationList[i].GetX() && x <= stationList[i].GetX() + 25 &&
                y >= stationList[i].GetY() && y <= stationList[i].GetY() + 25)
        {
            if (clickedStationNumA == -1 && clickedStationNumB == -1) clickedStationNumA = i;
            else if (clickedStationNumB == -1) clickedStationNumB = i;

            return true;
        }
    }

    return false;
}
bool Line::IsClickedTwoStation()
{
    if (clickedStationNumA != -1 && clickedStationNumB != -1)
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

void Line::DrawRailway(int start_x, int start_y, int end_x, int end_y)
{
    const int borderSize = 15;
    //const int rectHeight = 20;
    //取得 Back Plain 的 CDC 清除pen
    CDC* pDC = CDDraw::GetBackCDC();
    CPen* pp, p(PS_NULL, 0, RGB(0, 0, 0));
    pp = pDC->SelectObject(&p);
    /*//progress框
    CBrush* pb, b(RGB(255, 255, 255));
    pb = pDC->SelectObject(&b);
    pDC->Rectangle(x, y, x + borderSize * 2 + maxHP, y + borderSize * 2 + rectHeight);
    //progrss中心
    CBrush b1(RGB(0, 0, 0));
    pDC->SelectObject(&b1);
    pDC->Rectangle(x + borderSize, y + borderSize, x + borderSize + maxHP, y + borderSize + rectHeight);*/
    //progrss進度
    CBrush b1(RGB(255, 255, 0));
    pDC->SelectObject(&b1);
    pDC->Rectangle(start_x, start_y, end_x, start_y + borderSize);
    CBrush b2(RGB(255, 0, 0));
    pDC->SelectObject(&b2);
    pDC->Rectangle(end_x, start_y, end_x + borderSize, end_y);
    //釋放 pen brush、Back、Plain的CDC
    pDC->SelectObject(pp);
    //pDC->SelectObject(pb);
    CDDraw::ReleaseBackCDC();
}

}