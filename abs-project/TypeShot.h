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
	bool GetDeleteFlag(void) { return deleteFlag; };	//deleteFlagのゲッター
	void MoveAttack(VECTOR pPos);						//攻撃の移動処理
	ATTACK_TYPE GetMyAType(void) { return SHOT; };		//自分の攻撃タイプを返す
private:
	void SetBeginPos(Sprite sboss);		//攻撃の初期位置を設定
	float RandomPosY(Sprite sboss);	//攻撃のY座標をランダム生成する

	Sprite sattack;			//攻撃の中身
	bool deleteFlag;		//攻撃の消滅フラグ
	VECTOR screen;			//画面サイズ
	int moveAttack;			//攻撃速度
};

