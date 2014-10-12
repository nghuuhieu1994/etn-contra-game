#include "CGame.h"
#include "CGameLog.h"
#include "Markup.h"

#define WINDOWS_MODE
#if defined WINDOWS_MODE
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
#endif
#if defined CONSOLE_MODE
class GameObject
{
public:
	int _ID;
	int _X;
	int _Y;
	int _Type;
public:
	void Deserialize(const char *childContent)
	{
		CMarkup xml(childContent);
		xml.FindElem();
		_ID = atoi(xml.GetAttrib("ID").c_str());
		_Type = atoi(xml.GetAttrib("Type").c_str());
		_X = atoi(xml.GetAttrib("X").c_str());
		_Y = atoi(xml.GetAttrib("Y").c_str());
	}
	int GetID();
	int GetX();
	int GetY();
	int GetType();
};
int main()
{
	CMarkup xml;
	xml.Load("resources\\Map\\1\\contra_map1.xml");
	//CMarkup xml("resources\\Map\\1\\contra_map1.xml");
	
	GameObject *_GameObject;
	xml.FindElem("Objects");
	xml.IntoElem();
	while (xml.FindElem("Object"))
	{
		_GameObject = new GameObject();
		_GameObject->Deserialize(xml.GetSubDoc().c_str());
	}
	return 0;
}

#endif