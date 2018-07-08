#include "JSonWriter.h"

#include "JSonNodeWriter.h"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"

#include <fstream>

#include "../../CoreMacros.h"

using namespace rapidjson;


//-------------------------------------------------------------------------------------------------
JSonWriter::JSonWriter()
{
	m_rootNode												=	new JSonNodeWriter();
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
JSonWriter::~JSonWriter()
{
	SAFE_DELETE( m_rootNode );
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
JSonNodeWriter* JSonWriter::GetRootNode()
{
	return m_rootNode;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void JSonWriter::Save( const char* a_path )
{

	StringBuffer s;
	PrettyWriter<StringBuffer> writer(s);

	m_rootNode->Serialize( writer );

	std::ofstream t_outputStream(a_path );
	t_outputStream << s.GetString();

	if (!t_outputStream.good())
	{
		throw std::runtime_error("Can't write the JSON string to the file!");
	}

}
//-------------------------------------------------------------------------------------------------
