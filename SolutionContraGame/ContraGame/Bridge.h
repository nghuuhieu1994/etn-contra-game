#ifndef ___BRIDGE_H__
#define __BRIDGE_H__

#include "DynamicObject.h"

class Bridge : public DynamicObject
{
private:
	bool isExplosive;
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