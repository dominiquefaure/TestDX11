#ifndef __CORE_IO_JSON_BOOL_PROPERTY_H__
#define __CORE_IO_JSON_BOOL_PROPERTY_H__

#include "AJSonProperty.h"
#include "../../../Core/Base/BaseDataTypes.h"

class JSonNode;

class JSonBoolProperty : public AJsonProperty
{
	friend class JSonNode;

public:

	JSonBoolProperty();
	virtual ~JSonBoolProperty();

	TBool GetValue( )const;

protected:

	void SetValue( TBool a_value );

	/*
	* Serialize the Property value
	*/
	virtual void SerializeValue( rapidjson::PrettyWriter<rapidjson::StringBuffer> & a_writer );

private:

	TBool	m_value;

};

#endif