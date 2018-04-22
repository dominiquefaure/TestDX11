#include "JsonDocument.h"

#include <iostream>
#include <ostream>
#include <fstream>
#include <vector>

#include "../FileSystem.h"
#include "../FileHandle.h"


//--------------------------------------------------------------------------------------
JsonDocument::JsonDocument()
{
}
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
JsonDocument::~JsonDocument()
{
}
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
void JsonDocument::Load( const std::string& a_filePath )
{
	// Load the File content
	FileHandle* t_handle									=	FileSystem::GetInstance()->OpenRead( a_filePath );

	int t_size												=	t_handle->GetSize();
	char* t_buffer											=	new char[ t_size ];

	int t_readCount											=	t_handle->Read( t_buffer , t_size );

	t_handle->Close();

	m_jsonDocument.Parse( t_buffer , t_readCount );

//		Value t_rootNode										=	 m_jsonDocument.GetObject();
//		m_rootNode.SetNode( t_rootNode );
		
	m_rootNode.SetNode( &m_jsonDocument );

	// free the Temp buffer
	delete[] t_buffer;
}
//--------------------------------------------------------------------------------------

