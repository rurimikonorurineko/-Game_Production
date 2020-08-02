#include "Player.h"
#include "ImageMng.h"

#define GRAND_OFSEET 1.2		//プレイヤーの足もとのどのあたりに地面があるのかを決める
#define JUMP_FIRST_HIGHT 100	//プレイヤーがジャンプした時の初期高度
#define JUMP_COUNT 3			//連続ジャンプの回数
#define GRAVITY 0.2				//重力
#define ST_MO_PLAYER 2			//プレイヤーが止まっているときとその後元の位置まで戻る時の1フレームの移動値
#define AWAKENING_TIME 2		//攻撃ヒット後の覚醒時間

Player::Player()
{
	
}

Player::Player(VECTOR screen)
{
	this->screen = screen;
	player.pos = { 0,0,0 };
	player.Graph = 0;
	player.H = 0;
	player.W = 0;
	Initialize();
}

Player::~Player()
{
}

//イニシャライズ
void Player::Initialize(void)
{
	//プレイヤーの中身をセット
	player.Graph = ImageMng::GetInstance().GetID("image/player.png")[0];
	GetGraphSize(player.Graph, &player.W, &player.H);
	player.pos.x = screen.x / 2;
	player.pos.y = screen.y - player.H * GRAND_OFSEET;
	//フラグ類をイニシャライズ
	jumpFlag = false;
	jumpCount = 0;
	freeFall = 0;
	hitBoss = false;
	moveFlag = false;
	awTime = AWAKENING_TIME;
}

//更新
void Player::Update(Button button)
{
	//moveFlagがファルスならボスに近づく
	if (moveFlag == false)
	{
		player.pos.x -= ST_MO_PLAYER;
	}
	else
	{
		//始めの動き出しと攻撃に当たって復帰後所定の位置(中心)に少しずつ戻る
		if(player.pos.x <= screen.x /2)
		{
			player.pos.x += ST_MO_PLAYER /1.2;
		}
		//ジャンプが行われたか
		if (button.nowButton.Space == true && button.oldButton.Space == false)
		{
			jumpFlag = true;
			//ジャンプの回数が最大ではないとき
			if (jumpCount < JUMP_COUNT) {
				player.pos.y -= JUMP_FIRST_HIGHT;
				jumpCount++;
				freeFall = 0;
			}
		}
	}
	//hampFlagがtrueならJamp関数に飛ぶ
	if (jumpFlag == true)
	{
		Jump();
	}
	//moveFlagがfalseでスペースが押されたらmoveFlagをtrueにする
	if (moveFlag == false && (button.nowButton.Space == true && button.oldButton.Space == false))
	{
		//覚醒時間はMAXならtrueにする
		if (++awTime >= AWAKENING_TIME)
		{
			moveFlag = true;
		}
	}
}

//ジャンプ
int Player::Jump(void)
{
	freeFall += GRAVITY;
	player.pos.y += freeFall;
	if (CheckHitGrand())
	{
		jumpFlag = false;
		jumpCount = 0;
		freeFall = 0;
	}
	return 0;
}

//椅子の高さの調節
int Player::AdjustChair(void)
{
	return 0;
}

// 関数を呼び出すとき自分のアドレスを参照渡しで渡す
//当たり判定
bool Player::CheckHit(Sprite compSP, std::string comparer)
{
	bool hitflag = false;
	//当たり判定を取る
	//プレイヤーの左上から右下の中に入っているか
	if ((((player.pos.x			   < compSP.pos.x + compSP.W)		/*プレイヤーの左上 < posの右下*/
	&&	  (player.pos.y			   < compSP.pos.y + compSP.H))
	&&	 ((player.pos.x + player.W > compSP.pos.x)					/*プレイヤーの右下 > posの左上*/
	&&	  (player.pos.y + player.H > compSP.pos.y)))
		//プレイヤーの左下から右上の中に入っているか
	|| (((player.pos.x			   < compSP.pos.x + compSP.W)		/*プレイヤーの左下 > posの右上*/
	&&	 (player.pos.y + player.H  > compSP.pos.y))
	&&	((player.pos.x + player.W  > compSP.pos.x)					/*プレイヤーの右上 > posの左下*/
	&&	 (player.pos.y			   < compSP.pos.y + compSP.H))))
	{
		hitflag = true;
		//それぞれの処理
		if (comparer == "BOSS")
		{
			hitBoss = true;
		}
		if (comparer == "ATTACK")
		{
			moveFlag = false;
			awTime = 0;
		}
		if (comparer == "ITEM")
		{
		}
	}
	else
	{
		hitflag = false;
	}
	return hitflag;
}

//地面との当たり判定
bool Player::CheckHitGrand(void)
{
	if (player.pos.y >= screen.y - player.H * GRAND_OFSEET)
	{
		return true;
	}
	return false;
}

//ボスの攻撃に当たって日和る
int Player::BescaredBossAttack(void)
{
	return 0;
}

//アイテムの取得
int Player::PickupItem(void)
{
	return 0;
}

//描画
void Player::Draw(void)
{
	DrawGraph(player.pos.x, player.pos.y, player.Graph, true);
}