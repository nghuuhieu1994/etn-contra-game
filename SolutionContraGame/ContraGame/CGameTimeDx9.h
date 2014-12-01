#ifndef __GAMETIME_H__
#define	__GAMETIME_H__
#include <Windows.h>
#include "CTimeSpanDx9.h"

class CGameTimeDx9
{
private:
	
	static CGameTimeDx9*	s_Instance;

	CTimeSpanDx9			m_ElapsedGameTime;
	
	LARGE_INTEGER			m_Query;
	
	float					m_FreQuency;
	
	LONGLONG				StartTicks;
	
	LONGLONG				LastTicks;
	
	LONGLONG				CurTicks;

	CGameTimeDx9();

	CGameTimeDx9(CTimeSpanDx9& elapsedGameTime, CTimeSpanDx9& totalGameTime);

public:
	
	static CGameTimeDx9* getInstance();
	
	void InitGameTime();
	void ResetLastTick();
	void UpdateGameTime();
	
	CTimeSpanDx9	getElapsedGameTime();
	
	void			setElapsedGameTime(CTimeSpanDx9& elapsedGameTime);
	
};
#endif