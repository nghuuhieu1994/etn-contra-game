#ifndef __ANIMATION_H__
#define __ANIMATION_H__
#include "RectangleDx9.h"
#include "CGameTimeDx9.h"
class CAnimationDx9
{
private:

	int		m_TotalFrame;
	// Time to render next frame
	//int		m_TimeNextFrame;
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
	void nextFrame();
	void UpdateAnimation(CGameTimeDx9* gameTime, int timeAnimation);
	~CAnimationDx9();
};


#endif