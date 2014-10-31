#include "SpriteManager.h"
#ifndef __RAMBO_MOVE_SPRITE__
#define __RAMBO_MOVE_SPRITE__

class RamboSprite
{
	int m_inversePositionY;
	float timeAnimation;

	bool	m_isJump;

	CSpriteDx9* m_TopRight;
	CSpriteDx9* m_BottomRight;
	CSpriteDx9* m_Up;
	CSpriteDx9* m_Run;
	CSpriteDx9* m_Shoot;
	CSpriteDx9* m_Jump;
	CSpriteDx9* m_moveLeg;

	CSpriteDx9* m_Body;
	CSpriteDx9* m_Leg;
	D3DXVECTOR3 m_PositionBody;
	D3DXVECTOR3 m_PositionLeg;
	D3DXVECTOR2 m_frameSize;
public:
	RamboSprite(void);
	void UpdateAnimation();
	void Reset();
	void SetIsJump(bool _jump) { m_isJump = _jump; }
	D3DXVECTOR2 GetFrameSize() { return m_frameSize; }
	void Render(LPD3DXSPRITE spriteHandle, D3DXVECTOR2 position, ESpriteEffect effect, float rotateAngle, float scale, float deep);
	virtual ~RamboSprite(void);
};

#endif