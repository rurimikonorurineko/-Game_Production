#include "Player.h"
#include "ImageMng.h"

#define GRAND_OFSEET 1.5

Player::Player()
{
	player.pos = { 0,0,0 };
	player.Graph = 0;
	player.H = 0;
	player.W = 0;
	Initialize();
}


Player::~Player()
{
}

void Player::Initialize(void)
{
	player.Graph = ImageMng::GetInstance().GetID("image/player.png")[0];
	GetGraphSize(player.Graph, &player.H, &player.W);
	//マジックナンバーあとで何とかする
	//1316(スクリーンの横幅)
	//593(スクリーンの縦幅)
	player.pos.x = 1316 / 2;
	player.pos.y = 593 - player.H * GRAND_OFSEET;
	jumpFlag = false;


}

void Player::Update(Button button, VECTOR screen)
{
	this->screen = screen;
	if (button.nowButton.Space == true && button.oldButton.Space == false)
	{
		jumpFlag = true;
	}
	if (jumpFlag == true)
	{
		Jump();
	}
}

int Player::Jump(void)
{

	return 0;
}

int Player::AdjustChair(void)
{
	return 0;
}

bool Player::CheckHit(VECTOR pos, std::string comparer)
{
	bool hitflag = false;
	if (comparer == "Boss")
	{

	}
	if (comparer == "Attack")
	{

	}
	if (comparer == "Item")
	{

	}

	return hitflag;
}

int Player::BescaredBossAttack(void)
{
	return 0;
}

int Player::PickupItem(void)
{
	return 0;
}

void Player::Draw(void)
{
	DrawGraph(player.pos.x, player.pos.y, player.Graph, true);
}