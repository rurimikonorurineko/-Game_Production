#include <string>
#include "Boss.h"
#include "ImageMng.h"
#include "Attack.h"
#include "Player.h"
#include "TypeShot.h"
#include "TypeShockwave.h"
#include "TypePierce.h"
#include "TypeSlash.h"

#define BOSS_OFFSET_GRAND 15	//ボスの画面上の位置の補正
#define LINES_TIME	120			//ボスの「仕事しろ」発言の表示時間数
#define ATTACK_SHOT_NUMBER	3	//shot攻撃の数

Boss::Boss()
{
	
}

Boss::Boss(VECTOR screen)
{
	this->screen = screen;
	for (Sprite bossElement : boss)
	{
		bossElement.pos = { 0,0,0 };
		bossElement.Graph = 0;
		bossElement.H = 0;
		bossElement.W = 0;
	}
	word.pos = { 0,0,0 };
	word.Graph = 0;
	word.H = 0;
	word.W = 0;

	Initialize();
}


Boss::~Boss()
{
}
//イニシャライズ
void Boss::Initialize(void)
{
	//ボスタイプの画像を配列にセット
	std::string in[TYPE_MAX] = { "image/boss1.png", "image/boss2.png", "image/boss3.png", "image/boss4.png",};
	//ボスの進化時間を２次元配列にセット
	int time[3][TYPE_MAX] = { { 0,0,0,99 },{ 15,30,45,99 },{ 1,1,1,99 } };

	//全てのボスタイプのイニシャライズ
	for (int i = 0; i < TYPE_MAX; i++)
	{
		//ボスの中身をセット
		boss[i].Graph = ImageMng::GetInstance().GetID(in[i])[0];
		GetGraphSize(boss[i].Graph, &boss[i].W, &boss[i].H);
		boss[i].pos.x = 0 + BOSS_OFFSET_GRAND;
		boss[i].pos.y = screen.y - boss[i].H * 1.1;
		boss[i].pos.z = 0;
		//ボスの進化の時間を格納
		changeTimes[i].second.actual = time[0][i];
		changeTimes[i].minute.actual = time[1][i];
		changeTimes[i].hour.actual = time[2][i];
	}
	bossType = BOSS_TYPE::HUMAN;

	//attackListのclear
	if (attackList.size() != 0)
	{
		attackList.clear();
	}
	//「仕事しろ」の中身をセット
	word.Graph = ImageMng::GetInstance().GetID("image/word.png")[0];
	GetGraphSize(word.Graph, &word.W, &word.H);

	//フラグ類の初期化
	linesFlag = false;
	linesCount = 0;
}

//生成された攻撃クラスをリストに格納
auto Boss::AddAttackList(attack_ptr && attackPtr)
{
	attackList.push_back(attackPtr);
	auto itr = attackList.end();
	itr--;
	return itr;
}

//更新
void Boss::Update(Button button, std::unique_ptr<Player>& player, std::unique_ptr<Timer>& timer)
{
	//ボスが死神(最終進化)ではなかったら
	if (bossType != BOSS_TYPE::GODOFDEATH)
	{
		//ボスの進化時間とタイマーの時間が同じだったら
		if (timer->GetTimer().hour.actual == changeTimes[bossType].hour.actual
		&&	timer->GetTimer().minute.actual == changeTimes[bossType].minute.actual
		&&	timer->GetTimer().second.actual == changeTimes[bossType].second.actual)
		{
			//ボスを進化させる
			ChangeType(bossType);
		}
	}
	//プレイヤーとボスの当たり判定
	player->CheckHit(boss[bossType], "BOSS");

	for (auto itr : attackList)
	{
		itr->Update(player);
	}

	//20秒に1回攻撃を生成
	if (timer->GetTimer().second.actual %20 == 0)
	{
		if (linesFlag == false)
		{
			GenerateAttack(timer);
			linesFlag = true;
		}
	}

	//攻撃を出すときの「仕事しろ」発言の表示時間処理
	if (linesCount++ == LINES_TIME)
	{
		linesFlag = false;
		linesCount = 0;
	}

	//Attackクラスにdeleteフラグあったら
	for(auto itr : attackList)
	{
		if (itr->GetDeleteFlag() == true)
		{
			int i = 0;
			//attackList内のitrポインタの要素を削除(このままだと怒られる)
			
			//attackList.erase(itr);
		}
	}
}
//描画
void Boss::Draw(void)
{
	DrawGraph(boss[bossType].pos.x, boss[bossType].pos.y, boss[bossType].Graph, true);
	for (auto itr : attackList)
	{
		itr->Draw();
	}
	if (linesFlag == true)
	{
		DrawGraph(boss[bossType].pos.x + boss[bossType].W /2 - word.W /2,
				  boss[bossType].pos.y - word.H,word.Graph,true);
	}
}

//攻撃クラスを攻撃の種類を決定して生成
void Boss::GenerateAttack(std::unique_ptr<Timer>& timer)
{
	//斬撃攻撃
	if (timer->GetTimer().minute.actual % 10 == 0 && bossType == BOSS_TYPE::GODOFDEATH)
	{
		AddAttackList(std::make_shared<TypeSlash>(screen, boss[bossType]));
	}
	//貫通攻撃
	if (timer->GetTimer().minute.actual % 5 == 0 && bossType == BOSS_TYPE::STATUEOFGOD)
	{
		AddAttackList(std::make_shared<TypePierce>(screen, boss[bossType]));

	}
	//衝撃波攻撃
	if (timer->GetTimer().minute.actual % 2 == 0 && (bossType == BOSS_TYPE::OGRE || bossType == BOSS_TYPE::GODOFDEATH))
	{
		AddAttackList(std::make_shared<TypeShockwave>(screen, boss[bossType]));
	}
	//shot攻撃
	for (int i = 0; i < ATTACK_SHOT_NUMBER + (bossType == BOSS_TYPE::STATUEOFGOD ? 1 : bossType == BOSS_TYPE::GODOFDEATH ? 2 : 0); i++)
	{
		AddAttackList(std::make_shared<TypeShot>(screen, boss[bossType]));
	}
}


//ボスのタイプを一つ上のタイプにする(進化させる)
BOSS_TYPE & Boss::ChangeType(BOSS_TYPE & bossType)
{
	bossType = static_cast<BOSS_TYPE>(bossType + 1);
	return bossType;
}
