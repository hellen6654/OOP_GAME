/*
 * mygame.cpp: ���ɮ��x�C��������class��implementation
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
	�ݭ� �G
		���[
			����
			��u���Ԩ�s�������� �n�����pointX & pointY �M�w���[�n�^�����
			�ԥX�s���u�� ���[�|�ö] pointX & pointY �S�g�n
		����
			�Ϥ�����
		����
			ALL
	�ݥ[�G

		�ɭ�

*/
namespace game_framework
{
/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����C���}�Y�e������
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame* g)
    : CGameState(g)
{
}

void CGameStateInit::OnInit()
{
    //
    // ���ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
    //     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
    //
    ShowInitProgress(0);	// �@�}�l��loading�i�׬�0%
    //
    // �}�l���J���
    //
    // ���J����
    CAudio::Instance()->Load(AUDIO_SLIP, "sounds\\slip.mp3");
    CAudio::Instance()->Load(AUDIO_CLICK, "sounds\\click.mp3");
    CAudio::Instance()->Load(AUDIO_MUSIC, "sounds\\music.mp3");
    // ���J�Ϥ�
    logo.LoadBitmap(".\\RES\\title.bmp");
    start.LoadBitmap(".\\RES\\button\\start.bmp");
    startInvert.LoadBitmap(".\\RES\\button\\startInvert.bmp");
    end.LoadBitmap(".\\RES\\button\\end.bmp");
    endInvert.LoadBitmap(".\\RES\\button\\endInvert.bmp");
    //�]�w�Ѽ�
    CAudio::Instance()->Play(AUDIO_MUSIC);
    isMouseInStartBtn = false;
    isMouseInEndBtn = false;
    Sleep(300);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
    //
    // ��OnInit�ʧ@�|����CGameStaterRun::OnInit()�A�ҥH�i���٨S��100%
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
        GotoGameState(GAME_STATE_RUN);						// ������GAME_STATE_RUN
    else if (nChar == KEY_ESC)								// Demo �����C������k
        PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// �����C��
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
            GotoGameState(GAME_STATE_RUN);		// ������GAME_STATE_RUN
        }
        else if (isMouseInEndBtn)
        {
            PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// �����C��
        }
    }
}


void CGameStateInit::OnMouseMove(UINT nFlags, CPoint point)
{
    mouse_x = point.x;
    mouse_y = point.y;

    if ( start.IsBitmapLoaded() && end.IsBitmapLoaded())
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
    //�]�wLogo ��m �M���
    logo.SetTopLeft((SIZE_X / 2) - (logo.Width() / 2), SIZE_Y / 8 * 1);
    logo.ShowBitmap();
    //�}�l���s �������s����m
    start.SetTopLeft((SIZE_X / 2) - (start.Width() / 2), SIZE_Y / 8 * 4);
    end.SetTopLeft((SIZE_X / 2) - (end.Width() / 2), SIZE_Y / 8 * 6);
    //�Ϭ� �}�l���s �������s����m
    startInvert.SetTopLeft((SIZE_X / 2) - (start.Width() / 2), SIZE_Y / 8 * 4);
    endInvert.SetTopLeft((SIZE_X / 2) - (end.Width() / 2), SIZE_Y / 8 * 6);
    //��� �}�l���s �������s
    start.ShowBitmap();
    end.ShowBitmap();

    //
    // �ƹ�����W�� �����s�ܦ�
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
    // Demo�ù��r�����ϥΡA���L�}�o�ɽкɶq�קK�����ϥΦr���A���CMovingBitmap����n
    //
    /*
    CDC* pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC
    CFont f, *fp;
    f.CreatePointFont(160, "Times New Roman");	// ���� font f; 160����16 point���r
    fp = pDC->SelectObject(&f);					// ��� font f
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
    pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
    CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
    */
}

/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����������A(Game Over)
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
    // ���ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
    //     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
    //
    ShowInitProgress(66);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���66%
    //
    // �}�l���J���
    //
    Sleep(300);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
    //
    // �̲׶i�׬�100%
    //
    ShowInitProgress(100);
}

void CGameStateOver::OnShow()
{
    CDC* pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC
    CFont f, *fp;
    f.CreatePointFont(160, "Times New Roman");	// ���� font f; 160����16 point���r
    fp = pDC->SelectObject(&f);					// ��� font f
    pDC->SetBkColor(RGB(0, 0, 0));
    pDC->SetTextColor(RGB(255, 255, 0));
    char str[80];								// Demo �Ʀr��r�ꪺ�ഫ
    sprintf(str, "Game Over ! (%d)", counter / 30);
    pDC->TextOut(240, 210, str);
    pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
    CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
}

/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
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

void CGameStateRun::OnMove()							// ���ʹC������
{
    if (!isStop)
    {
        counter++;
        clock.OnMove();				//����clock�����ʵe
        vector<int> pointX;
        vector<int> pointY;
        vector<int> passedStation;

        //�C STATION_APPERAED_TIME ���N�X�@�Ө���
        if (counter % (30 * STATION_APPERAED_TIME) == 0 && currentStationNum < MAXIUM_STATION)
        {
            currentStationNum++;
            CAudio::Instance()->Play(AUDIO_APPEAR);
        }

        //�C PASSENAGER_APPERAED_TIME ���N�X�@�ӭ���
        if (counter % (30 * PASSENAGER_APPERAED_TIME) == 0 && currentPassenagerNum < MAXIUM_PASSANGER) currentPassenagerNum++;

        if (line->IsClickedTwoStation())
        {
            int R, G, B;
            line->SetPassedStation(line->GetClickedStartStationNum(), line->GetClickedEndStationNum());
            line->SetClickedStartStationNum(-1);
            line->SetClickedEndStationNum(-1);
            line->SetLinePointXY(stationList);

            line->GetLinePointXY(pointX, pointY);
            line->GetPassedStationNum(passedStation);
            line->GetLineColorRGB(R, G, B);

            Cabin c(pointX[0], pointY[0], R, G, B);
            c.SetLinePoint(pointX, pointY);
            c.SetPassedStation(passedStation);

            if (R == 255 && G == 0 && B == 0)
            {
                if (redCabinState == 0)
                {
                    redCabinList.push_back(c);
                    redCabinState = 1;
                }
				else
				{
					int sizeVec = redCabinList.size();
					for (int i = 0; i < sizeVec; i++)
					{
						redCabinList[i].SetLinePoint(pointX, pointY);
						redCabinList[i].SetPassedStation(passedStation);
					}
				}
            }
            else if (R == 255 && G == 144 && B == 0)
            {
                if (orangCabinState == 0)
                {
                    orangCabinList.push_back(c);
                    orangCabinState = 1;
                }
				else
				{
					int sizeVec = orangCabinList.size();
					for (int i = 0; i < sizeVec; i++)
					{
						orangCabinList[i].SetLinePoint(pointX, pointY);
						orangCabinList[i].SetPassedStation(passedStation);
					}
				}
            }
            else if (R == 255 && G == 255 && B == 0)
            {
                if (yellowCabinState == 0)
                {
                    yellowCabinList.push_back(c);
                    yellowCabinState = 1;
                }
				else
				{
					int sizeVec = yellowCabinList.size();
					for (int i = 0; i < sizeVec; i++)
					{
						yellowCabinList[i].SetLinePoint(pointX, pointY);
						yellowCabinList[i].SetPassedStation(passedStation);
					}
				}
            }
            else if (R == 0 && G == 255 && B == 0)
            {
                if (greenCabinState == 0)
                {
                    greenCabinList.push_back(c);
                    greenCabinState = 1;
                }
				else
				{
					int sizeVec = greenCabinList.size();
					for (int i = 0; i < sizeVec; i++)
					{
						greenCabinList[i].SetLinePoint(pointX, pointY);
						greenCabinList[i].SetPassedStation(passedStation);
					}
				}
            }
            else if (R == 0 && G == 138 && B == 255)
            {
                if (blueCabinState == 0)
                {
                    blueCabinList.push_back(c);
                    blueCabinState = 1;
                }
				else
				{
					int sizeVec = blueCabinList.size();
					for (int i = 0; i < sizeVec; i++)
					{
						blueCabinList[i].SetLinePoint(pointX, pointY);
						blueCabinList[i].SetPassedStation(passedStation);
					}
				}
            }
            else if (R == 0 && G == 6 && B == 255)
            {
                if (bblueCabinState == 0)
                {
                    bblueCabinList.push_back(c);
                    bblueCabinState = 1;
                }
				else
				{
					int sizeVec = bblueCabinList.size();
					for (int i = 0; i < sizeVec; i++)
					{
						bblueCabinList[i].SetLinePoint(pointX, pointY);
						bblueCabinList[i].SetPassedStation(passedStation);
					}
				}
            }
            else if (R == 144 && G == 0 && B == 255)
            {
                if (pupleCabinState == 0)
                {
                    pupleCabinList.push_back(c);
                    pupleCabinState = 1;
                }
				else
				{
					int sizeVec = pupleCabinList.size();
					for (int i = 0; i < sizeVec; i++)
					{
						pupleCabinList[i].SetLinePoint(pointX, pointY);
						pupleCabinList[i].SetPassedStation(passedStation);
					}
				}
            }
        }

        if (!redCabinList.empty())
        {
            int vecSize = redCabinList.size();
			redCabinList[0].GetNextPreStation(preP, nextP);
            for (int i = 0; i < vecSize; i++)
            {
                redCabinList[i].OnMove(stationList);
            }
        }

        if (!orangCabinList.empty())
        {
            int vecSize = orangCabinList.size();

            for (int i = 0; i < vecSize; i++)
            {
                orangCabinList[i].OnMove(stationList);
            }
        }

        if (!yellowCabinList.empty())
        {
            int vecSize = yellowCabinList.size();

            for (int i = 0; i < vecSize; i++)
            {
                yellowCabinList[i].OnMove(stationList);
            }
        }

        if (!greenCabinList.empty())
        {
            int vecSize = greenCabinList.size();

            for (int i = 0; i < vecSize; i++)
            {
                greenCabinList[i].OnMove(stationList);
            }
        }

        if (!blueCabinList.empty())
        {
            int vecSize = blueCabinList.size();

            for (int i = 0; i < vecSize; i++)
            {
                blueCabinList[i].OnMove(stationList);
            }
        }

        if (!bblueCabinList.empty())
        {
            int vecSize = bblueCabinList.size();

            for (int i = 0; i < vecSize; i++)
            {
                bblueCabinList[i].OnMove(stationList);
            }
        }

        if (!pupleCabinList.empty())
        {
            int vecSize = pupleCabinList.size();

            for (int i = 0; i < vecSize; i++)
            {
                pupleCabinList[i].OnMove(stationList);
            }
        }
    }
}

void CGameStateRun::OnInit()  								// �C������Ȥιϧγ]�w
{
    //
    // ���ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
    //     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
    //
    ShowInitProgress(33);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���33%
    //
    // �}�l���J���
    //
    Station* s = new Station;										//�Ψӫإ��H�������C�� �� �ˬd���� �C�� �O�_���|
    Passenger* p = new Passenger;									//�Ψӫإ��H�����ȭӼ� �� �H���C��
    line = &redLine;
    clock.LoadBitmap();
    week.LoadBitmap();
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
    s->RandomBuildStation(stationList);					//�إ��H�������C��
    s->CheckedOverLappingStation(stationList);			//�ˬd�����C���O�_�����|������
    p->RandomMadePassenger(passengerList, stationList, MAXIUM_STATION, MAXIUM_STATION_TYPE, MAXIUM_PASSANGER);
    //�إ߭��ȦC��

    for (int i = 0; i < MAXIUM_STATION; i++)			//���J�U�����Ϥ�
        stationList[i].LoadBitmap();

    for (int i = 0; i < MAXIUM_PASSANGER; i++)			//���J���ȹϤ�
        passengerList[i].LoadBitmap();

    currentStationNum = 3;								//�{���������T�� �C���}�l ���T�Ө���
    currentPassenagerNum = 0 ;							//�@�}�l�X�{�����ȼƬ�0
    clickedX = clickedY = -1;
    ShowInitProgress(50);
    CAudio::Instance()->Load(AUDIO_SELECT1, "sounds\\select1.mp3");
    CAudio::Instance()->Load(AUDIO_SELECT2, "sounds\\select2.mp3");
    CAudio::Instance()->Load(AUDIO_APPEAR, "sounds\\appear.mp3");
    delete s;
    delete p;
    //Sleep(300); // ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
    //
    // �~����J��L���
    //
    //CAudio::Instance()->Load(AUDIO_DING,  "sounds\\ding.wav");	// ���J�s��0���n��ding.wav
    //CAudio::Instance()->Load(AUDIO_LAKE,  "sounds\\lake.mp3");	// ���J�s��1���n��lake.mp3
    //CAudio::Instance()->Load(AUDIO_NTUT,  "sounds\\ntut.mid");	// ���J�s��2���n��ntut.mid
    //
    // ��OnInit�ʧ@�|����CGameStaterOver::OnInit()�A�ҥH�i���٨S��100%
    //
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    const char KEY_LEFT  = 0x25; // keyboard���b�Y
    const char KEY_UP    = 0x26; // keyboard�W�b�Y
    const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
    const char KEY_DOWN  = 0x28; // keyboard�U�b�Y
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    const char KEY_LEFT  = 0x25; // keyboard���b�Y
    const char KEY_UP    = 0x26; // keyboard�W�b�Y
    const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
    const char KEY_DOWN  = 0x28; // keyboard�U�b�Y
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)
{
    // �o��t�d�B�z���U�ƹ����䪺�ʧ@
    int start = line->GetClickedStartStationNum();	//�����_�l����
    int end   = line->GetClickedEndStationNum();	//�������I����

    if (!isStop)
    {
        if (start == -1) //�S�����󨮯��Q���
        {
            if (line->IsClickedStation(point.x, point.y, stationList, currentStationNum) ) //�ˬd�O�_���I�쨮��
            {
                CAudio::Instance()->Play(AUDIO_SELECT1);
                start = line->GetMouseClickedStationNum(point.x, point.y, stationList, currentStationNum);
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
        else //�p�G�_�I�����w�g�Q���
        {
            if (line->IsClickedStation(point.x, point.y, stationList, currentStationNum)) //�ˬd�O�_���I�쨮��
            {
                CAudio::Instance()->Play(AUDIO_SELECT2);
                end = line->GetMouseClickedStationNum(point.x, point.y, stationList, currentStationNum);
                line->SetClickedEndStationNum(end);
            }
            else
            {
                line->SetClickedStartStationNum(-1);
                line->SetClickedEndStationNum(-1);
            }
        }
    }

    if (point.x >= 750 && point.y >= 10 && point.x <= 790 && point.y <= 50 )
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

    clickedX = point.x;	//�Ψ�debug
    clickedY = point.y; //�Ψ�debug
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����䪺�ʧ@ ��}
{
    //���K�y���C��
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

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// �B�z�ƹ����䪺�ʧ@ ����
{
    // �S�ơC�p�G�ݭn�B�z�ƹ����ʪ��ܡA�gcode�b�o��
    if (point.x > MIN_GAME_MAP_SIDE_X && point.x < MAX_GAME_MAP_SIDE_X) mouse_x = point.x;

    if (point.y > MIN_GAME_MAP_SIDE_Y && point.y < MAX_GAME_MAP_SIDE_Y) mouse_y = point.y;
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnShow()
{
    //
    //  �`�N�GShow�̭��d�U���n���ʥ��󪫥󪺮y�СA���ʮy�Ъ��u�@����Move���~��A
    //        �_�h���������sø�Ϯ�(OnDraw)�A����N�|���ʡA�ݰ_�ӷ|�ܩǡC���ӳN�y
    //        ���AMove�t�dMVC����Model�AShow�t�dView�A��View�������Model�C
    //
    map.SetTopLeft(0, 0);	//�]�m�a�Ϧ�m
    map.ShowBitmap();		//��a����ܥX��
    clock.OnShow();			//��ܮ���
    //===============��ܦU�C�⪺���u===================
    purpleLine.ShowLineIconBitmap();	//����
    bblueLine.ShowLineIconBitmap();		//�Q��
    blueLine.ShowLineIconBitmap();		//�Ŧ�
    greenLine.ShowLineIconBitmap();		//���
    yellowLine.ShowLineIconBitmap();	//����
    orangeLine.ShowLineIconBitmap();	//���
    redLine.ShowLineIconBitmap();		//����
    //===============================================

    // �p�G���@�Ө����Q��� �N�n�e�X�� //���y�ܻ� �N�O�u���n��۷ƹ���
    if (line->GetClickedStartStationNum() != -1 && 
		(line->IsPassedStationEmpty() ||  line->GetClickedLastStation() == line->GetClickedStartStationNum()))
        line->DrawRailway(stationList[line->GetClickedStartStationNum()].GetX() + 5, stationList[line->GetClickedStartStationNum()].GetY() + 5, mouse_x, mouse_y);

    //��ܦU�C��u��
    purpleLine.ShowRailway(stationList, currentStationNum);
    bblueLine.ShowRailway(stationList, currentStationNum);
    blueLine.ShowRailway(stationList, currentStationNum);
    greenLine.ShowRailway(stationList, currentStationNum);
    yellowLine.ShowRailway(stationList, currentStationNum);
    orangeLine.ShowRailway(stationList, currentStationNum);
    redLine.ShowRailway(stationList, currentStationNum);

    //if (!cabinList.empty()) cabinList[0].OnShow();

    if (!redCabinList.empty())
    {
        int vecSize = redCabinList.size();

        for (int i = 0; i < vecSize; i++)
        {
            redCabinList[i].OnShow();
        }
    }

    if (!orangCabinList.empty())
    {
        int vecSize = orangCabinList.size();

        for (int i = 0; i < vecSize; i++)
        {
            orangCabinList[i].OnShow();
        }
    }

    if (!yellowCabinList.empty())
    {
        int vecSize = yellowCabinList.size();

        for (int i = 0; i < vecSize; i++)
        {
            yellowCabinList[i].OnShow();
        }
    }

    if (!greenCabinList.empty())
    {
        int vecSize = greenCabinList.size();

        for (int i = 0; i < vecSize; i++)
        {
            greenCabinList[i].OnShow();
        }
    }

    if (!blueCabinList.empty())
    {
        int vecSize = blueCabinList.size();

        for (int i = 0; i < vecSize; i++)
        {
            blueCabinList[i].OnShow();
        }
    }

    if (!bblueCabinList.empty())
    {
        int vecSize = bblueCabinList.size();

        for (int i = 0; i < vecSize; i++)
        {
            bblueCabinList[i].OnShow();
        }
    }

    if (!pupleCabinList.empty())
    {
        int vecSize = pupleCabinList.size();

        for (int i = 0; i < vecSize; i++)
        {
            pupleCabinList[i].OnShow();
        }
    }
	int a = stationList.size();
	int b = passengerList.size();
    // ��ܨ����M����
    for (int i = 0; i < currentStationNum; i++)
    {
        int n = stationList[i].GetPassenagerNum();
        stationList[i].OnShow();

        for (int j = 0; j < currentPassenagerNum; j++)
            if (passengerList[j].GetStartStation() <= i)
                passengerList[j].OnShow();
    }

    //week.OnShow();
    // �H�UDebug ��
    CDC* pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC
    CFont f, *fp;
    f.CreatePointFont(160, "Times New Roman");	// ���� font f; 160����16 point���r
    fp = pDC->SelectObject(&f);					// ��� font f
    //pDC->SetBkColor(RGB(0, 0, 0));
    pDC->SetBkColor(RGB(241, 241, 241));
    pDC->SetTextColor(RGB(0, 0, 0));
    char str[80];								// Demo �Ʀr��r�ꪺ�ഫ
    sprintf(str, "(%d,%d),(%d,%d),(%d,%d),(%d,%d)",  clickedX, clickedY,mouse_x, mouse_y ,line->GetClickedStartStationNum(),line->GetClickedEndStationNum(),preP,nextP);
    pDC->TextOut(10, 10, str);
    pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
    CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
}
}