/*
 * mygame.cpp: 本檔案儲遊戲本身的class的implementation
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 * This file is part of game, a free game development framework for windows.
 *
 * game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * game is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * History:
 *   2002-03-04 V3.1
 *          Add codes to demostrate the use of CMovingBitmap::ShowBitmap(CMovingBitmap &).
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *      2. Demo the use of CInteger in CGameStateRun.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *      1. Add codes to display IDC_GAMECURSOR in GameStateRun.
 *   2006-02-08 V4.2
 *      1. Revise sample screens to display in English only.
 *      2. Add code in CGameStateInit to demo the use of PostQuitMessage().
 *      3. Rename OnInitialUpdate() -> OnInit().
 *      4. Fix the bug that OnBeginState() of GameStateInit is not called.
 *      5. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      6. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2006-12-30
 *      1. Bug fix: fix a memory leak problem by replacing PostQuitMessage(0) as
 *         PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0).
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress.
 *   2010-03-23 V4.6
 *      1. Demo MP3 support: use lake.mp3 to replace lake.wav.
*/

#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <cstdlib>
#include <ctime>
#include <vector>
#include "mygame.h"

namespace game_framework
{
/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲開頭畫面物件
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame* g)
    : CGameState(g)
{
}

void CGameStateInit::OnInit()
{
    //
    // 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
    //     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
    //
    ShowInitProgress(0);	// 一開始的loading進度為0%
    //
    // 開始載入資料
    //
    logo.LoadBitmap(".\\RES\\title.bmp");
    start.LoadBitmap(".\\RES\\button\\start.bmp");
    end.LoadBitmap(".\\RES\\button\\end.bmp");
    Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
    //
    // 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
    //
}

void CGameStateInit::OnBeginState()
{
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    const char KEY_ESC = 27;
    const char KEY_SPACE = ' ';

    if (nChar == KEY_SPACE)
        GotoGameState(GAME_STATE_RUN);						// 切換至GAME_STATE_RUN
    else if (nChar == KEY_ESC)								// Demo 關閉遊戲的方法
        PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// 關閉遊戲
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
    // GotoGameState(GAME_STATE_RUN);		// 切換至GAME_STATE_RUN
}

void CGameStateInit::OnLButtonUp(UINT nFlags, CPoint point)
{
    if (mouse_x >= start.Left() && mouse_x <= start.Left() + start.Width() && mouse_y >= start.Top() && mouse_y <= start.Top() + start.Height())
    {
        GotoGameState(GAME_STATE_RUN);		// 切換至GAME_STATE_RUN
    }
    else if (mouse_x >= end.Left() && mouse_x <= end.Left() + end.Width() && mouse_y >= end.Top() && mouse_y <= end.Top() + end.Height())
    {
        PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// 關閉遊戲
    }
}

void CGameStateInit::OnMouseMove(UINT nFlags, CPoint point)
{
    mouse_x = point.x;
    mouse_y = point.y;
}

void CGameStateInit::OnShow()
{
    //
    // 貼上logo
    //
    logo.SetTopLeft((SIZE_X - logo.Width()) / 2, SIZE_Y / 8);
    logo.ShowBitmap();

    if (mouse_x > start.Left() && mouse_x < 491 && mouse_y > start.Top() && mouse_y < 302 )
    {
        start.SetTopLeft((SIZE_X - start.Width()) / 2 - 8, SIZE_Y / 8 + 166);
        start.ShowBitmap(1.05);
        end.SetTopLeft((SIZE_X - end.Width()) / 2, SIZE_Y / 8 + 270);
        end.ShowBitmap(0.9);
    }
    else if (mouse_x > end.Left() &&  mouse_x < 491 && mouse_y > end.Top() && mouse_y < 402)
    {
        start.SetTopLeft((SIZE_X - start.Width()) / 2, SIZE_Y / 8 + 170);
        start.ShowBitmap(0.9);
        end.SetTopLeft((SIZE_X - end.Width()) / 2 - 8, SIZE_Y / 8 + 266);
        end.ShowBitmap(1.05);
    }
    else
    {
        start.SetTopLeft((SIZE_X - start.Width()) / 2, SIZE_Y / 8 + 170);
        start.ShowBitmap(0.9);
        end.SetTopLeft((SIZE_X - end.Width()) / 2, SIZE_Y / 8 + 270);
        end.ShowBitmap(0.9);
    }

    //
    // Demo螢幕字型的使用，不過開發時請盡量避免直接使用字型，改用CMovingBitmap比較好
    //
    CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC
    CFont f, *fp;
    f.CreatePointFont(160, "Times New Roman");	// 產生 font f; 160表示16 point的字
    fp = pDC->SelectObject(&f);					// 選用 font f
    pDC->SetBkColor(RGB(0, 0, 0));
    pDC->SetTextColor(RGB(255, 255, 0));
    //pDC->TextOut(150, 275, "Please click mouse or press SPACE to begin.");
    pDC->TextOut(5, 493, "Press Ctrl-F to switch in between window mode and full screen mode.");
    char t[30];
    sprintf(t, "(%d,%d)", mouse_x, mouse_y);
    pDC->TextOut(10, 10, t);

    if (ENABLE_GAME_PAUSE)
        pDC->TextOut(6, 531, "Press Ctrl-Q to pause the Game.");

    pDC->TextOut(6, 569, "Press Alt-F4 or ESC to Quit.");
    pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
    CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
}

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的結束狀態(Game Over)
/////////////////////////////////////////////////////////////////////////////

CGameStateOver::CGameStateOver(CGame* g)
    : CGameState(g)
{
}

void CGameStateOver::OnMove()
{
    counter--;

    if (counter < 0)
        GotoGameState(GAME_STATE_INIT);
}

void CGameStateOver::OnBeginState()
{
    counter = 30 * 5; // 5 seconds
}

void CGameStateOver::OnInit()
{
    //
    // 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
    //     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
    //
    ShowInitProgress(66);	// 接個前一個狀態的進度，此處進度視為66%
    //
    // 開始載入資料
    //
    Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
    //
    // 最終進度為100%
    //
    ShowInitProgress(100);
}

void CGameStateOver::OnShow()
{
    CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC
    CFont f, *fp;
    f.CreatePointFont(160, "Times New Roman");	// 產生 font f; 160表示16 point的字
    fp = pDC->SelectObject(&f);					// 選用 font f
    pDC->SetBkColor(RGB(0, 0, 0));
    pDC->SetTextColor(RGB(255, 255, 0));
    char str[80];								// Demo 數字對字串的轉換
    sprintf(str, "Game Over ! (%d)", counter / 30);
    pDC->TextOut(240, 210, str);
    pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
    CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
}

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame* g)
    : CGameState(g)
{
}

CGameStateRun::~CGameStateRun()
{
}

void CGameStateRun::OnBeginState()
{
    counter = 0;
}

void CGameStateRun::OnMove()							// 移動遊戲元素
{
    counter++;
    clock.OnMove();				//播放clock時鐘動畫

    if (clock.IsFinalBitmap())	//播放week周次動畫
        week.OnMove();

    if (counter % (30 * 5) == 0 && currentStationNum < MAXIUM_STATION) //每五秒出一個車站
        currentStationNum++;

    if (line.IsClickedTwoStation())
    {
        if (stationRelation[line.GetclickedTwoNumB()][line.GetclickedTwoNumA()] != 1)
        {
            stationRelation[line.GetclickedTwoNumA()][line.GetclickedTwoNumB()] = 1;
        }

        line.SetclickedTwoNumA(-1);
        line.SetclickedTwoNumB(-1);
    }
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
    //
    // 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
    //     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
    //
    ShowInitProgress(33);	// 接個前一個狀態的進度，此處進度視為33%
    //
    // 開始載入資料
    clock.LoadBitmap();
    week.LoadBitmap();
    map.LoadBitmap(".\\RES\\map.bmp");
    color[0].LoadBitmap(".\\RES\\color\\red.bmp", RGB(255, 255, 255));
    color[1].LoadBitmap(".\\RES\\color\\orang.bmp", RGB(255, 255, 255));
    color[2].LoadBitmap(".\\RES\\color\\yellow.bmp", RGB(255, 255, 255));
    color[3].LoadBitmap(".\\RES\\color\\green.bmp", RGB(255, 255, 255));
    color[4].LoadBitmap(".\\RES\\color\\blue.bmp", RGB(255, 255, 255));
    color[5].LoadBitmap(".\\RES\\color\\bblue.bmp", RGB(255, 255, 255));
    color[6].LoadBitmap(".\\RES\\color\\purple.bmp", RGB(255, 255, 255));
    srand((unsigned)time(NULL));
    int station_y = 0, station_x = 0, station_type = 0;
    Station buffer;

    for (int i = 0; i < MAXIUM_STATION; i++)
    {
        int j = 0;
        station_type = rand() % MAXIUM_STATION_TYPE; //隨機選擇第一個的車站形狀
        station_x = MIN_GAME_MAP_SIDE_X + rand() % (MAX_GAME_MAP_SIDE_X - MIN_GAME_MAP_SIDE_X); // 隨機選第一個的車站位置
        station_y = MIN_GAME_MAP_SIDE_Y + rand() % (MAX_GAME_MAP_SIDE_Y - MIN_GAME_MAP_SIDE_Y);	// 隨機選第一個的車站位置

        while (i > j) // 確保車站不會重疊 且在距離車站附近100內不會出車站
        {
            if ((station_x > stationList[j].GetX() - 100 && station_x < stationList[j].GetX() + 100) &&
                    (station_y > stationList[j].GetY() - 100 && station_y < stationList[j].GetY() + 100))
            {
                station_x = MIN_GAME_MAP_SIDE_X + rand() % (MAX_GAME_MAP_SIDE_X - MIN_GAME_MAP_SIDE_X);
                station_y = MIN_GAME_MAP_SIDE_Y + rand() % (MAX_GAME_MAP_SIDE_Y - MIN_GAME_MAP_SIDE_Y);
            }
            else
                j++;
        }

        buffer.SetType(station_type);
        buffer.SetXY(station_x, station_y);
        stationList.push_back(buffer);
        stationList[i].LoadBitmap();
    }

    currentStationNum = 3;
    clickedX = clickedY = -1;

    for (int i = 0; i < MAXIUM_STATION; i++)
        for (int j = 0; j < MAXIUM_STATION; j++)
            stationRelation[i][j] = 0;

    ShowInitProgress(50);
    //Sleep(300); // 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
    //
    // 繼續載入其他資料
    //
    //CAudio::Instance()->Load(AUDIO_DING,  "sounds\\ding.wav");	// 載入編號0的聲音ding.wav
    //CAudio::Instance()->Load(AUDIO_LAKE,  "sounds\\lake.mp3");	// 載入編號1的聲音lake.mp3
    //CAudio::Instance()->Load(AUDIO_NTUT,  "sounds\\ntut.mid");	// 載入編號2的聲音ntut.mid
    //
    // 此OnInit動作會接到CGameStaterOver::OnInit()，所以進度還沒到100%
    //
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    const char KEY_LEFT  = 0x25; // keyboard左箭頭
    const char KEY_UP    = 0x26; // keyboard上箭頭
    const char KEY_RIGHT = 0x27; // keyboard右箭頭
    const char KEY_DOWN  = 0x28; // keyboard下箭頭
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    const char KEY_LEFT  = 0x25; // keyboard左箭頭
    const char KEY_UP    = 0x26; // keyboard上箭頭
    const char KEY_RIGHT = 0x27; // keyboard右箭頭
    const char KEY_DOWN  = 0x28; // keyboard下箭頭
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠左鍵的動作 按下
{
    //eraser.SetMovingLeft(true);
    if (stationX[line.GetclickedTwoNumA()] == 1)
    {
        if (!line.IsClickedStation(point.x, point.y, stationList, currentStationNum))
        {
            for (int i = 0; i < 10; i++)
            {
                stationX[i] = 0;
            }

            line.SetclickedTwoNumA(-1);
        }
    }
    else
    {
        if (line.IsClickedStation(point.x, point.y, stationList, currentStationNum))
        {
            stationX[line.GetclickedTwoNumA()] = 1;
        }
    }

    clickedX = point.x;
    clickedY = point.y;
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠左鍵的動作 放開
{
    //eraser.SetMovingLeft(false);
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠左鍵的動作 移動
{
    // 沒事。如果需要處理滑鼠移動的話，寫code在這裡
    mouse_x = point.x;
    mouse_y = point.y;
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnShow()
{
    //
    //  注意：Show裡面千萬不要移動任何物件的座標，移動座標的工作應由Move做才對，
    //        否則當視窗重新繪圖時(OnDraw)，物件就會移動，看起來會很怪。換個術語
    //        說，Move負責MVC中的Model，Show負責View，而View不應更動Model。
    //
    //
    //  貼上背景圖、撞擊數、球、擦子、彈跳的球
    //
    //timer.CountPassTime();
    map.SetTopLeft(0, 0);
    map.ShowBitmap();
    color[0].SetTopLeft(240, 565);
    color[0].ShowBitmap();
    color[1].SetTopLeft(285, 565);
    color[1].ShowBitmap();
    color[2].SetTopLeft(330, 565);
    color[2].ShowBitmap();
    color[3].SetTopLeft(375, 565);
    color[3].ShowBitmap();
    color[4].SetTopLeft(420, 565);
    color[4].ShowBitmap();
    color[5].SetTopLeft(465, 565);
    color[5].ShowBitmap();
    color[6].SetTopLeft(510, 565);
    color[6].ShowBitmap();

    if (stationX[line.GetclickedTwoNumA()] == 1)
    {
        line.DrawRailway(stationList[line.GetclickedTwoNumA()].GetX() + 5, stationList[line.GetclickedTwoNumA()].GetY() + 5,
                         mouse_x, mouse_y);
    }

    for (int i = 0; i < MAXIUM_STATION; i++)
    {
        for (int j = 0; j < MAXIUM_STATION; j++)
        {
            if (i != j)
            {
                if (stationRelation[i][j] == 1 )
                {
                    line.DrawRailway(stationList[i].GetX() + 5, stationList[i].GetY() + 5,
                                     stationList[j].GetX() + 5, stationList[j].GetY() + 5);
                }
            }
        }
    }

    /* for (int i = 0; i < currentStationNum; i++)
     {
         if (stationX[i] == 1)
         {
             line.DrawRailway(stationList[i].GetX() + 5, stationList[i].GetY() + 5,
                              mouse_x, mouse_y);

             for (int j = 0; j < currentStationNum; j++)
             {
                 if (stationRelation[i][j] == 1)
                 {
                     line.DrawRailway(stationList[i].GetX() + 5, stationList[i].GetY() + 5,
                                      stationList[j].GetX() + 5, stationList[j].GetY() + 5);
                 }
             }
         }
     }*/

    for (int i = 0; i < currentStationNum; i++)
        stationList[i].OnShow();

    week.OnShow();
    clock.OnShow();
    CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC
    CFont f, *fp;
    f.CreatePointFont(160, "Times New Roman");	// 產生 font f; 160表示16 point的字
    fp = pDC->SelectObject(&f);					// 選用 font f
    //pDC->SetBkColor(RGB(0, 0, 0));
    pDC->SetBkColor(RGB(241, 241, 241));
    pDC->SetTextColor(RGB(0, 0, 0));
    char str[80];								// Demo 數字對字串的轉換
    sprintf(str, "(%d,%d),(%d,%d),(%d,%d)", mouse_x, mouse_y, clickedX, clickedY, line.GetclickedTwoNumA(), line.GetclickedTwoNumB());
    pDC->TextOut(10, 10, str);
    pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
    CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
}
}