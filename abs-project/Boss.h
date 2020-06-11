#pragma once
#include <memory>
#include "DxLib.h"
#include "Sprite.h"
#include "GameTask.h"
#include "Timer.h"

enum BOSS_TYPE
{
	HUMAN,
	OGRE,
	STATUEOFGOD,
	GODOFDEATH,
	TYPE_MAX
};

class Boss
{
public:
	Boss();
	~Boss();
	void Initialize(void);
	void Update(Button button, VECTOR screen);
	void Draw(void);
private:
	Sprite boss[TYPE_MAX];
	TIMER changeTimes[TYPE_MAX];
	BOSS_TYPE bossType;

	BOSS_TYPE& ChangeType(BOSS_TYPE& bossType);

	std::unique_ptr<Timer> timer;
};

