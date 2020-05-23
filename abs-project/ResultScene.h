#pragma once
#include "BaseScene.h"
#include "GameTask.h"

class ResultScene :
	public BaseScene
{
public:
	ResultScene();
	~ResultScene();
	void Update(Button button);
	void TransltionScene(void);
	void Draw(void);
	Scene GetScene(void) { return scene; };
};

