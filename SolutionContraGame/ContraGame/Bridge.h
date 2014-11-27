#ifndef __BRIDGE_H__
#define __BRIDGE_H__

#include "DynamicObject.h"
#include "BridgeTile.h"
class Bridge : public DynamicObject
{
private:
	int _distanceX;
	BridgeTile*		m_HeadTile;
	BridgeTile*		m_BodyTile[2];
	BridgeTile* 	m_TailTile;
	CSpriteDx9*		m_HeadBreak;
	CSpriteDx9*		m_TailBreak;
public:
	Bridge();
	Bridge(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateCollision(Object* checkingObject);
	void UpdateAnimation();
	void UpdateMovement();
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	~Bridge();
};

#endif