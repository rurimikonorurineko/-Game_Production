#pragma once
#include <memory>
#include <list>
#include "DxLib.h"
#include "Sprite.h"
#include "GameTask.h"
#include "Timer.h"

class Attack;
class Player;

typedef std::shared_ptr<Attack> attack_ptr;
typedef std::list<attack_ptr> attack_List;

//ボスのタイプ
enum BOSS_TYPE
{
	HUMAN,
	OGRE,
	STATUEOFGOD,
	GODOFDEATH,
	TYPE_MAX
};

class Boss
{
public:
	Boss();
	Boss(VECTOR screen);
	~Boss();
	void Initialize(void);
	void Update(Button button, std::unique_ptr<Player>& player, std::unique_ptr<Timer>& timer);
	void Draw(void);
private:
	auto AddAttackList(attack_ptr&& attackPtr);	//攻撃のリストにインスタンスした攻撃をつける
	void GenerateAttack(std::unique_ptr<Timer>& timer);	//攻撃を生成
	BOSS_TYPE& ChangeType(BOSS_TYPE& bossType);	//ボスのタイプを1つ上にあげる

	Sprite boss[TYPE_MAX];						//ボスの中身
	Sprite word;								//仕事しろの中身
	TIMER changeTimes[TYPE_MAX];				//ボスの進化の時間
	BOSS_TYPE bossType;							//ボスのタイプ(主に引数に利用)
	bool linesFlag;								//ボスの「仕事しろ」発言と攻撃生成のフラグ
	int linesCount;								//「仕事しろ」発言の表示時間
	VECTOR screen;								//画面のサイズ
	attack_List attackList;						//攻撃のリスト
};

