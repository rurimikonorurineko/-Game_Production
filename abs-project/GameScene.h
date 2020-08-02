#pragma once
#include "memory"
#include "BaseScene.h"
#include "GameTask.h"
#include "Player.h"
#include "Boss.h"
#include "Sprite.h"

#define BC_SHEETS_NUMBER 2		//背景の枚数

class GameScene :
	public BaseScene
{
public:
	GameScene();
	GameScene(VECTOR screen);
	~GameScene();
	void Initialize(void);
	void Update(Button button, std::unique_ptr<Timer>& timer);
	void TransltionScene(void);				//次のシーンのセット
	void Draw(void);
	Scene GetScene(void) { return scene; };	//セットされているシーンを渡す
private:
	Sprite bcGround[BC_SHEETS_NUMBER];	//背景

	VECTOR screen;						//画面サイズ
	int move;								
	std::unique_ptr<Player> player;
	std::unique_ptr<Boss> boss;
};

