#include "RamboSprite.h"

#ifndef __RAMBO_MOVE_SPRITE__
#define __RAMBO_MOVE_SPRITE__

class RamboMoveSprite : public RamboSprite
{
	/*int m_inversePositionY;
	float timeAnimation;*/
public:
	RamboMoveSprite(void);
	void UpdateAnimation();
	void Reset();
	void Render(LPD3DXSPRITE spriteHandle, D3DXVECTOR2 position, ESpriteEffect effect, float rotateAngle, float scale, float deep);
	virtual ~RamboMoveSprite(void);
};

#endif