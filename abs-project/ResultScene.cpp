#include "DxLib.h"
#include "ImageMng.h"
#include "ResultScene.h"

#define FRAME 5
#define TIME_MAX 60

ResultScene::ResultScene()
{
}

ResultScene::ResultScene(VECTOR screen)
{
	this->screen = screen;
	//workPlayerGraph�̏�����
	workPlayerGraph.pos = { 0,0,0 };
	workPlayerGraph.Graph = workPlayerGraph.W = workPlayerGraph.H = 0;
	//transTitleGraph�̏�����
	transTitleGraph.pos = { 0,0,0 };
	transTitleGraph.Graph = transTitleGraph.W = transTitleGraph.H = 0;
	//transGameGraph�̏�����
	transTitleGraph.pos = { 0,0,0 };
	transTitleGraph.Graph = transTitleGraph.W = transTitleGraph.H = 0;

	//�C�j�V�����C�Y
	Initialize();
	//�t���O���̐ݒ�
	transitionFlag_Title = true;
	transitionFlag_Game = false;
	timerHour = timerMin = timerSec = 999;
	
}

ResultScene::~ResultScene()
{
}

//�C�j�V�����C�Y
void ResultScene::Initialize(void)
{
	//workPlayerGraph�̐ݒ�
	workPlayerGraph.Graph = ImageMng::GetInstance().GetID("image/gameover3.png")[0];
	GetGraphSize(workPlayerGraph.Graph, &workPlayerGraph.W, &workPlayerGraph.H);
	workPlayerGraph.pos = { (float)(screen.x - workPlayerGraph.W *1.25), 0 };
	//transTitleGraph�̐ݒ�
	transTitleGraph.Graph = ImageMng::GetInstance().GetID("image/title.png")[0];
	GetGraphSize(transTitleGraph.Graph, &transTitleGraph.W, &transTitleGraph.H);
	transTitleGraph.pos = {screen.x /5, screen.y *2 /6 - transTitleGraph.H /2 };
	//transGameGraph�̐ݒ�
	transGameGraph.Graph = ImageMng::GetInstance().GetID("image/game.png")[0];
	GetGraphSize(transGameGraph.Graph, &transGameGraph.W, &transGameGraph.H);
	transGameGraph.pos = {screen.x /5, screen.y * 4 /6 - transGameGraph.H /2 };
}


//�X�V
void ResultScene::Update(Button button, std::unique_ptr<Timer>& timer)
{
	if (!(timerHour != 999 && timerMin != 999 && timerSec != 999))
	{
		timerHour = timer->GetTimer().hour.actual;
		timerMin = timer->GetTimer().minute.actual;
		timerSec = timer->GetTimer().second.actual;
	}
	//�J�ڍ������߂�
	if (button.nowButton.Up_Chair == true)
	{
		ConversionTitle();
	}
	if (button.nowButton.Down_Chair == true)
	{
		ConversionGame();
	}
	scene = Scene::None;
	//�X�y�[�X�������ꂽ��J�ڂ���
	if (button.nowButton.Space == true && button.oldButton.Space == false)
	{
		//�����Ō��߂��J�ڐ�ɑJ�ڂ���
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
//���߂��J�ڐ���Z�b�g����
void ResultScene::TransltionScene(Scene scene)
{
	this->scene = scene;
}
//�`��
void ResultScene::Draw(void)
{
	DrawBox(0, 0, screen.x, screen.y, 0xffffff,true);
	DrawGraph(workPlayerGraph.pos.x, workPlayerGraph.pos.y, workPlayerGraph.Graph, false);
	//���U���g�\��
	if (timerHour <= 0)
	{
		DrawFormatString(screen.x *2 /3, screen.y - (screen.y - workPlayerGraph.H), 
						 0x000000, "%d��%d�b�x�e�Z�k", 
						 TIME_MAX - timerMin, TIME_MAX - timerSec);
	}
	else if(timerHour == 1 && timerMin == 0)
	{
		DrawString(screen.x *2 /3, screen.y - (screen.y - workPlayerGraph.H),
				   "�荏�ʂ�Ɏd���ĊJ", 0x000000);
	}
	else
	{
		DrawFormatString(screen.x *2 /3, screen.y - (screen.y - workPlayerGraph.H), 
						 0x000000, "%d��%d��%d�b�܂ŋx�e����", timerHour, timerMin, timerSec);
	}
	//�J�ڐ�I��\��
	if (transitionFlag_Title == true && transitionFlag_Game == false)
	{
		this->DrawLineBox(transTitleGraph);
	}
	else if(transitionFlag_Title == false && transitionFlag_Game == true)
	{
		this->DrawLineBox(transGameGraph);
	}
	else
	{
		this->DrawLineBox(transTitleGraph);
	}
	DrawGraph(transTitleGraph.pos.x, transTitleGraph.pos.y, transTitleGraph.Graph, true);
	DrawGraph(transGameGraph.pos.x, transGameGraph.pos.y, transGameGraph.Graph, true);
}

//�J�ڐ�̐ݒ��g���ň͂�
void ResultScene::DrawLineBox(Sprite transGraph)
{
	DrawBox(transGraph.pos.x - FRAME, transGraph.pos.y - FRAME,
			transGraph.pos.x + transGraph.W + FRAME, 
			transGraph.pos.y + transGraph.H + FRAME, 0x000000, true);
}

//�J�ڐ���^�C�g���ɃZ�b�g����
void ResultScene::ConversionTitle(void)
{
	transitionFlag_Title = true;
	transitionFlag_Game = false;
}

//�J�ڐ���Q�[���ɃZ�b�g����
void ResultScene::ConversionGame(void)
{
	transitionFlag_Title = false;
	transitionFlag_Game = true;
}
