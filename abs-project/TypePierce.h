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
	bool GetDeleteFlag(void) { return deleteFlag; };	//deleteFlagのゲッター
	void MoveAttack(VECTOR pPos);						//攻撃の移動処理
	ATTACK_TYPE GetMyAType(void) { return PIERCE; };	//自分の攻撃タイプを返す
private:
	void SetBeginPos(Sprite sboss);				//攻撃の初期位置を設定
	void MakePierceRad(VECTOR toPlayerVec);		//pierceの回転処理

	Sprite pattack;			//攻撃の中身
	bool deleteFlag;		//攻撃の消滅フラグ
	VECTOR screen;			//画面サイズ
	int moveAttack;			//攻撃速度
	VECTOR move;			//設定した移動ヴェクトルを保存
	bool psFlag;			//座標やらのセットフラグ
	float rad;				//斜角度(ラジアン)
};

