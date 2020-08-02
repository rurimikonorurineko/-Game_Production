#pragma once
#include "DxLib.h"
struct TIME_ELEMENT
{
	int actual;		//時間
	int Graph;		//画像
	int W, H;		//画像サイズ
	float rad;		//画像の回転角度(ラジアン)
};
struct TIMER
{
	TIME_ELEMENT second;	//秒
	TIME_ELEMENT minute;	//分
	TIME_ELEMENT hour;		//時
};

class Timer
{
public:
	Timer();
	Timer(VECTOR screen);
	~Timer();
	void Initialize(void);
	void Update(void);
	void ConventTimer(int fleamCount);			//フレームカウントを時間に作り替える
	void DrawTimer(void);
	TIMER GetTimer(void) { return timer; };		//タイマーのゲッター
private:
	//時計の針の回転角を形成
	void MakeHourRad(void);			//時針の角度を形成
	void MakeMinuteRad(void);		//分針の角度を形成
	void MakeSecondRad(void);		//秒針の角度を形成

	TIMER timer;		//タイマーの中身
	int fleamCount;		//フレームカウント
	VECTOR screen;		//画面サイズ
	TIME_ELEMENT clock;	//文字盤
};

