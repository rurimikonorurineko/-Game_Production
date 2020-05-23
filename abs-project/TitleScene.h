#pragma once
#include "BaseScene.h"
#include "GameTask.h"

class TitleScene :
	public BaseScene
{
public:
	TitleScene();
	~TitleScene();
	void Update(Button button);
	void TransltionScene(void);
	void Draw(void);
	Scene GetScene(void) { return scene; };
};

