#ifndef __RENDERER_CONSTANT_BUFFER_H__
#define __RENDERER_CONSTANT_BUFFER_H__

#include "Core/CoreIncludes.h"
#include "RHI/Includes.h"

/*
 * Platform independant version of ConstantBuffer
 * use an internal array to perform shadow copy
 */
class ConstantBuffer
{
public:

	ConstantBuffer( );
	~ConstantBuffer();

	/*
	 * Create the Contant Buffer
	 */
	void Init( RhiGraphicDevice* a_device , TUint32 a_registerCount );


	Vector4F GetValue( TUint32 a_registerIndex )const;


	TFloat32 GetValue( TUint32 a_registerIndex , TUint32 a_componentIndex )const;

	/*
	* Update a Full register
	*/
	void SetValue( TUint32 a_registerIndex , const Vector4F& a_value );

	/*
	* Update a register components
	*/
	void SetValue( TUint32 a_registerIndex , const Vector3F& a_value );

	/*
	* Update a register component
	*/
	void SetValue( TUint32 a_registerIndex , TUint32 a_componentIndex , const TFloat32& a_value );

	/*
	* Commit any updates made, into the Rhi version
	*/
	void Commit( RhiGraphicContext* a_context );

	/*
	 * Bind the RHI constant Buffer to the context. If any updates have been made, commit them 1st
	 */
	void Bind( RhiGraphicContext* a_context , RhiShaderType a_type , TUint32 a_slot );

private:

	// The Low level API constantBuffer
	RhiConstantBuffer*		m_constantBuffer;

	// Sizeof the Constant Buffer
	TUint32					m_size;

	// buffer used to store the data to commit to GPU
	TFixedArray<Vector4F>	m_internalBuffer;

	// flag used to know if there is data updates that need to be send to GPU
	TBool					m_isDirty;
};

#endif