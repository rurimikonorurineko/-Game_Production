#include "DxLib.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "ResultScene.h"
#include "ImageMng.h"
#include "Timer.h"


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

//�N���G�C�g
void GameTask::Create(void)
{
	if (!s_Instance)
	{
		s_Instance = new GameTask();
	}
}
//�f�X�g���C
void GameTask::Destroy(void)
{
	if (s_Instance)
	{
		delete s_Instance;
	}
	s_Instance = nullptr;
}
//�C�j�V�����C�Y
void GameTask::Initialize(void)
{
	screen = { SCREEN_SIZE_X, SCREEN_SIZE_Y, 0 };
}
//����(�Q�[���̃��[�v)
void GameTask::Run(void)
{
	Update();
}
//�X�V
int GameTask::Update(void)
{
	//�{�^���̍X�V����
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
	SetWindowText("�x�e������I�t�B�X���Ă̐w");
	if (DxLib_Init() == -1) return false;	// DXײ���؏���������
	SetDrawScreen(DX_SCREEN_BACK);		// �ЂƂ܂��ޯ��ޯ̧�ɕ`��
	Scene = &GameTask::TitleInit;
	Initialize();
	return true;
}
//�^�C�g���C�j�b�g
int GameTask::TitleInit(void)
{
	title = std::make_unique<TitleScene>(screen);
	timer = std::make_unique<Timer>(screen);
	Scene = &GameTask::Title;
	return 0;
}
//�^�C�g��
int GameTask::Title(void)
{
	//�X�V
	title->Update(controlButton,timer);
	if (title->GetScene() == Scene::Game)
	{
 		Scene = &GameTask::GameInit;
	}
	//�`��
	// ��ʂ�������(�^�����ɂ���)
	ClearDrawScreen();
	title->Draw();
	// ����ʂ̓��e��\��ʂɃR�s�[����i�`��̊m��j.
	ScreenFlip();
	return 0;
}
//�Q�[���C�j�b�g
int GameTask::GameInit(void)
{
	game = std::make_unique<GameScene>(screen);
	Scene = &GameTask::Game;
	return 0;
}
//�Q�[��
int GameTask::Game(void)
{
	//�X�V
	game->Update(controlButton,timer);
	if (game->GetScene() == Scene::Result)
	{
		Scene = &GameTask::ResultInit;
	}
	//�`��
	// ��ʂ�������(�^�����ɂ���)
	ClearDrawScreen();
	game->Draw();
	timer->DrawTimer();
	// ����ʂ̓��e��\��ʂɃR�s�[����i�`��̊m��j.
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
	//�X�V
	result->Update(controlButton, timer);
	if (result->GetScene() == Scene::Title)
	{
		Scene = &GameTask::TitleInit;
	}
	else if (result->GetScene() == Scene::Game)
	{
		Scene = &GameTask::GameInit;
	}
	//�`��
	// ��ʂ�������(�^�����ɂ���)
	ClearDrawScreen();
	result->Draw();
	// ����ʂ̓��e��\��ʂɃR�s�[����i�`��̊m��j.
	ScreenFlip();
	return 0;
}
//�{�^���̍X�V
void GameTask::UpdateButton(void)
{
	controlButton.oldButton = controlButton.nowButton;

	controlButton.nowButton.Space = false;
	controlButton.nowButton.Up_Chair = false;
	controlButton.nowButton.Down_Chair = false;

	if (CheckHitKey(KEY_INPUT_SPACE))				//�X�y�[�X
	{
		controlButton.nowButton.Space = true;
	}
	if (CheckHitKey(KEY_INPUT_UP))					//��
	{
		controlButton.nowButton.Up_Chair = true;
	}
	if (CheckHitKey(KEY_INPUT_DOWN))				//��
	{
		controlButton.nowButton.Down_Chair = true;
	}
}

