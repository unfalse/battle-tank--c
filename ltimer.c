#include <stdio.h>
#include <SDL2/SDL.h>
#include "includes.h"

//The application time based timer
//Initializes variables
void ltimer_Init();

//The various clock actions
void ltimer_Stop();
void ltimer_Pause();
void ltimer_Unpause();

//Checks the status of the timer
bool ltimer_IsStarted();
bool ltimer_IsPaused();

struct LTimer {
    //The clock time when the timer started
    Uint32 mStartTicks;

    //The ticks stored when the timer was paused
    Uint32 mPausedTicks;

    //The timer status
    bool mPaused;
    bool mStarted;
} ltimer;

void ltimer_Init()
{
    //Initialize the variables
    ltimer.mStartTicks = 0;
    ltimer.mPausedTicks = 0;

    ltimer.mPaused = false;
    ltimer.mStarted = false;
}

void ltimer_Start()
{
    //Start the timer
    ltimer.mStarted = true;

    //Unpause the timer
    ltimer.mPaused = false;

    //Get the current clock time
    ltimer.mStartTicks = SDL_GetTicks();
	ltimer.mPausedTicks = 0;
}

void ltimer_Stop()
{
    //Stop the timer
    ltimer.mStarted = false;

    //Unpause the timer
    ltimer.mPaused = false;

	//Clear tick variables
	ltimer.mStartTicks = 0;
	ltimer.mPausedTicks = 0;
}

void ltimer_Pause()
{
    //If the timer is running and isn't already paused
    if( ltimer.mStarted && !ltimer.mPaused )
    {
        //Pause the timer
        ltimer.mPaused = true;

        //Calculate the paused ticks
        ltimer.mPausedTicks = SDL_GetTicks() - ltimer.mStartTicks;
		ltimer.mStartTicks = 0;
    }
}

void ltimer_Unpause()
{
    //If the timer is running and paused
    if( ltimer.mStarted && ltimer.mPaused )
    {
        //Unpause the timer
        ltimer.mPaused = false;

        //Reset the starting ticks
        ltimer.mStartTicks = SDL_GetTicks() - ltimer.mPausedTicks;

        //Reset the paused ticks
        ltimer.mPausedTicks = 0;
    }
}

Uint32 ltimer_GetTicks()
{
	//The actual timer time
	Uint32 time = 0;

    //If the timer is running
    if( ltimer.mStarted )
    {
        //If the timer is paused
        if( ltimer.mPaused )
        {
            //Return the number of ticks when the timer was paused
            time = ltimer.mPausedTicks;
        }
        else
        {
            //Return the current time minus the start time
            time = SDL_GetTicks() - ltimer.mStartTicks;
        }
    }

    return time;
}

bool ltimer_IsStarted()
{
	//Timer is running and paused or unpaused
    return ltimer.mStarted;
}

bool ltimer_IsPaused()
{
	//Timer is running and paused
    return ltimer.mPaused && ltimer.mStarted;
}
