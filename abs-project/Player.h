#pragma once
#include <string>
#include "DxLib.h"

class Player
{
public:
	Player();
	~Player();
	void Update(void);
	void Draw(void);
	int Jump(void);
	//�֎q�̍�������
	int AdjustChair(void);
	//�����蔻��
	bool CheckHit(VECTOR pos, std::string comparer);
	//��i�̍U���ɓ������œ��a��
	int BescaredBossAttack(void);
	//�A�C�e�����擾
	int PickupItem(void);

};

