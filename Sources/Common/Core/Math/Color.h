#pragma once

#include "../CoreMacros.h"


struct Color
{
public:

	/*
	* Default constructor , init to White
	*/
	FORCE_INLINE Color();

	/*
	* Copy constructor
	*/
	FORCE_INLINE Color( const Color& _color );

	/*
	* Create a color from the given parameters
	*/
	FORCE_INLINE Color( float a_r , float a_g , float a_b , float a_alpha = 1.0f );

	/*
	* Set the Color components
	*/
	FORCE_INLINE void Set( float a_r , float a_g , float a_b , float a_alpha = 1.0f );



// Fields
public:

	float r;
	float g;
	float b;
	float a;

};


// The inline is included in the Header only if not in debug mode
#ifndef _DEBUG
#include "Color.inl"
#endif
