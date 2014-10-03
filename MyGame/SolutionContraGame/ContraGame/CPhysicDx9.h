#ifndef __PHYSIC_H__
#define __PHYSIC_H__

#include "CObjectDx9.h"
#include "CGameTimeDx9.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>

using namespace std;

struct Collision
{
	eObjectID	m_CollideObject;
	eDirection	m_CollidePosition;
};

class Object;
class Physic
{
	D3DXVECTOR3			m_Position;
	D3DXVECTOR2			m_Velocity;
	D3DXVECTOR2			m_Accelerate;
	eDirection			m_Direction;
	Collision			m_Collision;
	RECT				m_MovementRange;
	vector<Collision>	m_ListCollision;

public:
	void			setPosition(D3DXVECTOR3 _position){ m_Position = _position; }
	D3DXVECTOR3		getPosition(){ return m_Position; }

	void			setVelocity(D3DXVECTOR2 _velocity){ m_Velocity = _velocity; }
	D3DXVECTOR2		getVelocity(){ return m_Velocity; }

	void			setAccelerate(D3DXVECTOR2 _accelerate){ m_Accelerate = _accelerate; }
	D3DXVECTOR2		getAccelerate(){ return m_Accelerate; }

	void			setDirection(eDirection _direction){ m_Direction = _direction; }
	eDirection		getDirection(){ return m_Direction; }

	Physic();
	void SetMovementRange(int maxTop, int maxLeft, int maxRight, int maxBottom)
	{
		m_MovementRange.top		= maxTop;
		m_MovementRange.left	= maxLeft;
		m_MovementRange.right	= maxRight;
		m_MovementRange.bottom	= maxBottom;
	}

	bool CheckMovementRangeWidth();
	bool CheckMovementRangeHeight();

	void UpdateMovement(CGameTimeDx9* gameTime);
	void CheckCollision(Object _object);
	~Physic();
};

#endif