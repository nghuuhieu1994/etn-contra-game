#pragma once
#include "BillState.h"
class BillJumpState :
	public BillState
{
public:
	BillJumpState();
	virtual void Initialize();
	virtual void HandleInput(Bill &bill);
	virtual void Update();
	virtual void Render();
	virtual ~BillJumpState();
};

