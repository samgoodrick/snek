#ifndef TIMER_HPP
#define TIMER_HPP

#include "SDL/SDL.h"

class Timer
{
	int start_ticks;
	int paused_ticks;

	bool paused;
	bool started;

public:
	Timer()
		:start_ticks(), paused_ticks(), paused(), started()
	{
	}

	void start()
	{
		started = true;
		paused = false;
		start_ticks = SDL_GetTicks();
	}
	void stop()
	{
		started = false;
		paused = false;
	}
	void pause()
	{
		if( started && !paused )
		{
			paused = true;
			paused_ticks = SDL_GetTicks() - start_ticks;
		}
	}
	void unpause()
	{
		if( paused )
		{
			paused = false;
			start_ticks = SDL_GetTicks() - paused_ticks;
			paused_ticks = 0;
		}
	}

	int get_ticks()
	{
		if( started )
			if( paused )
				return paused_ticks;
			else
				return SDL_GetTicks() - start_ticks;
	}

	bool is_started() const
	{
		return started;
	}
	bool is_paused() const
	{
		return paused;
	}
	
};

#endif
