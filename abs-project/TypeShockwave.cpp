#include "TypeShockwave.h"
#include "ImageMng.h"
#include "Player.h"


TypeShockwave::TypeShockwave()
{
}

TypeShockwave::TypeShockwave(VECTOR screen, Sprite sboss):Attack(screen, sboss)
{
	swattack.pos = { 0,0,0 };
	swattack.Graph = 0;
	swattack.W = 0;
	swattack.H = 0;
	this->screen = screen;
	Initialize(sboss);
}


TypeShockwave::~TypeShockwave()
{
}

void TypeShockwave::Initialize(Sprite sboss)
{
	//�摜��ǂݍ��݁��摜�T�C�Y�擾
	swattack.Graph = ImageMng::GetInstance().GetID("image/shockwave.png")[0];
	GetGraphSize(swattack.Graph, &swattack.W, &swattack.H);
	SetBeginPos(sboss);
	this->moveAttack = Attack::moveAttack;

	//�t���O�ނ̏�����
	deleteFlag = false;
}

//�����ʒu��ݒ肷��
void TypeShockwave::SetBeginPos(Sprite sboss)
{
	swattack.pos = {sboss.pos.x + sboss.W, (float)(sboss.pos.y + sboss.H - swattack.H *1.5)};
}

void TypeShockwave::Update(std::unique_ptr<Player>& player)
{
	//�v���C���[���ǁA���ɓ���������t���O�𗧂Ă�
	if (player->CheckHit(swattack, "ATTACK") || swattack.pos.x > screen.x || swattack.pos.y > screen.y)
	{
		deleteFlag = true;
	}
	//�U���̈ړ������ɔ��
	MoveAttack(player->GetPlayerPos());
}

void TypeShockwave::Draw(void)
{
	DrawGraph(swattack.pos.x, swattack.pos.y, swattack.Graph, true);
}

//�U���𓮂���
void TypeShockwave::MoveAttack(VECTOR pPos)
{
	swattack.pos.x += moveAttack * 2;
}