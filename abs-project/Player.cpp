#include "Player.h"



Player::Player()
{
}


Player::~Player()
{
}

void Player::Update(void)
{
}

void Player::Draw(void)
{
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
	if (comparer == "Boss")
	{

	}
	if (comparer == "Attack")
	{

	}
	if (comparer == "Item")
	{

	}

	return false;
}

int Player::BescaredBossAttack(void)
{
	return 0;
}

int Player::PickupItem(void)
{
	return 0;
}
