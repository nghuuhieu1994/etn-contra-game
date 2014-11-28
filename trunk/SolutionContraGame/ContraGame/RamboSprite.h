#include "SpriteManager.h"
#include "EObjectState.h"
#ifndef __RAMBO_MOVE_SPRITE__
#define __RAMBO_MOVE_SPRITE__


//Need to implement fucking class called Animation because this game have so much fucking animation :((
class RamboSprite
{
	int m_inversePositionY;
	float m_timeShakeAnimation;

	bool	m_isJump;
	bool	m_isLieDown;
	bool	m_isMove;
	bool	m_isFall;

	CSpriteDx9* m_TopRight;
	CSpriteDx9* m_Dead;
	CSpriteDx9* m_BottomRight;
	CSpriteDx9* m_Up;
	CSpriteDx9* m_Run;
	CSpriteDx9* m_Shoot;
	CSpriteDx9* m_Jump;
	CSpriteDx9* m_Lie;
	CSpriteDx9* m_Swim;
	CSpriteDx9* m_Dive;
	CSpriteDx9* m_WaterBomb;
	CSpriteDx9* m_Climb;

	CSpriteDx9* m_moveLeg;

	CSpriteDx9* m_Body;
	CSpriteDx9* m_Leg;
	D3DXVECTOR3 m_PositionBody;
	D3DXVECTOR3 m_PositionLeg;
	D3DXVECTOR3 m_tempPositionBody;
	D3DXVECTOR3 m_tempPositionLeg;
	D3DXVECTOR2 m_frameSize;

	eObjectState m_previousState;

	int m_timesShake;

	bool		m_isShake;
public:
	RamboSprite(void);
	void UpdateAnimation(eObjectState _objectState);
	void Reset();
	void saveCurrentState();
	void loadCurrentState();
	void setIsShake(bool _isShake){ m_isShake = _isShake; }
	void resetInverseVariable();
	void SetIsJump(bool _jump) { m_isJump = _jump; }
	D3DXVECTOR2 GetFrameSize() { return m_frameSize; }
	bool IsCompleteAnimation(){ return m_timesShake? false : true; }
	void shakeBody();
	void shakeBodySwim();
	void setShakeTime(int _times){ m_timesShake = _times; }
	void IncreaseTimesShake(int _times){ m_timesShake += _times; }
	void Render(LPD3DXSPRITE spriteHandle, D3DXVECTOR2 position, ESpriteEffect effect, float rotateAngle, float scale, float deep);
	virtual ~RamboSprite(void);
};

#endif