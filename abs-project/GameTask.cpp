#include "DxLib.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "ResultScene.h"
#include "ImageMng.h"
#include "Timer.h"


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

//クリエイト
void GameTask::Create(void)
{
	if (!s_Instance)
	{
		s_Instance = new GameTask();
	}
}
//デストロイ
void GameTask::Destroy(void)
{
	if (s_Instance)
	{
		delete s_Instance;
	}
	s_Instance = nullptr;
}
//イニシャライズ
void GameTask::Initialize(void)
{
	screen = { SCREEN_SIZE_X, SCREEN_SIZE_Y, 0 };
}
//ラン(ゲームのループ)
void GameTask::Run(void)
{
	Update();
}
//更新
int GameTask::Update(void)
{
	//ボタンの更新処理
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
	SetWindowText("休憩延長戦オフィス初夏の陣");
	if (DxLib_Init() == -1) return false;	// DXﾗｲﾌﾞﾗﾘ初期化処理
	SetDrawScreen(DX_SCREEN_BACK);		// ひとまずﾊﾞｯｸﾊﾞｯﾌｧに描画
	Scene = &GameTask::TitleInit;
	Initialize();
	return true;
}
//タイトルイニット
int GameTask::TitleInit(void)
{
	title = std::make_unique<TitleScene>(screen);
	timer = std::make_unique<Timer>(screen);
	Scene = &GameTask::Title;
	return 0;
}
//タイトル
int GameTask::Title(void)
{
	//更新
	title->Update(controlButton,timer);
	if (title->GetScene() == Scene::Game)
	{
 		Scene = &GameTask::GameInit;
	}
	//描画
	// 画面を初期化(真っ黒にする)
	ClearDrawScreen();
	title->Draw();
	// 裏画面の内容を表画面にコピーする（描画の確定）.
	ScreenFlip();
	return 0;
}
//ゲームイニット
int GameTask::GameInit(void)
{
	game = std::make_unique<GameScene>(screen);
	Scene = &GameTask::Game;
	return 0;
}
//ゲーム
int GameTask::Game(void)
{
	//更新
	game->Update(controlButton,timer);
	if (game->GetScene() == Scene::Result)
	{
		Scene = &GameTask::ResultInit;
	}
	//描画
	// 画面を初期化(真っ黒にする)
	ClearDrawScreen();
	game->Draw();
	timer->DrawTimer();
	// 裏画面の内容を表画面にコピーする（描画の確定）.
	ScreenFlip();
	return 0;
}

int GameTask::ResultInit(void)
{
	result = std::make_unique<ResultScene>(screen);
	Scene = &GameTask::Result;
	return 0;
}

int GameTask::Result(void)
{
	//更新
	result->Update(controlButton, timer);
	if (result->GetScene() == Scene::Title)
	{
		Scene = &GameTask::TitleInit;
	}
	else if (result->GetScene() == Scene::Game)
	{
		Scene = &GameTask::GameInit;
	}
	//描画
	// 画面を初期化(真っ黒にする)
	ClearDrawScreen();
	result->Draw();
	// 裏画面の内容を表画面にコピーする（描画の確定）.
	ScreenFlip();
	return 0;
}
//ボタンの更新
void GameTask::UpdateButton(void)
{
	controlButton.oldButton = controlButton.nowButton;

	controlButton.nowButton.Space = false;
	controlButton.nowButton.Up_Chair = false;
	controlButton.nowButton.Down_Chair = false;

	if (CheckHitKey(KEY_INPUT_SPACE))				//スペース
	{
		controlButton.nowButton.Space = true;
	}
	if (CheckHitKey(KEY_INPUT_UP))					//↑
	{
		controlButton.nowButton.Up_Chair = true;
	}
	if (CheckHitKey(KEY_INPUT_DOWN))				//↓
	{
		controlButton.nowButton.Down_Chair = true;
	}
}

