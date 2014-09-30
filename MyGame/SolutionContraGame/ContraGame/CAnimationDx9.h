#ifndef __CANIMATION_H__
#define __CANIMATION_H__
#include "CGameTimeDx9.h"
#include "CGameLog.h"
#include "CGlobal.h"

#include <d3d9.h>
#include <d3dx9.h>

class CAnimationDx9
{
private:
	
	int				widthFrame;
	
	int				heightFrame;

	
	int				colFrame;
	
	int				totalFrame;

	
	int				index_Start;
	
	int				index_End;
	
	int				index_Current;
	
	int				timeAnimation;

	
	RECT*			sourceRect;
public:
	
	CAnimationDx9();
	
	CAnimationDx9(int width,int height, int col, int total);
	
	CAnimationDx9(const CAnimationDx9& Animation);
	
	~CAnimationDx9();
	
	void setIndexStart(int _start);
	
	void setIndexEnd(int _end);

	RECT* getSourceRect();
	
	void NextFrame();
	
	void UpdateAnimation(CGameTimeDx9* gameTime, int timeNexframe);

	D3DXVECTOR2 GetFrameSize();

	void Release();
};

#endif