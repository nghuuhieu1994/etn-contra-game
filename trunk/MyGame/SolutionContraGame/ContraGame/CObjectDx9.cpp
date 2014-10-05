#include "CObjectDx9.h"

Object::Object()
{

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