#ifndef __PHYSIC_H__
#define __PHYSIC_H__

#include "CGlobal.h"
#include <d3d9.h>
#include <d3dx9.h>

class Physic
{
	D3DXVECTOR3		m_Position;
	D3DXVECTOR2		m_Velocity;
	D3DXVECTOR2		m_Accelerate;
	eDirection		m_Direction;

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

	~Physic();
};

#endif