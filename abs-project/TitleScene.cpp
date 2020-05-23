#include "TitleScene.h"


TitleScene::TitleScene()
{
}


TitleScene::~TitleScene()
{
}

void TitleScene::Update(Button button)
{
	if (button.nowButton.Space == true && button.oldButton.Space == false)
	{
		TransltionScene();
	}
}

void TitleScene::TransltionScene(void)
{
	scene = Scene::Game;
}

void TitleScene::Draw(void)
{
}