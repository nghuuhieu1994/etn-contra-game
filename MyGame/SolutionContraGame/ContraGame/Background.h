#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__
#include "CGameLog.h"
#include "SpriteManager.h"
#include "CSpriteDx9.h"
#include "CGlobal.h"

class Background
{
	CSpriteDx9*		m_tileSet;
	int				m_Height;
	int				m_Width;
	int				m_Row;
	int				m_Column;
	int**			m_TileMap;
public:
	Background();
	void Initialize(string filePath);
	void Render(LPD3DXSPRITE spriteHandle);
	void Release();
	~Background();
};

#endif