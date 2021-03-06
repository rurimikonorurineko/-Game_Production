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
	bool GetDeleteFlag(void) { return deleteFlag; };	//deleteFlagÌQb^[
	void MoveAttack(VECTOR pPos);						//UÌÚ®
	ATTACK_TYPE GetMyAType(void) { return SLASH; };		//©ªÌU^CvðÔ·
private:
	void SetBeginPos(Sprite sboss);		//UÌúÊuðÝè

	Sprite slattack;			//UÌg
	bool deleteFlag;		//UÌÁÅtO
	VECTOR screen;			//æÊTCY
	int moveAttack;			//U¬x
};

