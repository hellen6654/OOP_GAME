#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Clock.h"

namespace game_framework
{
	/////////////////////////////////////////////////////////////////////////////
	// 
	/////////////////////////////////////////////////////////////////////////////

	Clock::Clock()
	{
		clk_x = 750;
		clk_y = 10;
		week_x = 700;
		week_y = 10;
	}

	void Clock::LoadBitmap()
	{
		char* clock_filename[100] = {
			".\\RES\\ClockImage\\Clock_0.bmp" ,".\\RES\\ClockImage\\Clock_1.bmp" ,".\\RES\\ClockImage\\Clock_2.bmp" ,".\\RES\\ClockImage\\Clock_3.bmp" ,".\\RES\\ClockImage\\Clock_4.bmp" ,
			".\\RES\\ClockImage\\Clock_5.bmp" ,".\\RES\\ClockImage\\Clock_6.bmp" ,".\\RES\\ClockImage\\Clock_7.bmp" ,".\\RES\\ClockImage\\Clock_8.bmp" ,".\\RES\\ClockImage\\Clock_9.bmp" ,
			".\\RES\\ClockImage\\Clock_10.bmp",".\\RES\\ClockImage\\Clock_11.bmp",".\\RES\\ClockImage\\Clock_12.bmp",".\\RES\\ClockImage\\Clock_13.bmp",".\\RES\\ClockImage\\Clock_14.bmp",
			".\\RES\\ClockImage\\Clock_15.bmp",".\\RES\\ClockImage\\Clock_16.bmp",".\\RES\\ClockImage\\Clock_17.bmp",".\\RES\\ClockImage\\Clock_18.bmp",".\\RES\\ClockImage\\Clock_19.bmp",
			".\\RES\\ClockImage\\Clock_20.bmp",".\\RES\\ClockImage\\Clock_21.bmp",".\\RES\\ClockImage\\Clock_22.bmp",".\\RES\\ClockImage\\Clock_23.bmp",".\\RES\\ClockImage\\Clock_24.bmp",
			".\\RES\\ClockImage\\Clock_25.bmp",".\\RES\\ClockImage\\Clock_26.bmp",".\\RES\\ClockImage\\Clock_27.bmp",".\\RES\\ClockImage\\Clock_28.bmp",".\\RES\\ClockImage\\Clock_29.bmp",
			".\\RES\\ClockImage\\Clock_30.bmp",".\\RES\\ClockImage\\Clock_31.bmp",".\\RES\\ClockImage\\Clock_32.bmp",".\\RES\\ClockImage\\Clock_33.bmp",".\\RES\\ClockImage\\Clock_34.bmp",
			".\\RES\\ClockImage\\Clock_35.bmp",".\\RES\\ClockImage\\Clock_36.bmp",".\\RES\\ClockImage\\Clock_37.bmp",".\\RES\\ClockImage\\Clock_38.bmp",".\\RES\\ClockImage\\Clock_39.bmp",
			".\\RES\\ClockImage\\Clock_40.bmp",".\\RES\\ClockImage\\Clock_41.bmp",".\\RES\\ClockImage\\Clock_42.bmp",".\\RES\\ClockImage\\Clock_43.bmp",".\\RES\\ClockImage\\Clock_44.bmp",
			".\\RES\\ClockImage\\Clock_45.bmp",".\\RES\\ClockImage\\Clock_46.bmp",".\\RES\\ClockImage\\Clock_47.bmp",".\\RES\\ClockImage\\Clock_48.bmp",".\\RES\\ClockImage\\Clock_49.bmp",
			".\\RES\\ClockImage\\Clock_50.bmp",".\\RES\\ClockImage\\Clock_51.bmp",".\\RES\\ClockImage\\Clock_52.bmp",".\\RES\\ClockImage\\Clock_53.bmp",".\\RES\\ClockImage\\Clock_54.bmp",
			".\\RES\\ClockImage\\Clock_55.bmp",".\\RES\\ClockImage\\Clock_56.bmp",".\\RES\\ClockImage\\Clock_57.bmp",".\\RES\\ClockImage\\Clock_58.bmp",".\\RES\\ClockImage\\Clock_59.bmp",
			".\\RES\\ClockImage\\Clock_60.bmp",".\\RES\\ClockImage\\Clock_61.bmp",".\\RES\\ClockImage\\Clock_62.bmp",".\\RES\\ClockImage\\Clock_63.bmp",".\\RES\\ClockImage\\Clock_64.bmp",
			".\\RES\\ClockImage\\Clock_65.bmp",".\\RES\\ClockImage\\Clock_66.bmp",".\\RES\\ClockImage\\Clock_67.bmp",".\\RES\\ClockImage\\Clock_68.bmp",".\\RES\\ClockImage\\Clock_69.bmp",
			".\\RES\\ClockImage\\Clock_70.bmp",".\\RES\\ClockImage\\Clock_71.bmp",".\\RES\\ClockImage\\Clock_72.bmp",".\\RES\\ClockImage\\Clock_73.bmp",".\\RES\\ClockImage\\Clock_74.bmp",
			".\\RES\\ClockImage\\Clock_75.bmp",".\\RES\\ClockImage\\Clock_76.bmp",".\\RES\\ClockImage\\Clock_77.bmp",".\\RES\\ClockImage\\Clock_78.bmp",".\\RES\\ClockImage\\Clock_79.bmp",
			".\\RES\\ClockImage\\Clock_80.bmp",".\\RES\\ClockImage\\Clock_81.bmp",".\\RES\\ClockImage\\Clock_82.bmp",".\\RES\\ClockImage\\Clock_83.bmp",".\\RES\\ClockImage\\Clock_84.bmp",
			".\\RES\\ClockImage\\Clock_85.bmp",".\\RES\\ClockImage\\Clock_86.bmp",".\\RES\\ClockImage\\Clock_87.bmp",".\\RES\\ClockImage\\Clock_88.bmp",".\\RES\\ClockImage\\Clock_89.bmp",
			".\\RES\\ClockImage\\Clock_90.bmp",".\\RES\\ClockImage\\Clock_91.bmp",".\\RES\\ClockImage\\Clock_92.bmp",".\\RES\\ClockImage\\Clock_93.bmp",".\\RES\\ClockImage\\Clock_94.bmp",
			".\\RES\\ClockImage\\Clock_95.bmp",".\\RES\\ClockImage\\Clock_96.bmp",".\\RES\\ClockImage\\Clock_97.bmp",".\\RES\\ClockImage\\Clock_98.bmp",".\\RES\\ClockImage\\Clock_99.bmp"
		};
		char* week_filename[7] = {
			".\\RES\\WeekImage\\1.bmp",".\\RES\\WeekImage\\2.bmp",".\\RES\\WeekImage\\3.bmp",".\\RES\\WeekImage\\4.bmp"
			,".\\RES\\WeekImage\\5.bmp",".\\RES\\WeekImage\\6.bmp",".\\RES\\WeekImage\\7.bmp"
		};
		for (int i = 0; i < 100; i++)  	// 載入動畫(由100張圖形構成)
			clock_animation.AddBitmap(clock_filename[i], RGB(0, 0, 0));

		clock_animation.SetDelayCount(5); // 延遲播放速度


		for (int i = 0; i < 7; i++)
			week_animation.AddBitmap(week_filename[i], RGB(0, 0, 0));
	}

	void Clock::OnMove()
	{
		clock_animation.OnMove();		// 執行一次animation.OnMove()，animation才會換圖
	}

	void Clock::OnShow()
	{
		clock_animation.SetTopLeft(clk_x, clk_y);
		clock_animation.OnShow();
		week_animation.SetTopLeft(week_x,week_y);
		week_animation.OnShow();
	}
}