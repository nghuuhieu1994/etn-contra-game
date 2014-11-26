#ifndef __DYNAMIC_OBJECT__
#define __DYNAMIC_OBJECT__

#include "cobjectdx9.h"
#include "Collision.h"
#include "CGameTimeDx9.h"


class Collision;
class DynamicObject :
	public Object 
{
protected:
	Physic*			m_Physic;
	eDirectAttack	m_DirectAttack;
	Collision*		m_Collision;
public:
	bool isDead;
	DynamicObject(void);
	Physic*			getPhysic() const { return m_Physic; }
	DynamicObject(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID);
    void UpdateBound();
	BOX GetBroadPhaseBox(D3DXVECTOR2);
	BOX GetBroadPhaseBox();
	BOX GetBoundForDynamicObject(D3DXVECTOR2);
	virtual void UpdateMovement() = 0;
	virtual ~DynamicObject(void);
};

#endif