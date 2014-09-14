#ifndef __CANIMATION_H__
#define __CANIMATION_H__
#include "CGameTimeDx9.h"
#include "CGameLog.h"

class CAnimationDx9
{
private:
	// Width frame
	int				widthFrame;
	// height frame
	int				heightFrame;

	// num col frame
	int				colFrame;
	// total frame
	int				totalFrame;

	// Frame start to rend animation
	int				index_Start;
	// Framew end to rend animation
	int				index_End;
	// current index to rend animation
	int				index_Current;
	// Time to next frame
	int				timeAnimation;

	// RECT using for cut frame
	RECT*			sourceRect;
public:
	// contructor
	CAnimationDx9();
	// constructor with parameter
	CAnimationDx9(int width,int height, int col, int total);
	// cpy contructor
	CAnimationDx9(const CAnimationDx9& Animation);
	// destructor
	~CAnimationDx9();
	// set index of frame start to make animation
	void setIndexStart(int _start);
	// set index of frame end of this animation action
	void setIndexEnd(int _end);
	// return the sourceRectangle, it contain all info to draw current frame to screen
	RECT* getSourceRect();
	// set current frame = next frame ---> make animation
	void NextFrame();
	// Update animation action
	void UpdateAnimation(CGameTimeDx9* gameTime, int timeNexframe);
	// relese this animation action
	void Release();
};

#endif