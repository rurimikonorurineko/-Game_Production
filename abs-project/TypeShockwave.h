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
	bool GetDeleteFlag(void) { return deleteFlag; };	//deleteFlagのゲッター
	void MoveAttack(VECTOR pPos);						//攻撃の移動処理
	ATTACK_TYPE GetMyAType(void) { return SHOCKWAVE; };	//自分の攻撃タイプを返す
private:
	void SetBeginPos(Sprite sboss);		//攻撃の初期位置を設定

	Sprite swattack;			//攻撃の中身
	bool deleteFlag;		//攻撃の消滅フラグ
	VECTOR screen;			//画面サイズ
	int moveAttack;			//攻撃速度
};

