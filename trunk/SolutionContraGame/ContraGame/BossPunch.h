#ifndef __BOSS_PUNCH_H__
#define __BOSS_PUNCH_H__

#include "DynamicObject.h"
#include "Bullet.h"
#include "math.h"

#define PI  3.14159265358979323846
class BossPunch : public DynamicObject
{
private:
	CSpriteDx9* spriteDead;
	CSpriteDx9*	spriteAlive;
	float		angle;
	D3DXVECTOR3 m_PositionOfOrigin;
	float m_AngleVeclocity;
public:
	BossPunch();
	BossPunch(D3DXVECTOR3, eDirection, eObjectID, D3DXVECTOR3);
	
	float getAngleVeclocity()const{ return this->m_AngleVeclocity;};
	void setAngleVeclocity(float _angleVeclocity) {this->m_AngleVeclocity = _angleVeclocity;};
	float getAngle() { return angle; }
	void setAngle(float ang){ angle = ang; }
	D3DXVECTOR3 getPositionOfOrgin() const{ return this->m_PositionOfOrigin;};
	void setPositionOfOring(D3DXVECTOR3 _positionOfOrigin) { this->m_PositionOfOrigin = _positionOfOrigin;};
	void Initialize();
	void UpdateAnimation();
	void UpdateCollision(Object* checkingObject);
	void UpdateMovement();
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	~BossPunch();
};
#endif