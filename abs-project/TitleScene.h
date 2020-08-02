#pragma once
#include "BaseScene.h"
#include "GameTask.h"

class TitleScene :
	public BaseScene
{
public:
	TitleScene();
	TitleScene(VECTOR screen);
	~TitleScene();
	void Initialize(void);
	void Update(Button button, std::unique_ptr<Timer>& timer);
	void TransltionScene(void);					//���̃V�[���̃Z�b�g
	void Draw(void);
	Scene GetScene(void) { return scene; };		//�Z�b�g����Ă���V�[����n��
private:
	VECTOR screen;		//��ʃT�C�Y
	int count;			//�_�ŃJ�E���^
};

