#include "Tank.h"
#include "Support.h"
#include <stdio.h>
#include "Bill.h"
#include "BillIdleState.h"
//demo game tank
int main()
{
	//init window
	init();
	Bill b;
	b.state = new BillIdleState;
	while (1)
	{
		system("cls");
		b.HandleInput();
		b.Render();
	}

	getch();
	return 0;
}

