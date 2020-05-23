#include "DxLib.h"
#include "GameTask.h"
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrecInstance, LPSTR lpCmdline, int nCmdline)
{
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		GameTask::GetInstance().Run();
	}
	GameTask::GetInstance().Destroy();
	DxLib_End();	// DX×²ÌŞ×Ø‚ÌI—¹ˆ—
	return 0;	// ‚±‚ÌÌßÛ¸Ş×Ñ‚ÌI—¹
}