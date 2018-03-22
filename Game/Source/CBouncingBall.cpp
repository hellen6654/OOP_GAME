#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CBouncingBall.h"

namespace game_framework
{
/////////////////////////////////////////////////////////////////////////////
// CBouncingBall: BouncingBall class
/////////////////////////////////////////////////////////////////////////////

CBouncingBall::CBouncingBall()
{
    const int INITIAL_VELOCITY = 20;	// ��l�W�ɳt��
    const int FLOOR = 400;				// �a�O�y��
    floor = FLOOR;
    x = 750;
    y = 10;				// y�y�Ф�a�O��1�I(���b�a�O�W)
    rising = true;
    initial_velocity = INITIAL_VELOCITY;
    velocity = initial_velocity;
}

void CBouncingBall::LoadBitmap()
{
    char* filename[12] = { ".\\bitmaps\\Comp 4_00000.bmp", ".\\bitmaps\\Comp 4_00020.bmp", ".\\bitmaps\\Comp 4_00042.bmp", ".\\bitmaps\\Comp 4_00062.bmp",
                           ".\\bitmaps\\Comp 4_00084.bmp", ".\\bitmaps\\Comp 4_00104.bmp", ".\\bitmaps\\Comp 4_00124.bmp", ".\\bitmaps\\Comp 4_00144.bmp",
                           ".\\bitmaps\\Comp 4_00167.bmp", ".\\bitmaps\\Comp 4_00187.bmp", ".\\bitmaps\\Comp 4_00207.bmp", ".\\bitmaps\\Comp 4_00230.bmp"
                         };
    char* filename2[7] = { ".\\bitmaps\\1.bmp", ".\\bitmaps\\2.bmp", ".\\bitmaps\\3.bmp", ".\\bitmaps\\4.bmp",
                           ".\\bitmaps\\5.bmp", ".\\bitmaps\\6.bmp", ".\\bitmaps\\7.bmp"
                         };
    day = 0;
    j = 0;

    for (int i = 0; i < 12; i++)  	// ���J�ʵe(��4�i�ϧκc��)
    {
        animation.AddBitmap(filename[i], RGB(0, 0, 0));
    }
}

void CBouncingBall::OnMove()
{
    /*if (rising)  			// �W�ɪ��A
    {
        if (velocity > 0)
        {
            y -= velocity;	// ��t�� > 0�ɡAy�b�W��(����velocity���I�Avelocity����쬰 �I/��)
            velocity--;		// �����O�v�T�A�U�����W�ɳt�׭��C
        }
        else
        {
            rising = false; // ��t�� <= 0�A�W�ɲפ�A�U���אּ�U��
            velocity = 1;	// �U������t(velocity)��1
        }
    }
    else  				// �U�����A
    {
        if (y < floor - 1)    // ��y�y���٨S�I��a�O
        {
            y += velocity;	// y�b�U��(����velocity���I�Avelocity����쬰 �I/��)
            velocity++;		// �����O�v�T�A�U�����U���t�׼W�[
        }
        else
        {
            y = floor - 1;  // ��y�y�ЧC��a�O�A�󥿬��a�O�W
            rising = true;	// �����ϼu�A�U���אּ�W��
            velocity = initial_velocity; // ���]�W�ɪ�l�t��
        }
    }*/
    animation.OnMove();		// ����@��animation.OnMove()�Aanimation�~�|����
}

void CBouncingBall::OnShow()
{
    animation.SetTopLeft(x, y);
    animation.OnShow();
}
}