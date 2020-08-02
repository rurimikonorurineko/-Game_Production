#pragma once
#include <memory>
#include "DxLib.h"
#include "Sprite.h"

class Player;

//�U���^�C�v
enum ATTACK_TYPE
{
	SHOT,
	SHOCKWAVE,
	PIERCE,
	SLASH,
	A_TYPE_MAX,
};

class Attack
{
public:
	Attack();
	Attack(VECTOR screen, Sprite sboss);
	virtual~Attack();
	virtual void Initialize(Sprite sboss);
	virtual void Update(std::unique_ptr<Player>& player) = 0;
	virtual void Draw() = 0;
	virtual bool GetDeleteFlag(void) { return deleteFlag; };	//deleteFlag�̃Q�b�^�[
	virtual ATTACK_TYPE GetMyAType(void) = 0;	//�����̍U���^�C�v��Ԃ�
private:
	bool deleteFlag;		//�U���̏���
	VECTOR screen;			//��ʃT�C�Y
protected:
	int moveAttack;	// �U�����ʂ̑��x�ݒ�
};

