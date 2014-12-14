#ifndef __BOSS_ARM_H__
#define __BOSS_ARM_H__

#include "DynamicObject.h"
#include "Bullet.h"
#include "math.h"

#define PI  3.14159265358979323846
class BossArm : public DynamicObject
{
private:
	CSpriteDx9* spriteDead;
	CSpriteDx9*	spriteAlive;
	D3DXVECTOR3 m_PositionOfOrigin;
	float		angle;
	float		factorAngle;
	float		factorR;
	D3DXVECTOR3 m_StartPosition;
	float deltaX;
	float deltaY;
	float m_AngleVeclocity;
	float		angleBlend;
	bool isRootNode;
public:
	bool IsRootNode() const{ return isRootNode;};
	void setIsRootNode(bool _rootNode){ isRootNode = _rootNode;};
	D3DXVECTOR3 getStartPosition()const{ return this->m_StartPosition;};
	void setStartPosition(D3DXVECTOR3 _startPosition){ this->m_StartPosition = _startPosition;};
	float getAngleVeclocity()const{ return this->m_AngleVeclocity;};
	void setAngleVeclocity(float _angleVeclocity) {this->m_AngleVeclocity = _angleVeclocity;};
	float getDeltaX()const{ return this->deltaX;};
	float getDeltaY()const{ return this->deltaY;};
	float getFactorR()const {return this->factorR;};
	void  setFactorR(float _factorR){this->factorR = _factorR;};
	float getFactorAngle() const{ return this->factorAngle;};
	void setFactorAngle(float _factorAngle){this->factorAngle = _factorAngle;};
	D3DXVECTOR3 getPositionOfOrgin() const{ return this->m_PositionOfOrigin;};
	void setPositionOfOring(D3DXVECTOR3 _positionOfOrigin) { this->m_PositionOfOrigin = _positionOfOrigin;};
	BossArm();
	BossArm(D3DXVECTOR3, eDirection, eObjectID, D3DXVECTOR3, float);
	float getAngle() { return angle; }
	void setAngle(float ang){ angle = ang; }
	void Initialize();
	void UpdateAnimation();
	void UpdateCollision(Object* checkingObject);
	void UpdateMovement();
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	~BossArm();
};

#endif