#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Week.h"

namespace game_framework
{
	/////////////////////////////////////////////////////////////////////////////
	// 
	/////////////////////////////////////////////////////////////////////////////

	Week::Week()
	{
		week_x = 700;
		week_y = 10;
	}

	void Week::LoadBitmap()
	{
		char* week_filename[7] = {
			".\\RES\\WeekImage\\1.bmp",".\\RES\\WeekImage\\2.bmp",".\\RES\\WeekImage\\3.bmp",".\\RES\\WeekImage\\4.bmp"
			,".\\RES\\WeekImage\\5.bmp",".\\RES\\WeekImage\\6.bmp",".\\RES\\WeekImage\\7.bmp"
		};
		for (int i = 0; i < 7; i++)
			week_animation.AddBitmap(week_filename[i], RGB(0, 0, 0));
		week_animation.SetDelayCount(600);
	}

	void Week::OnMove()
	{
		week_animation.OnMove();		// 執行一次animation.OnMove()，animation才會換圖
	}

	void Week::OnShow()
	{
		week_animation.SetTopLeft(week_x, week_y);
		week_animation.OnShow();
	}
}