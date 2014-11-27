#ifndef __CANIMATION_H__
#define __CANIMATION_H__
#include "CGameTimeDx9.h"
#include "CGameLog.h"
#include "FrameworkDefineMacro.h"
#include <d3d9.h>
#include <d3dx9.h>

class CAnimationDx9
{
private:
	int				m_widthFrame;

	int				m_heightFrame;

	int				m_columnFrame;

	int				m_rowFrame;

	int				m_totalFrame;

	int				m_index_Start;

	int				m_index_End;

	int				m_index_Current;

	int				m_timeAnimation;

	RECT*			m_sourceRect;
	int				m_inverseNumber;
public:

					CAnimationDx9();

					CAnimationDx9(int width,int height, int column, int total);

					CAnimationDx9(const CAnimationDx9& Animation);

					~CAnimationDx9();

	void			setIndexStart(int _start);

	void			setIndexEnd(int _end);

	void			setCurrentFrame(int Index);

	void			setSourceRectAtIndex(int Index);

	int				getCurrentIndex(){ return this->m_index_Current; }
	int				getStartIndex() { return this->m_index_Start; }
	int				getEndIndex() { return this->m_index_End; }

	int				getRowFrame(){ return this->m_rowFrame; }
	int				getColumnFrame(){ return this->m_columnFrame; }

	RECT*			getSourceRect();
	void			setSourceRect(RECT _rect);
	void			NextFrame();

	void			NextFrameInverse();

	void			UpdateAnimation(int timeNexframe);

	void			UpdateAnimationInverse(int timeNextFrame);

	void			CreateSourceRectangle();

	D3DXVECTOR2		getFrameSize();

	void			Reset();

	void			Release();
};

#endif