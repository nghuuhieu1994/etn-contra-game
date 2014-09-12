#include "CAnimationDx9.h"

CAnimationDx9::CAnimationDx9()
{
	curFrame = 0;
	startFrame = 5;
	endFrame = 7;
	m_LocalTime = 0;
}
CAnimationDx9::CAnimationDx9(int widthFrame, int heightFrame, int totalFrame, int colFrame, int rowFrame)
{
	this->curFrame				= 0;
	this->startFrame			= 0;
	this->endFrame				= 0;

	this->m_Rect				= new RECT();

	this->m_Rect->top			= 0;
	this->m_Rect->left			= 0;
	
	//this->m_TimeNextFrame		= 100;
	this->m_TotalFrame			= 1;
	this->m_LocalTime			= 0;
}
CAnimationDx9::CAnimationDx9(const CAnimationDx9* otherAnimation)
{
	this->curFrame			= otherAnimation->curFrame;
	this->endFrame			= otherAnimation->endFrame;
	this->m_LocalTime		= otherAnimation->m_LocalTime;
	this->m_Rect			= new RECT(*otherAnimation->m_Rect);
	//this->m_TimeNextFrame	= otherAnimation->m_TimeNextFrame;
	this->m_TotalFrame		= otherAnimation->m_TotalFrame;
	this->startFrame		= otherAnimation->startFrame;
}

int CAnimationDx9::GetCurrentFrameIndex()
{
	return curFrame;
}

void CAnimationDx9::setStartFrame(int startframe)
{
	this->startFrame = startframe;
}

void CAnimationDx9::setEndFrame(int endframe)
{
	this->endFrame = endframe;
}

void CAnimationDx9::nextFrame()
{
	this->curFrame++;
	if(this->curFrame > this->endFrame || this->curFrame < this->startFrame)
	{
		this->curFrame = this->startFrame;
	}
}

RECT* CAnimationDx9::getSourceRectangle()
{
	return m_Rect;
}

void CAnimationDx9::setSourceRectangle(const RECT* Rect)
{
	m_Rect->bottom = Rect->bottom;
	m_Rect->left = Rect->left;
	m_Rect->right = Rect->right;
	m_Rect->top = Rect->top;
}

void CAnimationDx9::UpdateAnimation(CGameTimeDx9* gameTime, int timeAnimation)
{
	m_LocalTime += gameTime->getElapsedGameTime().getMilliseconds();
	if(m_LocalTime > timeAnimation)
	{
		this->nextFrame();
		m_LocalTime = 0;
	}
}