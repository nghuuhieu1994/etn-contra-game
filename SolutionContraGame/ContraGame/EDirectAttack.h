#ifndef __EDirectAttack_h__
#define __EDirectAttack_h__
//dm thang nao code cai deo nay vay??? =))
enum eDirectAttack
{
	NONE = 0,
	NORTH = 1, // Bac // TOP
	SOUTH, // Nam //BOTTOM
	EAST, // Dong //RIGHT
	WEST, // Tay //LEFT
	NORTH_EAST, // Bac > Dong //TOP > RIGHT
	EAST_NORTH, // Dong > Bac //RIGHT > TOP
	NORTH_WEST, // Bac > Tay
	WEST_NORTH, // Tay > Bac
	WEST_SOUTH, // Tay > Nam
	SOUTH_WEST, // Nam > Tay
	SOUTH_EAST, // Nam > Dong
	EAST_SOUTH  // Dong > Nam 
};
#endif