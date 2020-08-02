#include <stdio.h>
#include <time.h>
#include "TypeShot.h"
#include "ImageMng.h"
#include "Player.h"


TypeShot::TypeShot()
{
}

TypeShot::TypeShot(VECTOR screen, Sprite sboss):Attack(screen, sboss)
{
	sattack.pos = { 0,0,0 };
	sattack.Graph = 0;
	sattack.W = 0;
	sattack.H = 0;
	this->screen = screen;
	Initialize(sboss);
}


TypeShot::~TypeShot()
{
}

void TypeShot::Initialize(Sprite sboss)
{
	//�摜��ǂݍ��݁��摜�T�C�Y�擾
	sattack.Graph = ImageMng::GetInstance().GetID("image/shot1.png")[0];
	GetGraphSize(sattack.Graph, &sattack.W, &sattack.H);
	SetBeginPos(sboss);
	this->moveAttack = Attack::moveAttack;
	//�t���O�ނ̏�����
	deleteFlag = false;
}

//�����ʒu��ݒ肷��
void TypeShot::SetBeginPos(Sprite sboss)
{
	sattack.pos = {sboss.pos.x + sboss.W ,RandomPosY(sboss),0 };
}

//�U����Y���W�������_����������
float TypeShot::RandomPosY(Sprite sboss)
{
	srand((unsigned int)time(NULL)*rand());
	int py = 0;
	int i = screen.y / sattack.H;
	py = ((rand() % i) * sattack.H);
 	return py;
}

void TypeShot::Update(std::unique_ptr<Player>& player)
{
	//�v���C���[���ǁA���ɓ���������t���O�𗧂Ă�
	if (player->CheckHit(sattack, "ATTACK") || sattack.pos.x > screen.x || sattack.pos.y > screen.y)
	{
		deleteFlag = true;
	}
	//�U���̈ړ������ɔ��
	MoveAttack(player->GetPlayerPos());
}

void TypeShot::Draw(void)
{
	DrawGraph(sattack.pos.x, sattack.pos.y, sattack.Graph, true);
}

//�U���𓮂���
void TypeShot::MoveAttack(VECTOR pPos)
{
	sattack.pos.x += moveAttack;
}
