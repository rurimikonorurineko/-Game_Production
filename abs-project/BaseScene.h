#pragma once
#include "GameTask.h"
enum Scene
{
	Title,
	Game,
	Result
};

class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();
	virtual void Update(Button button) = 0;
	virtual void TransltionScene(void);
	virtual void Draw(void);
protected:
	Scene scene;
};

