#pragma once
#include "Attack.h"

class Player;

class TypePierce :
	public Attack
{
public:
	TypePierce();
	TypePierce(VECTOR screen, Sprite sboss);
	~TypePierce();
	void Initialize(Sprite sboss);
	void Update(std::unique_ptr<Player>& player);
	void Draw(void);
	bool GetDeleteFlag(void) { return deleteFlag; };	//deleteFlag�̃Q�b�^�[
	void MoveAttack(VECTOR pPos);						//�U���̈ړ�����
	ATTACK_TYPE GetMyAType(void) { return PIERCE; };	//�����̍U���^�C�v��Ԃ�
private:
	void SetBeginPos(Sprite sboss);				//�U���̏����ʒu��ݒ�
	void MakePierceRad(VECTOR toPlayerVec);		//pierce�̉�]����

	Sprite pattack;			//�U���̒��g
	bool deleteFlag;		//�U���̏��Ńt���O
	VECTOR screen;			//��ʃT�C�Y
	int moveAttack;			//�U�����x
	VECTOR move;			//�ݒ肵���ړ����F�N�g����ۑ�
	bool psFlag;			//���W���̃Z�b�g�t���O
	float rad;				//�Ίp�x(���W�A��)
};

