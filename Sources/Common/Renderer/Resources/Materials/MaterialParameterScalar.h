#ifndef __RENDERER_BASE_SCALAR_MATERIAL_PARAMETER_H__
#define __RENDERER_BASE_SCALAR_MATERIAL_PARAMETER_H__

#include "Core/CoreIncludes.h"
#include "TMatrerialParameter.h"

class MaterialParameterScalar : public TMaterialParameter<TUint32>
{
public:

	MaterialParameterScalar()
	{
		SetType( BaseMaterialParameter::SCALAR_PARAMETER );
	}

	~MaterialParameterScalar()
	{
	}
};

#endif