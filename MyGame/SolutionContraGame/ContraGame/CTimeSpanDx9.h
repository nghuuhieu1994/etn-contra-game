#ifndef __TIMESPAN_H__
#define	__TIMESPAN_H__
#include <Windows.h>

class CTimeSpanDx9
{
private:
	UINT64	m_Ticks;
public:
	

	
	static const UINT64	TicksPerDay				= 86400000000;
	
	static const UINT64	TicksPerHour			= 3600000000;
	
    static const UINT64 TicksPerMinute			= 60000000;
	
    static const UINT64 TicksPerSecond			= 1000000;
	
    static const UINT64 TicksPerMillisecond		= 1000;

	
	CTimeSpanDx9();
	
	CTimeSpanDx9(UINT64 Ticks);

	
	float	getDays();
	
	float	getHours();
	
	float	getMins();
	
	float	getSeconds();
	
	float	getMilliseconds();

	
	UINT64	getTicks();

	
	UINT64	getTotalDays();
	
	UINT64	getTotalHours();
	
	UINT64	getTotalMins();
	
	UINT64	getTotalSeconds();
	
	UINT64	getTotalMilliseconds();

	
	CTimeSpanDx9& operator=(const CTimeSpanDx9& Timesp);
	
	~CTimeSpanDx9();
};

#endif