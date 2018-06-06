#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include <ctime>
#include "audio.h"
#include "gamelib.h"
#include "Timer.h"

namespace game_framework
{
	Timer::Timer()
	{
		time = 0;
	}

	void Timer::StartCount()
	{
		start_time = clock();
	}

	void Timer::CountPassTime()
	{
		end_time = clock();
		if (( (end_time - start_time) / CLOCKS_PER_SEC )/ 3600 > 1)
			time++;
	}

	void Timer::ResetCount()
	{
		start_time = end_time = clock();
	}

	int Timer::GetTime()
	{
		return time;
	}

	Timer::~Timer()
	{
	}
}
