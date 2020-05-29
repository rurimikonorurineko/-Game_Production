#include "DxLib.h"
#include "ResultScene.h"



ResultScene::ResultScene()
{
	transitionFlag_Title = false;
	transitionFlag_Game = false;
}


ResultScene::~ResultScene()
{
}

void ResultScene::Update(Button button)
{
	if (button.nowButton.Up_Chair == true)
	{
		ConversionTitle();
	}
	if (button.nowButton.Down_Chair == true)
	{
		ConversionGame();
	}
	scene = Scene::None;
	if (button.nowButton.Space == true && button.oldButton.Space == false)
	{
		if (transitionFlag_Title)
		{
			TransltionScene(Scene::Title);
		}
		else if (transitionFlag_Game)
		{
			TransltionScene(Scene::Game);
		}
		else
		{
			TransltionScene(Scene::Title);
		}
	}
}

void ResultScene::TransltionScene(Scene scene)
{
	this->scene = scene;
}

void ResultScene::Draw(void)
{
	
}

void ResultScene::ConversionTitle(void)
{
	transitionFlag_Title = true;
	transitionFlag_Game = false;
}

void ResultScene::ConversionGame(void)
{
	transitionFlag_Title = false;
	transitionFlag_Game = true;
}
