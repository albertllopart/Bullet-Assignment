// ----------------------------------------------------
// Timer.cpp
// Body for CPU Tick Timer class
// ----------------------------------------------------

#include "Timer.h"

// ---------------------------------------------
Timer::Timer()
{
}

// ---------------------------------------------
void Timer::Start()
{
	started_at = SDL_GetTicks();
}

// ---------------------------------------------
Uint32 Timer::Read()
{
	return SDL_GetTicks() - started_at;
}
// ----------------------------------------------
Uint32 Timer::ReadSec()
{
	return (SDL_GetTicks() - started_at) / 1000;
}


