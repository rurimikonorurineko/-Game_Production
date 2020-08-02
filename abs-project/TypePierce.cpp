#include "TypePierce.h"
#include "ImageMng.h"
#include "Player.h"

#define PAI 3.141592653589793	//�~����(��)
#define ANGLE_MAX 360			//����̊p�x

TypePierce::TypePierce()
{
}

TypePierce::TypePierce(VECTOR screen, Sprite sboss):Attack(screen, sboss)
{
	pattack.pos = { 0,0,0 };
	pattack.Graph = 0;
	pattack.W = 0;
	pattack.H = 0;
	this->screen = screen;
	move = { 0,0,0 };
	rad = 0;
	Initialize(sboss);
}


TypePierce::~TypePierce()
{
}

void TypePierce::Initialize(Sprite sboss)
{
	//�摜��ǂݍ��݁��摜�T�C�Y�擾
	pattack.Graph = ImageMng::GetInstance().GetID("image/pierce.png")[0];
	GetGraphSize(pattack.Graph, &pattack.W, &pattack.H);
	SetBeginPos(sboss);
	this->moveAttack = Attack::moveAttack;

	//�t���O�ނ̏�����
	deleteFlag = false;
	psFlag = false;
}

//�����ʒu��ݒ肷��
void TypePierce::SetBeginPos(Sprite sboss)
{
	pattack.pos = { pattack.pos.x - pattack.W, pattack.pos.y - pattack.H };
}

void TypePierce::Update(std::unique_ptr<Player>& player)
{
	//�v���C���[���ǁA���ɓ���������t���O�𗧂Ă�
	if (player->CheckHit(pattack, "ATTACK") || pattack.pos.x > screen.x || pattack.pos.y > screen.y)
	{
		deleteFlag = true;
	}
	if (psFlag == false)
	{
		//�U���̈ړ������ɔ��
		MoveAttack(player->GetPlayerPos());
	}
	else
	{
		pattack.pos = VAdd(pattack.pos, VScale(move, moveAttack));
	}
}

void TypePierce::Draw(void)
{ 
	DrawRotaGraph(pattack.pos.x, pattack.pos.y,1.0, rad, pattack.Graph, true);
}

void TypePierce::MoveAttack(VECTOR pPos)
{
	// ���@�_���̍U��

	//1,�n�_����I�_�܂ł̈ړ��x�N�g�������
	VECTOR v = VSub(pPos, pattack.pos);
	//2.1�ō�����ړ��x�N�g���𐳋K������
	move = VNorm(v);
	//3,2�ō�����ړ����K���x�N�g���𕪊����Ďn�_�x�N�g���ɓ���Ĉړ�������
	pattack.pos = VAdd(pattack.pos, VScale(move, moveAttack *2));
	psFlag = true;
	//MakePierceRad(move);
	rad = ANGLE_MAX *1 /8 * PAI / (ANGLE_MAX / 2);
}

void TypePierce::MakePierceRad(VECTOR toPlayerVec)
{
	//�@���x�N�g���𐶐�
	VECTOR n = { pattack.pos.x +10, pattack.pos.y, 0 };
	VECTOR nomal = VSub(n, pattack.pos);
	//�@���x�N�g���𐳋K��
	nomal = VNorm(nomal);
	//�p�x����(���W�A��)
	rad = VRad(nomal,toPlayerVec);
}