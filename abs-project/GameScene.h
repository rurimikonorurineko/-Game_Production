#pragma once
#include "memory"
#include "BaseScene.h"
#include "GameTask.h"
#include "Player.h"
#include "Sprite.h"
#include "Timer.h"

#define BC_SHEETS_NUMBER 2

class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();
	void Initialize(void);
	void Update(Button button, VECTOR screen);
	void TransltionScene(void);
	void Draw(void);
	Scene GetScene(void) { return scene; };
private:
	Sprite bcGround[BC_SHEETS_NUMBER];

	VECTOR screen;
	int move;
	std::unique_ptr<Timer> timer;
	std::unique_ptr<Player> player;
};

