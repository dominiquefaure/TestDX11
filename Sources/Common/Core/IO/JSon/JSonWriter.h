#ifndef __CORE_IO_JSON_WRITER_H__
#define __CORE_IO_JSON_WRITER_H__

class JSonNode;

class JSonWriter
{
public:

	JSonWriter();
	~JSonWriter();

	/*
	* Get an empty root ndoe to populate it
	*/
	JSonNode* GetRootNode();

	/*
	* Save the data to a file
	*/
	void Save( const char* a_path );

private:

	JSonNode* m_rootNode;
};

#endif