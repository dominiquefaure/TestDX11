#ifndef __RENDERER_MATERIAL_PARAMETER_VECTOR3_H__
#define __RENDERER_MATERIAL_PARAMETER_VECTOR3_H__

#include "Core/CoreIncludes.h"
#include "TMatrerialParameter.h"

class MaterialParameterVector3 : public TMaterialParameter<Vector3F>
{
public:

	MaterialParameterVector3()
	{
		SetType( BaseMaterialParameter::VECTOR_PARAMETER );
	}

	~MaterialParameterVector3()
	{
	}
};

#endif