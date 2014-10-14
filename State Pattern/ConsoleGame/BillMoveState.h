#pragma once
#include "Utils.h"
#include "BillState.h"
#include "Bill.h"
class BillMoveState :
	public BillState
{
public:
	BillMoveState();
	virtual void Initialize();
	virtual void HandleInput(Bill &bill);
	virtual void Update();
	virtual void Render();
	virtual ~BillMoveState();
};

