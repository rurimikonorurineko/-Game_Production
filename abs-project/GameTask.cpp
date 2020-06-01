#include "DxLib.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "ResultScene.h"
#include "ImageMng.h"


#define SCREEN_SIZE_X 1316				// ��ʂ̉��T�C�Y
#define SCREEN_SIZE_Y 593				// ��ʂ̏c�T�C�Y

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
	// ���я���
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);		// 65536�FӰ�ނɐݒ�
	ChangeWindowMode(true);				// true:window�@false:�ٽ�ذ�
	SetWindowText("�x�e������");
	if (DxLib_Init() == -1) return false;	// DXײ���؏���������
	SetDrawScreen(DX_SCREEN_BACK);		// �ЂƂ܂��ޯ��ޯ̧�ɕ`��
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
	// ��ʂ�������(�^�����ɂ���)
	ClearDrawScreen();
	DrawString(50, 50, "Title", GetColor(255,0,0), false);
	title->Draw();
	// ����ʂ̓��e��\��ʂɃR�s�[����i�`��̊m��j.
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
	// ��ʂ�������(�^�����ɂ���)
	ClearDrawScreen();
	DrawString(50, 50, "Game", GetColor(255, 255, 255), false);
	game->Draw();
	// ����ʂ̓��e��\��ʂɃR�s�[����i�`��̊m��j.
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
	// ��ʂ�������(�^�����ɂ���)
	ClearDrawScreen();
	DrawString(50, 50, "Result", GetColor(255, 255, 255), false);
	result->Draw();
	// ����ʂ̓��e��\��ʂɃR�s�[����i�`��̊m��j.
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

