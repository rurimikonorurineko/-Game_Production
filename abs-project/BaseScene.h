#pragma once
#include "GameTask.h"
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
	virtual ~BaseScene();
	virtual void Initialize(void);
	virtual void Update(Button button) = 0;
	virtual void TransltionScene(void);
	virtual void Draw(void);
protected:
	Scene scene;
};
