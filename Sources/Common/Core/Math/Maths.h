#pragma once

#include "../CoreMacros.h"

#include <math.h>


struct Maths
{
	/*
	* return the Abs value of a float number
	*/
	FORCE_INLINE static float Abs( float a_value );

	/*
	* Get the Cosinus
	*/
	FORCE_INLINE static float Cos( float a_angle );

	/*
	* Get the Sinu
	*/
	FORCE_INLINE static float Sin( float a_angle );

	/*
	* Get the Tangent
	*/
	FORCE_INLINE static float Tan( float a_angle );

};

// The inline is included in the Header only if not in debug mode
#ifndef _DEBUG
#include "Maths.inl"
#endif
