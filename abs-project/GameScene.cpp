#include "DxLib.h"
#include "GameScene.h"
#include "ImageMng.h"
#include "Timer.h"

#define SCROLL_ROTATIONS_NUMBER 2

GameScene::GameScene()
{
	for (int i = 0; i < BC_SHEETS_NUMBER; i++)
	{
		bcGround[i].pos = { 0,0,0 };
		bcGround[i].Graph = 0;
		bcGround[i].H = 0;
		bcGround[i].W = 0;
		Initialize();
	}
}


GameScene::~GameScene()
{
}

void GameScene::Initialize(void)
{
	for (int i = 0; i < BC_SHEETS_NUMBER; i++)
	{
		bcGround[i].Graph = ImageMng::GetInstance().GetID("image/bcGround.png")[0];
		GetGraphSize(bcGround[i].Graph, &bcGround[i].W, &bcGround[i].H);
		if (i == BC_SHEETS_NUMBER - 1)
		{
			bcGround[i].pos.x += bcGround[i].W;
		}
	}
	timer = std::make_unique<Timer>();
	player = std::make_unique<Player>();
}

void GameScene::Update(Button button, VECTOR screen)
{
	this->screen = screen;
	timer->Update();
	player->Update(button, screen);
	scene = Scene::None;
	if (button.nowButton.Space == true && button.oldButton.Space == false)
	{
		TransltionScene();
	}
	for (int i = 0; i < BC_SHEETS_NUMBER; i++)
	{
		bcGround[i].pos.x -= SCROLL_ROTATIONS_NUMBER;
		if (bcGround[i].pos.x <= -bcGround[i].W)
		{
			bcGround[i].pos.x = bcGround[i].W - 1;
		}
	}
}

void GameScene::TransltionScene(void)
{
 	scene = Scene::Result;
}

void GameScene::Draw(void)
{
	for (int i = 0; i < BC_SHEETS_NUMBER; i++)
	{
		DrawGraph(bcGround[i].pos.x, bcGround[i].pos.y, bcGround[i].Graph, false);
	}
	DrawBox(0, screen.y - screen.y / 4, screen.x, screen.y,GetColor(224,216,203),true);
	timer->DrawTimer();
	player->Draw();
}
