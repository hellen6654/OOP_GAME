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
    // ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
    //     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
    //
    ShowInitProgress(0);	// �@�}�l��loading�i�׬�0%
    //
    // �}�l���J���
    //
    logo.LoadBitmap(".\\RES\\title.bmp");
    start.LoadBitmap(".\\RES\\button\\start.bmp");
    end.LoadBitmap(".\\RES\\button\\end.bmp");
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
    // GotoGameState(GAME_STATE_RUN);		// ������GAME_STATE_RUN
}

void CGameStateInit::OnLButtonUp(UINT nFlags, CPoint point)
{
    if (mouse_x >= start.Left() && mouse_x <= start.Left() + start.Width() && mouse_y >= start.Top() && mouse_y <= start.Top() + start.Height())
    {
        GotoGameState(GAME_STATE_RUN);		// ������GAME_STATE_RUN
    }
    else if (mouse_x >= end.Left() && mouse_x <= end.Left() + end.Width() && mouse_y >= end.Top() && mouse_y <= end.Top() + end.Height())
    {
        PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// �����C��
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
    // �K�Wlogo
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
    else if (mouse_x > end.Left() && mouse_x < 491 && mouse_y > end.Top() && mouse_y < 402)
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
    // Demo�ù��r�����ϥΡA���L�}�o�ɽкɶq�קK�����ϥΦr���A���CMovingBitmap����n
    //
    CDC* pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC
    CFont f, *fp;
    f.CreatePointFont(160, "Times New Roman");	// ���� font f; 160���16 point���r
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
    // ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
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
    f.CreatePointFont(160, "Times New Roman");	// ���� font f; 160���16 point���r
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
    counter++;
    clock.OnMove();				//����clock�����ʵe

    if (clock.IsFinalBitmap())	//����week�P���ʵe
        week.OnMove();

    if (counter % (30 * 5) == 0 && currentStationNum < MAXIUM_STATION) //�C����X�@�Ө���
        currentStationNum++;

    if (line.IsClickedTwoStation())
    {
        stationRelation[line.GetclickedTwoNumA()][line.GetclickedTwoNumB()] = 1;
        line.SetclickedTwoNumA(-1);
        line.SetclickedTwoNumB(-1);
    }
}

void CGameStateRun::OnInit()  								// �C������Ȥιϧγ]�w
{
    //
    // ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
    //     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
    //
    ShowInitProgress(33);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���33%
    //
    // �}�l���J���
    clock.LoadBitmap();
    week.LoadBitmap();
    map.LoadBitmap(".\\RES\\map.bmp");
	line.LoadBitmap();

	//red(255.0.0),orang(255.144.0),yellow(255.255.0),green(0.255.0),blue(0.138.255),bblue(0.6.255),puple(144.0.255)
	redLine.SetLineColor(255, 0, 0);
	orangeLine.SetLineColor(255, 144, 0);
	yellowLine.SetLineColor(255, 255, 0);
	greenLine.SetLineColor(0, 255, 0);
	blueLine.SetLineColor(0, 138, 255);
	bblueLine.SetLineColor(0, 6, 255);
	purpleLine.SetLineColor(144, 0, 255);

	redLine.LoadBitmap();
	orangeLine.LoadBitmap();
	yellowLine.LoadBitmap();								
	greenLine.LoadBitmap();								
	blueLine.LoadBitmap();								
	bblueLine.LoadBitmap();								
	purpleLine.LoadBitmap();
	
	


	s.RandomBuildStation(stationList);					//�إ��H�������C��
	s.CheckedOverLappingStation(stationList);			//�ˬd�����C��ܬO�_�����|������
	
	for (int i = 0; i < MAXIUM_STATION; i++)			//���J�Ϥ�
		stationList[i].LoadBitmap();
	for (int i = 0; i < MAXIUM_STATION; i++)
		for (int j = 0; j < MAXIUM_STATION; j++)
			stationRelation[i][j] = 0;

	currentStationNum = 3;								//�{���������T�� �C���}�l ���T�Ө���

    clickedX = clickedY = -1;

    for (int i = 0; i < MAXIUM_STATION; i++)
        for (int j = 0; j < MAXIUM_STATION; j++)
            stationRelation[i][j] = 0;

    ShowInitProgress(50);
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

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����䪺�ʧ@ ���U
{
    //eraser.SetMovingLeft(true);
    if (line.GetclickedTwoNumA() != -1)
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

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����䪺�ʧ@ ��}
{
    //eraser.SetMovingLeft(false);
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// �B�z�ƹ����䪺�ʧ@ ����
{
    // �S�ơC�p�G�ݭn�B�z�ƹ����ʪ��ܡA�gcode�b�o��
    mouse_x = point.x;
    mouse_y = point.y;
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
    //        �_�h��������sø�Ϯ�(OnDraw)�A����N�|���ʡA�ݰ_�ӷ|�ܩǡC���ӳN�y
    //        ���AMove�t�dMVC����Model�AShow�t�dView�A��View�������Model�C
    //
    //
    //  �K�W�I���ϡB�����ơB�y�B���l�B�u�����y
    //
    //timer.CountPassTime();
    map.SetTopLeft(0, 0);
    map.ShowBitmap();
	line.ShowBitmap();

	redLine.ShowBitmap();
	orangeLine.ShowBitmap();
	yellowLine.ShowBitmap();
	greenLine.ShowBitmap();
	blueLine.ShowBitmap();
	bblueLine.ShowBitmap();
	purpleLine.ShowBitmap();

    if (line.GetclickedTwoNumA() != -1 ) // �Ĥ@�Ө����Q����F �N�n�e�X��
    {
        line.DrawRailway(stationList[line.GetclickedTwoNumA()].GetX() + 5, stationList[line.GetclickedTwoNumA()].GetY() + 5,mouse_x, mouse_y);
    }

    for (int i = 0; i < currentStationNum ; i++)
    {
        for (int j = 0; j < currentStationNum; j++)
        {
            if (stationRelation[i][j] == 1)
            {
                line.DrawRailway(stationList[i].GetX() + 5, stationList[i].GetY() + 5,stationList[j].GetX() + 5, stationList[j].GetY() + 5);
            }
        }
    }


    for (int i = 0; i < currentStationNum; i++)
        stationList[i].OnShow();

    week.OnShow();
    clock.OnShow();
    CDC* pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC
    CFont f, *fp;
    f.CreatePointFont(160, "Times New Roman");	// ���� font f; 160���16 point���r
    fp = pDC->SelectObject(&f);					// ��� font f
    //pDC->SetBkColor(RGB(0, 0, 0));
    pDC->SetBkColor(RGB(241, 241, 241));
    pDC->SetTextColor(RGB(0, 0, 0));
    char str[80];								// Demo �Ʀr��r�ꪺ�ഫ
    sprintf(str, "(%d,%d),(%d,%d),(%d,%d)",  clickedX, clickedY,mouse_x, mouse_y , line.GetclickedTwoNumA(), line.GetclickedTwoNumB());
    pDC->TextOut(10, 10, str);
    pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
    CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
}
}