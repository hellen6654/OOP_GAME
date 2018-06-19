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

		����

	�ݥ[�G


*/
namespace game_framework
{
int personss = 0;
bool isNight = false;
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
    // ���J����
    CAudio::Instance()->Load(AUDIO_SLIP, "sounds\\slip.mp3");
    CAudio::Instance()->Load(AUDIO_CLICK, "sounds\\click.mp3");
    CAudio::Instance()->Load(AUDIO_MUSIC, "sounds\\music.mp3");
    // ���J�Ϥ�
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
    //�]�w�Ѽ�
    CAudio::Instance()->Play(AUDIO_MUSIC);
    isMouseInStartBtn = false;
    isMouseInNightBtn = false;
    isMouseInInstructionsBtn = false;
    isMouseInEndBtn = false;
    isInInstructions = false;
    Sleep(300);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
    //
    // ��OnInit�ʧ@�|����CGameStaterRun::OnInit()�A�ҥH�i���٨S��100%
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
    const char KEY_RIGHT = 0x27; // keyboard�k�b�Y

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
        GotoGameState(GAME_STATE_RUN);						// ������GAME_STATE_RUN
    else if (nChar == KEY_ESC)								// Demo �����C������k
        PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// �����C��*/
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
                GotoGameState(GAME_STATE_RUN);		// ������GAME_STATE_RUN
            }
            else if (isMouseInEndBtn)
            {
                PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// �����C��
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
    //�]�wLogo ��m �M���
    logo.SetTopLeft((SIZE_X / 2) - (logo.Width() / 2), SIZE_Y / 8 * 1);
    logoNight.SetTopLeft((SIZE_X / 2) - (logo.Width() / 2), SIZE_Y / 8 * 1);
    //�}�l���s �������s����m
    start.SetTopLeft((SIZE_X / 2) - (start.Width() / 2), SIZE_Y / 8 * 3);
    night.SetTopLeft((SIZE_X / 2) - (start.Width() / 2), SIZE_Y / 8 * 4);
    morning.SetTopLeft((SIZE_X / 2) - (start.Width() / 2), SIZE_Y / 8 * 4);
    instructions.SetTopLeft((SIZE_X / 2) - (end.Width() / 2), SIZE_Y / 8 * 5);
    end.SetTopLeft((SIZE_X / 2) - (end.Width() / 2), SIZE_Y / 8 * 6);
    //�Ϭ� �}�l���s �������s����m
    startInvert.SetTopLeft((SIZE_X / 2) - (start.Width() / 2), SIZE_Y / 8 * 3);
    nightInvert.SetTopLeft((SIZE_X / 2) - (start.Width() / 2), SIZE_Y / 8 * 4);
    morningInvert.SetTopLeft((SIZE_X / 2) - (start.Width() / 2), SIZE_Y / 8 * 4);
    instructionsInvert.SetTopLeft((SIZE_X / 2) - (end.Width() / 2), SIZE_Y / 8 * 5);
    endInvert.SetTopLeft((SIZE_X / 2) - (end.Width() / 2), SIZE_Y / 8 * 6);
    //��� �}�l���s �������s

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
    //�]�w�K�y��m �M���
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
    // Demo�ù��r�����ϥΡA���L�}�o�ɽкɶq�קK�����ϥΦr���A���CMovingBitmap����n
    //
    /*
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
    // ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
    //     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
    //
    ShowInitProgress(66);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���66%
    //
    // �}�l���J���
    //
    Sleep(300);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
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
    // �̲׶i�׬�100%
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

    /*CDC* pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC
    CFont f, *fp;
    f.CreatePointFont(160, "Times New Roman");	// ���� font f; 160���16 point���r
    fp = pDC->SelectObject(&f);					// ��� font f
    pDC->SetBkColor(RGB(0, 0, 0));
    pDC->SetTextColor(RGB(255, 255, 0));
    char str[80];								// Demo �Ʀr��r�ꪺ�ഫ
    sprintf(str, "Game Over ! (%d)", counter / 30);
    pDC->TextOut(240, 210, str);
    pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
    CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC*/
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
    passengerTotalNumber.SetInteger(HITS_LEFT);					// ���w�ѤU��������
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
    Station* s = new Station;										//�Ψӫإ��H�������C�� �� �ˬd���� �C�� �O�_���|
    Passenger* p = new Passenger;									//�Ψӫإ��H�����ȭӼ� �� �H���C��
    line = &redLine;
    counter = 0;
    //�إ��H�������C��
    s->RandomBuildStation(stationList);
    //�ˬd�����C��O�_�����|������
    s->CheckedOverLappingStation(stationList);
    s->SetIsNight(isNight);
    //�إ߭��ȦC��
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
    currentStationNum = 3;								//�{���������T�� �C���}�l ���T�Ө���
    currentPassenagerNum = 0;							//�@�}�l�X�{�����ȼƬ�0
    clickedX = clickedY = -1;
    delete s;
    delete p;
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

        /*�C STATION_APPERAED_TIME ��N�X�@�Ө���
        if (counter % (30 * STATION_APPERAED_TIME) == 0 && currentStationNum < MAXIUM_STATION)
        {
        	currentStationNum++;
        	//CAudio::Instance()->Play(AUDIO_APPEAR);
        }
        */
        //�C PASSENAGER_APPERAED_TIME ��N�X�@�ӭ���
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
            for (unsigned i = 0; i < cabinList.size(); i++) //�C�Ө��[
            {
                cabinList[i].OnMove(stationList);

                if (cabinList[i].IsStop()) //�����i���o
                {
                    //���ȤW�U��
                    cabinList[i].SetAddCounter(1);
                    int nowCabinInStationNum = cabinList[i].GetNextStation(); //�ثe���[�b���Ө���

                    //���U����W��
                    //========�U��========
                    if ((int)passengerListOnCabin[i].size() > 0 && cabinList[i].GetCounter() == 10)
                    {
                        cabinList[i].PassengerGetOut(passengerListOnCabin[i], nowCabinInStationNum);
                        //cabinList[i].PassengerGetOut(nowCabinInStationNum);
                        totalper += cabinList[i].GetOutPeople();
                        passengerTotalNumber.Add(cabinList[i].GetOutPeople());
                    }

                    //========�W��========
                    if (cabinList[i].GetCounter() == 20)
                    {
                        for (unsigned j = passengerList.size() - 1; j >= 0; j--) //�C�ӭ���
                        {
                            if (j > passengerList.size())
                            {
                                break;
                            }
                            else if ((int)passengerListOnCabin[i].size() < MAX_PASSENGER_NUM) //���[���Ȥp�󤻭�
                            {
                                int cabinPassedStation[6] = { 0 }; //���[�|�g�L����
                                cabinList[i].GetLineStationNum(cabinPassedStation);

                                if (cabinPassedStation[passengerList[j]->GetFinalStation()] == 1 && passengerList[j]->GetStartStation() == nowCabinInStationNum)
                                    //�T�w���ȭn�h�������b�o���u���W
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

void CGameStateRun::OnInit()  								// �C������Ȥιϧγ]�w
{
    //
    // ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
    //     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
    //
    ShowInitProgress(33);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���33%
    //
    // �}�l���J���
    //
    Station* s = new Station;										//�Ψӫإ��H�������C�� �� �ˬd���� �C�� �O�_���|
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

    //�إ��H�������C��
    s->RandomBuildStation(stationList);
    //�ˬd�����C��O�_�����|������
    s->CheckedOverLappingStation(stationList);
    //���J�U�����Ϥ�
    ShowInitProgress(50);
    CAudio::Instance()->Load(AUDIO_SELECT1, "sounds\\select1.mp3");
    CAudio::Instance()->Load(AUDIO_SELECT2, "sounds\\select2.mp3");
    CAudio::Instance()->Load(AUDIO_APPEAR, "sounds\\appear.mp3");
    delete s;
    //Sleep(300); // ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
    //
    // �~����J��L���
    //
    //
    // ��OnInit�ʧ@�|����CGameStaterOver::OnInit()�A�ҥH�i���٨S��100%
    //
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    const char KEY_LEFT = 0x25; // keyboard���b�Y
    const char KEY_UP = 0x26; // keyboard�W�b�Y
    const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
    const char KEY_DOWN = 0x28; // keyboard�U�b�Y
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    const char KEY_LEFT = 0x25; // keyboard���b�Y
    const char KEY_UP = 0x26; // keyboard�W�b�Y
    const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
    const char KEY_DOWN = 0x28; // keyboard�U�b�Y
    const char KEY_ESC = 27;

    if (nChar == KEY_ESC)
    {
        if (!isStop2 && !isStop)
        {
            isStop2 = !isStop2;
            isStop = !isStop;
        }
    }

    if (nChar == KEY_UP)//�H�ƥ[�Q
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

    if (nChar == KEY_DOWN)//�ֳt����
    {
        if (!isStop && !isStop2)
        {
            counter = 120 * 30 - 1;
        }
    }
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)
{
    // �o��t�d�B�z���U�ƹ����䪺�ʧ@
    int start = line->GetClickedStartStationNum();	//�����_�l����
    int end = line->GetClickedEndStationNum();	//�������I����

    if (!isStop)
    {
        if (start == -1) //�S�����󨮯��Q���
        {
            if (line->IsClickedStation(point.x, point.y, stationList, MAXIUM_STATION)) //�ˬd�O�_���I�쨮��
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
        else //�p�G�_�I�����w�g�Q���
        {
            if (line->IsClickedStation(point.x, point.y, stationList, MAXIUM_STATION)) //�ˬd�O�_���I�쨮��
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

    clickedX = point.x;	//�Ψ�debug
    clickedY = point.y; //�Ψ�debug
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����䪺�ʧ@ ��}
{
    //���K�y���C��
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
                    PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// �����C��
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

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// �B�z�ƹ����䪺�ʧ@ ����
{
    // �S�ơC�p�G�ݭn�B�z�ƹ����ʪ��ܡA�gcode�b�o��
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
    map.SetTopLeft(0, 0);	//�]�m�a�Ϧ�m

    if (isNight)
    {
        nightMap.ShowBitmap();
    }
    else
    {
        map.ShowBitmap();		//��a����ܥX��
    }

    clock.OnShow();			//��ܮ���
    //===============��ܦU�C�⪺���u���ϼ�==============
    purpleLine.ShowLineIconBitmap();	//����
    bblueLine.ShowLineIconBitmap();		//�Q��
    blueLine.ShowLineIconBitmap();		//�Ŧ�
    greenLine.ShowLineIconBitmap();		//���
    yellowLine.ShowLineIconBitmap();	//����
    orangeLine.ShowLineIconBitmap();	//���
    redLine.ShowLineIconBitmap();		//����

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

    // �p�G���@�Ө����Q��� �N�n�e�X�� //���y�ܻ� �N�O�u���n��۷ƹ���
    if (line->GetClickedStartStationNum() != -1 &&
            (line->IsPassedStationEmpty() ||
             line->GetClickedLastStation() == line->GetClickedStartStationNum()))
        line->DrawRailway(stationList[line->GetClickedStartStationNum()].GetX() + 5,
                          stationList[line->GetClickedStartStationNum()].GetY() + 5, mouse_x, mouse_y);

    //��ܦU�C��u��
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

    //// �H�UDebug ��
    CDC* pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC
    CFont f, *fp;
    f.CreatePointFont(160, "Times New Roman");	// ���� font f; 160���16 point���r
    fp = pDC->SelectObject(&f);					// ��� font f

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

    char str[80];								// Demo �Ʀr��r�ꪺ�ഫ
    //sprintf(str, "(%d,%d),(%d,%d),(%d,%d),(%d,%d)(%d)", clickedX, clickedY, mouse_x, mouse_y, line->GetClickedStartStationNum(), line->GetClickedEndStationNum(), preP, nextP, nextS);
    sprintf(str, "�C���ɶ��G%d", 120 - counter / 30);
    pDC->TextOut(10, 10, str);
    pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
    CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
}
}