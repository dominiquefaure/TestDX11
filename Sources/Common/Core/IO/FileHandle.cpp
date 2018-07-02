#include "FileHandle.h"


//In debug configuration, the inline methods need to be include inside a cpp file, to avoid function redefinition errors
#ifdef _DEBUG

#include "../CoreIncludes.h"
#include "FileHandle.inl"

#endif


char* g_FileOpenModes[ FileHandle::FILE_MODE_COUNT ]
{
	"r",
	"rb",
	"w",
	"wb"
};



//--------------------------------------------------------------------------------
bool FileHandle::Open( const std::string& a_path , FileMode a_mode )
{
	// Save the FileName
	m_fileName												=	a_path;


	fopen_s( &m_file , a_path.c_str() , g_FileOpenModes[ a_mode ] );

	// test if fail to open
	if( !m_file )
	{
		return false;	
	}

	// the file is now Open
	m_isOpen												=	true;

	return true;
}
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
void FileHandle::Close()
{
	if( m_isOpen )
	{
		// Close the File
		fclose( m_file );

		// indicate to the File System that the file is now Closed
		FileSystem::GetInstance()->OnFileClosed( this );
		m_isOpen											=	false;
	}
}
//--------------------------------------------------------------------------------
