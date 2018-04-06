#ifndef __FILE_SYSTEM_H__
#define __FILE_SYSTEM_H__


#include "../DesignPatterns/Singleton.h"

#include <vector>

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


protected:

	/*
	* Callback called by the FileHandle when closing the File
	*/
	void OnFileClosed( FileHandle* a_file );


};


#endif