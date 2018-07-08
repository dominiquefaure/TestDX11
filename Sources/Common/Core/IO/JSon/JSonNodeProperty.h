#ifndef __CORE_IO_JSON_NODE_PROPERTY_H__
#define __CORE_IO_JSON_NODE_PROPERTY_H__

#include "AJSonProperty.h"
#include "../../../Core/Base/BaseDataTypes.h"

class JSonNodeWriter;


class JSonNodeProperty : public AJsonProperty
{
	friend class JSonNodeWriter;

public:

	JSonNodeProperty();
	virtual ~JSonNodeProperty();

	JSonNodeWriter* GetValue( )const;

	JSonNodeWriter* GetValue( );

protected:

	/*
	* Serialize the Property value
	*/
	virtual void SerializeValue( rapidjson::PrettyWriter<rapidjson::StringBuffer> & a_writer );

private:

	JSonNodeWriter* m_value;

};

#endif