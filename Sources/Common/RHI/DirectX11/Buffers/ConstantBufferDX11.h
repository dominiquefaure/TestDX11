#ifndef __RHI_CONSTANT_BUFFER_DX11_H__
#define __RHI_CONSTANT_BUFFER_DX11_H__

#include <d3d11.h>
#include "BaseBufferDX11.h"

#include "../../RhiEnums.h"
#include "../../../Core/CoreIncludes.h"


class GraphicDeviceDX11;
class GraphicContextDX11;

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
	void Update( TUint8* a_datas , TUint32 a_offset , TUint32 a_size );

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