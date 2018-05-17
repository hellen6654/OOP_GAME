/*
 * mygame.h: ���ɮ��x�C��������class��interface
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

enum AUDIO_ID  				// �w�q�U�ح��Ī��s��
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
// �o��class���C�����C���}�Y�e������
// �C��Member function��Implementation���n����
/////////////////////////////////////////////////////////////////////////////

class CGameStateInit : public CGameState
{
    public:
        CGameStateInit(CGame* g);
        void OnInit();  								// �C������Ȥιϧγ]�w
        void OnBeginState();							// �]�w�C�������һݪ��ܼ�
        void OnKeyUp(UINT, UINT, UINT); 				// �B�z��LUp���ʧ@
        void OnLButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
        void OnLButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
        void OnMouseMove(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
    protected:
        void OnShow();									// ��ܳo�Ӫ��A���C���e��
    private:
        CMovingBitmap end;
        CMovingBitmap start;
        CMovingBitmap logo;								// csie��logo
        int mouse_x = 0, mouse_y = 0;					//�ƹ���m

        int mouse_state = 1;
};

/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
// �C��Member function��Implementation���n����
/////////////////////////////////////////////////////////////////////////////

class CGameStateRun : public CGameState
{
    public:
        CGameStateRun(CGame* g);
        ~CGameStateRun();
        void OnBeginState();							// �]�w�C�������һݪ��ܼ�
        void OnInit();  								// �C������Ȥιϧγ]�w
        void OnKeyDown(UINT, UINT, UINT);
        void OnKeyUp(UINT, UINT, UINT);
        void OnLButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
        void OnLButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
        void OnMouseMove(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
        void OnRButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
        void OnRButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
    protected:
        void OnMove();									// ���ʹC������
        void OnShow();									// ��ܳo�Ӫ��A���C���e��
    private:
        CMovingBitmap  map;
        CMovingBitmap  color[7];
        const int STATION_APPERAED_TIME = 5;			//�����X�{�����
        const int PASSENAGER_APPERAED_TIME = 3;			//���ȥX�{�����
        const int MAXIUM_STATION = 10;					//�|�X�{�b�a�ϤW�����`��
        const int MAXIUM_STATION_TYPE = 7;				//�����˦��`�@��7�� 00~06
        const int LINE_COLOR_NUM = 7;					//�����˦��`�@��7�� 00~06

        const int MAXIUM_PASSANGER = MAXIUM_STATION * 5; //�����`�Ӽ�

        //station.h�̭��]���ۦP���ݩʭn��
        const int MAX_GAME_MAP_SIDE_X = 770;			//��ڤW���C�����X�b�u����770
        const int MIN_GAME_MAP_SIDE_X = 30;			    //��ڤW���C�����X�b�q30�}�l
        const int MAX_GAME_MAP_SIDE_Y = 560;			//��ڤW���C�����Y�b�u����560
        const int MIN_GAME_MAP_SIDE_Y = 60;			    //��ڤW���C�����Y�b�q60�}�l


        int currentStationNum;							//�ثe�X�{����Ө���
        int currentPassenagerNum;						//�ثe���X�ӭ��ȥX�{
        int counter;
        int clickedX;
        int clickedY;
        int lstart;
        int lend;
        int mouse_state = 1;
        Line*    line;									//�t�d�B�z�����u��������

        Line    redLine;								//����u��
        Line    orangeLine;								//���u��
        Line    yellowLine;								//����u��
        Line    greenLine;								//���u��
        Line    blueLine;								//�Ŧ�u��
        Line    bblueLine;								//�Q��u��
        Line    purpleLine;								//����u��

        Clock   clock;									//�|�ʪ�����
        Week    week;									//�|�ʪ��P��

        vector<Station> stationList;					//�@�諸����
        vector<Passenger> passengerList;				//�@�諸����
        vector<Cabin> cabinList;
        Cabin cabin;

        int stationRelation[10][10][7];					//�y�D��m
        int mouse_x = 0, mouse_y = 0;					//�ƹ���m
        int mouse_X = 0, mouse_Y = 0;
};

/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����������A(Game Over)
// �C��Member function��Implementation���n����
/////////////////////////////////////////////////////////////////////////////

class CGameStateOver : public CGameState
{
    public:
        CGameStateOver(CGame* g);
        void OnBeginState();							// �]�w�C�������һݪ��ܼ�
        void OnInit();
    protected:
        void OnMove();									// ���ʹC������
        void OnShow();									// ��ܳo�Ӫ��A���C���e��
    private:
        int counter;	// �˼Ƥ��p�ƾ�
};

}