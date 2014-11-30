#ifndef __BRIDGE_TILE_H__
#define __BRIGDE_TILE_H__

#include "DynamicObject.h"

class BridgeTile : public DynamicObject
{
private:
	CSpriteDx9*		m_BridgeSprite;
	CSpriteDx9*		m_DeadSprite;
	int timeExpl;
public:
	BridgeTile();
	BridgeTile(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateCollision(Object* checkingObject); 
	void UpdateAnimation();
	void UpdateMovement(){}
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	~BridgeTile();
};

#endif