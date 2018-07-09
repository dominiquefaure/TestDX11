#ifndef __CORE_IO_JSON_NODE_PROPERTY_H__
#define __CORE_IO_JSON_NODE_PROPERTY_H__

#include "AJSonProperty.h"
#include "../../../Core/Base/BaseDataTypes.h"

class JSonNode;


class JSonNodeProperty : public AJsonProperty
{
	friend class JSonNode;

public:

	JSonNodeProperty();
	virtual ~JSonNodeProperty();

	JSonNode* GetValue( )const;

	JSonNode* GetValue( );

protected:

	/*
	* Serialize the Property value
	*/
	virtual void SerializeValue( rapidjson::PrettyWriter<rapidjson::StringBuffer> & a_writer );

private:

	JSonNode* m_value;

};

#endif