#include "TypeSlash.h"
#include "ImageMng.h"
#include "Player.h"


TypeSlash::TypeSlash()
{
}

TypeSlash::TypeSlash(VECTOR screen, Sprite sboss):Attack(screen, sboss)
{
	slattack.pos = { 0,0,0 };
	slattack.Graph = 0;
	slattack.W = 0;
	slattack.H = 0;
	this->screen = screen;
	Initialize(sboss);
}


TypeSlash::~TypeSlash()
{
}

void TypeSlash::Initialize(Sprite sboss)
{
	//�摜��ǂݍ��݁��摜�T�C�Y�擾
	slattack.Graph = ImageMng::GetInstance().GetID("image/slash.png")[0];
	GetGraphSize(slattack.Graph, &slattack.W, &slattack.H);
	SetBeginPos(sboss);
	this->moveAttack = Attack::moveAttack;

	//�t���O�ނ̏�����
	deleteFlag = false;
}

//�����ʒu��ݒ肷��
void TypeSlash::SetBeginPos(Sprite sboss)
{
	slattack.pos = {sboss.pos.x + sboss.W,sboss.pos.y+sboss.H /2 - slattack.H /2};
}

void TypeSlash::Update(std::unique_ptr<Player>& player)
{
	//�v���C���[���ǁA���ɓ���������t���O�𗧂Ă�
	if (player->CheckHit(slattack, "ATTACK") || slattack.pos.x > screen.x || slattack.pos.y > screen.y)
	{
		deleteFlag = true;
	}
	//�U���̈ړ������ɔ��
	MoveAttack(player->GetPlayerPos());
}

void TypeSlash::Draw(void)
{
	DrawGraph(slattack.pos.x, slattack.pos.y, slattack.Graph, true);
}

void TypeSlash::MoveAttack(VECTOR pPos)
{
	slattack.pos.x += moveAttack * 2;
}