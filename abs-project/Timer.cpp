#include <math.h>
#include "DxLib.h"
#include "Timer.h"
#include "ImageMng.h"

#define CHANGE_TIME 60			//時間を作り替えるときの1つの大きさ
#define PAI 3.141592653589793	//円周率(π)
#define ANGLE_MAX 360			//一周の角度
#define CLOCK_ROUND	12			//時計一周の時間数字
Timer::Timer()
{

}

Timer::Timer(VECTOR screen)
{
	this->screen = screen;
	//時間を初期化
	fleamCount = 0;
	timer.second.actual = 0;
	timer.minute.actual = 0;
	timer.hour.actual = 0;
	//角度を初期化
	//ラジアン
	timer.second.rad = 0;
	timer.minute.rad = 0;
	timer.hour.rad = 0;
	//角度
	clock.actual = 0;

	Initialize();
}

Timer::~Timer()
{
}
//イニシャライズ
void Timer::Initialize(void)
{
	//初期値設定
	timer.minute.actual = 14;
	timer.hour.actual = 1;
	//秒針の画像読み込み＆画像サイズ取得
	timer.second.Graph = ImageMng::GetInstance().GetID("image/second-hand.png")[0];
	GetGraphSize(timer.second.Graph, &timer.second.W, &timer.second.H);

	//分針の画像読み込み＆画像サイズ取得
	timer.minute.Graph = ImageMng::GetInstance().GetID("image/minute-hand.png")[0];
	GetGraphSize(timer.minute.Graph, &timer.minute.W, &timer.minute.H);

	//時針の画像読み込み＆画像サイズ取得
	timer.hour.Graph = ImageMng::GetInstance().GetID("image/hour-hand.png")[0];
	GetGraphSize(timer.hour.Graph, &timer.hour.W, &timer.hour.H);

	//文字盤の画像読み込み＆画像サイズ取得
	clock.Graph = ImageMng::GetInstance().GetID("image/clock-dial.png")[0];
	GetGraphSize(clock.Graph, &clock.W, &clock.H);
}
//更新
void Timer::Update(void)
{
	fleamCount+=2;
	ConventTimer(fleamCount);
}
//フレームカウントを時間に作り替える
void Timer::ConventTimer(int fleamCount)
{
	//フレーム→秒
	if (fleamCount != 0 && fleamCount % (CHANGE_TIME/10) == 0)
	{
		timer.second.actual++;
	}
	//秒→分
	if (timer.second.actual >= CHANGE_TIME)
	{
		timer.minute.actual++;
		timer.second.actual = 0;
	}
	//分→時間
	if (timer.minute.actual >= CHANGE_TIME)
	{
		timer.hour.actual++;
		timer.minute.actual = 0;
	}
	//時計針の角度を形成
	MakeHourRad();
	MakeMinuteRad();
	MakeSecondRad();
	
}

//描画
void Timer::DrawTimer(void)
{
	//時計の座標をセット
	VECTOR tPos = { screen.x / 2 - clock.W / 4, 0, 0};
	//文字盤の描画
	DrawGraph(tPos.x, tPos.y, clock.Graph, true);

	//時針・分針・秒針の描画
	DrawRotaGraph(tPos.x + timer.hour.W / 2, tPos.y + timer.hour.H / 2, 1.0,
					timer.hour.rad, timer.hour.Graph,true);
	DrawRotaGraph(tPos.x + timer.minute.W / 2, tPos.y + timer.minute.H / 2, 1.0,
					timer.minute.rad, timer.minute.Graph, true);
	DrawRotaGraph(tPos.x + timer.second.W /2, tPos.y + timer.second.H / 2, 1.0, 
					timer.second.rad, timer.second.Graph, true);
	//DrawGraph(tPos.x, tPos.y, timer.second.Graph,true);
}

//時針の角度を形成
void Timer::MakeHourRad(void)
{
	int hr = timer.hour.actual * (ANGLE_MAX / CLOCK_ROUND) + timer.minute.actual /2;
	timer.hour.rad = hr * PAI / (ANGLE_MAX /2);
}
//分針の角度を形成
void Timer::MakeMinuteRad(void)
{
	int mi = timer.minute.actual * (ANGLE_MAX / CHANGE_TIME);
	timer.minute.rad = mi * PAI / (ANGLE_MAX /2);
}
//秒針の角度を形成
void Timer::MakeSecondRad(void)
{
	int sc = timer.second.actual * (ANGLE_MAX / CHANGE_TIME);
	timer.second.rad = sc * PAI / (ANGLE_MAX /2);
}


