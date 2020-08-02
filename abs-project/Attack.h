#pragma once
#include <memory>
#include "DxLib.h"
#include "Sprite.h"

class Player;

//攻撃タイプ
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
	virtual bool GetDeleteFlag(void) { return deleteFlag; };	//deleteFlagのゲッター
	virtual ATTACK_TYPE GetMyAType(void) = 0;	//自分の攻撃タイプを返す
private:
	bool deleteFlag;		//攻撃の消滅
	VECTOR screen;			//画面サイズ
protected:
	int moveAttack;	// 攻撃共通の速度設定
};

