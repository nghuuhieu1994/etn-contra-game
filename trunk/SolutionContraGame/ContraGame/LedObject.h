#ifndef __LEDOBJECT_H__
#define __LEDOBJECT_H__

#include "CObjectDx9.h"

class LedObject : public Object
{
	static LedObject* s_Instance;
public:
	LedObject();
	LedObject(D3DXVECTOR3, eObjectID);
	static LedObject* getStaticInstance();
	~LedObject();
	void Initialize() ;
	void UpdateAnimation();
	void UpdateCollision(Object* checkingObject);
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
};

#endif