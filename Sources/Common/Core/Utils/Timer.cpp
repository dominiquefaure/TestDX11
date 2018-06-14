#include "Timer.h"

#include "../Platforms/PlatformWrapper.h"

#include "../Math/includes.h"

#include <windows.h>

#ifdef _DEBUG
#include "Timer.inl"
#endif


//---------------------------------------------------------------------------------------------
Timer::Timer()
{
	m_isRunning												=	false;
	m_startCycle											=	0;
	m_lastPulseCycle										=	0;
	m_lastPulseDuration										=	0;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
Timer::~Timer()
{
	
}
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
TUint64 Timer::GetRunningCycle()
{
	if( m_isRunning )
	{
		TUint64 t_cycle										=	PlatformTime::GetCurrentCycle();

		return t_cycle - m_startCycle;
	}

	return ( m_lastPulseCycle - m_startCycle );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void Timer::Start()
{
	m_startCycle											=	PlatformTime::GetCurrentCycle();
	m_isRunning												=	true;

	m_lastPulseCycle										=	m_startCycle;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void Timer::Stop()
{
	m_isRunning												=	false;
	m_lastPulseCycle										=	PlatformTime::GetCurrentCycle();
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void Timer::Pulse( TFloat64 a_minPulseDuration )
{
	if( m_isRunning )
	{
		// Get the current Cycle
		TUint64 t_cycle										=	PlatformTime::GetCurrentCycle();

		// Get number of Cycles since last pulse
		TUint64 t_cycleCount								=	t_cycle - m_lastPulseCycle;

		// compute how many seconds we have to wait
		TFloat64 t_waitDuration								=	Maths::Max64( (a_minPulseDuration - PlatformTime::ToSeconds( t_cycleCount ) ) , 0.0f );

		// if we have to wait
		if( t_waitDuration > 0.0f )
		{
			// compute the End time
			TFloat64 t_endWait								=	PlatformTime::ToSeconds( m_lastPulseCycle ) + a_minPulseDuration;

			// spin loop
			while( PlatformTime::GetCurrentSecond() < t_endWait )
			{
				::SwitchToThread();
			}

			// refresh the cycle
			t_cycle											=	PlatformTime::GetCurrentCycle();
		}

		// compute the total duration of the last pulse
		m_lastPulseDuration									=	t_cycle - m_lastPulseCycle;

		// update the Last Cycle
		m_lastPulseCycle									=	t_cycle;
	}
}
//---------------------------------------------------------------------------------------------
