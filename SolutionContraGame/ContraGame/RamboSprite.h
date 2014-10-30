#include "SpriteManager.h"
#ifndef __RAMBO_MOVE_SPRITE__
#define __RAMBO_MOVE_SPRITE__

class RamboSprite
{
	int m_inversePositionY;
	float timeAnimation;
	CSpriteDx9* m_TopRight;
	CSpriteDx9* m_BottomRight;
	CSpriteDx9* m_Run;
	CSpriteDx9* m_Shoot;
	CSpriteDx9* m_Body;
	CSpriteDx9* m_Leg;
	D3DXVECTOR3 m_PositionBody;
	D3DXVECTOR3 m_PositionLeg;
public:
	RamboSprite(void);
	void UpdateAnimation();
	void Reset();
	D3DXVECTOR2 GetFrameSize() { return D3DXVECTOR2(30, 74); }
	void Render(LPD3DXSPRITE spriteHandle, D3DXVECTOR2 position, ESpriteEffect effect, float rotateAngle, float scale, float deep);
	virtual ~RamboSprite(void);
};

#endif