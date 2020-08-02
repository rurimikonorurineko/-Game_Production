#pragma once
#include "memory"
#include "BaseScene.h"
#include "GameTask.h"
#include "Player.h"
#include "Boss.h"
#include "Sprite.h"

#define BC_SHEETS_NUMBER 2		//�w�i�̖���

class GameScene :
	public BaseScene
{
public:
	GameScene();
	GameScene(VECTOR screen);
	~GameScene();
	void Initialize(void);
	void Update(Button button, std::unique_ptr<Timer>& timer);
	void TransltionScene(void);				//���̃V�[���̃Z�b�g
	void Draw(void);
	Scene GetScene(void) { return scene; };	//�Z�b�g����Ă���V�[����n��
private:
	Sprite bcGround[BC_SHEETS_NUMBER];	//�w�i

	VECTOR screen;						//��ʃT�C�Y
	int move;								
	std::unique_ptr<Player> player;
	std::unique_ptr<Boss> boss;
};

