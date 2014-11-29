#ifndef __TANK_TILE_H__
#define __TANK_TILE_H__

#include "DynamicObject.h"

class TankTile : public DynamicObject
{
private:
	CSpriteDx9*		m_TankSprite;
	CSpriteDx9*		m_DeadSprite;
public:
	TankTile();
	TankTile(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateCollision(Object* checkingObject); 
	void UpdateAnimation();
	void UpdateMovement(){}
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	~TankTile();
};

#endif