#pragma once
#include "BaseScene.h"
#include "GameTask.h"
class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();
	void Update(Button button);
	void TransltionScene(void);
	void Draw(void);
	Scene GetScene(void) { return scene; };
};

