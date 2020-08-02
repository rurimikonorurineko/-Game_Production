#pragma once
#include <string>
#include "DxLib.h"
#include "GameTask.h"
#include "Sprite.h"

class Player
{
public:
	Player();
	Player(VECTOR screen);
	~Player();
	void Initialize(void);
	void Update(Button button);
	void Draw(void);
	int Jump(void);
	int AdjustChair(void);		//椅子の高さ調整
	bool CheckHit(Sprite compSP, std::string comparer);		//当たり判定
	bool CheckHitGrand(void);
	bool GetHitBoss() { return hitBoss; };
	int BescaredBossAttack(void);	//上司の攻撃に当たっで日和る
	int PickupItem(void);			//アイテムを取得

	VECTOR GetPlayerPos(void) { return player.pos; };	//プレイヤーの座標のゲッター
private:
	Sprite player;				//プレイヤーの中身
	//ジャンプで使うあれこれ
	bool jumpFlag;				//フラグ
	int jumpCount;				//カウント
	float freeFall;				//落下速度
	int awTime;					//覚醒時間

	VECTOR screen;				//スクリーンのサイズ格納
	bool hitBoss;				//ボスとの接触フラグ
	bool moveFlag;				//プレイヤーが動いているか

};

