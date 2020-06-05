#pragma once
#include <string>
#include "DxLib.h"
#include "GameTask.h"
#include "Sprite.h"

class Player
{
public:
	Player();
	~Player();
	void Initialize(void);
	void Update(Button button, VECTOR screen);
	void Draw(void);
	int Jump(void);
	//�֎q�̍�������
	int AdjustChair(void);
	//�����蔻��
	bool CheckHit(Sprite compSP, std::string comparer);
	bool CheckHitGrand(void);
	//��i�̍U���ɓ������œ��a��
	int BescaredBossAttack(void);
	//�A�C�e�����擾
	int PickupItem(void);
private:
	//�v���C���[�̃X�v���C�g
	Sprite player;
	//�W�����v�t���E�O
	bool jumpFlag;
	int jumpCount;
	float freeFall;
	//�X�N���[���̃T�C�Y�i�[
	VECTOR screen;
};

