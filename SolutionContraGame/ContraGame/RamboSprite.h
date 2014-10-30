#ifndef __RAMBO_SPRITE_H__
#define __RAMBO_SPRITE_H__
#include "SpriteManager.h"

class RamboSprite
{
protected:
	CSpriteDx9* m_Body;
	CSpriteDx9* m_Leg;
	D3DXVECTOR3 m_PositionBody;
	D3DXVECTOR3 m_PositionLeg;
public:
	RamboSprite(void);
	virtual void UpdateAnimation() = 0;
	virtual void Reset() = 0;
	virtual void Render(LPD3DXSPRITE spriteHandle, D3DXVECTOR2 position, ESpriteEffect effect, float rotateAngle, float scale, float deep) = 0;
	virtual D3DXVECTOR2 GetFrameSize();
	virtual ~RamboSprite(void);
};

#endif