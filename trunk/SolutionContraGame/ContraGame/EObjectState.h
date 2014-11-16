#ifndef __EObjectState_h__
#define __EObjectState_h__
enum eObjectState
{
	STATE_ALIVE_IDLE = 0,
	STATE_ALIVE_MOVE = 1,
	STATE_SHOOTING, // dm deo them cai nay sao xet cho no ban?
	STATE_JUMP,
	STATE_BEFORE_DEATH,
	STATE_EXPLOISION,
	STATE_DEATH,

	STATE_RAMBO_AIM_BOTTOM_RIGHT,
	STATE_RAMBO_AIM_TOP_RIGHT,
	STATE_RAMBO_AIM_UP,
	STATE_RAMBO_CLIMB,
	STATE_RAMBO_DIVE,
	STATE_RAMBO_FALL,
	STATE_RAMBO_IDLE,
	STATE_RAMBO_JUMP,
	STATE_RAMBO_LIE,
	STATE_RAMBO_MOVE,
	STATE_RAMBO_RUN,
	STATE_RAMBO_SHOOT,
	STATE_RAMBO_SHOOT_RUN,
	STATE_RAMBO_SWIM,
	STATE_RAMBO_SWIM_SHOOT,
	STATE_RAMBO_SWIM_SHOOT_TOP_RIGHT,
	STATE_RAMBO_SWIM_SHOOT_UP,
	STATE_RAMBO_WATER_BOMB,
};
#endif