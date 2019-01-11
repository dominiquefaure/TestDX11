

#include "MathMacros.h"

//-----------------------------------------------------------------------------------------
FORCE_INLINE Matrix44::Matrix44()
{
	M[ 0 ][ 0 ]												=	0.0f;
	M[ 0 ][ 1 ]												=	0.0f;
	M[ 0 ][ 2 ]												=	0.0f;
	M[ 0 ][ 3 ]												=	0.0f;

	M[ 1 ][ 0 ]												=	0.0f;
	M[ 1 ][ 1 ]												=	0.0f;
	M[ 1 ][ 2 ]												=	0.0f;
	M[ 1 ][ 3 ]												=	0.0f;

	M[ 2 ][ 0 ]												=	0.0f;
	M[ 2 ][ 1 ]												=	0.0f;
	M[ 2 ][ 2 ]												=	0.0f;
	M[ 2 ][ 3 ]												=	0.0f;

	M[ 3 ][ 0 ]												=	0.0f;
	M[ 3 ][ 1 ]												=	0.0f;
	M[ 3 ][ 2 ]												=	0.0f;
	M[ 3 ][ 3 ]												=	0.0f;

}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
FORCE_INLINE Matrix44::Matrix44( const Matrix44& a_other )
{

	for( int j = 0 ; j < 4 ; j ++ )
	{
		for( int i = 0 ; i < 4 ; i ++ )
		{
			M[ j ][ i ]										=	a_other.M[ j ][ i ];	
		}
	}
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
FORCE_INLINE Matrix44::Matrix44(	TFloat32 m00 , TFloat32 m01 , TFloat32 m02 ,TFloat32 m03 ,
									TFloat32 m10 , TFloat32 m11 , TFloat32 m12 ,TFloat32 m13 ,
									TFloat32 m20 , TFloat32 m21 , TFloat32 m22 ,TFloat32 m23 ,
									TFloat32 m30 , TFloat32 m31 , TFloat32 m32 ,TFloat32 m33 )
{
	M[ 0 ][ 0 ]												=	m00;
	M[ 0 ][ 1 ]												=	m01;
	M[ 0 ][ 2 ]												=	m02;
	M[ 0 ][ 3 ]												=	m03;

	M[ 1 ][ 0 ]												=	m10;
	M[ 1 ][ 1 ]												=	m11;
	M[ 1 ][ 2 ]												=	m12;
	M[ 1 ][ 3 ]												=	m13;

	M[ 2 ][ 0 ]												=	m20;
	M[ 2 ][ 1 ]												=	m21;
	M[ 2 ][ 2 ]												=	m22;
	M[ 2 ][ 3 ]												=	m23;

	M[ 3 ][ 0 ]												=	m30;
	M[ 3 ][ 1 ]												=	m31;
	M[ 3 ][ 2 ]												=	m32;
	M[ 3 ][ 3 ]												=	m33;

}
//-----------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------
FORCE_INLINE void Matrix44::SetValues(	TFloat32 m00 , TFloat32 m01 , TFloat32 m02 , TFloat32 m03 ,
										TFloat32 m10 , TFloat32 m11 , TFloat32 m12 , TFloat32 m13 ,
										TFloat32 m20 , TFloat32 m21 , TFloat32 m22 , TFloat32 m23 ,
										TFloat32 m30 , TFloat32 m31 , TFloat32 m32 , TFloat32 m33 )
{

#if ( PLATFORM_CONFIG_MATRIX_ORDER == MATRIX_ORDER_ROW_MAJOR )
	Rows[ 0 ].Set( m00 , m01 , m02 , m03 );
	Rows[ 1 ].Set( m10 , m11 , m12 , m13 );
	Rows[ 2 ].Set( m20 , m21 , m22 , m23 );
	Rows[ 3 ].Set( m30 , m31 , m32 , m33 );
#else
	Columns[ 0 ].Set( m00 , m01 , m02 , m03 );
	Columns[ 1 ].Set( m10 , m11 , m12 , m13 );
	Columns[ 2 ].Set( m20 , m21 , m22 , m23 );
	Columns[ 3 ].Set( m30 , m31 , m32 , m33 );
#endif

}
//-----------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------
FORCE_INLINE void Matrix44::SetIdentity()
{
	M[ 0 ][ 0 ]												=	1.0f;
	M[ 0 ][ 1 ]												=	0.0f;
	M[ 0 ][ 2 ]												=	0.0f;
	M[ 0 ][ 3 ]												=	0.0f;

	M[ 1 ][ 0 ]												=	0.0f;
	M[ 1 ][ 1 ]												=	1.0f;
	M[ 1 ][ 2 ]												=	0.0f;
	M[ 1 ][ 3 ]												=	0.0f;

	M[ 2 ][ 0 ]												=	0.0f;
	M[ 2 ][ 1 ]												=	0.0f;
	M[ 2 ][ 2 ]												=	1.0f;
	M[ 2 ][ 3 ]												=	0.0f;

	M[ 3 ][ 0 ]												=	0.0f;
	M[ 3 ][ 1 ]												=	0.0f;
	M[ 3 ][ 2 ]												=	0.0f;
	M[ 3 ][ 3 ]												=	1.0f;
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
FORCE_INLINE TFloat32 Matrix44::GetDeterminant()const
{
	TFloat32 t00											=	( M[ 2 ][ 2 ] * M[ 3 ][ 3 ] ) - ( M[ 2 ][ 3 ] * M[ 3 ][ 2 ] );
	TFloat32 t01											=	( M[ 2 ][ 3 ] * M[ 3 ][ 1 ] ) - ( M[ 2 ][ 1 ] * M[ 3 ][ 3 ] );
	TFloat32 t02											=	( M[ 2 ][ 1 ] * M[ 3 ][ 2 ] ) - ( M[ 2 ][ 2 ] * M[ 3 ][ 1 ] );

	TFloat32 t10											=	t00;
	TFloat32 t11											=	( M[ 2 ][ 3 ] * M[ 3 ][ 0 ] ) - ( M[ 2 ][ 0 ] * M[ 3 ][ 3 ] );
	TFloat32 t12											=	( M[ 2 ][ 0 ] * M[ 3 ][ 2 ] ) - ( M[ 2 ][ 2 ] * M[ 3 ][ 0 ] );

	TFloat32 t20											=	( M[ 2 ][ 1 ] * M[ 3 ][ 3 ] ) - ( M[ 2 ][ 3 ] * M[ 3 ][ 1 ] );
	TFloat32 t21											=	t11;
	TFloat32 t22											=	( M[ 2 ][ 0 ] * M[ 3 ][ 1 ] ) - ( M[ 2 ][ 1 ] * M[ 3 ][ 0 ] );

	TFloat32 t30											=	t02;
	TFloat32 t31											=	( M[ 2 ][ 2 ] * M[ 3 ][ 0 ] ) - ( M[ 2 ][ 0 ] * M[ 3 ][ 2 ] );
	TFloat32 t32											=	t22;

	TFloat32 t0												=	( M[ 1 ][ 1 ] * t00 ) + ( M[ 1 ][ 2 ] * t01 ) + ( M[ 1 ][ 3 ] * t02 );
	TFloat32 t1												=	( M[ 1 ][ 0 ] * t10 ) + ( M[ 1 ][ 2 ] * t11 ) + ( M[ 1 ][ 3 ] * t12 );
	TFloat32 t2												=	( M[ 1 ][ 0 ] * t20 ) + ( M[ 1 ][ 1 ] * t21 ) + ( M[ 1 ][ 3 ] * t22 );
	TFloat32 t3												=	( M[ 1 ][ 0 ] * t30 ) + ( M[ 1 ][ 1 ] * t31 ) + ( M[ 1 ][ 2 ] * t32 );

	return ( ( M[ 0 ][ 0 ] * t0 ) - ( M[ 0 ][ 1 ] * t1 ) + ( M[ 0 ][ 2 ] * t2 ) - ( M[ 0 ][ 3 ] * t3 ) );
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
FORCE_INLINE void Matrix44::Inverse()
{
	// if determinant i 0, reset the matrix as identity
	if( GetDeterminant() == 0.0f )
	{
		SetIdentity();
	}
	else
	{
		Matrix44 t_temp;

		// copy the different cross product components
		TFloat32 t_1201										=	( M[ 1 ][ 0 ] * M[ 2 ][ 1 ] ) - ( M[ 1 ][ 1 ] * M[ 2 ][ 0 ] );
		TFloat32 t_1202										=	( M[ 1 ][ 0 ] * M[ 2 ][ 2 ] ) - ( M[ 1 ][ 2 ] * M[ 2 ][ 0 ] );
		TFloat32 t_1203										=	( M[ 1 ][ 0 ] * M[ 2 ][ 3 ] ) - ( M[ 1 ][ 3 ] * M[ 2 ][ 0 ] );

		TFloat32 t_1212										=	( M[ 1 ][ 1 ] * M[ 2 ][ 2 ] ) - ( M[ 1 ][ 2 ] * M[ 2 ][ 1 ] );
		TFloat32 t_1213										=	( M[ 1 ][ 1 ] * M[ 2 ][ 3 ] ) - ( M[ 1 ][ 3 ] * M[ 2 ][ 1 ] );
		TFloat32 t_1223										=	( M[ 1 ][ 2 ] * M[ 2 ][ 3 ] ) - ( M[ 1 ][ 3 ] * M[ 2 ][ 2 ] );

		TFloat32 t_1301										=	( M[ 1 ][ 0 ] * M[ 3 ][ 1 ] ) - ( M[ 1 ][ 1 ] * M[ 3 ][ 0 ] );
		TFloat32 t_1302										=	( M[ 1 ][ 0 ] * M[ 3 ][ 2 ] ) - ( M[ 1 ][ 2 ] * M[ 3 ][ 0 ] );
		TFloat32 t_1303										=	( M[ 1 ][ 0 ] * M[ 3 ][ 3 ] ) - ( M[ 1 ][ 3 ] * M[ 3 ][ 0 ] );

		TFloat32 t_1312										=	( M[ 1 ][ 1 ] * M[ 3 ][ 2 ] ) - ( M[ 1 ][ 2 ] * M[ 3 ][ 1 ] );
		TFloat32 t_1313										=	( M[ 1 ][ 1 ] * M[ 3 ][ 3 ] ) - ( M[ 1 ][ 3 ] * M[ 3 ][ 1 ] );
		TFloat32 t_1323										=	( M[ 1 ][ 2 ] * M[ 3 ][ 3 ] ) - ( M[ 1 ][ 3 ] * M[ 3 ][ 2 ] );

		TFloat32 t_2301										=	( M[ 2 ][ 0 ] * M[ 3 ][ 1 ] ) - ( M[ 2 ][ 1 ] * M[ 3 ][ 0 ] );
		TFloat32 t_2302										=	( M[ 2 ][ 0 ] * M[ 3 ][ 2 ] ) - ( M[ 2 ][ 2 ] * M[ 3 ][ 0 ] );
		TFloat32 t_2303										=	( M[ 2 ][ 0 ] * M[ 3 ][ 3 ] ) - ( M[ 2 ][ 3 ] * M[ 3 ][ 0 ] );

		TFloat32 t_2312										=	( M[ 2 ][ 1 ] * M[ 3 ][ 2 ] ) - ( M[ 2 ][ 2 ] * M[ 3 ][ 1 ] );
		TFloat32 t_2313										=	( M[ 2 ][ 1 ] * M[ 3 ][ 3 ] ) - ( M[ 2 ][ 3 ] * M[ 3 ][ 1 ] );
		TFloat32 t_2323										=	( M[ 2 ][ 2 ] * M[ 3 ][ 3 ] ) - ( M[ 2 ][ 3 ] * M[ 3 ][ 2 ] );

		// Set the Temp Matrix value
		t_temp.M[ 0 ][ 0 ]									=	( M[ 1 ] [ 1 ] * t_2323 ) - ( M[ 1 ] [ 2 ] * t_2313 ) + ( M[ 1 ][ 3 ] * t_2312 );
		t_temp.M[ 1 ][ 0 ]									=	( M[ 1 ] [ 2 ] * t_2303 ) - ( M[ 1 ] [ 0 ] * t_2323 ) - ( M[ 1 ][ 3 ] * t_2302 );
		t_temp.M[ 2 ][ 0 ]									=	( M[ 1 ] [ 0 ] * t_2313 ) - ( M[ 1 ] [ 1 ] * t_2303 ) + ( M[ 1 ][ 3 ] * t_2301 );
		t_temp.M[ 3 ][ 0 ]									=	( M[ 1 ] [ 1 ] * t_2302 ) - ( M[ 1 ] [ 0 ] * t_2312 ) - ( M[ 1 ][ 2 ] * t_2301 );

		t_temp.M[ 0 ][ 1 ]									=	( M[ 0 ] [ 2 ] * t_2313 ) - ( M[ 0 ] [ 1 ] * t_2323 ) - ( M[ 0 ][ 3 ] * t_2312 );
		t_temp.M[ 1 ][ 1 ]									=	( M[ 0 ] [ 0 ] * t_2323 ) - ( M[ 0 ] [ 2 ] * t_2303 ) + ( M[ 0 ][ 3 ] * t_2302 );
		t_temp.M[ 2 ][ 1 ]									=	( M[ 0 ] [ 1 ] * t_2303 ) - ( M[ 0 ] [ 0 ] * t_2313 ) - ( M[ 0 ][ 3 ] * t_2301 );
		t_temp.M[ 3 ][ 1 ]									=	( M[ 0 ] [ 0 ] * t_2312 ) - ( M[ 0 ] [ 1 ] * t_2302 ) + ( M[ 0 ][ 2 ] * t_2301 );

		t_temp.M[ 0 ][ 2 ]									=	( M[ 0 ] [ 1 ] * t_1323 ) - ( M[ 0 ] [ 2 ] * t_1313 ) + ( M[ 0 ][ 3 ] * t_1312 );
		t_temp.M[ 1 ][ 2 ]									=	( M[ 0 ] [ 2 ] * t_1303 ) - ( M[ 0 ] [ 0 ] * t_1323 ) - ( M[ 0 ][ 3 ] * t_1302 );
		t_temp.M[ 2 ][ 2 ]									=	( M[ 0 ] [ 0 ] * t_1313 ) - ( M[ 0 ] [ 1 ] * t_1303 ) + ( M[ 0 ][ 3 ] * t_1301 );
		t_temp.M[ 3 ][ 2 ]									=	( M[ 0 ] [ 1 ] * t_1302 ) - ( M[ 0 ] [ 0 ] * t_1312 ) - ( M[ 0 ][ 2 ] * t_1301 );

		t_temp.M[ 0 ][ 3 ]									=	( M[ 0 ] [ 2 ] * t_1213 ) - ( M[ 0 ] [ 1 ] * t_1223 ) - ( M[ 0 ][ 3 ] * t_1212 );
		t_temp.M[ 1 ][ 3 ]									=	( M[ 0 ] [ 0 ] * t_1223 ) - ( M[ 0 ] [ 2 ] * t_1203 ) + ( M[ 0 ][ 3 ] * t_1202 );
		t_temp.M[ 2 ][ 3 ]									=	( M[ 0 ] [ 1 ] * t_1203 ) - ( M[ 0 ] [ 0 ] * t_1213 ) - ( M[ 0 ][ 3 ] * t_1201 );
		t_temp.M[ 3 ][ 3 ]									=	( M[ 0 ] [ 0 ] * t_1212 ) - ( M[ 0 ] [ 1 ] * t_1202 ) + ( M[ 0 ][ 2 ] * t_1201 );

		//compute the determinant
		TFloat32 t_determinant								=	( M[ 0 ][ 0 ] * t_temp.M[ 0 ][ 0 ] ) +( M[ 1 ][ 0 ] * t_temp.M[ 0 ][ 1 ] ) + ( M[ 0 ][ 2 ] * t_temp.M[ 3 ][ 0 ] ) + ( M[ 3 ][ 0 ] * t_temp.M[ 0 ][ 3 ] );

		// if big enough
		if( t_determinant > 1.0e-16f )
		{
			TFloat32 t_scale								=	1.0f / t_determinant;

			*this											=	t_temp * t_scale;
		}
		else
		{
			//reet to identity 
			SetIdentity();
		}
	}

}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
FORCE_INLINE Matrix44 Matrix44::GetInverse()const
{
	Matrix44 t_result(*this);

	t_result.Inverse();

	return t_result;
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
FORCE_INLINE void Matrix44::Transpose()
{
	Matrix44 t_temp											=	*this;

	M[ 0 ][ 0 ]												=	t_temp.M[ 0 ][ 0 ];
	M[ 0 ][ 1 ]												=	t_temp.M[ 1 ][ 0 ];
	M[ 0 ][ 2 ]												=	t_temp.M[ 2 ][ 0 ];
	M[ 0 ][ 3 ]												=	t_temp.M[ 3 ][ 0 ];

	M[ 1 ][ 0 ]												=	t_temp.M[ 0 ][ 1 ];
	M[ 1 ][ 1 ]												=	t_temp.M[ 1 ][ 1 ];
	M[ 1 ][ 2 ]												=	t_temp.M[ 2 ][ 1 ];
	M[ 1 ][ 3 ]												=	t_temp.M[ 3 ][ 1 ];

	M[ 2 ][ 0 ]												=	t_temp.M[ 0 ][ 2 ];
	M[ 2 ][ 1 ]												=	t_temp.M[ 1 ][ 2 ];
	M[ 2 ][ 2 ]												=	t_temp.M[ 2 ][ 2 ];
	M[ 2 ][ 3 ]												=	t_temp.M[ 3 ][ 2 ];

	M[ 3 ][ 0 ]												=	t_temp.M[ 0 ][ 3 ];
	M[ 3 ][ 1 ]												=	t_temp.M[ 1 ][ 3 ];
	M[ 3 ][ 2 ]												=	t_temp.M[ 2 ][ 3 ];
	M[ 3 ][ 3 ]												=	t_temp.M[ 3 ][ 3 ];

}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
FORCE_INLINE Matrix44 Matrix44::GetTranspose()const
{
	Matrix44 t_result;

	t_result.M[ 0 ][ 0 ]									=	M[ 0 ][ 0 ];
	t_result.M[ 0 ][ 1 ]									=	M[ 1 ][ 0 ];
	t_result.M[ 0 ][ 2 ]									=	M[ 2 ][ 0 ];
	t_result.M[ 0 ][ 3 ]									=	M[ 3 ][ 0 ];

	t_result.M[ 1 ][ 0 ]									=	M[ 0 ][ 1 ];
	t_result.M[ 1 ][ 1 ]									=	M[ 1 ][ 1 ];
	t_result.M[ 1 ][ 2 ]									=	M[ 2 ][ 1 ];
	t_result.M[ 1 ][ 3 ]									=	M[ 3 ][ 1 ];

	t_result.M[ 2 ][ 0 ]									=	M[ 0 ][ 2 ];
	t_result.M[ 2 ][ 1 ]									=	M[ 1 ][ 2 ];
	t_result.M[ 2 ][ 2 ]									=	M[ 2 ][ 2 ];
	t_result.M[ 2 ][ 3 ]									=	M[ 3 ][ 2 ];

	t_result.M[ 3 ][ 0 ]									=	M[ 0 ][ 3 ];
	t_result.M[ 3 ][ 1 ]									=	M[ 1 ][ 3 ];
	t_result.M[ 3 ][ 2 ]									=	M[ 2 ][ 3 ];
	t_result.M[ 3 ][ 3 ]									=	M[ 3 ][ 3 ];

	return t_result;
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
FORCE_INLINE bool Matrix44::IsEqual( const Matrix44& a_other , TFloat32 a_tolerance )
{
	for( int j = 0 ; j < 4 ; j ++ )
	{
		for( int i = 0 ; i < 4 ; i ++ )
		{
			if( Maths::Abs( M[ j ][ i ] - a_other.M[ j ][ i ] ) > a_tolerance )
			{
				return false;
			}
		}
	}

	return true;
}
//-----------------------------------------------------------------------------------------



////////////
// Translation Methods
/////////////

//-----------------------------------------------------------------------------------------
FORCE_INLINE void Matrix44::SetTranslate( const Vector3F& a_translation )
{
	//reset the Matrix to identity
	SetIdentity();

	// Set the Translation to column 3
	SetColumn( 3 , a_translation );
}
//-----------------------------------------------------------------------------------------




////////////
// Scale Methods
/////////////

//-----------------------------------------------------------------------------------------
FORCE_INLINE void Matrix44::SetScale( const Vector3F& a_scale )
{
	SetValues(	a_scale.x	, 0.0f		, 0.0f		, 0.0f ,
				0.0f		, a_scale.y , 0.0f		, 0.0f ,
				0.0f		, 0.0f		, a_scale.z	, 0.0f ,
				0.0f		, 0.0f		, 0.0f		, 1.0f );
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
FORCE_INLINE void Matrix44::SetScale( TFloat32 a_scale )
{
	SetValues(	a_scale	, 0.0f		, 0.0f		, 0.0f ,
				0.0f	, a_scale	, 0.0f		, 0.0f ,
				0.0f	, 0.0f		, a_scale	, 0.0f ,
				0.0f	, 0.0f		, 0.0f		, 1.0f );
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
FORCE_INLINE void Matrix44::SetScale( TFloat32 a_scaleX , TFloat32 a_scaleY , TFloat32 a_scaleZ )
{
	SetValues(	a_scaleX, 0.0f		, 0.0f		, 0.0f ,
				0.0f	, a_scaleY	, 0.0f		, 0.0f ,
				0.0f	, 0.0f		, a_scaleZ	, 0.0f ,
				0.0f	, 0.0f		, 0.0f		, 1.0f );
}
//-----------------------------------------------------------------------------------------


////////////
// Rotate Methods
/////////////

//-----------------------------------------------------------------------------------------
FORCE_INLINE void Matrix44::SetRotateX( TFloat32 a_angle )
{
	// compute cos and sin
	TFloat32 t_cos											=	Maths::Cos( a_angle );
	TFloat32 t_sin											=	Maths::Sin( a_angle );

	SetValues(	1.0f	, 0.0f		, 0.0f		, 0.0f ,
				0.0f	, t_cos		, -t_sin	, 0.0f ,
				0.0f	, t_sin		, t_cos		, 0.0f ,
				0.0f	, 0.0f		, 0.0f		, 1.0f );

}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
FORCE_INLINE void Matrix44::SetRotateY( TFloat32 a_angle )
{
	// compute cos and sin
	TFloat32 t_cos											=	Maths::Cos( a_angle );
	TFloat32 t_sin											=	Maths::Sin( a_angle );

	SetValues(	t_cos	, 0.0f		, t_sin		, 0.0f ,
				0.0f	, 1.0f		, 0.0f		, 0.0f ,
				-t_sin	, 0.0f		, t_cos		, 0.0f ,
				0.0f	, 0.0f		, 0.0f		, 1.0f );

}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
FORCE_INLINE void Matrix44::SetRotateZ( TFloat32 a_angle )
{
	// compute cos and sin
	TFloat32 t_cos											=	Maths::Cos( a_angle );
	TFloat32 t_sin											=	Maths::Sin( a_angle );

	SetValues(	t_cos	, -t_sin	, 0.0f		, 0.0f ,
				t_sin	, t_cos		, 0.0f		, 0.0f ,
				0.0f	, 0.0f		, 1.0f		, 0.0f ,
				0.0f	, 0.0f		, 0.0f		, 1.0f );

}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
FORCE_INLINE void Matrix44::SetRotate( TFloat32 a_pitch , TFloat32 a_yaw , TFloat32 a_roll )
{
	// compute Sin and cos for the 3 angles

	TFloat32 t_cosPitch										=	Maths::Cos( a_pitch );
	TFloat32 t_sinPitch										=	Maths::Sin( a_pitch );
	TFloat32 t_cosYaw										=	Maths::Cos( a_yaw );
	TFloat32 t_sinYaw										=	Maths::Sin( a_yaw );
	TFloat32 t_cosRoll										=	Maths::Cos( a_roll );
	TFloat32 t_sinRoll										=	Maths::Sin( a_roll );

	TFloat32 t_sinPitchSinYaw								=	t_sinPitch * t_sinYaw;
	TFloat32 t_cosPitchSinYaw								=	t_cosPitch * t_sinYaw;

	_m00													=	t_cosYaw * t_cosRoll;
	_m10													=	t_cosYaw * t_sinRoll;
	_m20													=	-t_sinYaw;
	_m30													=	0.0f;

	_m01													=	( t_sinPitchSinYaw * t_cosRoll ) - ( t_cosPitch * t_sinRoll );
	_m11													=	( t_sinPitchSinYaw * t_sinRoll ) + ( t_cosPitch * t_cosRoll );
	_m21													=	t_sinPitch * t_cosYaw;
	_m31													=	0.0f;

	_m02													=	( t_cosPitchSinYaw * t_cosRoll ) + ( t_sinPitch * t_sinRoll );
	_m12													=	( t_cosPitchSinYaw * t_sinRoll ) - ( t_sinPitch * t_cosRoll );
	_m22													=	t_cosPitch * t_cosYaw;
	_m32													=	0.0f;

	_m03													=	0.0f;
	_m13													=	0.0f;
	_m23													=	0.0f;
	_m33													=	1.0f;

}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
FORCE_INLINE void Matrix44::SetRotate( const Vector3F& a_rotation )
{
	if (s_useCompose)
	{
		SetRotate( a_rotation.x , a_rotation.y , a_rotation.z );
	}
	else
	{
		Matrix44 t_rotX;
		Matrix44 t_rotY;
		Matrix44 t_rotZ;

		t_rotX.SetRotateX(a_rotation.x);
		t_rotY.SetRotateY(a_rotation.y);
		t_rotZ.SetRotateZ(a_rotation.z);

		*this = t_rotX * t_rotY * t_rotZ;
	}
}
//-----------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------
FORCE_INLINE void Matrix44::SetTransScaleRot( Vector3F a_translation , Vector3F a_scale , Vector3F a_rot )
{
	Matrix44 t_translation;
	Matrix44 t_scale;
	Matrix44 t_rot;

	// Set the different intermediates Matrix
	t_translation.SetTranslate( a_translation );
	t_scale.SetScale( a_scale );
	t_rot.SetRotate( a_rot );

#if ( PLATFORM_CONFIG_MATRIX_ORDER == MATRIX_ORDER_ROW_MAJOR )
	*this													=	t_translation * t_scale * t_rot;
#else
	*this													=	t_rot * t_scale * t_translation;
#endif

}
//-----------------------------------------------------------------------------------------

///////////////////////////
// Projection Matrix
//////////////////////////

//-----------------------------------------------------------------------------------------
FORCE_INLINE void Matrix44::SetOrthoProjection( TFloat32 a_left , TFloat32 a_right , TFloat32 a_top , TFloat32 a_bottom , TFloat32 a_zNear , TFloat32 a_zFar )
{
    TFloat32 sx												=	1.0f / ( a_right - a_left );
    TFloat32 sy												=	1.0f / ( a_top - a_bottom );
    TFloat32 sz												=	1.0f / ( a_zFar - a_zNear );

	_m00													=	2.0f * sx;
	_m01													=	0.0f;
	_m02													=	0.0f;
	_m03													=	0.0f;

	_m10													=	0.0f;
	_m11													=	2.0f * sy;
	_m12													=	0.0f;
	_m13													=	0.0f;

	_m20													=	0.0f;
	_m21													=	0.0f;
	_m22													=	sz;
	_m23													=	0.0f;


	_m30													=	( a_right + a_left ) / ( a_left - a_right );
	_m31													=	( a_top + a_bottom ) / ( a_bottom - a_top );
	_m32													=	a_zNear / ( a_zNear - a_zFar );
	_m33													=	1.0f;
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
FORCE_INLINE void Matrix44::SetPerpectiveProjection( TFloat32 a_fov , TFloat32 a_aspectRatio , TFloat32 a_zNear , TFloat32 a_zFar )
{
	//todo add asserts

	TFloat32 t_yScale										=	1.0f / Maths::Tan( a_fov * 0.5f );
	TFloat32 t_xScale										=	t_yScale / a_aspectRatio;

	SetValues(	t_xScale	, 0.0f		, 0.0f											, 0.0f ,
				0.0f		, t_yScale	, 0.0f											, 0.0f ,
				0.0f		, 0.0f		, a_zFar / ( a_zFar - a_zNear )					, 1.0f ,
				0.0f		, 0.0f		, -( a_zNear * a_zFar ) / ( a_zFar - a_zNear )	, 0.0f );

}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
FORCE_INLINE void Matrix44::SetLookAt( const Vector3F& a_position , const Vector3F& a_target , const Vector3F& a_up )
{
	//Get normalized up vector
	Vector3F t_up											=	a_up.GetNormalized();

	Vector3F t_zAxis										=	a_target - a_position;
	t_zAxis.Normalize();

	Vector3F t_xAxis										=	Vector3F::Cross( t_up , t_zAxis );
	t_xAxis.Normalize();

	Vector3F t_yAxis										=	Vector3F::Cross( t_zAxis , t_xAxis );
	t_yAxis.Normalize();

	SetValues(	t_xAxis.x					, t_yAxis.x					, t_zAxis.x					, 0.0f ,
				t_xAxis.y					, t_yAxis.y					, t_zAxis.y					, 0.0f ,
				t_xAxis.z					, t_yAxis.z					, t_zAxis.z					, 0.0f ,
				-t_xAxis.Dot( a_position )	, -t_yAxis.Dot( a_position ), -t_zAxis.Dot( a_position ), 1.0f );
}
//-----------------------------------------------------------------------------------------


////////////
// Operators Methods
/////////////


//-----------------------------------------------------------------------------------------
FORCE_INLINE Matrix44 Matrix44::operator+( const Matrix44& a_other )const
{
	// Create a Copy of this Matrix
	Matrix44 t_result( *this );

	// perform the Addition
	t_result												+=	a_other;

	//return the result
	return t_result;
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
FORCE_INLINE Matrix44 Matrix44::operator-( const Matrix44& a_other )const
{
	// Create a Copy of this Matrix
	Matrix44 t_result( *this );

	// perform the Substraction
	t_result												-=	a_other;

	//return the result
	return t_result;
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
FORCE_INLINE Matrix44 Matrix44::operator*( TFloat32 a_scale )const
{
	// Create a Copy of this Matrix
	Matrix44 t_result( *this );

	// perform the multiplication
	t_result												*=	a_scale;

	//return the result
	return t_result;
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
FORCE_INLINE Matrix44 Matrix44::operator/( TFloat32 a_divider )const
{
	// Create a Copy of this Matrix
	Matrix44 t_result( *this );

	// perform the Division
	t_result												/=	a_divider;

	//return the result
	return t_result;
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
FORCE_INLINE Matrix44& Matrix44::operator=( const Matrix44& a_other )
{
	for( int j = 0 ; j < 4 ; j ++ )
	{
		for( int i = 0 ; i < 4 ; i ++ )
		{
			M[ j ][ i ]										=	a_other.M[ j ][ i ];
		}
	}

	return *this;
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
FORCE_INLINE Matrix44& Matrix44::operator+=( const Matrix44& a_other )
{

	for( int j = 0 ; j < 4 ; j ++ )
	{
		for( int i = 0 ; i < 4 ; i ++ )
		{
			M[ j ][ i ]										+=	a_other.M[ j ][ i ];
		}
	}

	return *this;
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
FORCE_INLINE Matrix44& Matrix44::operator-=( const Matrix44& a_other )
{
	for( int j = 0 ; j < 4 ; j ++ )
	{
		for( int i = 0 ; i < 4 ; i ++ )
		{
			M[ j ][ i ]										-=	a_other.M[ j ][ i ];
		}
	}

	return *this;
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
FORCE_INLINE Matrix44 Matrix44::operator*( const Matrix44& a_other )const
{
	Matrix44 t_result;

#if ( PLATFORM_CONFIG_MATRIX_ORDER == MATRIX_ORDER_ROW_MAJOR )
//	Multiply( &t_result , a_other , *this );
		Multiply( &t_result , *this , a_other );
#else
	Multiply( &t_result , *this , a_other );
#endif

	return t_result;
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
FORCE_INLINE Matrix44& Matrix44::operator*=( const Matrix44& a_other )
{
#if ( PLATFORM_CONFIG_MATRIX_ORDER == MATRIX_ORDER_ROW_MAJOR )
//	Multiply( this , a_other , *this );
	Multiply( this , *this , a_other );

#else
	Multiply( this , *this , a_other );
#endif

	return *this;
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
FORCE_INLINE Matrix44& Matrix44::operator*=( TFloat32 a_scale )
{
	for( int j = 0 ; j < 4 ; j ++ )
	{
		for( int i = 0 ; i < 4 ; i ++ )
		{
			M[ j ][ i ]										*=	a_scale;
		}
	}
	return *this;
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
FORCE_INLINE Matrix44& Matrix44::operator/=( TFloat32 a_divider )
{
	TFloat32 t_scale										=	1.0f / a_divider;

	for( int j = 0 ; j < 4 ; j ++ )
	{
		for( int i = 0 ; i < 4 ; i ++ )
		{
			M[ j ][ i ]										*=	t_scale;
		}
	}

	return *this;
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
FORCE_INLINE bool Matrix44::operator==(const Matrix44& a_other)const
{
	for( int j = 0 ; j < 4 ; j ++ )
	{
		for( int i = 0 ; i < 4 ; i ++ )
		{
			if( M[ j ][ i ] != a_other.M[ j ][ i ] )
			{
				return false;
			}
		}
	}

	return true;
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
FORCE_INLINE bool Matrix44::operator!=(const Matrix44& a_other)const
{
	return !(*this == a_other);
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
FORCE_INLINE Vector4F Matrix44::TransformVector( const Vector4F& a_vector )const
{
	Vector4F t_result;

	t_result.x												=	( a_vector.x * _m00 ) + ( a_vector.y * _m10 ) + ( a_vector.z * _m20 ) + ( a_vector.w * _m30 );
	t_result.y												=	( a_vector.x * _m01 ) + ( a_vector.y * _m11 ) + ( a_vector.z * _m21 ) + ( a_vector.w * _m31 );
	t_result.z												=	( a_vector.x * _m02 ) + ( a_vector.y * _m12 ) + ( a_vector.z * _m22 ) + ( a_vector.w * _m32 );
	t_result.w												=	( a_vector.x * _m03 ) + ( a_vector.y * _m13 ) + ( a_vector.z * _m23 ) + ( a_vector.w * _m33 );
	return t_result;
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
FORCE_INLINE void Matrix44::Multiply( Matrix44* a_Result , const Matrix44& a_left , const Matrix44& a_right )
{
/*
	//todo use get row
	Vector4F t_result0									=	Mat2.TransformVector( Mat1.Rows[ 0 ] );
	Vector4F t_result1									=	Mat2.TransformVector( Mat1.Rows[ 1 ] );
	Vector4F t_result2									=	Mat2.TransformVector( Mat1.Rows[ 2 ] );
	Vector4F t_result3									=	Mat2.TransformVector( Mat1.Rows[ 3 ] );

	a_Result->SetRow( 0 , t_result0 );
	a_Result->SetRow( 1 , t_result1 );
	a_Result->SetRow( 2 , t_result2 );
	a_Result->SetRow( 3 , t_result3 );
*/


	a_Result->M[ 0 ][ 0 ]	=	( a_left.M[ 0 ][ 0 ] * a_right.M[ 0 ][ 0 ] ) + ( a_left.M[ 0 ][ 1 ] * a_right.M[ 1 ][ 0 ] ) + ( a_left.M[ 0 ][ 2 ] * a_right.M[ 2 ][ 0 ] ) + ( a_left.M[ 0 ][ 3 ] * a_right.M[ 3 ][ 0 ] );
	a_Result->M[ 0 ][ 1 ]	=	( a_left.M[ 0 ][ 0 ] * a_right.M[ 0 ][ 1 ] ) + ( a_left.M[ 0 ][ 1 ] * a_right.M[ 1 ][ 1 ] ) + ( a_left.M[ 0 ][ 2 ] * a_right.M[ 2 ][ 1 ] ) + ( a_left.M[ 0 ][ 3 ] * a_right.M[ 3 ][ 1 ] );
	a_Result->M[ 0 ][ 2 ]	=	( a_left.M[ 0 ][ 0 ] * a_right.M[ 0 ][ 2 ] ) + ( a_left.M[ 0 ][ 1 ] * a_right.M[ 1 ][ 2 ] ) + ( a_left.M[ 0 ][ 2 ] * a_right.M[ 2 ][ 2 ] ) + ( a_left.M[ 0 ][ 3 ] * a_right.M[ 3 ][ 2 ] );
	a_Result->M[ 0 ][ 3 ]	=	( a_left.M[ 0 ][ 0 ] * a_right.M[ 0 ][ 3 ] ) + ( a_left.M[ 0 ][ 1 ] * a_right.M[ 1 ][ 3 ] ) + ( a_left.M[ 0 ][ 2 ] * a_right.M[ 2 ][ 3 ] ) + ( a_left.M[ 0 ][ 3 ] * a_right.M[ 3 ][ 3 ] );

	a_Result->M[ 1 ][ 0 ]	=	( a_left.M[ 1 ][ 0 ] * a_right.M[ 0 ][ 0 ] ) + ( a_left.M[ 1 ][ 1 ] * a_right.M[ 1 ][ 0 ] ) + ( a_left.M[ 1 ][ 2 ] * a_right.M[ 2 ][ 0 ] ) + ( a_left.M[ 1 ][ 3 ] * a_right.M[ 3 ][ 0 ] );
	a_Result->M[ 1 ][ 1 ]	=	( a_left.M[ 1 ][ 0 ] * a_right.M[ 0 ][ 1 ] ) + ( a_left.M[ 1 ][ 1 ] * a_right.M[ 1 ][ 1 ] ) + ( a_left.M[ 1 ][ 2 ] * a_right.M[ 2 ][ 1 ] ) + ( a_left.M[ 1 ][ 3 ] * a_right.M[ 3 ][ 1 ] );
	a_Result->M[ 1 ][ 2 ]	=	( a_left.M[ 1 ][ 0 ] * a_right.M[ 0 ][ 2 ] ) + ( a_left.M[ 1 ][ 1 ] * a_right.M[ 1 ][ 2 ] ) + ( a_left.M[ 1 ][ 2 ] * a_right.M[ 2 ][ 2 ] ) + ( a_left.M[ 1 ][ 3 ] * a_right.M[ 3 ][ 2 ] );
	a_Result->M[ 1 ][ 3 ]	=	( a_left.M[ 1 ][ 0 ] * a_right.M[ 0 ][ 3 ] ) + ( a_left.M[ 1 ][ 1 ] * a_right.M[ 1 ][ 3 ] ) + ( a_left.M[ 1 ][ 2 ] * a_right.M[ 2 ][ 3 ] ) + ( a_left.M[ 1 ][ 3 ] * a_right.M[ 3 ][ 3 ] );

	a_Result->M[ 2 ][ 0 ]	=	( a_left.M[ 2 ][ 0 ] * a_right.M[ 0 ][ 0 ] ) + ( a_left.M[ 2 ][ 1 ] * a_right.M[ 1 ][ 0 ] ) + ( a_left.M[ 2 ][ 2 ] * a_right.M[ 2 ][ 0 ] ) + ( a_left.M[ 2 ][ 3 ] * a_right.M[ 3 ][ 0 ] );
	a_Result->M[ 2 ][ 1 ]	=	( a_left.M[ 2 ][ 0 ] * a_right.M[ 0 ][ 1 ] ) + ( a_left.M[ 2 ][ 1 ] * a_right.M[ 1 ][ 1 ] ) + ( a_left.M[ 2 ][ 2 ] * a_right.M[ 2 ][ 1 ] ) + ( a_left.M[ 2 ][ 3 ] * a_right.M[ 3 ][ 1 ] );
	a_Result->M[ 2 ][ 2 ]	=	( a_left.M[ 2 ][ 0 ] * a_right.M[ 0 ][ 2 ] ) + ( a_left.M[ 2 ][ 1 ] * a_right.M[ 1 ][ 2 ] ) + ( a_left.M[ 2 ][ 2 ] * a_right.M[ 2 ][ 2 ] ) + ( a_left.M[ 2 ][ 3 ] * a_right.M[ 3 ][ 2 ] );
	a_Result->M[ 2 ][ 3 ]	=	( a_left.M[ 2 ][ 0 ] * a_right.M[ 0 ][ 3 ] ) + ( a_left.M[ 2 ][ 1 ] * a_right.M[ 1 ][ 3 ] ) + ( a_left.M[ 2 ][ 2 ] * a_right.M[ 2 ][ 3 ] ) + ( a_left.M[ 2 ][ 3 ] * a_right.M[ 3 ][ 3 ] );


	a_Result->M[ 3 ][ 0 ]	=	( a_left.M[ 3 ][ 0 ] * a_right.M[ 0 ][ 0 ] ) + ( a_left.M[ 3 ][ 1 ] * a_right.M[ 1 ][ 0 ] ) + ( a_left.M[ 3 ][ 2 ] * a_right.M[ 2 ][ 0 ] ) + ( a_left.M[ 3 ][ 3 ] * a_right.M[ 3 ][ 0 ] );
	a_Result->M[ 3 ][ 1 ]	=	( a_left.M[ 3 ][ 0 ] * a_right.M[ 0 ][ 1 ] ) + ( a_left.M[ 3 ][ 1 ] * a_right.M[ 1 ][ 1 ] ) + ( a_left.M[ 3 ][ 2 ] * a_right.M[ 2 ][ 1 ] ) + ( a_left.M[ 3 ][ 3 ] * a_right.M[ 3 ][ 1 ] );
	a_Result->M[ 3 ][ 2 ]	=	( a_left.M[ 3 ][ 0 ] * a_right.M[ 0 ][ 2 ] ) + ( a_left.M[ 3 ][ 1 ] * a_right.M[ 1 ][ 2 ] ) + ( a_left.M[ 3 ][ 2 ] * a_right.M[ 2 ][ 2 ] ) + ( a_left.M[ 3 ][ 3 ] * a_right.M[ 3 ][ 2 ] );
	a_Result->M[ 3 ][ 3 ]	=	( a_left.M[ 3 ][ 0 ] * a_right.M[ 0 ][ 3 ] ) + ( a_left.M[ 3 ][ 1 ] * a_right.M[ 1 ][ 3 ] ) + ( a_left.M[ 3 ][ 2 ] * a_right.M[ 2 ][ 3 ] ) + ( a_left.M[ 3 ][ 3 ] * a_right.M[ 3 ][ 3 ] );

}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
FORCE_INLINE TFloat32 Matrix44::GetValue( TUint32 a_row , TUint32 a_column )
{
#if ( PLATFORM_CONFIG_MATRIX_ORDER == MATRIX_ORDER_ROW_MAJOR )
	return Rows[ a_row ][ a_column ];
#else
	return Columns[ a_column ][ a_row ];
#endif
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
FORCE_INLINE void Matrix44::SetRow( const TUint32& a_index , const Vector4F& a_values )
{
#if ( PLATFORM_CONFIG_MATRIX_ORDER == MATRIX_ORDER_ROW_MAJOR )
	M[a_index][0]										=	a_values.x;
	M[a_index][1]										=	a_values.y;
	M[a_index][2]										=	a_values.z;
	M[a_index][3]										=	a_values.w;
#else
	M[0][a_index]										=	a_values.x;
	M[1][a_index]										=	a_values.y;
	M[2][a_index]										=	a_values.z;
	M[3][a_index]										=	a_values.w;
#endif

}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
FORCE_INLINE void Matrix44::SetColumn( const TUint32& a_index , const Vector4F& a_values )
{
#if ( PLATFORM_CONFIG_MATRIX_ORDER == MATRIX_ORDER_ROW_MAJOR )
	M[0][a_index]										=	a_values.x;
	M[1][a_index]										=	a_values.y;
	M[2][a_index]										=	a_values.z;
	M[3][a_index]										=	a_values.w;
#else
	M[a_index][0]										=	a_values.x;
	M[a_index][1]										=	a_values.y;
	M[a_index][2]										=	a_values.z;
	M[a_index][3]										=	a_values.w;
#endif
}
//-----------------------------------------------------------------------------------------
