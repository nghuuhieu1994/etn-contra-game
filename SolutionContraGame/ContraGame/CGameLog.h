#ifndef __GAME_LOG__
#define __GAME_LOG__

#include <string>
#include "FrameworkDefineMacro.h"
using namespace std;

class CGameLog
{
public:

	static CGameLog* getInstance();

	static CGameLog* getInstance(string ModuleName);

	void SaveInfo(string Information);

	void SaveError(string Error);

	void SaveFloatNumber(float Number);
	string m_computerName;

	string GetCurrentDate();
	string GetOutFileName();
	string GetDateFileName();
private:

	CGameLog();

	~CGameLog();

	static CGameLog* s_Instance;

	//string m_LogFileName;

	string m_CurrentModuleName;
};

#endif