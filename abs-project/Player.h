#pragma once
#include <string>
#include "DxLib.h"
#include "GameTask.h"
#include "Sprite.h"

class Player
{
public:
	Player();
	Player(VECTOR screen);
	~Player();
	void Initialize(void);
	void Update(Button button);
	void Draw(void);
	int Jump(void);
	int AdjustChair(void);		//�֎q�̍�������
	bool CheckHit(Sprite compSP, std::string comparer);		//�����蔻��
	bool CheckHitGrand(void);
	bool GetHitBoss() { return hitBoss; };
	int BescaredBossAttack(void);	//��i�̍U���ɓ������œ��a��
	int PickupItem(void);			//�A�C�e�����擾

	VECTOR GetPlayerPos(void) { return player.pos; };	//�v���C���[�̍��W�̃Q�b�^�[
private:
	Sprite player;				//�v���C���[�̒��g
	//�W�����v�Ŏg�����ꂱ��
	bool jumpFlag;				//�t���O
	int jumpCount;				//�J�E���g
	float freeFall;				//�������x
	int awTime;					//�o������

	VECTOR screen;				//�X�N���[���̃T�C�Y�i�[
	bool hitBoss;				//�{�X�Ƃ̐ڐG�t���O
	bool moveFlag;				//�v���C���[�������Ă��邩

};

