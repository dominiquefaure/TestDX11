#pragma once
#ifndef __CORE_MATH_VECTOR4F_H__
#define __CORE_MATH_VECTOR4F_H__

#include "../CoreMacros.h"
#include "../Base/Includes.h"
#include "MathMacros.h"

#include "Vector3F.h"

/*
* Float Vector4,
*
* For performance reason , all the methods are inline
*/
struct Vector4F
{
	/*
	* Constructor that initialize each component
	*
	* @param a_x		x component
	* @param a_y		y component
	* @param a_z		z component
	* @param a_w		w component
	*/
	explicit FORCE_INLINE Vector4F( TFloat32 a_x = 0.0f , TFloat32 a_y = 0.0f  , TFloat32 a_z = 0.0f  , TFloat32 a_w = 1.0f );

	/*
	* Constructor That generate a Vector3 from a Vector3
	*
	* @param a_vector3	initial vector 3
	* @param a_w		w component
	*/
	FORCE_INLINE Vector4F( const Vector3F& a_vector3 , TFloat32 a_w = 1.0f );


	/**
	 * Access a specific component of the vector.
	 *
	 * @param a_index The index of the component.
	 * @return Reference to the desired component.
	 */
	FORCE_INLINE TFloat32& operator[]( TUint32 a_index );

	/**
	 * Access a specific component of the vector.
	 *
	 * @param a_index The index of the component.
	 * @return Reference to the desired component.
	 */
	FORCE_INLINE TFloat32 operator[]( TUint32 a_index ) const;


	/*
	* Set the Different components of the Vector
	*
	* @param a_x		x component
	* @param a_y		y component
	* @param a_z		z component
	* @param a_w		w component
	*/
	FORCE_INLINE void Set( TFloat32 a_x , TFloat32 a_y , TFloat32 a_z  , TFloat32 a_w );

	/*
	* Compute the Dot product between this vector and another one
	*
	* @param a_vector	2nd Vector
	* @return			the Dot Product
	*/
	FORCE_INLINE TFloat32 Dot( const Vector4F& a_vector )const;

	/*
	* Compute the Dot product between 2 Vectors
	*
	* @param a_v1		1st Vector
	* @param a_v2		2nd Vector
	* @return			the Dot Product
	*/
	FORCE_INLINE static TFloat32 Dot( const Vector4F& a_v1 , const Vector4F& a_v2 );

// Operators
public:

	/*
	* Get the Negated copy of this Vector
	*
	* @return a negated copy of this Vector
	*/
	FORCE_INLINE Vector4F operator-()const;

	/**
	* Get the result of component wise Addition of this vector by another one
	* 
	* @param a_vector	The vector to add to this one.
	* @return			The result vector.
	*/
	FORCE_INLINE Vector4F operator+( const Vector4F& a_vector )const;

	/**
	* Get the result of component wise Substraction of this vector by another one
	* 
	* @param a_vector	The vector to ubstract from this one.
	* @return			The result vector.
	*/
	FORCE_INLINE Vector4F operator-( const Vector4F& a_vector )const;


	/*
	* Get the Result of component wize Scaling of this Vector
	*
	* @param a_vector	The vector to multiply with
	* @return			The scaled vector
	*/
	FORCE_INLINE Vector4F operator*( const Vector4F& a_vector )const;

	/*
	* Get the Result of Uniform Scaling this Vector
	*
	* @param a_scale	Scale coeficient to apply to each component of the vector
	* @return			The scaled vector
	*/
	FORCE_INLINE Vector4F operator*( TFloat32 a_scale )const;


	/*
	* Get the Result of component wize Dividing of this Vector
	*
	* @param a_vector	The vector to divide with
	* @return			The scaled vector
	*/
	FORCE_INLINE Vector4F operator/( const Vector4F& a_vector )const;

	/*
	* Get the Result of Dividing this Vector
	*
	* @param a_scale	Scale coeficient to apply to each component of the vector
	* @return			The scaled vector
	*/
	FORCE_INLINE Vector4F operator/( TFloat32 a_scale )const;


	/*
	* Add the other vector to this one
	*
	* @param a_vector	the other vector to add to this one
	* @param copy of this vector after addition
	*/
	FORCE_INLINE Vector4F operator+=( const Vector4F& a_vector );

	/*
	* Sub the other vector from this one
	*
	* @param a_vector	the other vector to ub from this one
	* @param copy of this vector after Substraction
	*/
	FORCE_INLINE Vector4F operator-=( const Vector4F& a_vector );

	/*
	* Multiply this vector by another one, component wise
	*
	* @param a_vector	the other vector to multiply to this one
	* @param copy of this vector after multiplication
	*/
	FORCE_INLINE Vector4F operator*=( const Vector4F& a_vector );

	/*
	* Scale this vector
	*
	* @param a_scale	The scale coefficient to apply
	* @param copy of this vector after multiplication
	*/
	FORCE_INLINE Vector4F operator*=( TFloat32 a_scale );

	/*
	* Divide this vector by another one, component wise
	*
	* @param a_vector	the other vector to divide to this one
	* @param copy of this vector after division
	*/
	FORCE_INLINE Vector4F operator/=( const Vector4F& a_vector );

	/*
	* Divide this vector
	*
	* @param a_scale	The divide coefficient to apply
	* @param copy of this vector after multiplication
	*/
	FORCE_INLINE Vector4F operator/=( TFloat32 a_scale );

	/*
	* Compare if the 2 Vectors store the same values
	*
	* @param a_Vector	Vector to compare to
	* @result			return true if the 2 vectors are equal
	*/
	FORCE_INLINE bool operator==( const Vector4F& a_vector )const;

	/*
	* check that the 2 Vectors doesn't store the same values
	*
	* @param a_Vector	Vector to compare to
	* @return			return true if the 2 vectors are equal
	*/
	FORCE_INLINE bool operator!=( const Vector4F& a_vector )const;



// Fields
public:
	union
	{
		TFloat32 m_components[4];
		struct
		{
			// Vector Components
			TFloat32	x;
			TFloat32	y;
			TFloat32	z;
			TFloat32	w;
		};
	};

};

// The inline is included in the Header only if not in debug mode
#ifndef _DEBUG
#include "Vector4F.inl"
#endif

#endif