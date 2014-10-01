#include "CGameLog.h"
#include <fstream>
#include <time.h>
#include <windows.h>
#include <tchar.h>

using namespace std;

CGameLog* CGameLog::s_Instance = 0;

CGameLog::CGameLog()
{
	this->m_LogFileName = "../gamelog.log";

	char nameBuf[17];
	DWORD nameBufSize;

	nameBufSize = 16;

	GetComputerName(nameBuf, &nameBufSize);

	m_computerName = nameBuf;
}

CGameLog::~CGameLog()
{
	if (this->s_Instance != NULL)
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

CGameLog* CGameLog::GetInstance()
{
	if (s_Instance == NULL)
	{
		s_Instance = new CGameLog();
	}
	s_Instance->m_CurrentModuleName = "Unknown Module!!!";
	return s_Instance;
}

CGameLog* CGameLog::GetInstance(string ModuleName)
{
	if (s_Instance == NULL)
	{
		s_Instance = new CGameLog();
	}
	s_Instance->m_CurrentModuleName = ModuleName;
	return s_Instance;
}

void CGameLog::SetNameLogFile(string NameLogFile)
{
	if (s_Instance != NULL)
	{
		s_Instance->m_LogFileName = NameLogFile; 
	}
}

void CGameLog::SaveInfo(string Information)
{
	fstream fLog(m_LogFileName.c_str(), ios::out | ios::app);

	fLog << "[Computer Name: " << m_computerName << "]" << endl;
	fLog << "[" << this->GetCurrentDate() << "]" << endl;
	fLog << "Current Working Module: " << m_CurrentModuleName << endl;
    fLog << "Info : " << Information << endl << endl;

    fLog.close();
}

void CGameLog::SaveFloatNumber(float Number)
{
	fstream fLog(m_LogFileName.c_str(), ios::out | ios::app);

	fLog << "[Computer Name: " << m_computerName << "]" << endl;
	fLog << "[" << this->GetCurrentDate() << "]" << endl;
	fLog << "Current Working Module: " << m_CurrentModuleName << endl;
    fLog << "ElapsedMillisecond : " << Number << endl << endl;

    fLog.close();
}

void CGameLog::SaveError(string Error)
{
	fstream fLog(m_LogFileName.c_str(), ios::out | ios::app);

	fLog << "[Computer Name: " << m_computerName << "]" << endl;
	fLog << "[" << this->GetCurrentDate() << "]" << endl;
    fLog << "Current Working Module: " << m_CurrentModuleName << endl;
    fLog<<"Error : "<<Error<<endl<<endl;

    fLog.close();
}