#include "CPhysicDx9.h"

Physic::Physic()
{

}

bool Physic::CheckMovementRangeWidth()
{
	if(m_MovementRange != 0)
	{
		if(m_Position.x < m_MovementRange->left || m_Position.x > m_MovementRange->right)
		{
			return true;
		}
	}
	return false;
}

bool Physic::CheckMovementRangeHeight()
{
	if(m_MovementRange != 0)
	{
		if(m_Position.y < m_MovementRange->bottom || m_Position.y > m_MovementRange->top)
		{
			return true;
		}
	}
	return false;
}

void Physic::UpdateMovement(CGameTimeDx9* gameTime)
{
	if(CheckMovementRangeWidth())
	{
		m_Velocity.x *= -1.0f;
	}
	if(CheckMovementRangeHeight())
	{
		m_Velocity.y *= -1.0f;
	}

	float deltaTime = gameTime->getElapsedGameTime().getSeconds();
	
	deltaTime = deltaTime/((float)1/FRAME_RATE);

	m_Position.x += m_Velocity.x * deltaTime;
	m_Position.y += m_Velocity.y * deltaTime;
}

void Physic::CheckCollision(Object _object)
{

}

Physic::~Physic()
{

}