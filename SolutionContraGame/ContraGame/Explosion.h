#ifndef ___EXPLOSION_H__
#define __EXPLOSION_H__

#include "DynamicObject.h"

class Explosion : public DynamicObject
{
private:
	bool isExplosive;
public:
	Explosion();
	Explosion(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	void Initialize();
	void UpdateCollision(Object* checkingObject);
	void UpdateAnimation();
	void UpdateMovement();
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
	~Explosion();
};

#endif