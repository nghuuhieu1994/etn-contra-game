#include "BillJumpState.h"
#include "Utils.h"
#include "BillIdleState.h"
#include <stdio.h>

BillJumpState::BillJumpState()
{
}

void BillJumpState::Initialize()
{

}

void BillJumpState::HandleInput(Bill &bill)
{
	if (GIsElapsed(2000))
	{
		delete bill.state;
		//bill.state = new BillIdleState;
	}
}

void BillJumpState::Update()
{
	
}

void BillJumpState::Render()
{
	printf("Bill Jump State\n");
}

BillJumpState::~BillJumpState()
{
}
