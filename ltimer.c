#include <stdio.h>
#include <SDL2/SDL.h>
#include "includes.h"

//The application time based timer
//Initializes variables
void ltimer_Init(LTimer timer);

//The various clock actions
void ltimer_Stop(LTimer timer);
void ltimer_Pause(LTimer timer);
void ltimer_Unpause(LTimer timer);

//Checks the status of the timer
bool ltimer_IsStarted(LTimer timer);
bool ltimer_IsPaused(LTimer timer);

/*
void ltimer_capTimerStart() {
    capTimer.start();
}

int ltimer_getCapTimerTicks() {
    return capTimer.getTicks();
}
*/

void ltimer_Init(LTimer timer)
{
    //Initialize the variables
    timer.mStartTicks = 0;
    timer.mPausedTicks = 0;

    timer.mPaused = false;
    timer.mStarted = false;
}

void ltimer_Start(LTimer timer)
{
    //Start the timer
    timer.mStarted = true;

    //Unpause the timer
    timer.mPaused = false;

    //Get the current clock time
    timer.mStartTicks = SDL_GetTicks();
	timer.mPausedTicks = 0;
}

void ltimer_Stop(LTimer timer)
{
    //Stop the timer
    timer.mStarted = false;

    //Unpause the timer
    timer.mPaused = false;

	//Clear tick variables
	timer.mStartTicks = 0;
	timer.mPausedTicks = 0;
}

void ltimer_Pause(LTimer timer)
{
    //If the timer is running and isn't already paused
    if( timer.mStarted && !timer.mPaused )
    {
        //Pause the timer
        timer.mPaused = true;

        //Calculate the paused ticks
        timer.mPausedTicks = SDL_GetTicks() - timer.mStartTicks;
		timer.mStartTicks = 0;
    }
}

void ltimer_Unpause(LTimer timer)
{
    //If the timer is running and paused
    if( timer.mStarted && timer.mPaused )
    {
        //Unpause the timer
        timer.mPaused = false;

        //Reset the starting ticks
        timer.mStartTicks = SDL_GetTicks() - timer.mPausedTicks;

        //Reset the paused ticks
        timer.mPausedTicks = 0;
    }
}

Uint32 ltimer_GetTicks(LTimer timer)
{
	//The actual timer time
	Uint32 time = 0;

    //If the timer is running
    if( timer.mStarted )
    {
        //If the timer is paused
        if( timer.mPaused )
        {
            //Return the number of ticks when the timer was paused
            time = timer.mPausedTicks;
        }
        else
        {
            //Return the current time minus the start time
            time = SDL_GetTicks() - timer.mStartTicks;
        }
    }

    return time;
}

bool ltimer_IsStarted(LTimer timer)
{
	//Timer is running and paused or unpaused
    return timer.mStarted;
}

bool ltimer_IsPaused(LTimer timer)
{
	//Timer is running and paused
    return timer.mPaused && timer.mStarted;
}
