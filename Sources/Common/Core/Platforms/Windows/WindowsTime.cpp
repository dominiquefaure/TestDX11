#include "WindowsTime.h"

#include <windows.h>


TUint64	WindowsTime::s_cyclePerSeconds	=	0;
TFloat64 WindowsTime::s_secondsPerCycle	=	0.0f;
TFloat64 WindowsTime::s_milliSecondsPerCycle	=	0.0f;

#ifdef _DEBUG
#include "WindowsTime.inl"
#endif


//-------------------------------------------------------------------------------------------------
void WindowsTime::Initialize()
{
	LARGE_INTEGER t_frequency;

	// Get the Frequency of the Performance counter
	QueryPerformanceFrequency(&t_frequency);

	s_cyclePerSeconds										=	t_frequency.QuadPart;
	s_secondsPerCycle										=	1.0f / ( (TFloat64)(s_cyclePerSeconds) );

	s_milliSecondsPerCycle									=	s_secondsPerCycle * 1000.0f;
}
//-------------------------------------------------------------------------------------------------

