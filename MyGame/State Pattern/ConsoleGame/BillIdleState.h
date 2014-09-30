#ifndef __BILL_IDLE_STATE_H__
#define __BILL_IDLE_STATE_H__
#include "BillState.h"
class BillIdleState :
	public BillState
{
public:
	BillIdleState();
	virtual void Initialize();
	virtual void HandleInput(Bill &bill);
	virtual void Update();
	virtual void Render();
	virtual ~BillIdleState();
};

#endif