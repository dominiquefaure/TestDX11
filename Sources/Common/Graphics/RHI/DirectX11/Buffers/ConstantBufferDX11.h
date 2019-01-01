#ifndef __RHI_CONSTANT_BUFFER_DX11_H__
#define __RHI_CONSTANT_BUFFER_DX11_H__

#include <d3d11.h>
#include "BaseBufferDX11.h"

#include "../../RhiEnums.h"
#include "../../../../Core/CoreIncludes.h"



class GraphicDeviceDX11;
class GraphicContextDX11;

class ConstantBufferDX11 : public BaseBufferDX11
{
	friend class GraphicDeviceDX11;
	friend class GraphicContextDX11;

public:
	ConstantBufferDX11();
	~ConstantBufferDX11();

};

#endif