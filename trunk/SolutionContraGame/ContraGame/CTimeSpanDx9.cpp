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
float CTimeSpanDx9::getDays()
{
	return (float)m_Ticks / TicksPerDay;
}
float	CTimeSpanDx9::getHours()
{
	return (float)(m_Ticks) / TicksPerHour;
}
float	CTimeSpanDx9::getMins()
{
	return (float)(m_Ticks) / TicksPerMinute;
}
float CTimeSpanDx9::getSeconds()
{
	return (float)(m_Ticks) / TicksPerSecond;
}
float CTimeSpanDx9::getMilliseconds()
{
	return (float)(m_Ticks) / TicksPerMillisecond;
}
UINT64	CTimeSpanDx9::getTicks()
{
	return m_Ticks;
}

UINT64 CTimeSpanDx9::getTotalDays()
{
	return m_Ticks / TicksPerDay;
}
UINT64 CTimeSpanDx9::getTotalHours()
{
	return m_Ticks / TicksPerHour;
}
UINT64 CTimeSpanDx9::getTotalMins()
{
	return m_Ticks / TicksPerMinute;
}
UINT64 CTimeSpanDx9::getTotalSeconds()
{
	return m_Ticks / TicksPerSecond;
}
UINT64 CTimeSpanDx9::getTotalMilliseconds()
{
	return m_Ticks / TicksPerMillisecond;
}
CTimeSpanDx9& CTimeSpanDx9::operator=(const CTimeSpanDx9 &Timesp)
{
	this->m_Ticks = Timesp.m_Ticks;
	return *this;
}
