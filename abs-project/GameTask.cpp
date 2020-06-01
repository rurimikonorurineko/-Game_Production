#include "DxLib.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "ResultScene.h"
#include "ImageMng.h"


#define SCREEN_SIZE_X 1316				// 画面の横サイズ
#define SCREEN_SIZE_Y 593				// 画面の縦サイズ

GameTask *GameTask::s_Instance = nullptr;

GameTask::GameTask()
{
	System();
}


GameTask::~GameTask()
{
}


void GameTask::Create(void)
{
	if (!s_Instance)
	{
		s_Instance = new GameTask();
	}
}

void GameTask::Destroy(void)
{
	if (s_Instance)
	{
		delete s_Instance;
	}
	s_Instance = nullptr;
}

void GameTask::Initialize(void)
{
	title = std::make_unique<TitleScene>();
	game = std::make_unique<GameScene>();
	result = std::make_unique<ResultScene>();
}

void GameTask::Run(void)
{
	Update();
}

int GameTask::Update(void)
{
	UpdateButton();
	int scene_id;
	scene_id = (this->*Scene)();
	return scene_id;
}

int GameTask::System(void)
{
	// ｼｽﾃﾑ処理
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);		// 65536色ﾓｰﾄﾞに設定
	ChangeWindowMode(true);				// true:window　false:ﾌﾙｽｸﾘｰﾝ
	SetWindowText("休憩延長戦");
	if (DxLib_Init() == -1) return false;	// DXﾗｲﾌﾞﾗﾘ初期化処理
	SetDrawScreen(DX_SCREEN_BACK);		// ひとまずﾊﾞｯｸﾊﾞｯﾌｧに描画
	Scene = &GameTask::Title;
	Initialize();
	return true;
}

int GameTask::Title(void)
{
	title->Update(controlButton);
	if (title->GetScene() == Scene::Game)
	{
 		Scene = &GameTask::Game;
	}
	// 画面を初期化(真っ黒にする)
	ClearDrawScreen();
	DrawString(50, 50, "Title", GetColor(255,0,0), false);
	title->Draw();
	// 裏画面の内容を表画面にコピーする（描画の確定）.
	ScreenFlip();
	return 0;
}

int GameTask::Game(void)
{
	game->Update(controlButton);
	if (game->GetScene() == Scene::Result)
	{
		Scene = &GameTask::Result;
	}
	// 画面を初期化(真っ黒にする)
	ClearDrawScreen();
	DrawString(50, 50, "Game", GetColor(255, 255, 255), false);
	game->Draw();
	// 裏画面の内容を表画面にコピーする（描画の確定）.
	ScreenFlip();
	return 0;
}

int GameTask::Result(void)
{
	result->Update(controlButton);
	if (result->GetScene() == Scene::Title)
	{
		Scene = &GameTask::Title;
	}
	else if (result->GetScene() == Scene::Game)
	{
		Scene = &GameTask::Game;
	}
	// 画面を初期化(真っ黒にする)
	ClearDrawScreen();
	DrawString(50, 50, "Result", GetColor(255, 255, 255), false);
	result->Draw();
	// 裏画面の内容を表画面にコピーする（描画の確定）.
	ScreenFlip();
	return 0;
}

void GameTask::UpdateButton(void)
{
	controlButton.oldButton = controlButton.nowButton;

	controlButton.nowButton.Space = false;
	controlButton.nowButton.Up_Chair = false;
	controlButton.nowButton.Down_Chair = false;

	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		controlButton.nowButton.Space = true;
	}
	if (CheckHitKey(KEY_INPUT_UP))
	{
		controlButton.nowButton.Up_Chair = true;
	}
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		controlButton.nowButton.Down_Chair = true;
	}
}

