#include "CGameTimeDx9.h"

CGameTimeDx9* CGameTimeDx9::s_Instance = NULL;

CGameTimeDx9::CGameTimeDx9()
{
	this->m_ElapsedGameTime = CTimeSpanDx9(1);
	this->m_TotalGameTime	= CTimeSpanDx9(1);
}
CGameTimeDx9::CGameTimeDx9(CTimeSpanDx9 &elapsedGameTime, CTimeSpanDx9 &totalGameTime)
{
	this->m_ElapsedGameTime = elapsedGameTime;
	this->m_TotalGameTime	= totalGameTime;
}

CGameTimeDx9* CGameTimeDx9::getInstance()
{
	if(s_Instance == NULL)
	{
		s_Instance = new CGameTimeDx9();
	}
	return s_Instance;
}

void CGameTimeDx9::InitGameTime()
{
	QueryPerformanceFrequency(&this->m_Query);
	m_FreQuency = (float)m_Query.QuadPart / 1000000;
	QueryPerformanceCounter(&this->m_Query);
	StartTicks = LastTicks = this->m_Query.QuadPart;
}
void CGameTimeDx9::UpdateGameTime()
{
	QueryPerformanceCounter(&this->m_Query);
	CurTicks = this->m_Query.QuadPart;
	if(((CurTicks - LastTicks) / m_FreQuency) <= CTimeSpanDx9::TicksPerMillisecond)
	{
			return;
	}
	else
		{
			this->setTotalGameTime(CTimeSpanDx9((UINT64)((CurTicks - StartTicks) / m_FreQuency)));
			this->setElapsedGameTime(CTimeSpanDx9((UINT64)((CurTicks - LastTicks) / m_FreQuency)));
			LastTicks = CurTicks;
		}
}

void CGameTimeDx9::setElapsedGameTime(CTimeSpanDx9 &elapsedGameTime)
{
	this->m_ElapsedGameTime = elapsedGameTime;
}
void CGameTimeDx9::setTotalGameTime(CTimeSpanDx9 &totalGameTime)
{
	this->m_TotalGameTime = totalGameTime;
}
CTimeSpanDx9 CGameTimeDx9::getElapsedGameTime()
{
	return m_ElapsedGameTime;
}
CTimeSpanDx9 CGameTimeDx9::getTotalGameTime()
{
	return m_TotalGameTime;
}