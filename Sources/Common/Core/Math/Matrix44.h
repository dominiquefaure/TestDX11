#pragma once

#include "../CoreMacros.h"

#include "Maths.h"
#include "Vector3F.h"
#include "Vector4F.h"

struct Matrix44
{

public:

	/*
	* Default constructor , all the values will be set to 0
	*/
	FORCE_INLINE Matrix44();


	/*
	* copy constructor
	*
	* @param a_other	Matrix to copy
	*/
	FORCE_INLINE Matrix44( const Matrix44& a_other );

	/*
	* constructor
	*
	*/
	FORCE_INLINE Matrix44(	TFloat32 m00 , TFloat32 m01 , TFloat32 m02 ,TFloat32 m03 ,
							TFloat32 m10 , TFloat32 m11 , TFloat32 m12 ,TFloat32 m13 ,
							TFloat32 m20 , TFloat32 m21 , TFloat32 m22 ,TFloat32 m23 ,
							TFloat32 m30 , TFloat32 m31 , TFloat32 m32 ,TFloat32 m33 );


	/*
	* Get Cell Value
	*/
	FORCE_INLINE TFloat32 GetValue( TUint32 a_row , TUint32 a_column );

	/*
	* Set the Matrix as Identity
	*/
	FORCE_INLINE void SetIdentity();

	/*
	* Get the Determinant of this Matrix
	*
	* @return The determinant of this Matrix
	*/
	FORCE_INLINE TFloat32 GetDeterminant()const;

	/*
	* Inverse this Matrix
	*/
	FORCE_INLINE void Inverse();

	/*
	* Get the Inverse of this Matrix
	*
	* @return The invere Matrix if the Matrix cvan be inversed, else an Identity Matrix
	*/
	FORCE_INLINE Matrix44 GetInverse()const;


	/*
	* Check if both Matrix are eaual, within some tolerance ratio
	*
	* @param a_other		The Matrix to compare to
	* @param a_tolerance	tolerance allowed
	* @return				true if they are almost the same
	*/
	FORCE_INLINE bool IsEqual( const Matrix44& a_other , TFloat32 a_tolerance = DEFAULT_TOLEARANCE_VALUE );


	/*
	* Transpose this Matrix
	*/
	FORCE_INLINE void Transpose();

	/*
	* Get the Transpose of this Matrix
	*/
	FORCE_INLINE Matrix44 GetTranspose()const;



	////////////
	// Translation Methods
	/////////////

	/*
	* Set this Matrix as a Trnaslation Matrix. all the others components are reset
	*/
	FORCE_INLINE void SetTranslate( const Vector3F& a_translation );

	/*
	* Translate the current Matrix using the given Vector, the translation component are just added to this Matrix
	*
	* @param a_translation	The Translation to apply
	*/
//	FORCE_INLINE void Translate( const Vector3F& a_translation );

	/*
	* Apply a Translation to this Matrix , The translation is done by multiplication (M = M*T )
	*
	* @param a_translation	The Translation to apply
	*/
//	FORCE_INLINE void PostTranslate( const Vector3F& a_translation );


	////////////
	// Scale Methods
	/////////////

	/*
	* Set this Matrix a s Scale Matrix. all the others components are reset
	*/
	FORCE_INLINE void SetScale( const Vector3F& a_scale );

	/*
	* Set this Matrix a s Scale Matrix. all the others components are reset
	*/
	FORCE_INLINE void SetScale( TFloat32 a_scale );

	/*
	* Set this Matrix a s Scale Matrix. all the others components are reset
	*/
	FORCE_INLINE void SetScale( TFloat32 a_scaleX , TFloat32 a_scaleY , TFloat32 a_scaleZ );


	////////////
	// Rotation Methods
	/////////////

	/*
	* Set this Matrix as a Rotation Matrix around X axis. all others components are reset
	*/
	FORCE_INLINE void SetRotateX( TFloat32 a_angle );

	/*
	* Set this Matrix as a Rotation Matrix around Y axis. all others components are reset
	*/
	FORCE_INLINE void SetRotateY( TFloat32 a_angle );

	/*
	* Set this Matrix as a Rotation Matrix around Z axis. all others components are reset
	*/
	FORCE_INLINE void SetRotateZ( TFloat32 a_angle );

	/*
	* Set this MAtrix as a Matrix that perform rotation around the 3 axis
	*
	* @param a_pitch		Angle around the X Axis
	* @param a_yaw			Angle around the Y Axis
	* @param a_roll			Angle around the Z Axis
	*/
	FORCE_INLINE void SetRotateZYX( TFloat32 a_pitch , TFloat32 a_yaw , TFloat32 a_roll );

	/*
	* Set this MAtrix as a Matrix that perform rotation around the 3 axis
	*
	* @param a_rotation		Vector that store the angles around the 3 Axis
	*/
	FORCE_INLINE void SetRotateZYX( const Vector3F& a_rotation );


	/*
	* Set this Matrix as a Rotation Matrix around an arbitrary axis. all others components are reset
	*/
//	FORCE_INLINE void SetRotate( const Vector3F&a_axi , float a_angle );

/*
	* Set the MAtrix in order it perform Translation Scale and Rotation, all in once
	*
	* @param a_translation	The Translation to Perform
	* @param a_scale		The Scale to apply
	* @param a_rot			The Rotation to Perform
	*/
	FORCE_INLINE void SetTransScaleRot( Vector3F a_translation , Vector3F a_scale , Vector3F a_rot );



	///////////////////////////
	// Projection Matrix
	//////////////////////////

	/*
	* Set this Matrix as an Orthogonal Projection Matrix
	*
	* @param a_left		X value representing the Min X value seen on screen
	* @param a_right	X value representing the Max X value seen on screen
	* @param a_top		Y value representing the Top of the Screen
	* @param a_bottom	Y value representing the Bottom of the Screen
	* @param a_near		Z value representing the closest element that can be seen
	* @param a_far		Z value representing the fartest element that can be seen
	*/
	FORCE_INLINE void SetOrthoProjection( TFloat32 a_left , TFloat32 a_right , TFloat32 a_top , TFloat32 a_bottom , TFloat32 a_near , TFloat32 a_far );

	/*
	* Set thi Matrix as a Perspective Projection Matrix
	*
	* @param a_fow			the Fow to use , in Radian
	* @param a_aspectRatio	The Aspect Ratio to apply between width and height
	* @param a_zNear		Min Z visible
	* @param a_zFar			Max Z visible
	*/
	FORCE_INLINE void SetPerpectiveProjection( TFloat32 a_fov , TFloat32 a_aspectRatio , TFloat32 a_zNear , TFloat32 a_zFar );

	/*
	* Set thi Matrix as a View Matrix
	*
	* @param a_position		Position in Space of the Origin ( position of the Camera )
	* @param a_target		Target we are looking at
	* @param a_up			That is the up
	*/
	FORCE_INLINE void SetLookAt( const Vector3F& a_Position , const Vector3F& a_target , const Vector3F& a_up );


	///////////////////////////
	// Vector transformation
	//////////////////////////

	/*
	* Apply this matrix to the given Vector
	*/
	FORCE_INLINE Vector4F TransformVector( const Vector4F& a_vector )const;

//Operators
public:


	/*
	* Get the result of Adding a Matrix with this one
	*
	* @param a_other	The matrix to Add with.
	* @return			The result of Addition.
	*/
	FORCE_INLINE Matrix44 operator+( const Matrix44& a_other )const;

	/*
	* Get the result of Substracting a Matrix from this one
	*
	* @param a_other	The matrix to Substract.
	* @return			The result Matrix.
	*/
	FORCE_INLINE Matrix44 operator-( const Matrix44& a_other )const;

	/*
	* Get the result of Multiplying a Matrix with this one
	*
	* @param a_other	The matrix to multiply with.
	* @return			The result of multiplication.
	*/
	FORCE_INLINE Matrix44 operator*( const Matrix44& a_other )const;

	/*
	* Uniform Scale this Matrix
	*
	* @param a_scale	Scale to apply
	* @return			The result Matrix
	*/
	FORCE_INLINE Matrix44 operator*( TFloat32 a_scale )const;

	/*
	* Uniform Divide this Matrix
	*
	* @param a_scale	Divide to apply
	* @return			The result Matrix
	*/
	FORCE_INLINE Matrix44 operator/( TFloat32 a_divider )const;


	/*
	* Copy the different components of the other amtrix
	*/
	FORCE_INLINE Matrix44& operator=( const Matrix44& a_other );


	/*
	* Add a Matrix to this one
	*
	* @param a_other	The other matrix
	* @return			referecne to this Matrix
	*/
	FORCE_INLINE Matrix44& operator+=( const Matrix44& a_other );

	/*
	* Substract a Matrix to this one
	*
	* @param a_other	The other matrix
	* @return			referecne to this Matrix
	*/
	FORCE_INLINE Matrix44& operator-=( const Matrix44& a_other );

	/*
	* Multiply this matrix with another one
	*
	* @param a_other	The matrix to multiply with.
	* @return			referecne to this Matrix
	*/
	FORCE_INLINE Matrix44& operator*=( const Matrix44& a_other );

	/*
	* Scale this MAtrix
	*
	* @param a_scale	The scale to apply
	* @return			referecne to this Matrix
	*/
	FORCE_INLINE Matrix44& operator*=( TFloat32 a_scale );

	/*
	* Divide this MAtrix
	*
	* @param a_divider	The divider to apply
	* @return			referecne to this Matrix
	*/
	FORCE_INLINE Matrix44& operator/=( TFloat32 a_divider );


	/*
	* Check if this MAtrix component is the same as teh other one
	*
	* @param a_other	The Matrix to compare to
	* @return			true if all the components are the same
	*/
	FORCE_INLINE bool operator==(const Matrix44& a_other)const;

	/*
	* Check if this MAtrix component are not the same as teh other one
	*
	* @param a_other	The Matrix to compare to
	* @return			true if at least one of the components is not the same
	*/
	FORCE_INLINE bool operator!=(const Matrix44& a_other)const;


private:

	/*
	* Set all the Elements of the Matrix
	*/
	FORCE_INLINE void SetValues(	TFloat32 m00 , TFloat32 m01 , TFloat32 m02 , TFloat32 m03 ,
									TFloat32 m10 , TFloat32 m11 , TFloat32 m12 , TFloat32 m13 ,
									TFloat32 m20 , TFloat32 m21 , TFloat32 m22 , TFloat32 m23 ,
									TFloat32 m30 , TFloat32 m31 , TFloat32 m32 , TFloat32 m33 );

	/*
	* Set a Row values
	*/
	FORCE_INLINE void SetRow( const TUint32& a_index , const Vector4F& a_values );

	/*
	* Set a Column values
	*/
	FORCE_INLINE void SetColumn( const TUint32& a_index , const Vector4F& a_values );



	FORCE_INLINE static void Multiply( Matrix44* a_Result , const Matrix44& a_m1 , const Matrix44& a_m2 );


//Field
public:

	union
	{
		TFloat32 M[4][4];

		struct
		{
			TFloat32 _m00 , _m01 , _m02 , _m03;
			TFloat32 _m10 , _m11 , _m12 , _m13;
			TFloat32 _m20 , _m21 , _m22 , _m23;
			TFloat32 _m30 , _m31 , _m32 , _m33;
		};

#if ( PLATFORM_CONFIG_MATRIX_ORDER == MATRIX_ORDER_ROW_MAJOR )
		Vector4F	Rows[ 4 ];
#else
		Vector4F	Columns[4];
#endif
	};

public:
	static bool s_useCompose;
};

// The inline is included in the Header only if not in debug mode
#ifndef _DEBUG
#include "Matrix44.inl"
#endif
