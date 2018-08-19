/*
* Implementation of the Inline methods of Vector3F
*/

#include "Maths.h"


//----------------------------------------------------------------------------------------------------
FORCE_INLINE Vector4F::Vector4F( float a_x , float a_y , float a_z , float a_w )
{
	x														=	a_x;
	y														=	a_y;
	z														=	a_z;
	w														=	a_w;
}
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
FORCE_INLINE Vector4F::Vector4F( const Vector3F& a_vector , float a_w )
{
	x														=	a_vector.x;
	y														=	a_vector.y;
	z														=	a_vector.z;
	w														=	a_w;
}
//----------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------
FORCE_INLINE float& Vector4F::operator[]( TUint32 a_index )
{
	return m_components[ a_index ];
}
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
FORCE_INLINE float Vector4F::operator[]( TUint32 a_index ) const
{
	return m_components[ a_index ];
}
//----------------------------------------------------------------------------------------------------



////////////////////
// Operators
////////////////////



//----------------------------------------------------------------------------------------------------
FORCE_INLINE Vector4F Vector4F::operator-()const
{
	return Vector4F( -x , -y , -z , -w );
}
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
FORCE_INLINE Vector4F Vector4F::operator+( const Vector4F& a_vector )const
{
	return Vector4F(	x + a_vector.x ,
						y + a_vector.y ,
						z + a_vector.z ,
						w + a_vector.w );
}
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
FORCE_INLINE Vector4F Vector4F::operator-( const Vector4F& a_vector )const
{
	return Vector4F(	x - a_vector.x ,
						y - a_vector.y ,
						z - a_vector.z ,
						w - a_vector.w );
}
//----------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------
FORCE_INLINE Vector4F Vector4F::operator*( const Vector4F& a_vector )const
{
	return Vector4F(	x * a_vector.x ,
						y * a_vector.y ,
						z * a_vector.z ,
						w * a_vector.w );
}
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
FORCE_INLINE Vector4F Vector4F::operator*( float a_scale )const
{
	return Vector4F(	x * a_scale ,
						y * a_scale ,
						z * a_scale ,
						w * a_scale );
}
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
FORCE_INLINE Vector4F Vector4F::operator/( const Vector4F& a_vector )const
{
	return Vector4F(	x / a_vector.x ,
						y / a_vector.y ,
						z / a_vector.z ,
						w / a_vector.w );
}
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
FORCE_INLINE Vector4F Vector4F::operator/( float a_scale )const
{
	const float t_scale										=	1.0f / a_scale;

	return Vector4F(	x * t_scale ,
						y * t_scale ,
						z * t_scale ,
						w * t_scale );
}
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
FORCE_INLINE Vector4F Vector4F::operator+=( const Vector4F& a_vector )
{
	x														+=	a_vector.x;
	y														+=	a_vector.y;
	z														+=	a_vector.z;
	w														+=	a_vector.w;

	return *this;
}
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
FORCE_INLINE Vector4F Vector4F::operator-=( const Vector4F& a_vector )
{
	x														-=	a_vector.x;
	y														-=	a_vector.y;
	z														-=	a_vector.z;
	w														-=	a_vector.w;

	return *this;
}
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
FORCE_INLINE Vector4F Vector4F::operator*=( const Vector4F& a_vector )
{
	x														*=	a_vector.x;
	y														*=	a_vector.y;
	z														*=	a_vector.z;
	w														*=	a_vector.w;

	return *this;
}
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
FORCE_INLINE Vector4F Vector4F::operator*=( float a_scale )
{
	x														*=	a_scale;
	y														*=	a_scale;
	z														*=	a_scale;
	w														*=	a_scale;

	return *this;
}
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
FORCE_INLINE Vector4F Vector4F::operator/=( const Vector4F& a_vector )
{
	x														/=	a_vector.x;
	y														/=	a_vector.y;
	z														/=	a_vector.z;
	w														/=	a_vector.w;

	return *this;
}
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
FORCE_INLINE Vector4F Vector4F::operator/=( float a_scale )
{
	const float t_scale										=	1.0f / a_scale;

	x														*=	t_scale;
	y														*=	t_scale;
	z														*=	t_scale;
	w														*=	t_scale;

	return *this;

}
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
FORCE_INLINE bool Vector4F::operator==( const Vector4F& a_vector )const
{
	return ( ( x == a_vector.x ) && ( y == a_vector.y ) && ( z == a_vector.z )  && ( w == a_vector.w ) );
}
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
FORCE_INLINE bool Vector4F::operator!=( const Vector4F& a_vector )const
{
	return ( ( x != a_vector.x ) || ( y != a_vector.y ) || ( z != a_vector.z ) || ( w != a_vector.w ) );
}
//----------------------------------------------------------------------------------------------------


