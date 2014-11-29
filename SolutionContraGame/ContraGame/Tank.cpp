#include "Tank.h"

Tank::Tank()
{
}

Tank::Tank(D3DXVECTOR3 _position, eDirection _direction, eObjectID _objectID)
	: DynamicObject(_position, _direction, _objectID)
{
	m_Position.z = 0.4f;
}

void Tank::Initialize()
{ 
	m_Position.z = 0.4f;
}

void Tank::UpdateAnimation()
{
}


void Tank::UpdateCollision(Object* checkingObject)
{
}

void Tank:: UpdateMovement()
{
}

void Tank::Update()
{
}

void Tank::Render(SPRITEHANDLE spriteHandle)
{
}

void Tank::Release()
{
}

Tank::~Tank()
{
}