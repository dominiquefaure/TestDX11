#ifndef __FILE_H__
#define __FILE_H__

#include <string>

#include "../CoreMacros.h"


class FileSystem;

/*
* Class used to load a File Content
*/
class FileHandle
{
	friend class FileSystem;

public:
	enum FileMode
	{
		FILE_MODE_READ_TEXT	=	0,
		FILE_MODE_READ_BINARY,
		FILE_MODE_WRITE_TEXT,
		FILE_MODE_WRITE_BINARY,

		FILE_MODE_COUNT
	};

private:

	FORCE_INLINE FileHandle(  );

	/*
	* Open the File, reutrn true if succeed
	*/
	FORCE_INLINE bool Open( const std::string& a_path , FileMode a_mode );

public:

	FORCE_INLINE ~FileHandle();

	/*
	* Close the File
	*/
	FORCE_INLINE void Close();

	/*
	* Get the Size of the File
	*/
	FORCE_INLINE int GetSize();

	/*
	* Read a Byte
	*/
	FORCE_INLINE char ReadChar();

	/*
	* Read a Short
	*/
	FORCE_INLINE short ReadShort();

	/*
	* Read a Int
	*/
	FORCE_INLINE int ReadInt();

	/*
	* Read a Float
	*/
	FORCE_INLINE float ReadFloat();

	/*
	*  Read X bytes and store the result into a buffer
	* return the number of bytes read
	*/
	FORCE_INLINE int Read( char* a_buffer , int a_count );

private:

	std::string	m_fileName;


	bool		m_isOpen;


	FILE*		m_file;


};

// The inline is included in the Header only if not in debug mode
#ifndef _DEBUG
#include "FileHandle.inl"
#endif

#endif