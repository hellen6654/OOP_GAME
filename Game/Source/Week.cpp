#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Week.h"

namespace game_framework
{
Week::Week()
{
    x = 710;
    y = 20;
}

void Week::LoadBitmap()
{
    char* filename[7] = { ".\\RES\\week\\week1.bmp", ".\\RES\\week\\week2.bmp", ".\\RES\\week\\week3.bmp", ".\\RES\\week\\week4.bmp",
                          ".\\RES\\week\\week5.bmp", ".\\RES\\week\\week6.bmp", ".\\RES\\week\\week7.bmp"
                        };

    for (int i = 0; i < 7; i++)  	// 載入動畫(由7張圖形構成)
    {
        animation.AddBitmap(filename[i], RGB(255, 255, 255));
    }
}

void Week::OnMove()
{
    animation.OnMove();		// 執行一次animation.OnMove()，animation才會換圖
}

void Week::OnShow()
{
    animation.SetTopLeft(x, y);
    animation.OnShow();
}

}