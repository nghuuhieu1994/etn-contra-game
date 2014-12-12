#ifndef __BRIGDE_STONE_H__
#define __BRIGDE_STONE_H__

#include "DynamicObject.h"

class BridgeStone : public DynamicObject
{
private:
	CSpriteDx9* sprite_main;
public:
	BridgeStone();
	BridgeStone(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateCollision(Object* checkingObject);
	void UpdateAnimation();
	void UpdateMovement();
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	~BridgeStone();
};

#endif