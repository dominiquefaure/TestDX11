#ifndef __RENDERER_MATERIAL_PARAMETER_DESCRIPTOR_COLLECTION_H__
#define __RENDERER_MATERIAL_PARAMETER_DESCRIPTOR_COLLECTION_H__

#include "Core/CoreIncludes.h"
#include "Graphics/RHI/Includes.h"

#include "MaterialParameterDescriptor.h"

/*
* Store a Collection of Material Parameter Descriptor and the Name of the ConstantBuffer they belong to
*/
class MaterialParameterDescriptorCollection
{
public:

	MaterialParameterDescriptorCollection();
	~MaterialParameterDescriptorCollection();


	/*
	* Get the Collection name
	*/
	FORCE_INLINE const std::string& GetName()const;

	/*
	* Does this collection describe global parameters
	*/
	FORCE_INLINE TBool IsGlobalCB()const;

	/*
	* Get the number of Parameters defined
	*/
	FORCE_INLINE TUint32 GetParameterCount()const;

	/*
	* Get the Descriptor present at the Given Index
	*/
	FORCE_INLINE const MaterialParameterDescriptor* GetParameterAt( TUint32 a_index )const;


	/*
	* Get the max Register index used by the different parameters
	*/
	TUint32 GetMaxRegisterIndex();

	/*
	* Get the Index of the Parameter with the given name , -1 if not found 
	*/
	TSint32 IndexOf( const std::string& a_name )const;

	/*
	* get the parameter descriptor with the given name
	*
	*/
	const MaterialParameterDescriptor* GetDescriptor( const std::string& a_name )const;

	/*
	* Init the Descriptor
	*/
	void Init( const std::string& a_name );

	/*
	* Add a Parameter . return it's index
	*/
	TUint32 AddParameter(  const std::string& a_name , MaterialParameterDescriptor::ParameterType a_type , TUint16 a_registerIndex , TUint16 a_compomentIndex );




private:

	// Name of the CB associated
	std::string									m_name;

	// is it the Global CB
	TBool										m_isglobal;

	// List of Parameters
	std::vector<MaterialParameterDescriptor*>	m_paramList;

};


// The inline is included in the Header only if not in debug mode
#ifndef _DEBUG
#include "MaterialParameterDescriptor.inl"
#endif

#endif
