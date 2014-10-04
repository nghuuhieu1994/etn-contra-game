#include "CAnimationDx9.h"

CAnimationDx9::CAnimationDx9()
{
	this->m_columnFrame			= 0;
	this->m_heightFrame			= 0;
	this->m_index_End			= 0;
	this->m_index_Start			= 0;
	this->m_index_Current		= 0;
	this->m_sourceRect			= 0;
	this->m_timeAnimation		= 0;
	this->m_totalFrame			= 0;
	this->m_widthFrame			= 0;
}
CAnimationDx9::CAnimationDx9(int width, int height, int col, int total)
{
	this->m_widthFrame				= width;
	this->m_heightFrame				= height;
	this->m_columnFrame				= col;
	this->m_totalFrame				= total;

	this->m_index_Current			= 0;
	this->m_index_Start				= 0;
	this->m_index_End				= total - 1;

	this->m_sourceRect				= new RECT();
	this->m_sourceRect->top			= 0;
	this->m_sourceRect->left		= 0;
	this->m_sourceRect->bottom		= m_heightFrame;
	this->m_sourceRect->right		= m_widthFrame;

	this->m_timeAnimation			= 0;
}

CAnimationDx9::CAnimationDx9(const CAnimationDx9& Animation)
{
	this->m_columnFrame				= Animation.m_columnFrame;
	this->m_heightFrame				= Animation.m_heightFrame;
	this->m_index_End				= Animation.m_index_End;
	this->m_index_Start				= Animation.m_index_Start;
	this->m_index_Current			= Animation.m_index_Current;
	this->m_timeAnimation			= 0;
	this->m_totalFrame				= Animation.m_totalFrame;
	this->m_widthFrame				= Animation.m_widthFrame;


	this->m_sourceRect				= new RECT();
	this->m_sourceRect->top			= Animation.m_sourceRect->top;
	this->m_sourceRect->left		= Animation.m_sourceRect->left;
	this->m_sourceRect->right		= Animation.m_sourceRect->right;
	this->m_sourceRect->bottom		= Animation.m_sourceRect->bottom;
}

CAnimationDx9::~CAnimationDx9()
{
	SAFE_DELETE(this->m_sourceRect);
}

void CAnimationDx9::setIndexStart(int _start)
{
	this->m_index_Start = _start;
}

void CAnimationDx9::setIndexEnd(int _end)
{
	this->m_index_End = _end;
}

RECT* CAnimationDx9::getSourceRect()
{
	return m_sourceRect;
}

void CAnimationDx9::NextFrame()
{
	this->m_index_Current ++;
	if(this->m_index_Current > this->m_index_End)
	{
		this->m_index_Current = this->m_index_Start;
	}
}

void CAnimationDx9::UpdateAnimation(int timeNexframe)
{
	this->m_timeAnimation += (int)CGameTimeDx9::getInstance()->getElapsedGameTime().getMilliseconds();

	if(this->m_timeAnimation > timeNexframe)
	{
		NextFrame();
		m_sourceRect->top			= (m_index_Current / m_columnFrame) * m_heightFrame;
		m_sourceRect->left			= (m_index_Current % m_columnFrame) * m_widthFrame;
		m_sourceRect->bottom		= m_sourceRect->top + m_heightFrame;
		m_sourceRect->right			= m_sourceRect->left + m_widthFrame;
		this->m_timeAnimation = 0;
	}
}

void CAnimationDx9::NextSourceRect()
{
	m_sourceRect->top			= (m_index_Current / m_columnFrame) * m_heightFrame;
	m_sourceRect->left			= (m_index_Current % m_columnFrame) * m_widthFrame;
	m_sourceRect->bottom		= m_sourceRect->top + m_heightFrame;
	m_sourceRect->right			= m_sourceRect->left + m_widthFrame;
}

D3DXVECTOR2 CAnimationDx9::getFrameSize()
{
	return D3DXVECTOR2((float)this->m_widthFrame, (float)this->m_heightFrame);
}

void CAnimationDx9::Release()
{
	SAFE_DELETE(m_sourceRect);
}