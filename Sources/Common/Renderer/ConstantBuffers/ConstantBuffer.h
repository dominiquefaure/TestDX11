#ifndef __RENDERER_CONSTANT_BUFFER_H__
#define __RENDERER_CONSTANT_BUFFER_H__

#include "../../Core/CoreIncludes.h"
#include "../../RHI/Includes.h"

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
	void Init( RhiGraphicDevice* a_device , TUint32 a_size );


	/*
	* Update the part of the Content of this Constant Buffer
	*/
	void Update( TUint32 a_index , TUint32 a_byteCount , const void* a_value );

	/*
	 * Update a parameter
	 * 
	 * @param a_param	Store info about the parameter to update inside the constant buffer
	 * @param a_value	the Value to set
	 */
	void Update( const RhiShaderParameterDesc* a_param , const void* a_value );

	/*
	* Commit any updates made, into the Rhi version
	*/
	void Commit( RhiGraphicContext* a_context , RhiShaderType a_type , TUint32 a_slot );

	/*
	 * Bind the RHI constant Buffer to the context. If any updates have been made, commit them 1st
	 */
	void Bind( RhiGraphicContext* a_context , RhiShaderType a_type , TUint32 a_slot );

private:

	// The Low level API constantBuffer
	RhiConstantBuffer*	m_constantBuffer;

	// Sizeof the Constant Buffer
	TUint32				m_size;

	// buffer used to store the data to commit to GPU
	TUint8*				m_internalBuffer;

	// flag used to know if there is data updates that need to be send to GPU
	TBool				m_isDirty;
};

#endif