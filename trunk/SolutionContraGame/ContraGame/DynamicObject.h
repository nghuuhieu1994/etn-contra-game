#ifndef __DYNAMIC_OBJECT__
#define __DYNAMIC_OBJECT__

#include "cobjectdx9.h"
class DynamicObject :
	public Object
{
protected:
	Physic*			m_Physic;
public:
	DynamicObject(void);
	Physic*			getPhysic() const { return m_Physic; }
	DynamicObject(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
	virtual void UpdateMovement() = 0;
	virtual ~DynamicObject(void);
};

#endif