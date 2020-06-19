#include "DxLib.h"
#include "Timer.h"
#include "ImageMng.h"

#define CHANGE_TIME 60

Timer::Timer()
{

}

Timer::Timer(VECTOR screen)
{
	//èâä˙âª
	fleamCount = 0;
	timer.second.actual = 0;
	timer.minute.actual = 12;
	timer.hour.actual = 13;
	timer.second.Graph = ImageMng::GetInstance().GetID("image/second-hand.png")[0];
	timer.minute.Graph = ImageMng::GetInstance().GetID("image/minute-hand.png")[0];
	timer.hour.Graph = ImageMng::GetInstance().GetID("image/hour-hand.png")[0];
	this->screen = screen;
	clock.Graph = ImageMng::GetInstance().GetID("image/clock-dial.png")[0];
	GetGraphSize(clock.Graph,&clock.W,&clock.H);
	clock.pos = {screen.x /2 - clock.W /5,0};
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
	//ÉtÉåÅ[ÉÄÅ®ïb
	if (fleamCount != 0 && fleamCount % (CHANGE_TIME/10) == 0)
	{
		timer.second.actual++;
	}
	//ïbÅ®ï™
	if (timer.second.actual != 0 && timer.second.actual % CHANGE_TIME == 0)
	{
		timer.minute.actual++;
		timer.second.actual = 0;
	}
	//ï™Å®éûä‘
	if (timer.minute.actual != 0 && timer.minute.actual % CHANGE_TIME == 0)
	{
		timer.hour.actual++;
		timer.minute.actual = 0;
	}
}

bool Timer::CheckChangeTime(TIMER changeTime)
{
	if (timer.hour.actual == changeTime.hour.actual
		&&  timer.minute.actual == changeTime.minute.actual
		&&  timer.second.actual == changeTime.second.actual)
	{
		return true;
	}
	return false;
}

void Timer::DrawTimer(void)
{
	DrawFormatString(650, 10, GetColor(0,0,0), "%d:%d:%d", timer.hour.actual, timer.minute.actual, timer.second.actual);
	DrawExtendGraph(clock.pos.x, clock.pos.y,
					clock.pos.x + clock.W /1.5, 
					clock.pos.y + clock.H /1.5,clock.Graph, true);
	
	//DrawRotaGraph2(,,ImageMng::GetInstance().GetID[0],true);
	/*
	DrawRotaGraph2(, , ImageMng::GetInstance().GetID[0], true);
	DrawRotaGraph2(, , ImageMng::GetInstance().GetID[0], true);
	*/
}
