#pragma once
#include "DxLib.h"
#include "GameTask.h"
class Boss
{
public:
	Boss();
	~Boss();
	void Initialize(void);
	void Update(Button button, VECTOR screen);
	void Draw(void);
};

