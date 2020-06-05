#pragma once
#include <string>
#include "DxLib.h"
#include "GameTask.h"
#include "Sprite.h"

class Player
{
public:
	Player();
	~Player();
	void Initialize(void);
	void Update(Button button, VECTOR screen);
	void Draw(void);
	int Jump(void);
	//椅子の高さ調整
	int AdjustChair(void);
	//当たり判定
	bool CheckHit(Sprite compSP, std::string comparer);
	bool CheckHitGrand(void);
	//上司の攻撃に当たっで日和る
	int BescaredBossAttack(void);
	//アイテムを取得
	int PickupItem(void);
private:
	//プレイヤーのスプライト
	Sprite player;
	//ジャンプフラウグ
	bool jumpFlag;
	int jumpCount;
	float freeFall;
	//スクリーンのサイズ格納
	VECTOR screen;
};

