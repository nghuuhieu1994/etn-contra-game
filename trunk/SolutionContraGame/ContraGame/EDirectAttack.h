#ifndef __EDirectAttack_h__
#define __EDirectAttack_h__
//dm thang nao code cai deo nay vay??? =))
enum eDirectAttack
{
	//NONE = 0,
	//NORTH = 1, // Bac // TOP
	//SOUTH, // Nam //BOTTOM
	//EAST, // Dong //RIGHT
	//WEST, // Tay //LEFT
	//NORTH_EAST, // Bac > Dong //TOP > RIGHT
	//EAST_NORTH, // Dong > Bac //RIGHT > TOP
	//NORTH_WEST, // Bac > Tay
	//WEST_NORTH, // Tay > Bac
	//WEST_SOUTH, // Tay > Nam
	//SOUTH_WEST, // Nam > Tay
	//SOUTH_EAST, // Nam > Dong
	//EAST_SOUTH  // Dong > Nam 
	
	ZERO_CLOCK_DIRECTION = 0,
	ONE_CLOCK_DIRECTION = 1,
	TWO_CLOCK_DIRECTION = 2,
	THREE_CLOCK_DIRECTION = 3,
	FOUR_CLOCK_DIRECTION = 4,
	FIVE_CLOCK_DIRECTION = 5,
	SIX_CLOCK_DIRECTION = 6,
	SEVEN_CLOCK_DIRECTION = 7,
	EIGHT_CLOCK_DIRECTION = 8,
	NINE_CLOCK_DIRECTION = 9,
	TEN_CLOCK_DIRECTION = 10,
	ELEVEN_CLOCK_DIRECTION = 11,
	TWELVE_CLOCK_DIRECTION = 12,
	

	AD_TOP,
	AD_BOTTOM,
	AD_LEFT,
	AD_RIGHT,
	AD_TOP_RIGHT,   
	AD_TOP_LEFT,
	AD_BOTTOM_RIGHT,
	AD_BOTTOM_LEFT,
};
#endif