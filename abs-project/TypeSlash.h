#pragma once
#include "Attack.h"

class Player;

class TypeSlash :
	public Attack
{
public:
	TypeSlash();
	TypeSlash(VECTOR screen, Sprite sboss);
	~TypeSlash();
	void Initialize(Sprite sboss);
	void Update(std::unique_ptr<Player>& player);
	void Draw(void);
	bool GetDeleteFlag(void) { return deleteFlag; };	//deleteFlag�̃Q�b�^�[
	void MoveAttack(VECTOR pPos);						//�U���̈ړ�����
	ATTACK_TYPE GetMyAType(void) { return SLASH; };		//�����̍U���^�C�v��Ԃ�
private:
	void SetBeginPos(Sprite sboss);		//�U���̏����ʒu��ݒ�

	Sprite slattack;			//�U���̒��g
	bool deleteFlag;		//�U���̏��Ńt���O
	VECTOR screen;			//��ʃT�C�Y
	int moveAttack;			//�U�����x
};

