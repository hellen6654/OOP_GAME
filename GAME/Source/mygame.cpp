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

/*
	待修 ：
		車廂

		車站

		乘客

	待加：


*/
namespace game_framework
{
int personss = 0;
bool isNight = false;
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
    // 載入音效
    CAudio::Instance()->Load(AUDIO_SLIP, "sounds\\slip.mp3");
    CAudio::Instance()->Load(AUDIO_CLICK, "sounds\\click.mp3");
    CAudio::Instance()->Load(AUDIO_MUSIC, "sounds\\music.mp3");
    // 載入圖片
    logo.LoadBitmap(".\\RES\\title.bmp");
    logoNight.LoadBitmap(".\\RES\\titlenight.bmp", RGB(0, 0, 0));
    nightMap.LoadBitmap(".\\RES\\backgroundnight.bmp");
    page1.LoadBitmap(".\\RES\\Instruction.bmp");
    page2.LoadBitmap(".\\RES\\Instruction2.bmp");
    start.LoadBitmap(".\\RES\\button\\start.bmp");
    startInvert.LoadBitmap(".\\RES\\button\\startInvert.bmp");
    night.LoadBitmap(".\\RES\\button\\night.bmp");
    nightInvert.LoadBitmap(".\\RES\\button\\nightInvert.bmp");
    morning.LoadBitmap(".\\RES\\button\\morning.bmp");
    morningInvert.LoadBitmap(".\\RES\\button\\morningInvert.bmp");
    instructions.LoadBitmap(".\\RES\\button\\Instructions.bmp");
    instructionsInvert.LoadBitmap(".\\RES\\button\\InstructionsInvert.bmp");
    end.LoadBitmap(".\\RES\\button\\end.bmp");
    endInvert.LoadBitmap(".\\RES\\button\\endInvert.bmp");
    red.LoadBitmap(".\\RES\\Cover\\red.bmp", RGB(255, 255, 255));
    orange.LoadBitmap(".\\RES\\Cover\\orange.bmp", RGB(255, 255, 255));
    blue.LoadBitmap(".\\RES\\Cover\\blue.bmp", RGB(255, 255, 255));
    bblue.LoadBitmap(".\\RES\\Cover\\bblue.bmp", RGB(255, 255, 255));
    redCabin.LoadBitmap(".\\RES\\Cabin\\Cabin_rad2.bmp", RGB(255, 255, 255));
    redCabin2.LoadBitmap(".\\RES\\Cabin\\Cabin_rad3.bmp", RGB(255, 255, 255));
    orangeCabin.LoadBitmap(".\\RES\\Cabin\\Cabin_orange2.bmp", RGB(255, 255, 255));
    orangeCabin2.LoadBitmap(".\\RES\\Cabin\\Cabin_orange3.bmp", RGB(255, 255, 255));
    blueCabin.LoadBitmap(".\\RES\\Cabin\\Cabin_blue2.bmp", RGB(255, 255, 255));
    blueCabin2.LoadBitmap(".\\RES\\Cabin\\Cabin_blue3.bmp", RGB(255, 255, 255));
    bblueCabin.LoadBitmap(".\\RES\\Cabin\\Cabin_bblue2.bmp", RGB(255, 255, 255));
    bblueCabin2.LoadBitmap(".\\RES\\Cabin\\Cabin_bblue3.bmp", RGB(255, 255, 255));
    //設定參數
    CAudio::Instance()->Play(AUDIO_MUSIC);
    isMouseInStartBtn = false;
    isMouseInNightBtn = false;
    isMouseInInstructionsBtn = false;
    isMouseInEndBtn = false;
    isInInstructions = false;
    Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
    //
    // 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
    //
}

void CGameStateInit::OnBeginState()
{
    isInInstructions = false;
    page = 0;
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    const char KEY_ESC = 27;
    const char KEY_SPACE = ' ';
    const char KEY_RIGHT = 0x27; // keyboard右箭頭

    if (nChar == KEY_RIGHT)
    {
        if (isInInstructions)
        {
            if (page == 2)
            {
                page = 0;
                isInInstructions = !isInInstructions;
            }
            else
            {
                page++;
            }
        }
    }

    /*if (nChar == KEY_SPACE)
        GotoGameState(GAME_STATE_RUN);						// 切換至GAME_STATE_RUN
    else if (nChar == KEY_ESC)								// Demo 關閉遊戲的方法
        PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// 關閉遊戲*/
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
    if (start.IsBitmapLoaded() && end.IsBitmapLoaded())
    {
        if (mouse_x >= start.Left() && mouse_x <= start.Left() + start.Width() && mouse_y >= start.Top() && mouse_y <= start.Top() + start.Height())
        {
            CAudio::Instance()->Play(AUDIO_CLICK);
        }
        else if (mouse_x >= end.Left() && mouse_x <= end.Left() + end.Width() && mouse_y >= end.Top() && mouse_y <= end.Top() + end.Height())
        {
            CAudio::Instance()->Play(AUDIO_CLICK);
        }
    }
}

void CGameStateInit::OnLButtonUp(UINT nFlags, CPoint point)
{
    if (isInInstructions)
    {
    }
    else
    {
        if (start.IsBitmapLoaded() && end.IsBitmapLoaded())
        {
            if (isMouseInStartBtn)
            {
                GotoGameState(GAME_STATE_RUN);		// 切換至GAME_STATE_RUN
            }
            else if (isMouseInEndBtn)
            {
                PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// 關閉遊戲
            }
            else if (isMouseInNightBtn)
            {
                isNight = !isNight;
            }
            else if (isMouseInInstructionsBtn)
            {
                page = 1;
                isInInstructions = !isInInstructions;
            }
        }
    }
}

void CGameStateInit::OnMouseMove(UINT nFlags, CPoint point)
{
    mouse_x = point.x;
    mouse_y = point.y;

    if (!isInInstructions)
    {
        if (start.IsBitmapLoaded() && end.IsBitmapLoaded())
        {
            if (mouse_x > start.Left() && mouse_x < start.Left() + start.Width() &&
                    mouse_y > start.Top() && mouse_y < start.Top() + start.Height())
            {
                if (mouse_state == 1)
                {
                    isMouseInStartBtn = true;
                    CAudio::Instance()->Play(AUDIO_SLIP);
                    mouse_state = 0;
                }
            }
            else if (mouse_x > end.Left() && mouse_x < end.Left() + end.Width() &&
                     mouse_y > end.Top() && mouse_y < end.Top() + end.Height())
            {
                if (mouse_state == 1)
                {
                    isMouseInEndBtn = true;
                    CAudio::Instance()->Play(AUDIO_SLIP);
                    mouse_state = 0;
                }
            }
            else if (mouse_x > night.Left() && mouse_x < night.Left() + night.Width() &&
                     mouse_y > night.Top() && mouse_y < night.Top() + night.Height())
            {
                if (mouse_state == 1)
                {
                    isMouseInNightBtn = true;
                    CAudio::Instance()->Play(AUDIO_SLIP);
                    mouse_state = 0;
                }
            }
            else if (mouse_x > instructions.Left() && mouse_x < instructions.Left() + instructions.Width() &&
                     mouse_y > instructions.Top() && mouse_y < instructions.Top() + instructions.Height())
            {
                if (mouse_state == 1)
                {
                    isMouseInInstructionsBtn = true;
                    CAudio::Instance()->Play(AUDIO_SLIP);
                    mouse_state = 0;
                }
            }
            else
            {
                mouse_state = 1;
                isMouseInNightBtn = false;
                isMouseInStartBtn = false;
                isMouseInInstructionsBtn = false;
                isMouseInEndBtn = false;
            }
        }
    }
}

void CGameStateInit::OnMove()
{
    if (redCabinY > 800)
    {
        redCabinX = -50;
        redCabinY = 270;
    }
    else if (redCabinY < 375)
    {
        redCabinY += 2;
        redCabinX += 2;
    }
    else
    {
        redCabinY += 2;
    }

    if (orangeCabinY > 333)
    {
        orangeCabinY -= 2;
    }
    else if (orangeCabinY < 334 && orangeCabinX > -100)
    {
        orangeCabinX -= 2;
        orangeCabinY -= 2;
    }
    else if (orangeCabinX <= -100)
    {
        orangeCabinX = 38;
        orangeCabinY = 800;
    }

    if (bblueCabinY > 425)
    {
        bblueCabinY -= 2;
    }
    else if (bblueCabinY <= 424 && bblueCabinX < 850)
    {
        bblueCabinX += 2;
        bblueCabinY -= 2;
    }
    else if (bblueCabinX >= 850)
    {
        bblueCabinX = 675;
        bblueCabinY = 1000;
    }

    if (blueCabinY > 70)
    {
        blueCabinY -= 2;
    }
    else if (blueCabinY <= 70 && blueCabinX < 1500)
    {
        blueCabinX += 2;
        blueCabinY -= 2;
    }
    else if (blueCabinX >= 1500)
    {
        blueCabinX = 694;
        blueCabinY = 600;
    }
}

void CGameStateInit::OnShow()
{
    //設定Logo 位置 和顯示
    logo.SetTopLeft((SIZE_X / 2) - (logo.Width() / 2), SIZE_Y / 8 * 1);
    logoNight.SetTopLeft((SIZE_X / 2) - (logo.Width() / 2), SIZE_Y / 8 * 1);
    //開始按鈕 結束按鈕的位置
    start.SetTopLeft((SIZE_X / 2) - (start.Width() / 2), SIZE_Y / 8 * 3);
    night.SetTopLeft((SIZE_X / 2) - (start.Width() / 2), SIZE_Y / 8 * 4);
    morning.SetTopLeft((SIZE_X / 2) - (start.Width() / 2), SIZE_Y / 8 * 4);
    instructions.SetTopLeft((SIZE_X / 2) - (end.Width() / 2), SIZE_Y / 8 * 5);
    end.SetTopLeft((SIZE_X / 2) - (end.Width() / 2), SIZE_Y / 8 * 6);
    //反相 開始按鈕 結束按鈕的位置
    startInvert.SetTopLeft((SIZE_X / 2) - (start.Width() / 2), SIZE_Y / 8 * 3);
    nightInvert.SetTopLeft((SIZE_X / 2) - (start.Width() / 2), SIZE_Y / 8 * 4);
    morningInvert.SetTopLeft((SIZE_X / 2) - (start.Width() / 2), SIZE_Y / 8 * 4);
    instructionsInvert.SetTopLeft((SIZE_X / 2) - (end.Width() / 2), SIZE_Y / 8 * 5);
    endInvert.SetTopLeft((SIZE_X / 2) - (end.Width() / 2), SIZE_Y / 8 * 6);
    //顯示 開始按鈕 結束按鈕

    if (!isNight)
    {
        logo.ShowBitmap();
        night.ShowBitmap();
    }
    else
    {
        nightMap.ShowBitmap();
        morning.ShowBitmap();
        logoNight.ShowBitmap();
    }

    start.ShowBitmap();
    instructions.ShowBitmap();
    end.ShowBitmap();
    //設定鐵軌位置 和顯示
    orange.SetTopLeft(0, 280);
    orange.ShowBitmap();

    if (orangeCabinY > 333)
    {
        orangeCabin.SetTopLeft(orangeCabinX, orangeCabinY);
        orangeCabin.ShowBitmap();
    }
    else
    {
        orangeCabin2.SetTopLeft(orangeCabinX, orangeCabinY);
        orangeCabin2.ShowBitmap();
    }

    red.SetTopLeft(0, 307);
    red.ShowBitmap();

    if (redCabinY < 375)
    {
        redCabin2.SetTopLeft(redCabinX, redCabinY);
        redCabin2.ShowBitmap();
    }
    else
    {
        redCabin.SetTopLeft(redCabinX, redCabinY);
        redCabin.ShowBitmap();
    }

    blue.SetTopLeft(699, 0);
    blue.ShowBitmap();

    if (blueCabinY < 70)
    {
        blueCabin2.SetTopLeft(blueCabinX, blueCabinY);
        blueCabin2.ShowBitmap();
    }
    else
    {
        blueCabin.SetTopLeft(694, blueCabinY);
        blueCabin.ShowBitmap();
    }

    bblue.SetTopLeft(691, 337);
    bblue.ShowBitmap();

    if (bblueCabinY < 425)
    {
        bblueCabin2.SetTopLeft(bblueCabinX, bblueCabinY);
        bblueCabin2.ShowBitmap();
    }
    else
    {
        bblueCabin.SetTopLeft(bblueCabinX, bblueCabinY);
        bblueCabin.ShowBitmap();
    }

    //
    // 滑鼠移到上面 讓按鈕變色
    //

    if (isMouseInStartBtn)
    {
        startInvert.ShowBitmap();
    }
    else if (isMouseInEndBtn)
    {
        endInvert.ShowBitmap();
    }
    else if (isMouseInNightBtn && !isNight)
    {
        nightInvert.ShowBitmap();
    }
    else if (isMouseInNightBtn && isNight)
    {
        morningInvert.ShowBitmap();
    }
    else if (isMouseInInstructionsBtn)
    {
        instructionsInvert.ShowBitmap();
    }

    if (isInInstructions)
    {
        if (page == 1)
        {
            page1.SetTopLeft(0, 0);
            page1.ShowBitmap();
        }
        else if (page == 2)
        {
            page2.SetTopLeft(0, 0);
            page2.ShowBitmap();
        }
    }

    //
    // Demo螢幕字型的使用，不過開發時請盡量避免直接使用字型，改用CMovingBitmap比較好
    //
    /*
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
    */
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
    endl.LoadBitmap(".\\RES\\Gameover\\gameover.bmp");
    endlNight.LoadBitmap(".\\RES\\Gameover\\gameovernight.bmp", RGB(0, 0, 0));
    mapNight.LoadBitmapA(".\\RES\\backgroundnight.bmp");
    sp4.LoadBitmap(".\\RES\\Gameover\\sp4.bmp", RGB(255, 255, 255));
    sp4Night.LoadBitmap(".\\RES\\Gameover\\sp4night.bmp");
    good.LoadBitmap(".\\RES\\Gameover\\good.bmp", RGB(255, 255, 255));
    goodNight.LoadBitmap(".\\RES\\Gameover\\goodnight.bmp");
    bad.LoadBitmap(".\\RES\\Gameover\\bad.bmp", RGB(255, 255, 255));
    badNight.LoadBitmap(".\\RES\\Gameover\\badnight.bmp");
    //
    // 最終進度為100%
    //
    ShowInitProgress(100);
}

void CGameStateOver::OnShow()
{
    endl.SetTopLeft((SIZE_X / 2) - (endl.Width() / 2), SIZE_Y / 8 * 1);
    endlNight.SetTopLeft((SIZE_X / 2) - (endl.Width() / 2), SIZE_Y / 8 * 1);
    mapNight.SetTopLeft(0, 0);
    sp4.SetTopLeft(0, 0);
    sp4Night.SetTopLeft(0, 0);
    good.SetTopLeft(0, 0);
    goodNight.SetTopLeft(0, 0);
    bad.SetTopLeft(0, 0);
    badNight.SetTopLeft(0, 0);

    if (personss <= 30)
    {
        if (isNight)
        {
            sp4Night.ShowBitmap();
            endlNight.ShowBitmap();
        }
        else
        {
            endl.ShowBitmap();
            sp4.ShowBitmap();
        }
    }
    else if (personss > 30 && personss <= 50)
    {
        if (isNight)
        {
            goodNight.ShowBitmap();
            endlNight.ShowBitmap();
        }
        else
        {
            endl.ShowBitmap();
            good.ShowBitmap();
        }
    }
    else if (personss > 50)
    {
        if (isNight)
        {
            badNight.ShowBitmap();
            endlNight.ShowBitmap();
        }
        else
        {
            endl.ShowBitmap();
            bad.ShowBitmap();
        }
    }

    /*CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC
    CFont f, *fp;
    f.CreatePointFont(160, "Times New Roman");	// 產生 font f; 160表示16 point的字
    fp = pDC->SelectObject(&f);					// 選用 font f
    pDC->SetBkColor(RGB(0, 0, 0));
    pDC->SetTextColor(RGB(255, 255, 0));
    char str[80];								// Demo 數字對字串的轉換
    sprintf(str, "Game Over ! (%d)", counter / 30);
    pDC->TextOut(240, 210, str);
    pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
    CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC*/
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
    for (unsigned i = 0; i < passengerList.size(); i++)
    {
        if (passengerList[i] != nullptr)
        {
            delete passengerList[i];
        }
    }
}

void CGameStateRun::OnBeginState()
{
    isInInstructions = false;
    isMouseInInstructionsBtn = false;
    page = 0;
    totalper = 0;
    passengerTotalNumber.SetIsNight(isNight);
    red = true;
    orange = false;
    yellow = false;
    green = false;
    blue = false;
    bblue = false;
    purple = false;
    const int HITS_LEFT = 0;
    const int HITS_LEFT_X = 680;
    const int HITS_LEFT_Y = 20;
    passengerTotalNumber.SetInteger(HITS_LEFT);					// 指定剩下的撞擊數
    passengerTotalNumber.SetTopLeft(HITS_LEFT_X, HITS_LEFT_Y);
    redLine.Reset();
    orangeLine.Reset();
    yellowLine.Reset();
    greenLine.Reset();
    blueLine.Reset();
    bblueLine.Reset();
    purpleLine.Reset();
    redLine.SetLineColor(255, 0, 0);
    redLine.SetIsCanbeClicked(true);
    orangeLine.SetLineColor(255, 144, 0);
    yellowLine.SetLineColor(255, 255, 0);
    greenLine.SetLineColor(0, 255, 0);
    blueLine.SetLineColor(0, 138, 255);
    bblueLine.SetLineColor(0, 6, 255);
    purpleLine.SetLineColor(144, 0, 255);

    for (int i = 0; i < 7; i++)
    {
        passengerListOnCabin[i].clear();
    }

    vector <Cabin> a;
    cabinList.assign(a.begin(), a.end());
    Station* s = new Station;										//用來建立隨機車站列表 及 檢查車站 列表 是否重疊
    Passenger* p = new Passenger;									//用來建立隨機乘客個數 及 隨機列表
    line = &redLine;
    counter = 0;
    //建立隨機車站列表
    s->RandomBuildStation(stationList);
    //檢查車站列表是否有重疊的車站
    s->CheckedOverLappingStation(stationList);
    s->SetIsNight(isNight);
    //建立乘客列表
    p->RandomMadePassenger(passengerList, stationList, MAXIUM_STATION, MAXIUM_STATION_TYPE, INIT_PASSANGER);
    p->SetIsNight(isNight);
    garyIcon[0].SetTopLeft(285, 570);
    garyIcon[1].SetTopLeft(330, 570);
    garyIcon[2].SetTopLeft(375, 570);
    garyIcon[3].SetTopLeft(420, 570);
    garyIcon[4].SetTopLeft(465, 570);
    garyIcon[5].SetTopLeft(510, 570);
    chooseColor.SetTopLeft(240, 570);
    chooseColorNight.SetTopLeft(240, 570);
    currentStationNum = 3;								//現有車站為三個 遊戲開始 有三個車站
    currentPassenagerNum = 0;							//一開始出現的乘客數為0
    clickedX = clickedY = -1;
    delete s;
    delete p;
}

void CGameStateRun::OnMove()							// 移動遊戲元素
{
    if (!isStop)
    {
        counter++;
        clock.OnMove();				//播放clock時鐘動畫
        vector<int> pointX;
        vector<int> pointY;
        vector<int> passedStation;

        /*每 STATION_APPERAED_TIME 秒就出一個車站
        if (counter % (30 * STATION_APPERAED_TIME) == 0 && currentStationNum < MAXIUM_STATION)
        {
        	currentStationNum++;
        	//CAudio::Instance()->Play(AUDIO_APPEAR);
        }
        */
        //每 PASSENAGER_APPERAED_TIME 秒就出一個乘客
        if (counter % (30 * PASSENAGER_APPERAED_TIME) == 0)
        {
            Passenger* p = new Passenger;
            p->RandomOnePassenger(passengerList, stationList, MAXIUM_STATION, MAXIUM_STATION_TYPE);
            delete p;
        }

        if (counter >= LINE_CAN_USE_TIME * 2 * 30)
            orangeLine.SetIsCanbeClicked(true);

        if (counter >= LINE_CAN_USE_TIME * 3 * 30)
            yellowLine.SetIsCanbeClicked(true);

        if (counter >= LINE_CAN_USE_TIME * 4 * 30)
            greenLine.SetIsCanbeClicked(true);

        if (counter >= LINE_CAN_USE_TIME * 5 * 30)
            blueLine.SetIsCanbeClicked(true);

        if (counter >= LINE_CAN_USE_TIME * 6 * 30)
            bblueLine.SetIsCanbeClicked(true);

        if (counter >= LINE_CAN_USE_TIME * 7 * 30)
            purpleLine.SetIsCanbeClicked(true);

        if (line->IsClickedTwoStation())
        {
            int R, G, B;
            int countPassedStation[6] = { 0 };
            Cabin c ;
            line->SetPassedStation(line->GetClickedStartStationNum(), line->GetClickedEndStationNum());
            line->SetLinePointXY(stationList);
            line->SetClickedStartStationNum(-1);
            line->SetClickedEndStationNum(-1);
            line->GetLinePointXY(pointX, pointY);
            line->GetPassedStationNum(passedStation);
            line->GetLineColorRGB(R, G, B);
            line->CountTotalPassedStation();
            line->GetTotalPassedStation(countPassedStation);

            if (!c.IsCabinColorRepeat(cabinList, R, G, B))
            {
                Cabin buf(pointX[0], pointY[0], R, G, B);
                buf.SetLinePoint(pointX, pointY);
                buf.SetPassedStation(passedStation);
                buf.SetLineStationNum(countPassedStation);
                cabinList.push_back(buf);
            }
            else
            {
                int pos = c.GetCabinPointer(cabinList, R, G, B);
                cabinList[pos].SetLinePoint(pointX, pointY);
                cabinList[pos].SetPassedStation(passedStation);
                cabinList[pos].SetLineStationNum(countPassedStation);
            }
        }

        if (!cabinList.empty())
        {
            for (unsigned i = 0; i < cabinList.size(); i++) //每個車廂
            {
                cabinList[i].OnMove(stationList);

                if (cabinList[i].IsStop()) //火車進站囉
                {
                    //乘客上下車
                    cabinList[i].SetAddCounter(1);
                    int nowCabinInStationNum = cabinList[i].GetNextStation(); //目前車廂在哪個車站

                    //先下車後上車
                    //========下車========
                    if ((int)passengerListOnCabin[i].size() > 0 && cabinList[i].GetCounter() == 10)
                    {
                        cabinList[i].PassengerGetOut(passengerListOnCabin[i], nowCabinInStationNum);
                        //cabinList[i].PassengerGetOut(nowCabinInStationNum);
                        totalper += cabinList[i].GetOutPeople();
                        passengerTotalNumber.Add(cabinList[i].GetOutPeople());
                    }

                    //========上車========
                    if (cabinList[i].GetCounter() == 20)
                    {
                        for (unsigned j = passengerList.size() - 1; j >= 0; j--) //每個乘客
                        {
                            if (j > passengerList.size())
                            {
                                break;
                            }
                            else if ((int)passengerListOnCabin[i].size() < MAX_PASSENGER_NUM) //車廂乘客小於六個
                            {
                                int cabinPassedStation[6] = { 0 }; //車廂會經過的站
                                cabinList[i].GetLineStationNum(cabinPassedStation);

                                if (cabinPassedStation[passengerList[j]->GetFinalStation()] == 1 && passengerList[j]->GetStartStation() == nowCabinInStationNum)
                                    //確定乘客要去的站有在這條線路上
                                {
                                    //cabinList[i].PassengerGetOn(passengerList[j]);
                                    passengerListOnCabin[i].push_back(passengerList[j]);
                                    cabinList[i].SetPassengerPosition(passengerListOnCabin[i]);
                                    stationList[nowCabinInStationNum].ErasePassenger(passengerList[j]);
                                    passengerList.erase(passengerList.begin() + j);
                                }
                            }
                        }
                    }

                    if (cabinList[i].GetCounter() == 30)
                    {
                        cabinList[i].SetCounter(0);
                        cabinList[i].SetIsStop(false);
                    }
                }
            }

            for (unsigned i = 0; i < stationList.size(); i++)
            {
                stationList[i].RefreshPassengerPosition();
            }
        }

        if (counter == 120 * 30)
        {
            personss = totalper;
            GotoGameState(GAME_STATE_OVER);
        }
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
    //
    Station* s = new Station;										//用來建立隨機車站列表 及 檢查車站 列表 是否重疊
    instructions.LoadBitmap(".\\RES\\button\\Instructions.bmp");
    instructionsInvert.LoadBitmap(".\\RES\\button\\InstructionsInvert.bmp");
    page1.LoadBitmap(".\\RES\\Instruction.bmp");
    page2.LoadBitmap(".\\RES\\Instruction2.bmp");
    clock.LoadBitmap();
    esc.LoadBitmap(".\\RES\\esc.bmp", RGB(255, 255, 255));
    esc.SetTopLeft(700, 565);
    escNight.LoadBitmap(".\\RES\\escnight.bmp", RGB(0, 0, 0));
    escNight.SetTopLeft(700, 565);
    passengerTotalNumber.LoadBitmap();
    mapnight.LoadBitmap(".\\RES\\backgroundnight.bmp");
    map.LoadBitmap(".\\RES\\map.bmp");
    nightMap.LoadBitmap(".\\RES\\mapNight.bmp");
    person.LoadBitmap(".\\RES\\person.bmp", RGB(255, 255, 255));
    personNight.LoadBitmap(".\\RES\\personnight.bmp", RGB(0, 0, 0));
    backGround.LoadBitmap(".\\RES\\background.bmp");
    continu.LoadBitmap(".\\RES\\button\\continu.bmp");
    continuInvert.LoadBitmap(".\\RES\\button\\continuInvert.bmp");
    restart.LoadBitmap(".\\RES\\button\\restart.bmp");
    restartInvert.LoadBitmap(".\\RES\\button\\restartInvert.bmp");
    night.LoadBitmap(".\\RES\\button\\night.bmp");
    nightInvert.LoadBitmap(".\\RES\\button\\nightInvert.bmp");
    morning.LoadBitmap(".\\RES\\button\\morning.bmp");
    morningInvert.LoadBitmap(".\\RES\\button\\morningInvert.bmp");
    night.SetTopLeft((SIZE_X / 2) - (restart.Width() / 2), SIZE_Y / 8 * 4);
    morning.SetTopLeft((SIZE_X / 2) - (restart.Width() / 2), SIZE_Y / 8 * 4);
    nightInvert.SetTopLeft((SIZE_X / 2) - (restart.Width() / 2), SIZE_Y / 8 * 4);
    morningInvert.SetTopLeft((SIZE_X / 2) - (restart.Width() / 2), SIZE_Y / 8 * 4);
    restart.SetTopLeft((SIZE_X / 2) - (restart.Width() / 2), SIZE_Y / 8 * 3);
    restartInvert.SetTopLeft((SIZE_X / 2) - (restart.Width() / 2), SIZE_Y / 8 * 3);
    continu.SetTopLeft((SIZE_X / 2) - (restart.Width() / 2), SIZE_Y / 8 * 2);
    continuInvert.SetTopLeft((SIZE_X / 2) - (restart.Width() / 2), SIZE_Y / 8 * 2);
    end.LoadBitmap(".\\RES\\button\\end.bmp");
    endInvert.LoadBitmap(".\\RES\\button\\endInvert.bmp");
    instructions.SetTopLeft((SIZE_X / 2) - (end.Width() / 2), SIZE_Y / 8 * 5);
    instructionsInvert.SetTopLeft((SIZE_X / 2) - (end.Width() / 2), SIZE_Y / 8 * 5);
    end.SetTopLeft((SIZE_X / 2) - (end.Width() / 2), SIZE_Y / 8 * 6);
    endInvert.SetTopLeft((SIZE_X / 2) - (end.Width() / 2), SIZE_Y / 8 * 6);
    isStop = false;
    isStop2 = false;
    isMouseInRestartBtn = false;
    isMouseInEndBtn = false;
    CAudio::Instance()->Load(AUDIO_STOP1, "sounds\\stop1.mp3");
    CAudio::Instance()->Load(AUDIO_STOP2, "sounds\\stop2.mp3");
    CAudio::Instance()->Load(AUDIO_COLOR, "sounds\\odd.wav");
    /*red(255.0.0),orang(255.144.0),yellow(255.255.0),green(0.255.0),blue(0.138.255),bblue(0.6.255),puple(144.0.255)*/
    redLine.SetLineColor(255, 0, 0);
    redLine.SetIsCanbeClicked(true);
    orangeLine.SetIsCanbeClicked(true);
    yellowLine.SetIsCanbeClicked(true);
    greenLine.SetIsCanbeClicked(true);
    blueLine.SetIsCanbeClicked(true);
    bblueLine.SetIsCanbeClicked(true);
    purpleLine.SetIsCanbeClicked(true);
    orangeLine.SetLineColor(255, 144, 0);
    yellowLine.SetLineColor(255, 255, 0);
    greenLine.SetLineColor(0, 255, 0);
    blueLine.SetLineColor(0, 138, 255);
    bblueLine.SetLineColor(0, 6, 255);
    purpleLine.SetLineColor(144, 0, 255);
    ShowInitProgress(40);
    redLine.LoadBitmap();
    orangeLine.LoadBitmap();
    yellowLine.LoadBitmap();
    greenLine.LoadBitmap();
    blueLine.LoadBitmap();
    bblueLine.LoadBitmap();
    purpleLine.LoadBitmap();
    chooseColor.LoadBitmap(".\\RES\\color\\choosecolor.bmp", RGB(255, 255, 255));
    chooseColorNight.LoadBitmap(".\\RES\\color\\choosecolornight.bmp", RGB(0, 0, 0));

    for (unsigned i = 0; i < 6; i++)
    {
        CMovingBitmap a;
        a.LoadBitmap(".\\RES\\color\\gray.bmp", RGB(255, 255, 255));
        garyIcon.push_back(a);
    }

    //建立隨機車站列表
    s->RandomBuildStation(stationList);
    //檢查車站列表是否有重疊的車站
    s->CheckedOverLappingStation(stationList);
    //載入各車站圖片
    ShowInitProgress(50);
    CAudio::Instance()->Load(AUDIO_SELECT1, "sounds\\select1.mp3");
    CAudio::Instance()->Load(AUDIO_SELECT2, "sounds\\select2.mp3");
    CAudio::Instance()->Load(AUDIO_APPEAR, "sounds\\appear.mp3");
    delete s;
    //Sleep(300); // 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
    //
    // 繼續載入其他資料
    //
    //
    // 此OnInit動作會接到CGameStaterOver::OnInit()，所以進度還沒到100%
    //
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    const char KEY_LEFT = 0x25; // keyboard左箭頭
    const char KEY_UP = 0x26; // keyboard上箭頭
    const char KEY_RIGHT = 0x27; // keyboard右箭頭
    const char KEY_DOWN = 0x28; // keyboard下箭頭
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    const char KEY_LEFT = 0x25; // keyboard左箭頭
    const char KEY_UP = 0x26; // keyboard上箭頭
    const char KEY_RIGHT = 0x27; // keyboard右箭頭
    const char KEY_DOWN = 0x28; // keyboard下箭頭
    const char KEY_ESC = 27;

    if (nChar == KEY_ESC)
    {
        if (!isStop2 && !isStop)
        {
            isStop2 = !isStop2;
            isStop = !isStop;
        }
    }

    if (nChar == KEY_UP)//人數加十
    {
        if (!isStop && !isStop2)
        {
            if (passengerTotalNumber.GetInteger() < 999)
            {
                if (passengerTotalNumber.GetInteger() == 990)
                {
                    totalper += 9;
                    passengerTotalNumber.Add(9);
                }
                else
                {
                    totalper += 10;
                    passengerTotalNumber.Add(10);
                }
            }
        }
    }

    if (isInInstructions)
    {
        if (nChar == KEY_RIGHT)
        {
            if (isInInstructions)
            {
                if (page == 2)
                {
                    page = 0;
                    isInInstructions = !isInInstructions;
                }
                else
                {
                    page++;
                }
            }
        }
    }

    if (nChar == KEY_DOWN)//快速結算
    {
        if (!isStop && !isStop2)
        {
            counter = 120 * 30 - 1;
        }
    }
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)
{
    // 這邊負責處理按下滑鼠左鍵的動作
    int start = line->GetClickedStartStationNum();	//紀錄起始車站
    int end = line->GetClickedEndStationNum();	//紀錄終點車站

    if (!isStop)
    {
        if (start == -1) //沒有任何車站被選取
        {
            if (line->IsClickedStation(point.x, point.y, stationList, MAXIUM_STATION)) //檢查是否有點到車站
            {
                CAudio::Instance()->Play(AUDIO_SELECT1);
                start = line->GetMouseClickedStationNum(point.x, point.y, stationList, MAXIUM_STATION);
                line->SetClickedStartStationNum(start);

                if (!(line->IsPassedStationEmpty() || line->GetClickedFirstStation() == line->GetClickedStartStationNum() || line->GetClickedLastStation() == line->GetClickedStartStationNum()))
                {
                    line->SetClickedStartStationNum(-1);
                    line->SetClickedEndStationNum(-1);
                }
            }
            else
            {
                line->SetClickedStartStationNum(-1);
                line->SetClickedEndStationNum(-1);
            }
        }
        else //如果起點車站已經被選取
        {
            if (line->IsClickedStation(point.x, point.y, stationList, MAXIUM_STATION)) //檢查是否有點到車站
            {
                CAudio::Instance()->Play(AUDIO_SELECT2);
                end = line->GetMouseClickedStationNum(point.x, point.y, stationList, MAXIUM_STATION);
                line->SetClickedEndStationNum(end);
            }
            else
            {
                line->SetClickedStartStationNum(-1);
                line->SetClickedEndStationNum(-1);
            }
        }
    }

    if (!isStop2)
    {
        if (point.x >= 750 && point.y >= 10 && point.x <= 790 && point.y <= 50)
        {
            CAudio::Instance()->Play(AUDIO_SLIP);

            if (isStop)
            {
                CAudio::Instance()->Play(AUDIO_STOP1);
            }
            else
            {
                CAudio::Instance()->Play(AUDIO_STOP2);
            }

            isStop = !isStop;
        }
    }

    clickedX = point.x;	//用來debug
    clickedY = point.y; //用來debug
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠左鍵的動作 放開
{
    //換鐵軌的顏色
    if (redLine.IsMouseClickedLineColorBMP(point.x, point.y))
    {
        line = &redLine;
        CAudio::Instance()->Play(AUDIO_COLOR);
        red = true;
        orange = false;
        yellow = false;
        green = false;
        blue = false;
        bblue = false;
        purple = false;
    }
    else if (orangeLine.IsMouseClickedLineColorBMP(point.x, point.y))
    {
        line = &orangeLine;
        CAudio::Instance()->Play(AUDIO_COLOR);
        red = false;
        orange = true;
        yellow = false;
        green = false;
        blue = false;
        bblue = false;
        purple = false;
    }
    else if (yellowLine.IsMouseClickedLineColorBMP(point.x, point.y))
    {
        line = &yellowLine;
        CAudio::Instance()->Play(AUDIO_COLOR);
        red = false;
        orange = false;
        yellow = true;
        green = false;
        blue = false;
        bblue = false;
        purple = false;
    }
    else if (greenLine.IsMouseClickedLineColorBMP(point.x, point.y))
    {
        line = &greenLine;
        CAudio::Instance()->Play(AUDIO_COLOR);
        red = false;
        orange = false;
        yellow = false;
        green = true;
        blue = false;
        bblue = false;
        purple = false;
    }
    else if (blueLine.IsMouseClickedLineColorBMP(point.x, point.y))
    {
        line = &blueLine;
        CAudio::Instance()->Play(AUDIO_COLOR);
        red = false;
        orange = false;
        yellow = false;
        green = false;
        blue = true;
        bblue = false;
        purple = false;
    }
    else if (bblueLine.IsMouseClickedLineColorBMP(point.x, point.y))
    {
        line = &bblueLine;
        CAudio::Instance()->Play(AUDIO_COLOR);
        red = false;
        orange = false;
        yellow = false;
        green = false;
        blue = false;
        bblue = true;
        purple = false;
    }
    else if (purpleLine.IsMouseClickedLineColorBMP(point.x, point.y))
    {
        line = &purpleLine;
        CAudio::Instance()->Play(AUDIO_COLOR);
        red = false;
        orange = false;
        yellow = false;
        green = false;
        blue = false;
        bblue = false;
        purple = true;
    }

    if (isStop2)
    {
        if (!isInInstructions)
        {
            if (restart.IsBitmapLoaded() && restartInvert.IsBitmapLoaded())
            {
                if (isMouseInRestartBtn)
                {
                    isStop = !isStop;
                    isStop2 = !isStop2;
                    GotoGameState(GAME_STATE_INIT);
                }
                else if (isMouseInEndBtn)
                {
                    PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// 關閉遊戲
                }
                else if (isMouseInNightBtn)
                {
                    isNight = !isNight;
                }
                else if (isMouseInContinuBtn)
                {
                    isStop = !isStop;
                    isStop2 = !isStop2;
                }
                else if (isMouseInInstructionsBtn)
                {
                    isInInstructions = !isInInstructions;
                    page = 1;
                }
            }
        }
    }
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠左鍵的動作 移動
{
    // 沒事。如果需要處理滑鼠移動的話，寫code在這裡
    if (point.x > MIN_GAME_MAP_SIDE_X && point.x < MAX_GAME_MAP_SIDE_X + 135) mouse_x = point.x;

    if (point.y > MIN_GAME_MAP_SIDE_Y && point.y < MAX_GAME_MAP_SIDE_Y) mouse_y = point.y;

    if (!isInInstructions && isStop2)
    {
        if (restart.IsBitmapLoaded() && restartInvert.IsBitmapLoaded())
        {
            if (mouse_x > restart.Left() && mouse_x < restart.Left() + restart.Width() &&
                    mouse_y > restart.Top() && mouse_y < restart.Top() + restart.Height())
            {
                if (mouse_state == 1)
                {
                    isMouseInRestartBtn = true;
                    CAudio::Instance()->Play(AUDIO_SLIP);
                    mouse_state = 0;
                }
            }
            else if (mouse_x > end.Left() && mouse_x < end.Left() + end.Width() &&
                     mouse_y > end.Top() && mouse_y < end.Top() + end.Height())
            {
                if (mouse_state == 1)
                {
                    isMouseInEndBtn = true;
                    CAudio::Instance()->Play(AUDIO_SLIP);
                    mouse_state = 0;
                }
            }
            else if (mouse_x > night.Left() && mouse_x < night.Left() + night.Width() &&
                     mouse_y > night.Top() && mouse_y < night.Top() + night.Height())
            {
                if (mouse_state == 1)
                {
                    isMouseInNightBtn = true;
                    CAudio::Instance()->Play(AUDIO_SLIP);
                    mouse_state = 0;
                }
            }
            else if (mouse_x > continu.Left() && mouse_x < continu.Left() + continu.Width() &&
                     mouse_y > continu.Top() && mouse_y < continu.Top() + continu.Height())
            {
                if (mouse_state == 1)
                {
                    isMouseInContinuBtn = true;
                    CAudio::Instance()->Play(AUDIO_SLIP);
                    mouse_state = 0;
                }
            }
            else if (mouse_x > instructions.Left() && mouse_x < instructions.Left() + instructions.Width() &&
                     mouse_y > instructions.Top() && mouse_y < instructions.Top() + instructions.Height())
            {
                if (mouse_state == 1)
                {
                    isMouseInInstructionsBtn = true;
                    CAudio::Instance()->Play(AUDIO_SLIP);
                    mouse_state = 0;
                }
            }
            else
            {
                mouse_state = 1;
                isMouseInContinuBtn = false;
                isMouseInNightBtn = false;
                isMouseInEndBtn = false;
                isMouseInInstructionsBtn = false;
                isMouseInRestartBtn = false;
            }
        }
    }
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
    map.SetTopLeft(0, 0);	//設置地圖位置

    if (isNight)
    {
        nightMap.ShowBitmap();
    }
    else
    {
        map.ShowBitmap();		//把地圖顯示出來
    }

    clock.OnShow();			//顯示時鐘
    //===============顯示各顏色的路線的圖標==============
    purpleLine.ShowLineIconBitmap();	//紫色
    bblueLine.ShowLineIconBitmap();		//靛色
    blueLine.ShowLineIconBitmap();		//藍色
    greenLine.ShowLineIconBitmap();		//綠色
    yellowLine.ShowLineIconBitmap();	//黃色
    orangeLine.ShowLineIconBitmap();	//橘色
    redLine.ShowLineIconBitmap();		//紅色

    if (!orangeLine.IsIconCanBeClicked())
        garyIcon[0].ShowBitmap();

    if (!yellowLine.IsIconCanBeClicked())
        garyIcon[1].ShowBitmap();

    if (!greenLine.IsIconCanBeClicked())
        garyIcon[2].ShowBitmap();

    if (!blueLine.IsIconCanBeClicked())
        garyIcon[3].ShowBitmap();

    if (!bblueLine.IsIconCanBeClicked())
        garyIcon[4].ShowBitmap();

    if (!purpleLine.IsIconCanBeClicked())
        garyIcon[5].ShowBitmap();

    if (red)
    {
        chooseColor.SetTopLeft(240, 570);
        chooseColorNight.SetTopLeft(240, 570);
    }

    if (orange)
    {
        chooseColor.SetTopLeft(285, 570);
        chooseColorNight.SetTopLeft(285, 570);
    }

    if (yellow)
    {
        chooseColor.SetTopLeft(330, 570);
        chooseColorNight.SetTopLeft(330, 570);
    }

    if (green)
    {
        chooseColor.SetTopLeft(375, 570);
        chooseColorNight.SetTopLeft(375, 570);
    }

    if (blue)
    {
        chooseColor.SetTopLeft(420, 570);
        chooseColorNight.SetTopLeft(420, 570);
    }

    if (bblue)
    {
        chooseColor.SetTopLeft(465, 570);
        chooseColorNight.SetTopLeft(465, 570);
    }

    if (purple)
    {
        chooseColor.SetTopLeft(510, 570);
        chooseColorNight.SetTopLeft(510, 570);
    }

    passengerTotalNumber.SetIsNight(isNight);

    if (isNight)
    {
        personNight.SetTopLeft(640, 10);
        personNight.ShowBitmap();
        passengerTotalNumber.ShowBitmap();
        chooseColorNight.ShowBitmap();
        escNight.ShowBitmap();
    }
    else
    {
        chooseColor.ShowBitmap();
        person.SetTopLeft(640, 10);
        person.ShowBitmap();
        passengerTotalNumber.ShowBitmap();
        esc.ShowBitmap();
    }

    //===============================================

    // 如果有一個車站被選取 就要畫出來 //換句話說 就是線路要跟著滑鼠動
    if (line->GetClickedStartStationNum() != -1 &&
            (line->IsPassedStationEmpty() ||
             line->GetClickedLastStation() == line->GetClickedStartStationNum()))
        line->DrawRailway(stationList[line->GetClickedStartStationNum()].GetX() + 5,
                          stationList[line->GetClickedStartStationNum()].GetY() + 5, mouse_x, mouse_y);

    //顯示各顏色線路
    purpleLine.ShowRailway(stationList);
    bblueLine.ShowRailway(stationList);
    blueLine.ShowRailway(stationList);
    greenLine.ShowRailway(stationList);
    yellowLine.ShowRailway(stationList);
    orangeLine.ShowRailway(stationList);
    redLine.ShowRailway(stationList);

    if (!cabinList.empty())
        for (unsigned i = 0; i < cabinList.size(); i++)
        {
            cabinList[i].OnShow();
            cabinList[i].SetPassengerPosition(passengerListOnCabin[i]);
        }

    for (int i = 0; i < MAXIUM_STATION; i++)
    {
        stationList[i].SetIsNight(isNight);
        stationList[i].OnShowStation();
    }

    for (int i = 0; i < (int)passengerList.size(); i++)
    {
        passengerList[i]->SetIsNight(isNight);
        passengerList[i]->OnShow();
    }

    for (int i = 0; i < 7; i++)
    {
        for (unsigned j = 0; j < passengerListOnCabin[i].size(); j++)
        {
            passengerListOnCabin[i][j]->OnShow();
        }
    }

    if (isStop2)
    {
        if (isNight)
        {
            mapnight.ShowBitmap();
            morning.ShowBitmap();
        }
        else
        {
            backGround.ShowBitmap();
            night.ShowBitmap();
        }

        restart.ShowBitmap();
        end.ShowBitmap();
        continu.ShowBitmap();
        instructions.ShowBitmap();

        if (isMouseInRestartBtn)
        {
            restartInvert.ShowBitmap();
        }
        else if (isMouseInEndBtn)
        {
            endInvert.ShowBitmap();
        }
        else if (isMouseInContinuBtn)
        {
            continuInvert.ShowBitmap();
        }
        else if (isMouseInNightBtn && isNight)
        {
            morningInvert.ShowBitmap();
        }
        else if (isMouseInNightBtn && !isNight)
        {
            nightInvert.ShowBitmap();
        }
        else if (isMouseInInstructionsBtn)
        {
            instructionsInvert.ShowBitmap();
        }

        if (isInInstructions)
        {
            if (page == 1)
            {
                page1.SetTopLeft(0, 0);
                page1.ShowBitmap();
            }
            else if (page == 2)
            {
                page2.SetTopLeft(0, 0);
                page2.ShowBitmap();
            }
        }
    }

    //// 以下Debug 用
    CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC
    CFont f, *fp;
    f.CreatePointFont(160, "Times New Roman");	// 產生 font f; 160表示16 point的字
    fp = pDC->SelectObject(&f);					// 選用 font f

    if (isNight)
    {
        pDC->SetBkColor(RGB(45, 45, 45));
        pDC->SetTextColor(RGB(255, 255, 255));
    }
    else
    {
        if (isStop2)
        {
            pDC->SetBkColor(RGB(255, 255, 255));
        }
        else
        {
            pDC->SetBkColor(RGB(241, 241, 241));
        }

        pDC->SetTextColor(RGB(0, 0, 0));
    }

    char str[80];								// Demo 數字對字串的轉換
    //sprintf(str, "(%d,%d),(%d,%d),(%d,%d),(%d,%d)(%d)", clickedX, clickedY, mouse_x, mouse_y, line->GetClickedStartStationNum(), line->GetClickedEndStationNum(), preP, nextP, nextS);
    sprintf(str, "遊戲時間：%d", 120 - counter / 30);
    pDC->TextOut(10, 10, str);
    pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
    CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
}
}