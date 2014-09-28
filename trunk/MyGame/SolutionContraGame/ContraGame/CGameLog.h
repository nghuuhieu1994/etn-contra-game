#ifndef __GAME_LOG__
#define __GAME_LOG__

#define SAFE_DELETE(p)       if(p) { delete (p);     (p)=NULL; }

#define SAFE_DELETE_ARRAY(p) if(p) { delete[] (p);   (p)=NULL; }

#define SAFE_RELEASE(p)      if(p) { (p)->Release(); (p)=NULL; }

#define DIRECTINPUT_VERSION 0X0800

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
	
	string GetCurrentDate();
private:
	
	CGameLog();
	
	~CGameLog();
	
	static CGameLog* s_Instance;
	
	string m_LogFileName;
	
	string m_CurrentModuleName;
};

#endif