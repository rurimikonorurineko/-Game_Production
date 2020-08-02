#include "Player.h"
#include "ImageMng.h"

#define GRAND_OFSEET 1.2		//�v���C���[�̑����Ƃ̂ǂ̂�����ɒn�ʂ�����̂������߂�
#define JUMP_FIRST_HIGHT 100	//�v���C���[���W�����v�������̏������x
#define JUMP_COUNT 3			//�A���W�����v�̉�
#define GRAVITY 0.2				//�d��
#define ST_MO_PLAYER 2			//�v���C���[���~�܂��Ă���Ƃ��Ƃ��̌㌳�̈ʒu�܂Ŗ߂鎞��1�t���[���̈ړ��l
#define AWAKENING_TIME 2		//�U���q�b�g��̊o������

Player::Player()
{
	
}

Player::Player(VECTOR screen)
{
	this->screen = screen;
	player.pos = { 0,0,0 };
	player.Graph = 0;
	player.H = 0;
	player.W = 0;
	Initialize();
}

Player::~Player()
{
}

//�C�j�V�����C�Y
void Player::Initialize(void)
{
	//�v���C���[�̒��g���Z�b�g
	player.Graph = ImageMng::GetInstance().GetID("image/player.png")[0];
	GetGraphSize(player.Graph, &player.W, &player.H);
	player.pos.x = screen.x / 2;
	player.pos.y = screen.y - player.H * GRAND_OFSEET;
	//�t���O�ނ��C�j�V�����C�Y
	jumpFlag = false;
	jumpCount = 0;
	freeFall = 0;
	hitBoss = false;
	moveFlag = false;
	awTime = AWAKENING_TIME;
}

//�X�V
void Player::Update(Button button)
{
	//moveFlag���t�@���X�Ȃ�{�X�ɋ߂Â�
	if (moveFlag == false)
	{
		player.pos.x -= ST_MO_PLAYER;
	}
	else
	{
		//�n�߂̓����o���ƍU���ɓ������ĕ��A�㏊��̈ʒu(���S)�ɏ������߂�
		if(player.pos.x <= screen.x /2)
		{
			player.pos.x += ST_MO_PLAYER /1.2;
		}
		//�W�����v���s��ꂽ��
		if (button.nowButton.Space == true && button.oldButton.Space == false)
		{
			jumpFlag = true;
			//�W�����v�̉񐔂��ő�ł͂Ȃ��Ƃ�
			if (jumpCount < JUMP_COUNT) {
				player.pos.y -= JUMP_FIRST_HIGHT;
				jumpCount++;
				freeFall = 0;
			}
		}
	}
	//hampFlag��true�Ȃ�Jamp�֐��ɔ��
	if (jumpFlag == true)
	{
		Jump();
	}
	//moveFlag��false�ŃX�y�[�X�������ꂽ��moveFlag��true�ɂ���
	if (moveFlag == false && (button.nowButton.Space == true && button.oldButton.Space == false))
	{
		//�o�����Ԃ�MAX�Ȃ�true�ɂ���
		if (++awTime >= AWAKENING_TIME)
		{
			moveFlag = true;
		}
	}
}

//�W�����v
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

//�֎q�̍����̒���
int Player::AdjustChair(void)
{
	return 0;
}

// �֐����Ăяo���Ƃ������̃A�h���X���Q�Ɠn���œn��
//�����蔻��
bool Player::CheckHit(Sprite compSP, std::string comparer)
{
	bool hitflag = false;
	//�����蔻������
	//�v���C���[�̍��ォ��E���̒��ɓ����Ă��邩
	if ((((player.pos.x			   < compSP.pos.x + compSP.W)		/*�v���C���[�̍��� < pos�̉E��*/
	&&	  (player.pos.y			   < compSP.pos.y + compSP.H))
	&&	 ((player.pos.x + player.W > compSP.pos.x)					/*�v���C���[�̉E�� > pos�̍���*/
	&&	  (player.pos.y + player.H > compSP.pos.y)))
		//�v���C���[�̍�������E��̒��ɓ����Ă��邩
	|| (((player.pos.x			   < compSP.pos.x + compSP.W)		/*�v���C���[�̍��� > pos�̉E��*/
	&&	 (player.pos.y + player.H  > compSP.pos.y))
	&&	((player.pos.x + player.W  > compSP.pos.x)					/*�v���C���[�̉E�� > pos�̍���*/
	&&	 (player.pos.y			   < compSP.pos.y + compSP.H))))
	{
		hitflag = true;
		//���ꂼ��̏���
		if (comparer == "BOSS")
		{
			hitBoss = true;
		}
		if (comparer == "ATTACK")
		{
			moveFlag = false;
			awTime = 0;
		}
		if (comparer == "ITEM")
		{
		}
	}
	else
	{
		hitflag = false;
	}
	return hitflag;
}

//�n�ʂƂ̓����蔻��
bool Player::CheckHitGrand(void)
{
	if (player.pos.y >= screen.y - player.H * GRAND_OFSEET)
	{
		return true;
	}
	return false;
}

//�{�X�̍U���ɓ������ē��a��
int Player::BescaredBossAttack(void)
{
	return 0;
}

//�A�C�e���̎擾
int Player::PickupItem(void)
{
	return 0;
}

//�`��
void Player::Draw(void)
{
	DrawGraph(player.pos.x, player.pos.y, player.Graph, true);
}