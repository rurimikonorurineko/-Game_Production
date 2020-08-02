#pragma once
#include "DxLib.h"
#include "GameTask.h"
#include "Timer.h"
enum Scene
{
	None,
	Title,
	Game,
	Result
};

class BaseScene
{
public:
	BaseScene();
	BaseScene(VECTOR screen);
	virtual ~BaseScene();
	virtual void Initialize(void);
	virtual void Update(Button button, std::unique_ptr<Timer>& timer) = 0;
	virtual void TransltionScene(void);
	virtual void Draw(void);
protected:
	Scene scene;
};

