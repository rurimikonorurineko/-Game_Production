#pragma once
#include "BaseScene.h"
#include "GameTask.h"

class TitleScene :
	public BaseScene
{
public:
	TitleScene();
	TitleScene(VECTOR screen);
	~TitleScene();
	void Initialize(void);
	void Update(Button button, std::unique_ptr<Timer>& timer);
	void TransltionScene(void);					//次のシーンのセット
	void Draw(void);
	Scene GetScene(void) { return scene; };		//セットされているシーンを渡す
private:
	VECTOR screen;		//画面サイズ
	int count;			//点滅カウンタ
};

