#ifndef __TIMER_H__
#define __TIMER_H__

#include "Globals.h"
#include "SDL\include\SDL.h"

class Timer
{
public:

	// Constructor
	Timer();

	void Start();

	Uint32 Read();
	Uint32 ReadSec();

private:

	Uint32	started_at;
};

#endif //__TIMER_H__