#include "DxLib.h"
#include "GameScene.h"
#include "ImageMng.h"
#include "Timer.h"

#define SPLIT_X 16
#define SPLIT_Y 5

#define SCROLL_ROTATIONS_NUMBER 2
#define GROUND_SIZE_PERCENTT 8/*•ªŠ„*/

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
	move = 0;
}

void GameScene::Update(Button button, VECTOR screen)
{
	this->screen = screen;
	timer->Update();
	player->Update(button, screen);
	scene = Scene::None;
	//if (button.nowButton.Space == true && button.oldButton.Space == false)
	{
		//TransltionScene();
	}
	for (int i = 0; i < BC_SHEETS_NUMBER; i++)
	{
		bcGround[i].pos.x -= SCROLL_ROTATIONS_NUMBER;
		if (bcGround[i].pos.x <= -bcGround[i].W)
		{
			bcGround[i].pos.x = bcGround[i].W - 5;
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
	// ‘«êˆê–Ê‚ÌBOX
	DrawBox(0, screen.y - screen.y / GROUND_SIZE_PERCENTT,
			screen.x, screen.y,GetColor(224,216,203),true);
	//c
	int first = screen.y - screen.y / GROUND_SIZE_PERCENTT;
	int pline = (screen.y - screen.y * 3 / GROUND_SIZE_PERCENTT) / GROUND_SIZE_PERCENTT;
	move += SCROLL_ROTATIONS_NUMBER;
	if (move >= screen.x / SPLIT_X)
	{
		move = 0;
	}
	for (int i = 0; i < SPLIT_X +2; i++)
	{
		DrawLine((screen.x /SPLIT_X) *i - move, first
			  , ((screen.x /SPLIT_X) *(i+1)) +2 - move, screen.y
			  , GetColor(200, 200, 200), true);
	}
	//‰¡
	int hline = (screen.y - screen.y * (GROUND_SIZE_PERCENTT -1) / GROUND_SIZE_PERCENTT) /4;
	for (int i = 0; i < SPLIT_Y; i++)
	{
		DrawBox(0, first + (hline * i)
			   , screen.x, first + (hline * i) +2
			   , GetColor(200, 200, 200), true);
	}
	timer->DrawTimer();
	player->Draw();
}
