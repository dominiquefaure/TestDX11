#pragma once
#ifndef __CORE_MATH_VECTOR3F_H__
#define __CORE_MATH_VECTOR3F_H__

#include "../CoreMacros.h"
#include "MathMacros.h"


/*
* Float Vector3,
*
* For performance reason , all the methods are inline
*/
struct Vector3F
{

	/*
	* Default Constructor
	*/
	FORCE_INLINE Vector3F();

	/*
	* Constructor that initialize all the components to the same value
	*/
	FORCE_INLINE Vector3F( float a_value );

	/*
	* Constructor that initialize each component
	*
	* @param a_x		x component
	* @param a_y		y component
	* @param a_z		z component
	*/
	FORCE_INLINE Vector3F( float a_x , float a_y , float a_z );

	/*
	* Compute the Dot product between 2 Vectors
	*
	* @param a_v1		1st Vector
	* @param a_v2		2nd Vector
	* @return			the Dot Product
	*/
	FORCE_INLINE static float Dot( const Vector3F& a_v1 , const Vector3F& a_v2 );

	/*
	* Compute the Dot product between this vector and another one
	*
	* @param a_vector	2nd Vector
	* @return			the Dot Product
	*/
	FORCE_INLINE float Dot( const Vector3F& a_vector )const;


	/*
	* Compute the Cross product between 2 Vectors
	*
	* @param a_v1		1st Vector
	* @param a_v2		2nd Vector
	* @return			the Cross Product
	*/
	FORCE_INLINE static Vector3F Cross(  const Vector3F& a_v1 , const Vector3F& a_v2 );

	/*
	* Compute the Cross product between 2 Vectors
	*
	* @param a_vector	2nd Vector
	* @return			the Cross Product
	*/
	FORCE_INLINE Vector3F Cross( const Vector3F& a_vector )const;

	/*
	* Set new values
	*
	* @param a_x	new X value to set
	* @param a_y	new Y value to set
	* @param a_z	new Z value to set
	*/
	FORCE_INLINE void Set( float a_x , float a_y , float a_z );

	/*
	* Get the Length of this vectors
	*
	* @return Length of the Vector
	*/
	FORCE_INLINE float GetLength()const;

	/*
	* Get the quared Lenght of this vector
	*
	* @return SuqaredLength of the Vector
	*/
	FORCE_INLINE float GetSquaredLength()const;

	/*
	* Normalize this Vector, if large engouth , else set to (0,0,0)
	*
	* @return true if the vector was normalized correctly
	*/
	FORCE_INLINE bool Normalize( float a_tolerance = DEFAULT_TOLEARANCE_VALUE );

	/*
	* Check if the vector is already Normalized
	*
	* @return true if the vector is normalized
	*/
	FORCE_INLINE bool IsNormalized()const;


	FORCE_INLINE Vector3F GetNormalized()const;

	/*
	* Check if all the components are 0
	*
	*/
	FORCE_INLINE bool IsZero()const;

	/*
	* Check if this Vector is 0, or really close to it
	*/
	FORCE_INLINE bool IsAlmostZero( float a_tolerance = DEFAULT_TOLEARANCE_VALUE );


	/*
	* Check if the 2 vectors are equal, with e delta tolerance value
	*
	* @param a_Vector		Vector to compare to
	* @param a_tolerance	rounding error tolerance
	* @return				true if the 2 vectors are equal within the given tolerance
	*/
	FORCE_INLINE bool Equals( const Vector3F& a_vector , float a_tolerance = DEFAULT_TOLEARANCE_VALUE )const;


// Operatorss
public:


	/**
	* Get the result of component wise Addition of this vector by another one
	* 
	* @param a_vector	The vector to add to this one.
	* @return			The result vector.
	*/
	FORCE_INLINE Vector3F operator+( const Vector3F& a_vector )const;

	/**
	* Get the result of Adding to each components
	* 
	* @param a_value	The value to add to each vector
	* @return			The result vector.
	*/
	FORCE_INLINE Vector3F operator+( float a_value )const;

	/**
	* Get the result of component wise Substraction of this vector by another one
	* 
	* @param a_vector	The vector to ubstract from this one.
	* @return			The result vector.
	*/
	FORCE_INLINE Vector3F operator-( const Vector3F& a_vector )const;

	/**
	* Get the result of Substraction to each components
	* 
	* @param a_value	The value to Substract to each vector
	* @return			The result vector.
	*/
	FORCE_INLINE Vector3F operator-( float a_value )const;

	/*
	* Get the Negated copy of this Vector
	*
	* @return a negated copy of this Vector
	*/
	FORCE_INLINE Vector3F operator-()const;

	/*
	* Get the Result of component wize Scaling of this Vector
	*
	* @param a_vector	The vector to multiply with
	* @return			The scaled vector
	*/
	FORCE_INLINE Vector3F operator*( const Vector3F& a_vector )const;

	/*
	* Get the Result of Uniform Scaling this Vector
	*
	* @param a_scale	Scale coeficient to apply to each component of the vector
	* @return			The scaled vector
	*/
	FORCE_INLINE Vector3F operator*( float a_scale )const;


	/*
	* Get the Result of component wize Dividing of this Vector
	*
	* @param a_vector	The vector to divide with
	* @return			The scaled vector
	*/
	FORCE_INLINE Vector3F operator/( const Vector3F& a_vector )const;

	/*
	* Get the Result of Dividing this Vector
	*
	* @param a_scale	Scale coeficient to apply to each component of the vector
	* @return			The scaled vector
	*/
	FORCE_INLINE Vector3F operator/( float a_scale )const;


	/*
	* Add the other vector to this one
	*
	* @param a_vector	the other vector to add to this one
	* @param copy of this vector after addition
	*/
	FORCE_INLINE Vector3F operator+=( const Vector3F& a_vector );

	/*
	* Sub the other vector from this one
	*
	* @param a_vector	the other vector to ub from this one
	* @param copy of this vector after Substraction
	*/
	FORCE_INLINE Vector3F operator-=( const Vector3F& a_vector );

	/*
	* Multiply this vector by another one, component wise
	*
	* @param a_vector	the other vector to multiply to this one
	* @param copy of this vector after multiplication
	*/
	FORCE_INLINE Vector3F operator*=( const Vector3F& a_vector );

	/*
	* Scale this vector
	*
	* @param a_scale	The scale coefficient to apply
	* @param copy of this vector after multiplication
	*/
	FORCE_INLINE Vector3F operator*=( float a_scale );

	/*
	* Divide this vector by another one, component wise
	*
	* @param a_vector	the other vector to divide to this one
	* @param copy of this vector after division
	*/
	FORCE_INLINE Vector3F operator/=( const Vector3F& a_vector );

	/*
	* Divide this vector
	*
	* @param a_scale	The divide coefficient to apply
	* @param copy of this vector after multiplication
	*/
	FORCE_INLINE Vector3F operator/=( float a_scale );

	/*
	* Compare if the 2 Vectors store the same values
	*
	* @param a_Vector	Vector to compare to
	* @result			return true if the 2 vectors are equal
	*/
	FORCE_INLINE bool operator==( const Vector3F& a_vector )const;

	/*
	* check that the 2 Vectors doesn't store the same values
	*
	* @param a_Vector	Vector to compare to
	* @return			return true if the 2 vectors are equal
	*/
	FORCE_INLINE bool operator!=( const Vector3F& a_vector )const;



// Fields
public:

	// Vector Components
	float	x;
	float	y;
	float	z;

// static Helper Vectors
public:
	
	// the Zero vector ( 0 , 0 , 0 )
	static const Vector3F ZeroVector;

	// the Unit vector ( 1 , 1 , 1 )
	static const Vector3F UnitVector;

	// the Up vector ( 0 , 0 , 0 )
	static const Vector3F UpVector;

};

// The inline is included in the Header only if not in debug mode
#ifndef _DEBUG
#include "Vector3F.inl"
#endif

#endif