#include "CGameTimeDx9.h"

CGameTimeDx9* CGameTimeDx9::s_Instance = 0;

CGameTimeDx9::CGameTimeDx9()
{
	this->m_ElapsedGameTime = CTimeSpanDx9(1);
}

CGameTimeDx9::CGameTimeDx9(CTimeSpanDx9 &elapsedGameTime, CTimeSpanDx9 &totalGameTime)
{
	this->m_ElapsedGameTime = elapsedGameTime;
}

CGameTimeDx9* CGameTimeDx9::getInstance()
{
	if(s_Instance == 0)
	{
		s_Instance = new CGameTimeDx9();
	}
	return s_Instance;
}

void CGameTimeDx9::InitGameTime()
{
	QueryPerformanceFrequency(&this->m_Query);
	m_FreQuency = (float)m_Query.QuadPart / 10000000;
	QueryPerformanceCounter(&this->m_Query);
	StartTicks = LastTicks = this->m_Query.QuadPart;
}
void CGameTimeDx9::UpdateGameTime()
{
	QueryPerformanceCounter(&this->m_Query);
	CurTicks = this->m_Query.QuadPart;
	if(((CurTicks - LastTicks) / m_FreQuency) < CTimeSpanDx9::TicksPerMillisecond)
	{
		return;
	}
	else
		{
			this->setElapsedGameTime( CTimeSpanDx9( ( (CurTicks - LastTicks) / m_FreQuency ) ));
			LastTicks = CurTicks;
		}
}

void CGameTimeDx9::setElapsedGameTime(CTimeSpanDx9 &elapsedGameTime)
{
	this->m_ElapsedGameTime = elapsedGameTime;
}
CTimeSpanDx9 CGameTimeDx9::getElapsedGameTime()
{
	return m_ElapsedGameTime;
}
