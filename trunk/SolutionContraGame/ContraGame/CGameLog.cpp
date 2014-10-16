#include "CGameLog.h"
#include <fstream>
#include <time.h>
#include <windows.h>
#include <tchar.h>
#include <algorithm>
using namespace std;

CGameLog* CGameLog::s_Instance = 0;

CGameLog::CGameLog()
{
	//this->m_LogFileName = "../gamelog.log";

	char nameBuf[17];
	DWORD nameBufSize;

	nameBufSize = 16;

	GetComputerName(nameBuf, &nameBufSize);

	m_computerName = nameBuf;
}

CGameLog::~CGameLog()
{
	if (this->s_Instance != 0)
	{
		delete this->s_Instance;
	}
}

string CGameLog::GetCurrentDate()
{
	time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
	tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "Date: %d-%m-%Y | Time: %X", &tstruct);

    return buf;
}

string CGameLog::GetDateFileName()
{
	time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
	tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "Date_%d_%m_%Y_Time_%X", &tstruct);
	string temp = buf;

	replace(temp.begin(), temp.end(), ':', '_');
    return temp;
}

CGameLog* CGameLog::getInstance()
{
	if (s_Instance == 0)
	{
		s_Instance = new CGameLog();
	}
	s_Instance->m_CurrentModuleName = "Unknown Module!!!";
	return s_Instance;
}

CGameLog* CGameLog::getInstance(string ModuleName)
{
	if (s_Instance == 0)
	{
		s_Instance = new CGameLog();
	}

	s_Instance->m_CurrentModuleName = ModuleName;
	return s_Instance;
}

string CGameLog::GetOutFileName()
{
	string outFileName = "../gamelog/gamelog_";
	outFileName += m_computerName;
	outFileName += "_";
	outFileName += GetDateFileName();
	outFileName += ".log";
	return outFileName;
}

void CGameLog::SaveInfo(string Information)
{

	fstream fLog(GetOutFileName().c_str(), ios::out| ios::app);
	
	//fLog << "[Computer Name: " << m_computerName << "]" << endl;
	//fLog << "[" << this->GetCurrentDate() << "]" << endl;
	fLog << "Current Working Module: " << m_CurrentModuleName << endl;
    fLog << "Info : " << Information;
    fLog.close();
}

void CGameLog::SaveFloatNumber(float Number)
{
	fstream fLog(GetOutFileName().c_str(), ios::out | ios::app);
	
	//fLog << "[Computer Name: " << m_computerName << "]" << endl;
	//fLog << "[" << this->GetCurrentDate() << "]" << endl;
	fLog << "Current Working Module: " << m_CurrentModuleName << endl;
    fLog << "ElapsedMillisecond : " << Number;

    fLog.close();
}

void CGameLog::SaveError(string Error)
{
	fstream fLog(GetOutFileName().c_str(), ios::out| ios::app);

	//fLog << "[Computer Name: " << m_computerName << "]" << endl;
	//fLog << "[" << this->GetCurrentDate() << "]" << endl;
    fLog << "Current Working Module: " << m_CurrentModuleName << endl;
    fLog<<"Error : "<<Error;

    fLog.close();
}