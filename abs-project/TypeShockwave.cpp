#include "TypeShockwave.h"
#include "ImageMng.h"
#include "Player.h"


TypeShockwave::TypeShockwave()
{
}

TypeShockwave::TypeShockwave(VECTOR screen, Sprite sboss):Attack(screen, sboss)
{
	swattack.pos = { 0,0,0 };
	swattack.Graph = 0;
	swattack.W = 0;
	swattack.H = 0;
	this->screen = screen;
	Initialize(sboss);
}


TypeShockwave::~TypeShockwave()
{
}

void TypeShockwave::Initialize(Sprite sboss)
{
	//画像を読み込み＆画像サイズ取得
	swattack.Graph = ImageMng::GetInstance().GetID("image/shockwave.png")[0];
	GetGraphSize(swattack.Graph, &swattack.W, &swattack.H);
	SetBeginPos(sboss);
	this->moveAttack = Attack::moveAttack;

	//フラグ類の初期化
	deleteFlag = false;
}

//初期位置を設定する
void TypeShockwave::SetBeginPos(Sprite sboss)
{
	swattack.pos = {sboss.pos.x + sboss.W, (float)(sboss.pos.y + sboss.H - swattack.H *1.5)};
}

void TypeShockwave::Update(std::unique_ptr<Player>& player)
{
	//プレイヤーか壁、床に当たったらフラグを立てる
	if (player->CheckHit(swattack, "ATTACK") || swattack.pos.x > screen.x || swattack.pos.y > screen.y)
	{
		deleteFlag = true;
	}
	//攻撃の移動処理に飛ぶ
	MoveAttack(player->GetPlayerPos());
}

void TypeShockwave::Draw(void)
{
	DrawGraph(swattack.pos.x, swattack.pos.y, swattack.Graph, true);
}

//攻撃を動かす
void TypeShockwave::MoveAttack(VECTOR pPos)
{
	swattack.pos.x += moveAttack * 2;
}