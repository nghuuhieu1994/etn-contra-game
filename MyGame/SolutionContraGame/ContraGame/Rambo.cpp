#include "Rambo.h"

Rambo::Rambo()
{
	state = new RamboIdleState();
}

void Rambo::HandleInput()
{
	state->HandleInput(this);
}

void Rambo::UpdateAnimation()
{
	state->UpdateAnimation();
}

void Rambo::UpdateCollision(Object* checkingObject)
{
	state->UpdateCollision(this, checkingObject);
}

void Rambo::UpdateMovement()
{
	state->UpdateMovement(this);
}

void Rambo::Render(SPRITEHANDLE spriteHandle)
{
	state->Render(spriteHandle);
}

Rambo::~Rambo()
{

}