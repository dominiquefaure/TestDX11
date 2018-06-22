#ifndef __RHI_CONSTANT_BUFFER_DX11_H__
#define __RHI_CONSTANT_BUFFER_DX11_H__

#include <d3d11.h>
#include "BaseBufferDX11.h"

#include "../../RhiEnums.h"
#include "../../../Core/CoreIncludes.h"


class GraphicDeviceDX11;
class GraphicContextDX11;
class RhiShaderParameterDesc;

class ConstantBufferDX11 : public BaseBufferDX11
{
	friend class GraphicDeviceDX11;
	friend class GraphicContextDX11;

public:
	ConstantBufferDX11();
	~ConstantBufferDX11();

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
	void Update( RhiShaderParameterDesc& a_param , const void* a_value );

	/*
	* Commit any updates and set this Constant Buffer as the one to use for the Given Slot
	*/
	void Commit( GraphicContextDX11* a_context , RhiShaderType a_type , TUint32 a_slot );

private:

	virtual void OnInit();

// Fields
private:

	// buffer used to store the data to commit to GPU
	TUint8*	m_cpuBuffer;

	// flag used to know if there is data updates that need to be send to GPU
	TBool	m_isDirty;

};

#endif