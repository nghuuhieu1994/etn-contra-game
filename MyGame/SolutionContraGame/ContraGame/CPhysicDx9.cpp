#include "CPhysicDx9.h"

Physic::Physic()
{

}

void Physic::UpdateMovement(CGameTimeDx9* gameTime)
{
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