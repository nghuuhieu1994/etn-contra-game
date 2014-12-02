#include "CTimeSpanDx9.h"

CTimeSpanDx9::CTimeSpanDx9()
{
	this->m_Ticks = 0;
}
CTimeSpanDx9::CTimeSpanDx9(UINT64 Ticks)
{
	this->m_Ticks = Ticks;
}
CTimeSpanDx9::~CTimeSpanDx9()
{}
int CTimeSpanDx9::getMilliseconds()
{
	return (int)(m_Ticks / TicksPerMillisecond);
}
UINT64	CTimeSpanDx9::getTicks()
{
	return m_Ticks;
}

CTimeSpanDx9& CTimeSpanDx9::operator=(const CTimeSpanDx9 &Timesp)
{
	this->m_Ticks = Timesp.m_Ticks;
	return *this;
}
