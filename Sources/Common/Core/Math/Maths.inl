
//-------------------------------------------------------------------------
FORCE_INLINE TFloat32 Maths::Abs( TFloat32 a_value )
{
	return fabsf( a_value );
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
FORCE_INLINE TFloat32 Maths::Cos( TFloat32 a_angle )
{
	return cosf( a_angle );
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
FORCE_INLINE TFloat32 Maths::Sin( TFloat32 a_angle )
{
	return sinf( a_angle );
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
FORCE_INLINE TFloat32 Maths::Tan( TFloat32 a_angle )
{
	return tanf( a_angle );
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
FORCE_INLINE TFloat32 Maths::Max( TFloat32 a_value1 , TFloat32 a_value2 )
{
	return ( ( a_value1 >= a_value2 )? a_value1 : a_value2 );
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
FORCE_INLINE TFloat64 Maths::Max64( TFloat64 a_value1 , TFloat64 a_value2 )
{
	return ( ( a_value1 >= a_value2 )? a_value1 : a_value2 );
}
//-------------------------------------------------------------------------
