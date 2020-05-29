#pragma once
#include "BaseScene.h"
#include "GameTask.h"

class ResultScene :
	public BaseScene
{
public:
	ResultScene();
	~ResultScene();
	void Update(Button button);
	void TransltionScene(Scene scene);
	void Draw(void);
	Scene GetScene(void) { return scene; };
	void ConversionTitle(void);
	void ConversionGame(void);
private:
	bool transitionFlag_Title;
	bool transitionFlag_Game;
};

