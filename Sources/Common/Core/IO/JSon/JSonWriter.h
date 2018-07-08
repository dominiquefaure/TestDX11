#ifndef __CORE_IO_JSON_WRITER_H__
#define __CORE_IO_JSON_WRITER_H__

class JSonNodeWriter;

class JSonWriter
{
public:

	JSonWriter();
	~JSonWriter();

	/*
	* Get an empty root ndoe to populate it
	*/
	JSonNodeWriter* GetRootNode();

	/*
	* Save the data to a file
	*/
	void Save( const char* a_path );

private:

	JSonNodeWriter* m_rootNode;
};

#endif