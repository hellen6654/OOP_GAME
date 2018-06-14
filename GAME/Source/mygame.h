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

#include "Station.h"
#include "Clock.h"
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
    AUDIO_CLICK,			// 1
    AUDIO_MUSIC,			// 2
    AUDIO_SELECT1,			// 3
    AUDIO_SELECT2,			// 4
    AUDIO_APPEAR,			// 5
    AUDIO_STOP1,			// 6
    AUDIO_STOP2,			// 7
	AUDIO_COLOR				// 8
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
		void OnMove();									// ���ʹC������
        void OnShow();									// ��ܳo�Ӫ��A���C���e��
    private:
        CMovingBitmap start;							//�C���}�l�����s��
        CMovingBitmap startInvert;						//�C���}�l���C��Ϭ۫��s��
        CMovingBitmap end;								//�C�����������s��
        CMovingBitmap endInvert;						//�C���������C��Ϭ۫��s��
        CMovingBitmap logo;								//�C����logo
		CMovingBitmap red;								//�ʭ��������K�y
		CMovingBitmap orange;							//�ʭ�������K�y
		CMovingBitmap blue;								//�ʭ����Ŧ��K�y
		CMovingBitmap bblue;							//�ʭ����`�Ŧ��K�y

		CMovingBitmap redCabin;							//�ʭ������⨮�[
		CMovingBitmap redCabin2;						//�ʭ������⨮�[
		CMovingBitmap orangeCabin;						//�ʭ�����⨮�[
		CMovingBitmap orangeCabin2;						//�ʭ�����⨮�[
		CMovingBitmap blueCabin;						//�ʭ����Ŧ⨮�[
		CMovingBitmap blueCabin2;						//�ʭ����Ŧ⨮�[
		CMovingBitmap bblueCabin;						//�ʭ����`�Ŧ⨮�[
		CMovingBitmap bblueCabin2;						//�ʭ����`�Ŧ⨮�[

		int redCabinX = -50;
		int redCabinY = 270;
		int orangeCabinX = 38;
		int orangeCabinY = 800;
		int blueCabinX = 694;
		int blueCabinY = 600;
		int bblueCabinX = 675;
		int bblueCabinY = 1000;

        bool isMouseInStartBtn;							//�ƹ��b�}�l���s
        bool isMouseInEndBtn;							//�ƹ��b�������s
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
        const int MAXIUM_STATION = 6;					//�|�X�{�b�a�ϤW�����`��
        const int MAXIUM_STATION_TYPE = 6;				//�����˦��`�@��6�� 00~05
        const int LINE_COLOR_NUM = 7;					//�u���˦��`�@��7�� 00~06
        const int INIT_PASSANGER = MAXIUM_STATION * 2;	//���Ȫ�l�Ӽ�
		const int MAX_PASSENGER_NUM = 6;				//���[�̦h���ӭ���
		const int LINE_CAN_USE_TIME = 5;				//�i�H�ԥX��L�C�⪺�ɶ�
		//station.h�̭��]���ۦP���ݩʭn��
        const int MAX_GAME_MAP_SIDE_X = 770-135;		//��ڤW���C�����X�b�u����770
        const int MIN_GAME_MAP_SIDE_X = 30;			    //��ڤW���C�����X�b�q30�}�l
        const int MAX_GAME_MAP_SIDE_Y = 560-25;			//��ڤW���C�����Y�b�u����560
        const int MIN_GAME_MAP_SIDE_Y = 60;			    //��ڤW���C�����Y�b�q60�}�l

        bool isStop;

        int currentStationNum;							//�ثe�X�{����Ө���
        int currentPassenagerNum;						//�ثe���X�ӭ��ȥX�{
        int counter;
		
        int clickedX;
        int clickedY;
		int preP=0, nextP=0,nextS=0;
        Line*    line;									//�t�d�B�z�����u��������
        Line    redLine;								//����u��
        Line    orangeLine;								//���u��
        Line    yellowLine;								//����u��
        Line    greenLine;								//���u��
        Line    blueLine;								//�Ŧ�u��
        Line    bblueLine;								//�Q��u��
        Line    purpleLine;								//����u��
		vector<CMovingBitmap> garyIcon;					//�t�d�\���L�C�⪺�ϼ�
        Clock   clock;									//�|�ʪ�����

        vector<Station> stationList;					//�@�諸����
        vector<Passenger*> passengerList;				//�@�諸����



		vector<Cabin> cabinList;



        int redCabinState = 0;
        int orangCabinState = 0;
        int yellowCabinState = 0;
        int greenCabinState = 0;
        int blueCabinState = 0;
        int bblueCabinState = 0;
        int pupleCabinState = 0;

        int mouse_x = 0, mouse_y = 0;					//�ƹ���m
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