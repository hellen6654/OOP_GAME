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
		start.LoadBitmap(".\\RES\\button\\start.bmp");
		startInvert.LoadBitmap(".\\RES\\button\\startInvert.bmp");
		end.LoadBitmap(".\\RES\\button\\end.bmp");
		endInvert.LoadBitmap(".\\RES\\button\\endInvert.bmp");
		//設定參數
		CAudio::Instance()->Play(AUDIO_MUSIC);
		isMouseInStartBtn = false;
		isMouseInEndBtn = false;
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
		}
	}

	void CGameStateInit::OnMouseMove(UINT nFlags, CPoint point)
	{
		mouse_x = point.x;
		mouse_y = point.y;

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
			else
			{
				mouse_state = 1;
				isMouseInStartBtn = false;
				isMouseInEndBtn = false;
			}
		}
	}

	void CGameStateInit::OnShow()
	{
		//設定Logo 位置 和顯示
		logo.SetTopLeft((SIZE_X / 2) - (logo.Width() / 2), SIZE_Y / 8 * 1);
		logo.ShowBitmap();
		//開始按鈕 結束按鈕的位置
		start.SetTopLeft((SIZE_X / 2) - (start.Width() / 2), SIZE_Y / 8 * 4);
		end.SetTopLeft((SIZE_X / 2) - (end.Width() / 2), SIZE_Y / 8 * 6);
		//反相 開始按鈕 結束按鈕的位置
		startInvert.SetTopLeft((SIZE_X / 2) - (start.Width() / 2), SIZE_Y / 8 * 4);
		endInvert.SetTopLeft((SIZE_X / 2) - (end.Width() / 2), SIZE_Y / 8 * 6);
		//顯示 開始按鈕 結束按鈕
		start.ShowBitmap();
		end.ShowBitmap();

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
		for (unsigned i = 0; i < passengerList.size(); i++)
		{
			if (passengerList[i] != nullptr)
			{
				delete passengerList[i];
				passengerList.erase(passengerList.begin()+i);
			}
		}
	}

	void CGameStateRun::OnBeginState()
	{
		counter = 0;
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

			if (line->IsClickedTwoStation())
			{
				int R, G, B;
				int countPassedStation[6] = { 0 };
				Cabin* c = new Cabin;
				line->SetPassedStation(line->GetClickedStartStationNum(), line->GetClickedEndStationNum());
				line->SetLinePointXY(stationList);
				
				
				line->SetClickedStartStationNum(-1);
				line->SetClickedEndStationNum(-1);
				line->GetLinePointXY(pointX, pointY);
				line->GetPassedStationNum(passedStation);
				line->GetLineColorRGB(R, G, B);
				line->CountTotalPassedStation();
				line->GetTotalPassedStation(countPassedStation);
				if (!c->IsCabinColorRepeat(cabinList, R, G, B))
				{
					Cabin buf(pointX[0], pointY[0], R, G, B);
					buf.SetLinePoint(pointX, pointY);
					buf.SetPassedStation(passedStation);
					buf.SetLineStationNum(countPassedStation);
					cabinList.push_back(buf);
				}
				else
				{
					int pos = c->GetCabinPointer(cabinList, R, G, B);
					cabinList[pos].SetLinePoint(pointX, pointY);
					cabinList[pos].SetPassedStation(passedStation);
					cabinList[pos].SetLineStationNum(countPassedStation);
				}
				delete c;
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
						int cabinPassedStation[6] = {0}; //車廂會經過的站
						cabinList[i].GetLineStationNum(cabinPassedStation);
						int nowCabinInStationNum = cabinList[i].GetNextStation(); //目前車廂在哪個車站

						//先下車後上車
						//========下車========
						if (cabinList[i].GetPassengerNum()>0&& cabinList[i].GetCounter()==20)
						{
							cabinList[i].PassengerGetOut(nowCabinInStationNum);
						}
						//========上車========
						if (cabinList[i].GetCounter() == 40)
						{
							for (unsigned j = passengerList.size() - 1; j >= 0; j--) //每個乘客
							{
								if (j > passengerList.size())
								{
									break;
								}
								else if (cabinList[i].GetPassengerNum() < MAX_PASSENGER_NUM) //車廂乘客小於六個
								{
									if (cabinPassedStation[passengerList[j]->GetFinalStation()] == 1 && passengerList[j]->GetStartStation() == nowCabinInStationNum) //確定乘客要去的站有在這條線路上
									{
										stationList[nowCabinInStationNum].ErasePassenger(passengerList[j]);
										cabinList[i].PassengerGetOn(passengerList[j], nowCabinInStationNum);
										passengerList.erase(passengerList.begin()+j);
									}
								}
							}
						}
						if (cabinList[i].GetCounter() == 60)
						{
							cabinList[i].SetCounter(0);
							cabinList[i].SetIsStop(false);
						}
					}
				}
				if (1)
				{

				}
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
		Passenger* p = new Passenger;									//用來建立隨機乘客個數 及 隨機列表
		line = &redLine;
		clock.LoadBitmap();
		map.LoadBitmap(".\\RES\\map.bmp");
		isStop = false;
		CAudio::Instance()->Load(AUDIO_STOP1, "sounds\\stop1.mp3");
		CAudio::Instance()->Load(AUDIO_STOP2, "sounds\\stop2.mp3");
		/*red(255.0.0),orang(255.144.0),yellow(255.255.0),green(0.255.0),blue(0.138.255),bblue(0.6.255),puple(144.0.255)*/
		redLine.SetLineColor(255, 0, 0);
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

		//建立隨機車站列表
		s->RandomBuildStation(stationList);

		//檢查車站列表是否有重疊的車站
		s->CheckedOverLappingStation(stationList);

		//建立乘客列表
		p->RandomMadePassenger(passengerList, stationList, MAXIUM_STATION, MAXIUM_STATION_TYPE, MAXIUM_PASSANGER);

		

		//載入各車站圖片
		for (int i = 0; i < MAXIUM_STATION; i++)
			stationList[i].LoadBitmap();

		currentStationNum = 3;								//現有車站為三個 遊戲開始 有三個車站
		currentPassenagerNum = 0;							//一開始出現的乘客數為0
		clickedX = clickedY = -1;
		ShowInitProgress(50);
		CAudio::Instance()->Load(AUDIO_SELECT1, "sounds\\select1.mp3");
		CAudio::Instance()->Load(AUDIO_SELECT2, "sounds\\select2.mp3");
		CAudio::Instance()->Load(AUDIO_APPEAR, "sounds\\appear.mp3");
		delete s;
		delete p;
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

		clickedX = point.x;	//用來debug
		clickedY = point.y; //用來debug
	}

	void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠左鍵的動作 放開
	{
		//換鐵軌的顏色
		if (redLine.IsMouseClickedLineColorBMP(point.x, point.y))
			line = &redLine;
		else if (orangeLine.IsMouseClickedLineColorBMP(point.x, point.y))
			line = &orangeLine;
		else if (yellowLine.IsMouseClickedLineColorBMP(point.x, point.y))
			line = &yellowLine;
		else if (greenLine.IsMouseClickedLineColorBMP(point.x, point.y))
			line = &greenLine;
		else if (blueLine.IsMouseClickedLineColorBMP(point.x, point.y))
			line = &blueLine;
		else if (bblueLine.IsMouseClickedLineColorBMP(point.x, point.y))
			line = &bblueLine;
		else if (purpleLine.IsMouseClickedLineColorBMP(point.x, point.y))
			line = &purpleLine;
	}

	void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠左鍵的動作 移動
	{
		// 沒事。如果需要處理滑鼠移動的話，寫code在這裡
		if (point.x > MIN_GAME_MAP_SIDE_X && point.x < MAX_GAME_MAP_SIDE_X) mouse_x = point.x;

		if (point.y > MIN_GAME_MAP_SIDE_Y && point.y < MAX_GAME_MAP_SIDE_Y) mouse_y = point.y;
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
		map.ShowBitmap();		//把地圖顯示出來
		clock.OnShow();			//顯示時鐘
		//===============顯示各顏色的路線===================
		purpleLine.ShowLineIconBitmap();	//紫色
		bblueLine.ShowLineIconBitmap();		//靛色
		blueLine.ShowLineIconBitmap();		//藍色
		greenLine.ShowLineIconBitmap();		//綠色
		yellowLine.ShowLineIconBitmap();	//黃色
		orangeLine.ShowLineIconBitmap();	//橘色
		redLine.ShowLineIconBitmap();		//紅色
		//===============================================

		// 如果有一個車站被選取 就要畫出來 //換句話說 就是線路要跟著滑鼠動
		if (line->GetClickedStartStationNum() != -1 &&
			(line->IsPassedStationEmpty() || line->GetClickedLastStation() == line->GetClickedStartStationNum()))
			line->DrawRailway(stationList[line->GetClickedStartStationNum()].GetX() + 5, stationList[line->GetClickedStartStationNum()].GetY() + 5, mouse_x, mouse_y);

		//顯示各顏色線路
		purpleLine.ShowRailway(stationList);
		bblueLine.ShowRailway(stationList);
		blueLine.ShowRailway(stationList);
		greenLine.ShowRailway(stationList);
		yellowLine.ShowRailway(stationList);
		orangeLine.ShowRailway(stationList);
		redLine.ShowRailway(stationList);
		for (int i = 0; i < MAXIUM_STATION; i++)
			stationList[i].OnShowStation();
		if (!cabinList.empty()) nextS=cabinList[0].GetNextStation();

		if (!cabinList.empty())
			for (unsigned i = 0; i < cabinList.size(); i++)
				cabinList[i].OnShow();
		for (int i = 0; i < MAXIUM_STATION; i++)
			stationList[i].OnShowPassengerInStation();

		// 顯示車站和乘客
		

		/*for (unsigned i = 0; i < passengerList.size(); i++)
			passengerList[i]->OnShow();*/

		// 以下Debug 用
		CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC
		CFont f, *fp;
		f.CreatePointFont(160, "Times New Roman");	// 產生 font f; 160表示16 point的字
		fp = pDC->SelectObject(&f);					// 選用 font f
		pDC->SetBkColor(RGB(241, 241, 241));
		pDC->SetTextColor(RGB(0, 0, 0));
		char str[80];								// Demo 數字對字串的轉換
		sprintf(str, "(%d,%d),(%d,%d),(%d,%d),(%d,%d)(%d)", clickedX, clickedY, mouse_x, mouse_y, line->GetClickedStartStationNum(), line->GetClickedEndStationNum(), preP, nextP,nextS);
		pDC->TextOut(10, 10, str);
		pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	}
}