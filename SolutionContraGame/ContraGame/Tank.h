#ifndef __TANK_H__
#define __TANK_H__

#include "DynamicObject.h"
#include "TankTile.h"
class Tank : public DynamicObject
{
private:
	TankTile* m_TankSprite;
public:
	Tank();
	Tank(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateCollision(Object* checkingObject);
	void UpdateAnimation();
	void UpdateMovement();
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	~Tank();
};

#endif