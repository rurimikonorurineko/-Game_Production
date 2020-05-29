#pragma once
#include "BaseScene.h"
#include "GameTask.h"
#include "Sprite.h"

#define BC_SHEETS_NUMBER 2

class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();
	void Initialize(void);
	void Update(Button button);
	void TransltionScene(void);
	void Draw(void);
	Scene GetScene(void) { return scene; };
private:
	Sprite bcGround[BC_SHEETS_NUMBER];

};

