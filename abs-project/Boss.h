#pragma once
#include <memory>
#include <list>
#include "DxLib.h"
#include "Sprite.h"
#include "GameTask.h"
#include "Timer.h"

class Attack;
class Player;

typedef std::shared_ptr<Attack> attack_ptr;
typedef std::list<attack_ptr> attack_List;

//�{�X�̃^�C�v
enum BOSS_TYPE
{
	HUMAN,
	OGRE,
	STATUEOFGOD,
	GODOFDEATH,
	TYPE_MAX
};

class Boss
{
public:
	Boss();
	Boss(VECTOR screen);
	~Boss();
	void Initialize(void);
	void Update(Button button, std::unique_ptr<Player>& player, std::unique_ptr<Timer>& timer);
	void Draw(void);
private:
	auto AddAttackList(attack_ptr&& attackPtr);	//�U���̃��X�g�ɃC���X�^���X�����U��������
	void GenerateAttack(std::unique_ptr<Timer>& timer);	//�U���𐶐�
	BOSS_TYPE& ChangeType(BOSS_TYPE& bossType);	//�{�X�̃^�C�v��1��ɂ�����

	Sprite boss[TYPE_MAX];						//�{�X�̒��g
	Sprite word;								//�d������̒��g
	TIMER changeTimes[TYPE_MAX];				//�{�X�̐i���̎���
	BOSS_TYPE bossType;							//�{�X�̃^�C�v(��Ɉ����ɗ��p)
	bool linesFlag;								//�{�X�́u�d������v�����ƍU�������̃t���O
	int linesCount;								//�u�d������v�����̕\������
	VECTOR screen;								//��ʂ̃T�C�Y
	attack_List attackList;						//�U���̃��X�g
};

