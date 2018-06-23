#ifndef __RHI_SHADER_REFLECTION_INFOS_H__
#define __RHI_SHADER_REFLECTION_INFOS_H__


#include "RhiShaderConstantBufferDesc.h"

/*
 * Class that store all the reflection information's about an RhiShader
 */
class RhiShaderReflectionInfos
{
	
public:

	RhiShaderReflectionInfos();
	~RhiShaderReflectionInfos();



	FORCE_INLINE TUint32 GetConstantBufferCount( )const;

	/*
	 * Runtime access to the ConstantBufferDEsc
	 */
	FORCE_INLINE const RhiShaderConstantBufferDesc* GetConstantBufferDesc( TUint32 a_index )const;

	/*
	 * Access to the ConstantBufferDesc used during setup
	 */
	FORCE_INLINE RhiShaderConstantBufferDesc* GetConstantBufferDesc( TUint32 a_index );

	void Init( TUint32 a_constantBufferCount );

private:

	// number of ConstantBuffer defined in the Shader
	TUint8							m_constantBufferCount;

	// informations for the different constant buffers
	RhiShaderConstantBufferDesc*	m_constantBufferList;

};



// The inline is included in the Header only if not in debug mode
#ifndef _DEBUG
#include "RhiShaderReflectionInfos.inl"
#endif



#endif
