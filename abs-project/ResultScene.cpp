#include "DxLib.h"
#include "ImageMng.h"
#include "ResultScene.h"

#define FRAME 5
#define TIME_MAX 60

ResultScene::ResultScene()
{
}

ResultScene::ResultScene(VECTOR screen)
{
	this->screen = screen;
	//workPlayerGraphの初期化
	workPlayerGraph.pos = { 0,0,0 };
	workPlayerGraph.Graph = workPlayerGraph.W = workPlayerGraph.H = 0;
	//transTitleGraphの初期化
	transTitleGraph.pos = { 0,0,0 };
	transTitleGraph.Graph = transTitleGraph.W = transTitleGraph.H = 0;
	//transGameGraphの初期化
	transTitleGraph.pos = { 0,0,0 };
	transTitleGraph.Graph = transTitleGraph.W = transTitleGraph.H = 0;

	//イニシャライズ
	Initialize();
	//フラグ等の設定
	transitionFlag_Title = true;
	transitionFlag_Game = false;
	timerHour = timerMin = timerSec = 999;
	
}

ResultScene::~ResultScene()
{
}

//イニシャライズ
void ResultScene::Initialize(void)
{
	//workPlayerGraphの設定
	workPlayerGraph.Graph = ImageMng::GetInstance().GetID("image/gameover3.png")[0];
	GetGraphSize(workPlayerGraph.Graph, &workPlayerGraph.W, &workPlayerGraph.H);
	workPlayerGraph.pos = { (float)(screen.x - workPlayerGraph.W *1.25), 0 };
	//transTitleGraphの設定
	transTitleGraph.Graph = ImageMng::GetInstance().GetID("image/title.png")[0];
	GetGraphSize(transTitleGraph.Graph, &transTitleGraph.W, &transTitleGraph.H);
	transTitleGraph.pos = {screen.x /5, screen.y *2 /6 - transTitleGraph.H /2 };
	//transGameGraphの設定
	transGameGraph.Graph = ImageMng::GetInstance().GetID("image/game.png")[0];
	GetGraphSize(transGameGraph.Graph, &transGameGraph.W, &transGameGraph.H);
	transGameGraph.pos = {screen.x /5, screen.y * 4 /6 - transGameGraph.H /2 };
}


//更新
void ResultScene::Update(Button button, std::unique_ptr<Timer>& timer)
{
	if (!(timerHour != 999 && timerMin != 999 && timerSec != 999))
	{
		timerHour = timer->GetTimer().hour.actual;
		timerMin = timer->GetTimer().minute.actual;
		timerSec = timer->GetTimer().second.actual;
	}
	//遷移差を決める
	if (button.nowButton.Up_Chair == true)
	{
		ConversionTitle();
	}
	if (button.nowButton.Down_Chair == true)
	{
		ConversionGame();
	}
	scene = Scene::None;
	//スペースが押されたら遷移する
	if (button.nowButton.Space == true && button.oldButton.Space == false)
	{
		//うえで決めた遷移先に遷移する
		if (transitionFlag_Title)
		{
			TransltionScene(Scene::Title);
		}
		else if (transitionFlag_Game)
		{
			TransltionScene(Scene::Game);
		}
		else
		{
			TransltionScene(Scene::Title);
		}
	}
}
//決めた遷移先をセットする
void ResultScene::TransltionScene(Scene scene)
{
	this->scene = scene;
}
//描画
void ResultScene::Draw(void)
{
	DrawBox(0, 0, screen.x, screen.y, 0xffffff,true);
	DrawGraph(workPlayerGraph.pos.x, workPlayerGraph.pos.y, workPlayerGraph.Graph, false);
	//リザルト表示
	if (timerHour <= 0)
	{
		DrawFormatString(screen.x *2 /3, screen.y - (screen.y - workPlayerGraph.H), 
						 0x000000, "%d分%d秒休憩短縮", 
						 TIME_MAX - timerMin, TIME_MAX - timerSec);
	}
	else if(timerHour == 1 && timerMin == 0)
	{
		DrawString(screen.x *2 /3, screen.y - (screen.y - workPlayerGraph.H),
				   "定刻通りに仕事再開", 0x000000);
	}
	else
	{
		DrawFormatString(screen.x *2 /3, screen.y - (screen.y - workPlayerGraph.H), 
						 0x000000, "%d時%d分%d秒まで休憩延長", timerHour, timerMin, timerSec);
	}
	//遷移先選択表示
	if (transitionFlag_Title == true && transitionFlag_Game == false)
	{
		this->DrawLineBox(transTitleGraph);
	}
	else if(transitionFlag_Title == false && transitionFlag_Game == true)
	{
		this->DrawLineBox(transGameGraph);
	}
	else
	{
		this->DrawLineBox(transTitleGraph);
	}
	DrawGraph(transTitleGraph.pos.x, transTitleGraph.pos.y, transTitleGraph.Graph, true);
	DrawGraph(transGameGraph.pos.x, transGameGraph.pos.y, transGameGraph.Graph, true);
}

//遷移先の設定を枠線で囲う
void ResultScene::DrawLineBox(Sprite transGraph)
{
	DrawBox(transGraph.pos.x - FRAME, transGraph.pos.y - FRAME,
			transGraph.pos.x + transGraph.W + FRAME, 
			transGraph.pos.y + transGraph.H + FRAME, 0x000000, true);
}

//遷移先をタイトルにセットする
void ResultScene::ConversionTitle(void)
{
	transitionFlag_Title = true;
	transitionFlag_Game = false;
}

//遷移先をゲームにセットする
void ResultScene::ConversionGame(void)
{
	transitionFlag_Title = false;
	transitionFlag_Game = true;
}
