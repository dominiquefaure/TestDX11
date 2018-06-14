
//-------------------------------------------------------------------------------------------------
FORCE_INLINE TFloat64 WindowsTime::GetSecondsPerCycle( )
{
	return s_secondsPerCycle;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
FORCE_INLINE TFloat64 WindowsTime::GetMilliSecondsPerCycle( )
{
	return s_milliSecondsPerCycle;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
FORCE_INLINE TFloat64 WindowsTime::ToSeconds( const TUint64 a_cycleCount )
{
	return ( a_cycleCount * s_secondsPerCycle );
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
FORCE_INLINE TFloat64 WindowsTime::ToMilliSeconds( const TUint64 a_cycleCount )
{
	return ( a_cycleCount * s_milliSecondsPerCycle );
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
FORCE_INLINE TUint64 WindowsTime::GetCurrentCycle()
{
	LARGE_INTEGER t_cycle;
	QueryPerformanceCounter( &t_cycle );

	return t_cycle.QuadPart;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
FORCE_INLINE TFloat64 WindowsTime::GetCurrentSecond()
{
	LARGE_INTEGER t_cycle;
	QueryPerformanceCounter( &t_cycle );

	return ( t_cycle.QuadPart * s_secondsPerCycle );
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
FORCE_INLINE TFloat64 WindowsTime::GetCurrentMilliSecond()
{
	LARGE_INTEGER t_cycle;
	QueryPerformanceCounter( &t_cycle );

	return ( t_cycle.QuadPart * s_milliSecondsPerCycle );
}
//-------------------------------------------------------------------------------------------------
