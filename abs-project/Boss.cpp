#include <string>
#include "Boss.h"
#include "ImageMng.h"

#define BOSS_OFFSET 15

Boss::Boss()
{
	for (Sprite bossElement : boss)
	{
		bossElement.pos = { 0,0,0 };
		bossElement.Graph = 0;
		bossElement.H = 0;
		bossElement.W - 0;
	}
	Initialize();
}


Boss::~Boss()
{
}

void Boss::Initialize(void)
{
	std::string in[TYPE_MAX] = { "image/boss1.png", "image/boss2.png", "image/boss3.png", "image/boss4.png",};
	for (int i = 0; i < TYPE_MAX; i++)
	{
		boss[i].Graph = ImageMng::GetInstance().GetID(in[i])[0];
		GetGraphSize(boss[i].Graph, &boss[i].W, &boss[i].H);
		boss[i].pos.x = 0 + BOSS_OFFSET;
		boss[i].pos.y = 593 - boss[i].H * 1.1;
		boss[i].pos.z = 0;

		int time[3][TYPE_MAX-1] = {{0,0,0 }, {15,30,45}, {13,13,13}};
		changeTimes[i].second = time[0][i];
		changeTimes[i].minute = time[1][i];
		changeTimes[i].hour	  = time[2][i];
	}
	bossType = BOSS_TYPE::HUMAN;
	timer = std::make_unique<Timer>();

}

void Boss::Update(Button button, VECTOR screen)
{
	if (bossType != BOSS_TYPE::GODOFDEATH)
	{
		if (timer->CheckChangeTime(changeTimes[bossType]))
		{
			ChangeType(bossType);
		}
	}
}

void Boss::Draw(void)
{
	DrawGraph(boss[bossType].pos.x, boss[bossType].pos.y, boss[bossType].Graph, true);
}

BOSS_TYPE & Boss::ChangeType(BOSS_TYPE & bossType)
{
	bossType = static_cast<BOSS_TYPE>(bossType + 1);
	return bossType;
	// TODO: return ステートメントをここに挿入します
}
