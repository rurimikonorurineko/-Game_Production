#include "DxLib.h"
#include "GameScene.h"
#include "ImageMng.h"
#include "Timer.h"

#define SPLIT_X 16	//地面ラインのX方向分割数
#define SPLIT_Y 5	//地面ラインのY方向分割数

#define SCROLL_ROTATIONS_NUMBER 2	//背景の1フレームの移動数
#define GROUND_SIZE_PERCENTT 8		//分割

GameScene::GameScene()
{
	
}

GameScene::GameScene(VECTOR screen)
{
	this->screen = screen;
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
//イニシャライズ
void GameScene::Initialize(void)
{
	for (int i = 0; i < BC_SHEETS_NUMBER; i++)
	{
		//背景の画像のセットと画像サイズの取得
		bcGround[i].Graph = ImageMng::GetInstance().GetID("image/bcGround.png")[0];
		GetGraphSize(bcGround[i].Graph, &bcGround[i].W, &bcGround[i].H);
		if (i == BC_SHEETS_NUMBER - 1)
		{
			bcGround[i].pos.x += bcGround[i].W;
		}
	}
	player = std::make_unique<Player>(screen);
	boss = std::make_unique<Boss>(screen);
	move = 0;
}
//更新
void GameScene::Update(Button button, std::unique_ptr<Timer>& timer)
{
 	timer->Update();
	player->Update(button);
	boss->Update(button, player, timer);
	scene = Scene::None;
	//ボスに当たっていたらリザルトシーンをセットする関数に飛ぶ
	if (player->GetHitBoss())
	{
		TransltionScene();
	}
	//背景が左端まで来たら右端に移す
	for (int i = 0; i < BC_SHEETS_NUMBER; i++)
	{
		bcGround[i].pos.x -= SCROLL_ROTATIONS_NUMBER;
		if (bcGround[i].pos.x <= -bcGround[i].W)
		{
			bcGround[i].pos.x = bcGround[i].W - 5;
		}
	}
}
//リザルトシーンをセットする
void GameScene::TransltionScene(void)
{
 	scene = Scene::Result;
}
//描画
void GameScene::Draw(void)
{
	//背景の描画
	for (int i = 0; i < BC_SHEETS_NUMBER; i++)
	{
		DrawGraph(bcGround[i].pos.x, bcGround[i].pos.y, bcGround[i].Graph, false);
	}
	// 足場一面のBOX
	DrawBox(0, screen.y - screen.y / GROUND_SIZE_PERCENTT,
			screen.x, screen.y,GetColor(224,216,203),true);
	//縦
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
	//横
	int hline = (screen.y - screen.y * (GROUND_SIZE_PERCENTT -1) / GROUND_SIZE_PERCENTT) /4;
	for (int i = 0; i < SPLIT_Y; i++)
	{
		DrawBox(0, first + (hline * i)
			   , screen.x, first + (hline * i) +2
			   , GetColor(200, 200, 200), true);
	}
	player->Draw();
	boss->Draw();
}
