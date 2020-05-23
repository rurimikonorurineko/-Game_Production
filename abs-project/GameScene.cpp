#include "GameScene.h"



GameScene::GameScene()
{
}


GameScene::~GameScene()
{
}

void GameScene::Update(Button button)
{
	if (button.nowButton.Space == true && button.oldButton.Space == false)
	{
		TransltionScene();
	}
}

void GameScene::TransltionScene(void)
{
 	scene = Scene::Result;
}

void GameScene::Draw(void)
{
}
