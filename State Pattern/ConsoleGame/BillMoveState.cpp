#include "BillMoveState.h"
#include "BillIdleState.h"

BillMoveState::BillMoveState()
{
}

void BillMoveState::Initialize()
{

}

void BillMoveState::HandleInput(Bill &bill)
{
	if (GIsKeyUp(GKeys::KEY_LEFT) && GIsKeyUp(GKeys::KEY_RIGHT))
	{
		delete bill.state;
		bill.state = new BillIdleState;
	}
}

void BillMoveState::Update()
{

}

void BillMoveState::Render()
{
	printf("Bill Move State\n");
}

BillMoveState::~BillMoveState()
{
}
