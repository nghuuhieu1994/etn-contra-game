#include "CAnimationDx9.h"

CAnimationDx9::CAnimationDx9()
{
	this->colFrame = 0;
	this->heightFrame = 0;
	this->index_End = 0;
	this->index_Start = 0;
	this->index_Current = 0;
	this->sourceRect = NULL;
	this->timeAnimation = 0;
	this->totalFrame = 0;
	this->widthFrame = 0;
}
CAnimationDx9::CAnimationDx9(int width, int height, int col, int total)
{
	this->widthFrame = width;
	this->heightFrame = height;
	this->colFrame = col;
	this->totalFrame = total;

	this->index_Current = 0;
	this->index_Start = 0;
	this->index_End = 0;

	this->sourceRect = new RECT();
	this->sourceRect->top = 0;
	this->sourceRect->left = 0;
	this->sourceRect->bottom = heightFrame;
	this->sourceRect->right = widthFrame;

	this->timeAnimation = 0;
}

CAnimationDx9::CAnimationDx9(const CAnimationDx9& Animation)
{
	this->colFrame = Animation.colFrame;
	this->heightFrame = Animation.heightFrame;
	this->index_End = Animation.index_End;
	this->index_Start = Animation.index_Start;
	this->index_Current = Animation.index_Current;
	this->timeAnimation = 0;
	this->totalFrame = Animation.totalFrame;
	this->widthFrame = Animation.widthFrame;


	this->sourceRect = new RECT();
	this->sourceRect->top = Animation.sourceRect->top;
	this->sourceRect->left = Animation.sourceRect->left;
	this->sourceRect->right = Animation.sourceRect->right;
	this->sourceRect->bottom = Animation.sourceRect->bottom;
}
CAnimationDx9::~CAnimationDx9()
{
	SAFE_DELETE(this->sourceRect);
}
void CAnimationDx9::setIndexStart(int _start)
{
	this->index_Start = _start;
}
void CAnimationDx9::setIndexEnd(int _end)
{
	this->index_End = _end;
}
RECT* CAnimationDx9::getSourceRect()
{
	return sourceRect;
}
void CAnimationDx9::NextFrame()
{
	this->index_Current ++;
	if(this->index_Current > this->index_End)
		this->index_Current = this->index_Start;
}
void CAnimationDx9::UpdateAnimation(CGameTimeDx9* gameTime, int timeNexframe)
{
	this->timeAnimation += (int)gameTime->getElapsedGameTime().getMilliseconds();
	if(this->timeAnimation > timeNexframe)
	{
		NextFrame();
		this->timeAnimation = 0;
	}
	sourceRect->top = (index_Current / colFrame) * heightFrame;
	sourceRect->left = (index_Current % colFrame) * widthFrame;
	sourceRect->bottom		= sourceRect->top + heightFrame;
	sourceRect->right		= sourceRect->left + widthFrame;
}

D3DXVECTOR2 CAnimationDx9::GetFrameSize()
{
	return D3DXVECTOR2(this->widthFrame, this->heightFrame);
}

void CAnimationDx9::Release()
{
	SAFE_DELETE(sourceRect);
}