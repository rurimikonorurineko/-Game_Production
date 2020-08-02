#pragma once
#include "Attack.h"

class Player;

class TypeShot :
	public Attack
{
public:
	TypeShot();
	TypeShot(VECTOR screen, Sprite sboss);
	~TypeShot();
	void Initialize(Sprite sboss);
	void Update(std::unique_ptr<Player>& player);
	void Draw(void);
	bool GetDeleteFlag(void) { return deleteFlag; };	//deleteFlag�̃Q�b�^�[
	void MoveAttack(VECTOR pPos);						//�U���̈ړ�����
	ATTACK_TYPE GetMyAType(void) { return SHOT; };		//�����̍U���^�C�v��Ԃ�
private:
	void SetBeginPos(Sprite sboss);		//�U���̏����ʒu��ݒ�
	float RandomPosY(Sprite sboss);	//�U����Y���W�������_����������

	Sprite sattack;			//�U���̒��g
	bool deleteFlag;		//�U���̏��Ńt���O
	VECTOR screen;			//��ʃT�C�Y
	int moveAttack;			//�U�����x
};

