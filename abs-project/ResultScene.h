#pragma once
#include "DxLib.h"
#include "Sprite.h"
#include "BaseScene.h"
#include "GameTask.h"

class ResultScene :
	public BaseScene
{
public:
	ResultScene();
	ResultScene(VECTOR screen);
	~ResultScene();
	void Update(Button button, std::unique_ptr<Timer>& timer);
	void TransltionScene(Scene scene);			//次のシーンのセット
	void Draw(void);
	Scene GetScene(void) { return scene; };		//セットされているシーンを渡す
	void ConversionTitle(void);					//タイトルへのセット関数
	void ConversionGame(void);					//ゲームへのセット関数
private:
	void Initialize(void);					//イニシャライズ
	void DrawLineBox(Sprite transGraph);	//四角枠線を表示

	Sprite workPlayerGraph;				//仕事に捕まったプレイヤ―
	Sprite transTitleGraph;				//タイトル遷移選択時のボタン
	Sprite transGameGraph;				//ゲーム遷移選択時のボタン
	bool transitionFlag_Title;			//タイトルへのセット
	bool transitionFlag_Game;			//ゲームへのセット
	int timerHour, timerMin, timerSec;	//タイマーの中身を格納

	VECTOR screen;			//画面サイズ
};

