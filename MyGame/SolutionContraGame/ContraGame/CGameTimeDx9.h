#ifndef __GAMETIME_H__
#define	__GAMETIME_H__
#include <Windows.h>
#include "CTimeSpanDx9.h"

class CGameTimeDx9
{
private:
	
	CTimeSpanDx9	m_ElapsedGameTime;
	
	CTimeSpanDx9	m_TotalGameTime;
	
	LARGE_INTEGER	m_Query;
	
	float			m_FreQuency;
	// start time Ticks
	UINT64			StartTicks;
	// Last Tick update
	UINT64			LastTicks;
	// Current Ticks Update
	UINT64			CurTicks;
public:
	// Constructor none parametor
	CGameTimeDx9();
	// Constructor 2 parametor
	CGameTimeDx9(CTimeSpanDx9& elapsedGameTime, CTimeSpanDx9& totalGameTime);
	// Init GameTime
	void InitGameTime();
	// GameTime Update
	void UpdateGameTime();
	// Set ElapsedGameTime
	CTimeSpanDx9	getElapsedGameTime();
	// Set TotalGameTime
	CTimeSpanDx9	getTotalGameTime();
	// set ElapsedGameTime
	void			setElapsedGameTime(CTimeSpanDx9& elapsedGameTime);
	// set TotalGameTime
	void			setTotalGameTime(CTimeSpanDx9& totalGameTime);
};
#endif