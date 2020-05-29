#include "DxLib.h"
#include "TitleScene.h"


TitleScene::TitleScene()
{
}


TitleScene::~TitleScene()
{
}

void TitleScene::Initialize(void)
{
}

void TitleScene::Update(Button button)
{
	scene = Scene::None;
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
	DrawString(150, 150, scene == Scene::Title ? "TITLE" : scene == Scene::Game ? "GAME" : "RESULT",true);
}