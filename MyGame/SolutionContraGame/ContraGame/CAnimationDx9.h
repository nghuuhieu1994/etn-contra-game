#ifndef __ANIMATION_H__
#define __ANIMATION_H__
#include "RectangleDx9.h"
#include "CGameTimeDx9.h"
class CAnimationDx9
{
private:
	// total frame in sheet
	int		m_TotalFrame;
	// Local time to make animation
	float		m_LocalTime;
	// Rect using for render an frame
	RECT*	m_Rect;
	// index current frame u wanna render
	int		curFrame;
	// index start frame
	int		startFrame;
	// index end Frame
	int		endFrame;
public:
	CAnimationDx9();
	CAnimationDx9(int widthFrame, int heightFrame, int totalFrame, int colFrame, int rowFrame);
	CAnimationDx9(const CAnimationDx9* otherAnimation);
	void setStartFrame(int startframe);
	void setEndFrame(int endFrame);
	int GetCurrentFrameIndex();
	RECT* getSourceRectangle();
	void setSourceRectangle(const RECT* Rect);
	void nextFrame();
	void UpdateAnimation(CGameTimeDx9* gameTime, int timeAnimation);
	~CAnimationDx9();
};


#endif