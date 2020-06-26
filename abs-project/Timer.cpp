#include "DxLib.h"
#include "Timer.h"
#include "ImageMng.h"

#define CHANGE_TIME 60

Timer::Timer()
{

}

Timer::Timer(VECTOR screen)
{
	//������
	fleamCount = 0;
	timer.second.actual = 0;
	timer.minute.actual = 13;
	timer.hour.actual = 13;
	//�b�j�̏�����
	timer.second.Graph = ImageMng::GetInstance().GetID("image/second-hand.png")[0];
	GetGraphSize(timer.second.Graph, &timer.second.W, &timer.second.H);
	//���j�̏�����
	timer.minute.Graph = ImageMng::GetInstance().GetID("image/minute-hand.png")[0];
	GetGraphSize(timer.minute.Graph, &timer.minute.W, &timer.minute.H);
	//���j�̏�����
	timer.hour.Graph = ImageMng::GetInstance().GetID("image/hour-hand.png")[0];
	GetGraphSize(timer.hour.Graph, &timer.hour.W, &timer.hour.H);
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
	//�t���[�����b
	if (fleamCount != 0 && fleamCount % (CHANGE_TIME/10) == 0)
	{
		timer.second.actual++;
	}
	//�b����
	if (timer.second.actual != 0 && timer.second.actual % CHANGE_TIME == 0)
	{
		timer.minute.actual++;
		timer.second.actual = 0;
	}
	//��������
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
	DrawFormatString(650, 300, GetColor(0,0,0), "%d:%d:%d", timer.hour.actual, timer.minute.actual, timer.second.actual);
	DrawExtendGraph(clock.pos.x, clock.pos.y,
					clock.pos.x + clock.W /1.5, 
					clock.pos.y + clock.H /1.5,clock.Graph, true);


	//DrawRotaGraph2(,,ImageMng::GetInstance().GetID[0],true);
	//DrawRotaGraph2(, , ImageMng::GetInstance().GetID[0], true);
	DrawRotaGraph2(100,100
				 , timer.second.W - timer.second.W /2, timer.second.H - timer.second.H /10
				 , 0, 0, timer.second.Graph, false);
}
