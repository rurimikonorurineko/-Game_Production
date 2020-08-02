#pragma once
#include <memory>
#include "GameTask.h"

class TitleScene;
class GameScene;
class ResultScene;
class Timer;

struct ControlButton
{
	bool Space;			//スペース
	bool Up_Chair;		//椅子を上げる
	bool Down_Chair;	//椅子を下げる
};

struct Button
{
	ControlButton nowButton;	//今のボタン
	ControlButton oldButton;	//一つ前のボタン
};


class GameTask
{
public:
	static void Create(void);			//クリエイト
	static void Destroy(void);			//デストロイ
	static GameTask &GetInstance(void)	//インスタンス
	{
		Create();
		return *s_Instance;
	}
	void Initialize(void);
	void Run(void);
	int Update(void);
private:
	GameTask();
	~GameTask();
	int System(void);					//システム
	//シーンズ
	int TitleInit(void);
	int Title(void);
	int GameInit(void);
	int Game(void);
	int ResultInit(void);
	int Result(void);

	void UpdateButton(void);		//ボタンの更新
	int (GameTask::*Scene)(void);	//ゲーム遷移
	Button controlButton;			//コントローラ

	// シーンのスマートポインタ
	std::unique_ptr<TitleScene> title;
	std::unique_ptr<GameScene> game;
	std::unique_ptr<ResultScene> result;
	std::unique_ptr<Timer> timer;
	VECTOR screen;					//画面サイズ
	static GameTask *s_Instance;	//インスタンスポインタ
};

