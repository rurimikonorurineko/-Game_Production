#pragma once
#include "BaseScene.h"
#include "GameTask.h"

class TitleScene :
	public BaseScene
{
public:
	TitleScene();
	~TitleScene();
	void Initialize(void);
	void Update(Button button, VECTOR screen);
	void TransltionScene(void);
	void Draw(void);
	Scene GetScene(void) { return scene; };
};

