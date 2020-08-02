#include "DxLib.h"
#include "GameScene.h"
#include "ImageMng.h"
#include "Timer.h"

#define SPLIT_X 16	//�n�ʃ��C����X����������
#define SPLIT_Y 5	//�n�ʃ��C����Y����������

#define SCROLL_ROTATIONS_NUMBER 2	//�w�i��1�t���[���̈ړ���
#define GROUND_SIZE_PERCENTT 8		//����

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
//�C�j�V�����C�Y
void GameScene::Initialize(void)
{
	for (int i = 0; i < BC_SHEETS_NUMBER; i++)
	{
		//�w�i�̉摜�̃Z�b�g�Ɖ摜�T�C�Y�̎擾
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
//�X�V
void GameScene::Update(Button button, std::unique_ptr<Timer>& timer)
{
 	timer->Update();
	player->Update(button);
	boss->Update(button, player, timer);
	scene = Scene::None;
	//�{�X�ɓ������Ă����烊�U���g�V�[�����Z�b�g����֐��ɔ��
	if (player->GetHitBoss())
	{
		TransltionScene();
	}
	//�w�i�����[�܂ŗ�����E�[�Ɉڂ�
	for (int i = 0; i < BC_SHEETS_NUMBER; i++)
	{
		bcGround[i].pos.x -= SCROLL_ROTATIONS_NUMBER;
		if (bcGround[i].pos.x <= -bcGround[i].W)
		{
			bcGround[i].pos.x = bcGround[i].W - 5;
		}
	}
}
//���U���g�V�[�����Z�b�g����
void GameScene::TransltionScene(void)
{
 	scene = Scene::Result;
}
//�`��
void GameScene::Draw(void)
{
	//�w�i�̕`��
	for (int i = 0; i < BC_SHEETS_NUMBER; i++)
	{
		DrawGraph(bcGround[i].pos.x, bcGround[i].pos.y, bcGround[i].Graph, false);
	}
	// �����ʂ�BOX
	DrawBox(0, screen.y - screen.y / GROUND_SIZE_PERCENTT,
			screen.x, screen.y,GetColor(224,216,203),true);
	//�c
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
	//��
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
