#include "RhiShaderReflectionInfos.h"
#include "../../../../Core/CoreIncludes.h"

#ifdef _DEBUG
#include "RhiShaderReflectionInfos.inl"
#endif


//---------------------------------------------------------------------------------------------------------
RhiShaderReflectionInfos::RhiShaderReflectionInfos()
{
	m_constantBufferList									=	nullptr;
	m_constantBufferCount									=	0;
}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
RhiShaderReflectionInfos::~RhiShaderReflectionInfos()
{
	SAFE_DELETE_ARRAY( m_constantBufferList );
}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
void RhiShaderReflectionInfos::Init( TUint32 a_constantBufferCount )
{
	m_constantBufferList									=	new RhiShaderConstantBufferDesc[ a_constantBufferCount ];
	m_constantBufferCount									=	a_constantBufferCount;
}
//---------------------------------------------------------------------------------------------------------
