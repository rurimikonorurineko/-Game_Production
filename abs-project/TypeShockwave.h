#pragma once
#include "Attack.h"

class Player;

class TypeShockwave :
	public Attack
{
public:
	TypeShockwave();
	TypeShockwave(VECTOR screen, Sprite sboss);
	~TypeShockwave();
	void Initialize(Sprite sboss);
	void Update(std::unique_ptr<Player>& player);
	void Draw(void);
	bool GetDeleteFlag(void) { return deleteFlag; };	//deleteFlag�̃Q�b�^�[
	void MoveAttack(VECTOR pPos);						//�U���̈ړ�����
	ATTACK_TYPE GetMyAType(void) { return SHOCKWAVE; };	//�����̍U���^�C�v��Ԃ�
private:
	void SetBeginPos(Sprite sboss);		//�U���̏����ʒu��ݒ�

	Sprite swattack;			//�U���̒��g
	bool deleteFlag;		//�U���̏��Ńt���O
	VECTOR screen;			//��ʃT�C�Y
	int moveAttack;			//�U�����x
};

