#ifndef __GAME_LOG__
#define __GAME_LOG__


#include <string>

using namespace std;

class CGameLog
{
public:
	
	static CGameLog* GetInstance();
	
	static CGameLog* GetInstance(string ModuleName);
	
	void SetNameLogFile(string NameLogFile);
	
	void SaveInfo(string Information);
	
	void SaveError(string Error);
	
	void SaveFloatNumber(float Number);
	string m_computerName;

	string GetCurrentDate();
private:
	
	CGameLog();
	
	~CGameLog();
	
	static CGameLog* s_Instance;
	
	string m_LogFileName;
	
	string m_CurrentModuleName;
};

#endif