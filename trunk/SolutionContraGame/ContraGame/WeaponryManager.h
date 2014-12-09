#ifndef __WEAPONRY_MANAGER_H__
#define __WEAPONRY_MANAGER_H__
#include "DynamicObject.h"
#include <list>
using namespace std;


class WeaponryManager
{
private:
	WeaponryManager(){}
	~WeaponryManager(){}
	static WeaponryManager*		_instance; 
	list<DynamicObject*>		m_ListWeaponry;

public:
	static WeaponryManager*	getInstance();
	void AddElement(DynamicObject* objectWeaponry);
	void UpdateCollision(Object* checkingObject);
	void Update();
	void Render(SPRITEHANDLE spriteHandle);
	void Release();
};

#endif