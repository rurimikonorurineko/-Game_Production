#include "DxLib.h"
#include "GameTask.h"
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrecInstance, LPSTR lpCmdline, int nCmdline)
{
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		GameTask::GetInstance().Run();
	}
	GameTask::GetInstance().Destroy();
	DxLib_End();	// DXײ���؂̏I������
	return 0;	// ������۸��т̏I��
}