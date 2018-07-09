#include "JsonReader.h"

#include "../../../Core/CoreMacros.h"

#include "JSonNodeWriter.h"

#include "../FileSystem.h"
#include "../FileHandle.h"

#include "rapidjson/document.h"

using namespace rapidjson;

//-------------------------------------------------------------------------------------------------
JSonReader::JSonReader()
{
	m_rootNode												=	nullptr;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
JSonReader::~JSonReader()
{
	SAFE_DELETE( m_rootNode );
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
const JSonNodeWriter* JSonReader::GetRootNode()
{
	return m_rootNode;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void JSonReader::Load( const std::string& a_filePath )
{
	// Load the File content
	FileHandle* t_handle									=	FileSystem::GetInstance()->OpenRead( a_filePath );

	int t_size												=	t_handle->GetSize();
	char* t_buffer											=	new char[ t_size ];

	int t_readCount											=	t_handle->Read( t_buffer , t_size );

	t_handle->Close();

	// Parse the loaded content and generate a JSon document
	Document t_jsonDocument;
	t_jsonDocument.Parse( t_buffer , t_readCount );

	// generate our runtime hierarchy
	m_rootNode												=	new JSonNodeWriter();
	m_rootNode->Parse( t_jsonDocument );
}
//-------------------------------------------------------------------------------------------------
