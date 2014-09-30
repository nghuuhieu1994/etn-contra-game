#include "Bill.h"
#include <stdio.h>
#ifndef __BILL_STATE__
#define __BILL_STATE__
class Bill;
class BillState
{
public:
	BillState();
	virtual void Initialize() = 0;
	virtual void HandleInput(Bill &bill) = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual ~BillState();
};
#endif