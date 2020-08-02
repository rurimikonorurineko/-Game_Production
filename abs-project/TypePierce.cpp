#include "TypePierce.h"
#include "ImageMng.h"
#include "Player.h"

#define PAI 3.141592653589793	//円周率(π)
#define ANGLE_MAX 360			//一周の角度

TypePierce::TypePierce()
{
}

TypePierce::TypePierce(VECTOR screen, Sprite sboss):Attack(screen, sboss)
{
	pattack.pos = { 0,0,0 };
	pattack.Graph = 0;
	pattack.W = 0;
	pattack.H = 0;
	this->screen = screen;
	move = { 0,0,0 };
	rad = 0;
	Initialize(sboss);
}


TypePierce::~TypePierce()
{
}

void TypePierce::Initialize(Sprite sboss)
{
	//画像を読み込み＆画像サイズ取得
	pattack.Graph = ImageMng::GetInstance().GetID("image/pierce.png")[0];
	GetGraphSize(pattack.Graph, &pattack.W, &pattack.H);
	SetBeginPos(sboss);
	this->moveAttack = Attack::moveAttack;

	//フラグ類の初期化
	deleteFlag = false;
	psFlag = false;
}

//初期位置を設定する
void TypePierce::SetBeginPos(Sprite sboss)
{
	pattack.pos = { pattack.pos.x - pattack.W, pattack.pos.y - pattack.H };
}

void TypePierce::Update(std::unique_ptr<Player>& player)
{
	//プレイヤーか壁、床に当たったらフラグを立てる
	if (player->CheckHit(pattack, "ATTACK") || pattack.pos.x > screen.x || pattack.pos.y > screen.y)
	{
		deleteFlag = true;
	}
	if (psFlag == false)
	{
		//攻撃の移動処理に飛ぶ
		MoveAttack(player->GetPlayerPos());
	}
	else
	{
		pattack.pos = VAdd(pattack.pos, VScale(move, moveAttack));
	}
}

void TypePierce::Draw(void)
{ 
	DrawRotaGraph(pattack.pos.x, pattack.pos.y,1.0, rad, pattack.Graph, true);
}

void TypePierce::MoveAttack(VECTOR pPos)
{
	// 自機狙いの攻撃

	//1,始点から終点までの移動ベクトルを作る
	VECTOR v = VSub(pPos, pattack.pos);
	//2.1で作った移動ベクトルを正規化する
	move = VNorm(v);
	//3,2で作った移動正規化ベクトルを分割して始点ベクトルに入れて移動させる
	pattack.pos = VAdd(pattack.pos, VScale(move, moveAttack *2));
	psFlag = true;
	//MakePierceRad(move);
	rad = ANGLE_MAX *1 /8 * PAI / (ANGLE_MAX / 2);
}

void TypePierce::MakePierceRad(VECTOR toPlayerVec)
{
	//法線ベクトルを生成
	VECTOR n = { pattack.pos.x +10, pattack.pos.y, 0 };
	VECTOR nomal = VSub(n, pattack.pos);
	//法線ベクトルを正規化
	nomal = VNorm(nomal);
	//角度生成(ラジアン)
	rad = VRad(nomal,toPlayerVec);
}