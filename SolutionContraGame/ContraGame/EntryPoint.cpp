#include "CGame.h"

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpStrCmdLine,
	int nShowCmd)
{
	CGameLog::getInstance("EntryPoint")->SaveInfo("Testing Game");
	
	CGame* Run = new CGame();
	Run->Initialize(hInstance, true);
	Run->Run();
	Run->Exit();
	
	return 0;
}