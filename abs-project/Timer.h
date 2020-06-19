#pragma once
#include "DxLib.h"
#include "Sprite.h"
struct TIME_ELEMENT
{
	int actual;
	int Graph;
};
struct TIMER
{
	TIME_ELEMENT second;
	TIME_ELEMENT minute;
	TIME_ELEMENT hour;
};

class Timer
{
public:
	Timer();
	Timer(VECTOR screen);
	~Timer();
	void Update(void);
	void ConventTimer(int fleamCount);
	void DrawTimer(void);
	bool CheckChangeTime(TIMER changeTime);
private:
	TIMER timer;
	int fleamCount;
	VECTOR screen;
	Sprite clock;
};

