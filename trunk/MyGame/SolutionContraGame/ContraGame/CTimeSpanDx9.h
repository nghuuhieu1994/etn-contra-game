#ifndef __TIMESPAN_H__
#define	__TIMESPAN_H__
#include <Windows.h>

class CTimeSpanDx9
{
private:
	UINT64	m_Ticks;
public:
	// we should fix this fucking const. cuz im feeling its wrought!

	// This is the fucking const ---> Ticks per Day
	static const UINT64	TicksPerDay				= 86400000000;
	// This is the fucking const ---> Ticks per Hour
	static const UINT64	TicksPerHour			= 3600000000;
	// This is the fucking const ---> Tick per Min
    static const UINT64 TicksPerMinute			= 60000000;
	// This is the fucking const ---> Tick per second
    static const UINT64 TicksPerSecond			= 1000000;
	// This is the fucking const ---> Tick per Milliseconds
    static const UINT64 TicksPerMillisecond		= 1000;

	// Constructor
	CTimeSpanDx9();
	// Constructor 1 parametor
	CTimeSpanDx9(UINT64 Ticks);

	// get Day
	float	getDays();
	// get Hours
	float	getHours();
	// get Mins
	float	getMins();
	// get Seconds
	float	getSeconds();
	// get Milliseconds
	float	getMilliseconds();

	// get Ticks
	UINT64	getTicks();

	// get Total Days
	UINT64	getTotalDays();
	// get Total Hours
	UINT64	getTotalHours();
	// get Total Mins
	UINT64	getTotalMins();
	// get Total Seconds
	UINT64	getTotalSeconds();
	// get Total Milliseconds
	UINT64	getTotalMilliseconds();

	// overload operator
	CTimeSpanDx9& operator=(const CTimeSpanDx9& Timesp);
	// Destructor
	~CTimeSpanDx9();
};

#endif