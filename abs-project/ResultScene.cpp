#include "ResultScene.h"



ResultScene::ResultScene()
{
}


ResultScene::~ResultScene()
{
}

void ResultScene::Update(Button button)
{
	if (button.nowButton.Space == true && button.oldButton.Space == false)
	{
		TransltionScene();
	}
}

void ResultScene::TransltionScene(void)
{
	scene = Scene::Title;
}

void ResultScene::Draw(void)
{
}
