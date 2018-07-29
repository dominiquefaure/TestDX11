#ifndef __FILE_SYSTEM_H__
#define __FILE_SYSTEM_H__


#include "../DesignPatterns/Singleton.h"

#include <vector>

#include "../Base/BaseDataTypes.h"

class FileHandle;

class FileSystem : public Singleton<FileSystem>
{
	friend class Singleton<FileSystem>;

	friend class FileHandle;
public:


	/*
	* Open a File in Read mode, and return a pointer
	*/
	FileHandle* OpenRead( const std::string& a_path , bool a_binaryMode = true );

	/*
	* Evaluate if the given file exist
	*/
	TBool Exist( const std::string& a_path );

protected:

	/*
	* Callback called by the FileHandle when closing the File
	*/
	void OnFileClosed( FileHandle* a_file );


};


#endif