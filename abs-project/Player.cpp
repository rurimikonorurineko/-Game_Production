#include "Player.h"
#include "ImageMng.h"

#define GRAND_OFSEET 1.2
#define JUMP_FIRST_HIGHT 100
#define JUMP_COUNT 3
#define GRAVITY 0.2

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
	GetGraphSize(player.Graph, &player.W, &player.H);
	//�}�W�b�N�i���o�[���Ƃŉ��Ƃ�����
	//1316(�X�N���[���̉���)
	//593(�X�N���[���̏c��)
	player.pos.x = 1316 / 2;
	player.pos.y = 593 - player.H * GRAND_OFSEET;
	jumpFlag = false;
	jumpCount = 0;
	freeFall = 0;
}

void Player::Update(Button button, VECTOR screen)
{
	this->screen = screen;
	if (button.nowButton.Space == true && button.oldButton.Space == false)
	{
		jumpFlag = true;
		if (jumpCount < JUMP_COUNT){
			player.pos.y -= JUMP_FIRST_HIGHT;
			jumpCount++;
			freeFall = 0;
		}
	}
	if (jumpFlag == true)
	{
		Jump();
	}
}

int Player::Jump(void)
{
	freeFall += GRAVITY;
	player.pos.y += freeFall;
	if (CheckHitGrand())
	{
		jumpFlag = false;
		jumpCount = 0;
		freeFall = 0;
	}
	return 0;
}

int Player::AdjustChair(void)
{
	return 0;
}

bool Player::CheckHit(Sprite compSP, std::string comparer)
{
	bool hitflag = false;
	//�����蔻������
	//�v���C���[�̍��ォ��E���̒��ɓ����Ă��邩
	if ((((player.pos.x				< compSP.pos.x + compSP.W)		/*�v���C���[�̍��� < pos�̉E��*/
	&&	  (player.pos.y				< compSP.pos.y + compSP.H))		
	&&	 ((player.pos.x + player.W	> compSP.pos.x)					/*�v���C���[�̉E�� > pos�̍���*/
	&&	  (player.pos.y + player.H	> compSP.pos.y)))
	//�v���C���[�̍�������E��̒��ɓ����Ă��邩
	||	 (((player.pos.x			< compSP.pos.x + compSP.W)		/*�v���C���[�̍��� > pos�̉E��*/
	&&	   (player.pos.y + player.H	> compSP.pos.y))
	&&	  ((player.pos.x + player.W	> compSP.pos.x)					/*�v���C���[�̉E�� > pos�̍���*/
	&&	   (player.pos.y			< compSP.pos.y + compSP.H))))
	{
		hitflag = true;
	}
	else
	{
		hitflag = false;
	}

	//���ꂼ��̏���
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

bool Player::CheckHitGrand(void)
{
	if (player.pos.y >= screen.y - player.H * GRAND_OFSEET)
	{
		return true;
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

void Player::Draw(void)
{
	DrawGraph(player.pos.x, player.pos.y, player.Graph, true);
}