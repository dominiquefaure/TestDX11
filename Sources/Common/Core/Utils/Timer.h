#ifndef __CORE_TIMER_H__
#define __CORE_TIMER_H__

#include "../CoreMacros.h"
#include "../Base/Includes.h"

class Timer
{
public:
	
	Timer();
	~Timer();


	FORCE_INLINE TBool IsRunning();

	/*
	 * Get the last pulse cycle count
	 */
	FORCE_INLINE TUint64 GetEleapsedCycle();

	/*
	 * Get the ladt pulse duration in seconds
	 */
	FORCE_INLINE TFloat64 GetEleapsedSeconds();

	/*
	 * Get the Number of Cycles since start called
	 */
	TUint64 GetRunningCycle();

	/*
	 * Start the Timer
	 */
	void Start();

	/*
	 * Stop the Timer
	 */
	void Stop();

	/*
	 * Compute eleapsed time, since last pulse, if running , else 0
	 * 
	 * @a_minPulseDuration	Minimum duration a pluse must have, if the time is lower, will spin loop until reach this time
	 */
	void Pulse( TFloat64 a_minPulseDuration = 0.0f );

private:

	// is the Timer currently running?
	TBool	m_isRunning;

	// Cycle when start the timer
	TUint64 m_startCycle;

	// cycle the last pulse occured
	TUint64	m_lastPulseCycle;

	// duration of hte Last pulse
	TUint64	m_lastPulseDuration;
};


// The inline is included in the Header only if not in debug mode
#ifndef _DEBUG
#include "Timer.inl"
#endif



#endif