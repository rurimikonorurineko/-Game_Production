#pragma once

struct TIMER
{
	int second;
	int minute;
	int hour;
};

class Timer
{
public:
	Timer();
	~Timer();
	void Update(void);
	void ConventTimer(int fleamCount);
	void DrawTimer(void);
	TIMER GetTimer(void) { return timer; };
private:
	TIMER timer;
	int fleamCount;
};
