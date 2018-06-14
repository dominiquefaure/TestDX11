#ifndef __CORE_MATH_MATH_H__
#define __CORE_MATH_MATH_H__

#include "../CoreMacros.h"
#include "../Base/BaseDataTypes.h"
#include <math.h>


struct Maths
{
	/*
	* return the Abs value of a float number
	*/
	FORCE_INLINE static TFloat32 Abs( TFloat32 a_value );

	/*
	* Get the Cosinus
	*/
	FORCE_INLINE static TFloat32 Cos( TFloat32 a_angle );

	/*
	* Get the Sinu
	*/
	FORCE_INLINE static TFloat32 Sin( TFloat32 a_angle );

	/*
	* Get the Tangent
	*/
	FORCE_INLINE static TFloat32 Tan( TFloat32 a_angle );

	/*
	 * Get the Max between 2 values
	 */
	FORCE_INLINE static TFloat32 Max( TFloat32 a_value1 , TFloat32 a_value2 );

	FORCE_INLINE static TFloat64 Max64( TFloat64 a_value1 , TFloat64 a_value2 );

};

// The inline is included in the Header only if not in debug mode
#ifndef _DEBUG
#include "Maths.inl"
#endif


#endif