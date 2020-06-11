#include "DxLib.h"
#include "Timer.h"

#define CHANGE_TIME 60

Timer::Timer()
{
	//‰Šú‰»
	fleamCount = 0;
	timer.second = 0;
	timer.minute = 12;
	timer.hour = 13;
	fleamCount = 0;
}


Timer::~Timer()
{
}

void Timer::Update(void)
{
	fleamCount++;
	ConventTimer(fleamCount);
}

void Timer::ConventTimer(int fleamCount)
{
	//ƒtƒŒ[ƒ€¨•b
	if (fleamCount != 0 && fleamCount % (CHANGE_TIME/10) == 0)
	{
		timer.second++;
	}
	//•b¨•ª
	if (timer.second != 0 && timer.second % CHANGE_TIME == 0)
	{
		timer.minute++;
		timer.second = 0;
	}
	//•ª¨ŠÔ
	if (timer.minute != 0 && timer.minute % CHANGE_TIME == 0)
	{
		timer.hour++;
		timer.minute = 0;
	}
}

bool Timer::CheckChangeTime(TIMER changeTime)
{
	if (timer.hour == changeTime.hour
		&&  timer.minute == changeTime.minute
		&&  timer.second == changeTime.second)
	{
		return true;
	}
	return false;
}

void Timer::DrawTimer(void)
{
	DrawFormatString(650, 10, GetColor(0,0,0), "%d:%d:%d", timer.hour, timer.minute, timer.second);
}
