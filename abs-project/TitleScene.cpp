#include "DxLib.h"
#include "TitleScene.h"


TitleScene::TitleScene()
{
}

TitleScene::TitleScene(VECTOR screen)
{
	this->screen = screen;
	count = 0;
}


TitleScene::~TitleScene()
{
}
//イニシャライズ
void TitleScene::Initialize(void)
{
}
//更新
void TitleScene::Update(Button button, std::unique_ptr<Timer>& timer)
{
	scene = Scene::None;
	//spaceが押されたらゲームシーンをセットする関数に飛ぶ
	if (button.nowButton.Space == true && button.oldButton.Space == false)
	{
		TransltionScene();
	}
}
//ゲームシーンをセットする
void TitleScene::TransltionScene(void)
{
 	scene = Scene::Game;
}
//描画
void TitleScene::Draw(void)
{
	if ((count++ /30) %2 == 0)
	{
		DrawString(screen.x / 2 - 20, screen.y - 100, "please_push_space", 0xffffff, true);
	}
}