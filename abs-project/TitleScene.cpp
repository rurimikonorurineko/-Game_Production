#include "DxLib.h"
#include "TitleScene.h"


TitleScene::TitleScene()
{
}

TitleScene::TitleScene(VECTOR screen)
{
	this->screen = screen;
	count = 0;
}


TitleScene::~TitleScene()
{
}
//�C�j�V�����C�Y
void TitleScene::Initialize(void)
{
}
//�X�V
void TitleScene::Update(Button button, std::unique_ptr<Timer>& timer)
{
	scene = Scene::None;
	//space�������ꂽ��Q�[���V�[�����Z�b�g����֐��ɔ��
	if (button.nowButton.Space == true && button.oldButton.Space == false)
	{
		TransltionScene();
	}
}
//�Q�[���V�[�����Z�b�g����
void TitleScene::TransltionScene(void)
{
 	scene = Scene::Game;
}
//�`��
void TitleScene::Draw(void)
{
	if ((count++ /30) %2 == 0)
	{
		DrawString(screen.x / 2 - 20, screen.y - 100, "please_push_space", 0xffffff, true);
	}
}