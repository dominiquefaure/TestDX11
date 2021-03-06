#include "FileSystem.h"
#include "FileHandle.h"

#include <windows.h>


//-------------------------------------------------------------------------------
FileHandle* FileSystem::OpenRead( const std::string& a_path, bool a_binaryMode )
{
	// Create the Handle
	FileHandle* t_handle								=	new FileHandle( );

	if( a_binaryMode )
	{
		// Try to open the File in Read mode
		t_handle->Open( a_path , FileHandle::FILE_MODE_READ_BINARY );
	}
	else
	{
		// Try to open the File in Read mode
		t_handle->Open( a_path , FileHandle::FILE_MODE_READ_TEXT );
	}

	if( !t_handle->m_isOpen )
	{
		delete t_handle;
		return NULL;
	}

	return t_handle;

}
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
void FileSystem::OnFileClosed( FileHandle* a_file )
{
}
//-------------------------------------------------------------------------------

