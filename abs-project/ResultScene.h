#pragma once
#include "DxLib.h"
#include "Sprite.h"
#include "BaseScene.h"
#include "GameTask.h"

class ResultScene :
	public BaseScene
{
public:
	ResultScene();
	ResultScene(VECTOR screen);
	~ResultScene();
	void Update(Button button, std::unique_ptr<Timer>& timer);
	void TransltionScene(Scene scene);			//���̃V�[���̃Z�b�g
	void Draw(void);
	Scene GetScene(void) { return scene; };		//�Z�b�g����Ă���V�[����n��
	void ConversionTitle(void);					//�^�C�g���ւ̃Z�b�g�֐�
	void ConversionGame(void);					//�Q�[���ւ̃Z�b�g�֐�
private:
	void Initialize(void);					//�C�j�V�����C�Y
	void DrawLineBox(Sprite transGraph);	//�l�p�g����\��

	Sprite workPlayerGraph;				//�d���ɕ߂܂����v���C���\
	Sprite transTitleGraph;				//�^�C�g���J�ڑI�����̃{�^��
	Sprite transGameGraph;				//�Q�[���J�ڑI�����̃{�^��
	bool transitionFlag_Title;			//�^�C�g���ւ̃Z�b�g
	bool transitionFlag_Game;			//�Q�[���ւ̃Z�b�g
	int timerHour, timerMin, timerSec;	//�^�C�}�[�̒��g���i�[

	VECTOR screen;			//��ʃT�C�Y
};

