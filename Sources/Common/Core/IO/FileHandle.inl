
#include "FileSystem.h"

char* g_FileOpenModes[ FileHandle::FILE_MODE_COUNT ]
{
	"r",
	"rb",
	"w",
	"wb"
};


//--------------------------------------------------------------------------------
FileHandle::FileHandle( )
{
	m_isOpen												=	false;
}
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
FileHandle::~FileHandle()
{
	Close();
}
//--------------------------------------------------------------------------------

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

//--------------------------------------------------------------------------------
int FileHandle::GetSize()
{
	// check the File is Open
	if( m_isOpen )
	{
		// Save the Current Position
		long t_currPosition									=	ftell( m_file );

		// go to end of file
		if( fseek( m_file, 0, SEEK_END ) != 0 )
		{
			return 0;
		}
		
		// get the Offset == size
		long t_size											=	ftell( m_file );

		// reset the cursor to the previous position
		if( fseek(m_file , t_currPosition , SEEK_SET) != 0 )
		{
			return 0;
		}

		return t_size;
	}

	return 0;
}
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
char FileHandle::ReadChar()
{
	char t_value;

	fread( &t_value, 1, 1, m_file );

	return t_value;

}
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
short FileHandle::ReadShort()
{
	short t_value;
#ifdef BIGENDIAN
	char* tmp = (char*)&t_value;
	fread(&tmp[1], 1, 1, m_file);
	fread(&tmp[0], 1, 1, m_file);

#else  //little Endian
	fread(&t_value, 2, 1, m_file );
#endif

	return t_value;
}
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
int FileHandle::ReadInt()
{
	int t_value = 0;
#ifdef BIGENDIAN
	char* tmp = (char*)&t_value;
	fread(&tmp[3], 1, 1, m_file);
	fread(&tmp[2], 1, 1, m_file);
	fread(&tmp[1], 1, 1, m_file);
	fread(&tmp[0], 1, 1, m_file);

#else
	fread((void*)&t_value, 4, 1, m_file);

#endif
	return t_value;

}
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
float FileHandle::ReadFloat()
{
	float t_value = 0;
#ifdef BIGENDIAN
	char* tmp = (char*)&t_value;

	fread(&tmp[3], 1, 1, m_file);
	fread(&tmp[2], 1, 1, m_file);
	fread(&tmp[1], 1, 1, m_file);
	fread(&tmp[0], 1, 1, m_file);

#else
	fread(&t_value, 4, 1, m_file);

#endif
	return t_value;

}
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
int FileHandle::Read( char* a_buffer , int a_count )
{
	return (int)fread(a_buffer, 1, a_count, m_file );

}
//--------------------------------------------------------------------------------
