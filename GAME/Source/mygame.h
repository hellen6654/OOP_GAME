/*
 * mygame.h: 本檔案儲遊戲本身的class的interface
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
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *   2006-02-08 V4.2
 *      1. Rename OnInitialUpdate() -> OnInit().
 *      2. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      3. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress.
*/

#include "CEraser.h"
#include "CBall.h"
#include "CBouncingBall.h"
#include "Station.h"
#include "Clock.h"
#include "Week.h"
#include "Timer.h"
#include "Line.h"
#include "Passenger.h"
#include "Cabin.h"

namespace game_framework
{
/////////////////////////////////////////////////////////////////////////////
// Constants
/////////////////////////////////////////////////////////////////////////////

enum AUDIO_ID  				// 定義各種音效的編號
{
    AUDIO_SLIP,				// 0
    AUDIO_CLICK,				// 1
    AUDIO_MUSIC,			// 2
    AUDIO_SELECT1,
    AUDIO_SELECT2,
    AUDIO_APPEAR,
    AUDIO_STOP1,
    AUDIO_STOP2
};

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲開頭畫面物件
// 每個Member function的Implementation都要弄懂
/////////////////////////////////////////////////////////////////////////////

class CGameStateInit : public CGameState
{
    public:
        CGameStateInit(CGame* g);
        void OnInit();  								// 遊戲的初值及圖形設定
        void OnBeginState();							// 設定每次重玩所需的變數
        void OnKeyUp(UINT, UINT, UINT); 				// 處理鍵盤Up的動作
        void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
        void OnLButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
        void OnMouseMove(UINT nFlags, CPoint point);	// 處理滑鼠的動作
    protected:
        void OnShow();									// 顯示這個狀態的遊戲畫面
    private:
        CMovingBitmap end;
        CMovingBitmap start;
        CMovingBitmap logo;								// csie的logo
        int mouse_x = 0, mouse_y = 0;					//滑鼠位置

        int mouse_state = 1;
};

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
// 每個Member function的Implementation都要弄懂
/////////////////////////////////////////////////////////////////////////////

class CGameStateRun : public CGameState
{
    public:
        CGameStateRun(CGame* g);
        ~CGameStateRun();
        void OnBeginState();							// 設定每次重玩所需的變數
        void OnInit();  								// 遊戲的初值及圖形設定
        void OnKeyDown(UINT, UINT, UINT);
        void OnKeyUp(UINT, UINT, UINT);
        void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
        void OnLButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
        void OnMouseMove(UINT nFlags, CPoint point);	// 處理滑鼠的動作
        void OnRButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
        void OnRButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
    protected:
        void OnMove();									// 移動遊戲元素
        void OnShow();									// 顯示這個狀態的遊戲畫面
    private:
        CMovingBitmap  map;
        CMovingBitmap  color[7];
        const int STATION_APPERAED_TIME = 5;			//車站出現的秒數
        const int PASSENAGER_APPERAED_TIME = 3;			//乘客出現的秒數
        const int MAXIUM_STATION = 10;					//會出現在地圖上車站總數
        const int MAXIUM_STATION_TYPE = 7;				//車站樣式總共有7個 00~06
        const int LINE_COLOR_NUM = 7;					//車站樣式總共有7個 00~06

        const int MAXIUM_PASSANGER = MAXIUM_STATION * 5; //乘客總個數

        //station.h裡面也有相同的屬性要改
        const int MAX_GAME_MAP_SIDE_X = 770;			//實際上的遊戲邊界X軸只有到770
        const int MIN_GAME_MAP_SIDE_X = 30;			    //實際上的遊戲邊界X軸從30開始
        const int MAX_GAME_MAP_SIDE_Y = 560;			//實際上的遊戲邊界Y軸只有到560
        const int MIN_GAME_MAP_SIDE_Y = 60;			    //實際上的遊戲邊界Y軸從60開始


        int currentStationNum;							//目前出現到哪個車站
        int currentPassenagerNum;						//目前有幾個乘客出現
        int counter;
        int clickedX;
        int clickedY;
        int lstart;
        int lend;
        int mouse_state = 1;
        Line*    line;									//負責處理火車線路的指標

        Line    redLine;								//紅色線路
        Line    orangeLine;								//橘色線路
        Line    yellowLine;								//黃色線路
        Line    greenLine;								//綠色線路
        Line    blueLine;								//藍色線路
        Line    bblueLine;								//靛色線路
        Line    purpleLine;								//紫色線路

        Clock   clock;									//會動的時鐘
        Week    week;									//會動的周次

        vector<Station> stationList;					//一堆的車站
        vector<Passenger> passengerList;				//一堆的乘客
        vector<Cabin> cabinList;
        Cabin cabin;

        int stationRelation[10][10][7];					//軌道位置
        int mouse_x = 0, mouse_y = 0;					//滑鼠位置
        int mouse_X = 0, mouse_Y = 0;
};

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的結束狀態(Game Over)
// 每個Member function的Implementation都要弄懂
/////////////////////////////////////////////////////////////////////////////

class CGameStateOver : public CGameState
{
    public:
        CGameStateOver(CGame* g);
        void OnBeginState();							// 設定每次重玩所需的變數
        void OnInit();
    protected:
        void OnMove();									// 移動遊戲元素
        void OnShow();									// 顯示這個狀態的遊戲畫面
    private:
        int counter;	// 倒數之計數器
};

}