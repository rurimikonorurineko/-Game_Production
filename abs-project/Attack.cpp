#include <string>
#include "Attack.h"
#include "Player.h"
#include "Timer.h"
#include "ImageMng.h"

#define MOVEATTACK 5		//�U���̈ړ��X�s�[�h��
Attack::Attack()
{
}

Attack::Attack(VECTOR screen, Sprite sboss)
{
	this->screen = screen;
	moveAttack = MOVEATTACK;
	//Initialize(sboss);
}

Attack::~Attack()
{
}

void Attack::Initialize(Sprite sboss)
{
	
}
/*
void Attack::Draw(Sprite attack)
{
	DrawGraph(attack.pos.x, attack.pos.y, attack.Graph, false);
}
*/


