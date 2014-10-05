#include "CObjectDx9.h"

Object::Object()
{

}

Object::Object(D3DXVECTOR3 _position, eDirection _direction, ObjectState* _state)
{
	this->state = _state;
	this->state->getPhysic()->setPosition(_position);
	this->state->getPhysic()->setDirection(_direction);
}

void Object::UpdateCollision(Object* checkingObject)
{
	ObjectState* tempState = 0;
	tempState = state->UpdateCollision(this, checkingObject);
	if (tempState != 0)
	{
		delete state;
		state = tempState;
	}
}

void Object::UpdateMovement()
{
	ObjectState* tempState = 0;
	tempState = state->UpdateMovement(this);
	if (tempState != 0)
	{
		delete state;
		state = tempState;
	}
}

void Object::Render(SPRITEHANDLE spriteHandle)
{
	state->Render(spriteHandle);
}

Object::~Object()
{

}