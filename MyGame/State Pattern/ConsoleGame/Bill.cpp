#include "Bill.h"


Bill::Bill()
{
}

void Bill::Initialize()
{
	state->Initialize();
}
void Bill::HandleInput()
{
	state->HandleInput(*this);
}

void Bill::Update()
{
	state->Update();
}

void Bill::Render()
{
	state->Render();
}

Bill::~Bill()
{
}
