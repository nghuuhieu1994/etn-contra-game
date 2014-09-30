#include "BillMoveState.h"
#include "BillIdleState.h"
#include "BillJumpState.h"
#include "Utils.h"

BillIdleState::BillIdleState()
{
}

void BillIdleState::Initialize()
{

}

void BillIdleState::Update()
{

}

void BillIdleState::HandleInput(Bill &bill)
{
	if (GIsKeyDown(GKeys::KEY_LEFT) || GIsKeyDown(GKeys::KEY_RIGHT))
	{
		delete bill.state;
		bill.state = new BillMoveState;
	}
	if (GIsKeyPress(GKeys::KEY_UP))
	{
		delete bill.state;
		bill.state = new BillJumpState;
	}
}

void BillIdleState::Render()
{
	printf("Bill Idle State\n");
}

BillIdleState::~BillIdleState()
{
}
