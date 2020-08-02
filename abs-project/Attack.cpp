#include <string>
#include "Attack.h"
#include "Player.h"
#include "Timer.h"
#include "ImageMng.h"

#define MOVEATTACK 5		//攻撃の移動スピード量
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


