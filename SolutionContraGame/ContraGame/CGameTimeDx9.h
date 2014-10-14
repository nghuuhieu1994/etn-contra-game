#ifndef __GAMETIME_H__
#define	__GAMETIME_H__
#include <Windows.h>
#include "CTimeSpanDx9.h"

class CGameTimeDx9
{
private:
	
	static CGameTimeDx9* s_Instance;

	CTimeSpanDx9	m_ElapsedGameTime;
	
	CTimeSpanDx9	m_TotalGameTime;
	
	LARGE_INTEGER	m_Query;
	
	float			m_FreQuency;
	
	UINT64			StartTicks;
	
	UINT64			LastTicks;
	
	UINT64			CurTicks;

	CGameTimeDx9();

	CGameTimeDx9(CTimeSpanDx9& elapsedGameTime, CTimeSpanDx9& totalGameTime);

public:
	
	static CGameTimeDx9* getInstance();
	
	void InitGameTime();
	
	void UpdateGameTime();
	
	CTimeSpanDx9	getElapsedGameTime();
	
	CTimeSpanDx9	getTotalGameTime();
	
	void			setElapsedGameTime(CTimeSpanDx9& elapsedGameTime);
	
	void			setTotalGameTime(CTimeSpanDx9& totalGameTime);
};
#endif