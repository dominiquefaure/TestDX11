#ifndef __CORE_PLATFORM_WINDOWS_TIME_H__
#define __CORE_PLATFORM_WINDOWS_TIME_H__

#include "../../Base/Includes.h"
#include "../../CoreMacros.h"

class WindowsTime
{
public:

	/*
	 * set the internal data
	 */
	static void Initialize();

	/*
	 * Get the number of seconds eleapsed per cycles
	 */
	static FORCE_INLINE TFloat64 GetSecondsPerCycle( );

	/*
	 * Get the number of MS eleapsed per cycles
	 */
	static FORCE_INLINE TFloat64 GetMilliSecondsPerCycle( );

	/*
	 * Get the amount of seconds the given number of cycles represents
	 */
	static FORCE_INLINE TFloat64 ToSeconds( const TUint64 a_cycleCount );

	/*
	 * Get the amount of MS the given number of cycles represents
	 */
	static FORCE_INLINE TFloat64 ToMilliSeconds( const TUint64 a_cycleCount );

	/*
	 * Get the current CPU cycle
	 */
	static FORCE_INLINE TUint64 GetCurrentCycle();

	/*
	 * Get the current time in seconds
	 */
	static FORCE_INLINE TFloat64 GetCurrentSecond();

	/*
	 * Get the current time in MS
	 */
	static FORCE_INLINE TFloat64 GetCurrentMilliSecond();

private:

	// number of CPU Cycles per seconds
	static TUint64	s_cyclePerSeconds;

	//amount of seconds per cycle : 1/s_cyclePerSeconds
	static TFloat64	s_secondsPerCycle;

	//amount of milli seconds per cycle : 1/s_cyclePerSeconds
	static TFloat64	s_milliSecondsPerCycle;

};

// The inline is included in the Header only if not in debug mode
#ifndef _DEBUG
#include "WindowsTime.inl"
#endif



#endif