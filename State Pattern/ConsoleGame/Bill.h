#ifndef __BILL_H__
#define __BILL_H__

#include "BillState.h"
#include "BillIdleState.h"

class Bill
{
public:
	BillState* state;
	Bill();
	void Initialize();
	void HandleInput();
	void Update();
	void Render();
	void CheckPhysic();
	virtual ~Bill();
};

#endif