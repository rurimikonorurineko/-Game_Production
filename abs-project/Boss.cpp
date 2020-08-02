#include <string>
#include "Boss.h"
#include "ImageMng.h"
#include "Attack.h"
#include "Player.h"
#include "TypeShot.h"
#include "TypeShockwave.h"
#include "TypePierce.h"
#include "TypeSlash.h"

#define BOSS_OFFSET_GRAND 15	//�{�X�̉�ʏ�̈ʒu�̕␳
#define LINES_TIME	120			//�{�X�́u�d������v�����̕\�����Ԑ�
#define ATTACK_SHOT_NUMBER	3	//shot�U���̐�

Boss::Boss()
{
	
}

Boss::Boss(VECTOR screen)
{
	this->screen = screen;
	for (Sprite bossElement : boss)
	{
		bossElement.pos = { 0,0,0 };
		bossElement.Graph = 0;
		bossElement.H = 0;
		bossElement.W = 0;
	}
	word.pos = { 0,0,0 };
	word.Graph = 0;
	word.H = 0;
	word.W = 0;

	Initialize();
}


Boss::~Boss()
{
}
//�C�j�V�����C�Y
void Boss::Initialize(void)
{
	//�{�X�^�C�v�̉摜��z��ɃZ�b�g
	std::string in[TYPE_MAX] = { "image/boss1.png", "image/boss2.png", "image/boss3.png", "image/boss4.png",};
	//�{�X�̐i�����Ԃ��Q�����z��ɃZ�b�g
	int time[3][TYPE_MAX] = { { 0,0,0,99 },{ 15,30,45,99 },{ 1,1,1,99 } };

	//�S�Ẵ{�X�^�C�v�̃C�j�V�����C�Y
	for (int i = 0; i < TYPE_MAX; i++)
	{
		//�{�X�̒��g���Z�b�g
		boss[i].Graph = ImageMng::GetInstance().GetID(in[i])[0];
		GetGraphSize(boss[i].Graph, &boss[i].W, &boss[i].H);
		boss[i].pos.x = 0 + BOSS_OFFSET_GRAND;
		boss[i].pos.y = screen.y - boss[i].H * 1.1;
		boss[i].pos.z = 0;
		//�{�X�̐i���̎��Ԃ��i�[
		changeTimes[i].second.actual = time[0][i];
		changeTimes[i].minute.actual = time[1][i];
		changeTimes[i].hour.actual = time[2][i];
	}
	bossType = BOSS_TYPE::HUMAN;

	//attackList��clear
	if (attackList.size() != 0)
	{
		attackList.clear();
	}
	//�u�d������v�̒��g���Z�b�g
	word.Graph = ImageMng::GetInstance().GetID("image/word.png")[0];
	GetGraphSize(word.Graph, &word.W, &word.H);

	//�t���O�ނ̏�����
	linesFlag = false;
	linesCount = 0;
}

//�������ꂽ�U���N���X�����X�g�Ɋi�[
auto Boss::AddAttackList(attack_ptr && attackPtr)
{
	attackList.push_back(attackPtr);
	auto itr = attackList.end();
	itr--;
	return itr;
}

//�X�V
void Boss::Update(Button button, std::unique_ptr<Player>& player, std::unique_ptr<Timer>& timer)
{
	//�{�X�����_(�ŏI�i��)�ł͂Ȃ�������
	if (bossType != BOSS_TYPE::GODOFDEATH)
	{
		//�{�X�̐i�����Ԃƃ^�C�}�[�̎��Ԃ�������������
		if (timer->GetTimer().hour.actual == changeTimes[bossType].hour.actual
		&&	timer->GetTimer().minute.actual == changeTimes[bossType].minute.actual
		&&	timer->GetTimer().second.actual == changeTimes[bossType].second.actual)
		{
			//�{�X��i��������
			ChangeType(bossType);
		}
	}
	//�v���C���[�ƃ{�X�̓����蔻��
	player->CheckHit(boss[bossType], "BOSS");

	for (auto itr : attackList)
	{
		itr->Update(player);
	}

	//20�b��1��U���𐶐�
	if (timer->GetTimer().second.actual %20 == 0)
	{
		if (linesFlag == false)
		{
			GenerateAttack(timer);
			linesFlag = true;
		}
	}

	//�U�����o���Ƃ��́u�d������v�����̕\�����ԏ���
	if (linesCount++ == LINES_TIME)
	{
		linesFlag = false;
		linesCount = 0;
	}

	//Attack�N���X��delete�t���O��������
	for(auto itr : attackList)
	{
		if (itr->GetDeleteFlag() == true)
		{
			int i = 0;
			//attackList����itr�|�C���^�̗v�f���폜(���̂܂܂��Ɠ{����)
			
			//attackList.erase(itr);
		}
	}
}
//�`��
void Boss::Draw(void)
{
	DrawGraph(boss[bossType].pos.x, boss[bossType].pos.y, boss[bossType].Graph, true);
	for (auto itr : attackList)
	{
		itr->Draw();
	}
	if (linesFlag == true)
	{
		DrawGraph(boss[bossType].pos.x + boss[bossType].W /2 - word.W /2,
				  boss[bossType].pos.y - word.H,word.Graph,true);
	}
}

//�U���N���X���U���̎�ނ����肵�Đ���
void Boss::GenerateAttack(std::unique_ptr<Timer>& timer)
{
	//�a���U��
	if (timer->GetTimer().minute.actual % 10 == 0 && bossType == BOSS_TYPE::GODOFDEATH)
	{
		AddAttackList(std::make_shared<TypeSlash>(screen, boss[bossType]));
	}
	//�ђʍU��
	if (timer->GetTimer().minute.actual % 5 == 0 && bossType == BOSS_TYPE::STATUEOFGOD)
	{
		AddAttackList(std::make_shared<TypePierce>(screen, boss[bossType]));

	}
	//�Ռ��g�U��
	if (timer->GetTimer().minute.actual % 2 == 0 && (bossType == BOSS_TYPE::OGRE || bossType == BOSS_TYPE::GODOFDEATH))
	{
		AddAttackList(std::make_shared<TypeShockwave>(screen, boss[bossType]));
	}
	//shot�U��
	for (int i = 0; i < ATTACK_SHOT_NUMBER + (bossType == BOSS_TYPE::STATUEOFGOD ? 1 : bossType == BOSS_TYPE::GODOFDEATH ? 2 : 0); i++)
	{
		AddAttackList(std::make_shared<TypeShot>(screen, boss[bossType]));
	}
}


//�{�X�̃^�C�v�����̃^�C�v�ɂ���(�i��������)
BOSS_TYPE & Boss::ChangeType(BOSS_TYPE & bossType)
{
	bossType = static_cast<BOSS_TYPE>(bossType + 1);
	return bossType;
}
