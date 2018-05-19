#ifndef __SINGLETON_H__
#define __SINGLETON_H__

#include "../CoreMacros.h"

template <typename T> 
class Singleton
{
public:

	//------------------------------------------------------------
	static inline void CreateInstance()
	{
		//Todo : Add Assert

		s_instance										=	new T();

		s_instance->OnInit();
	}
	//------------------------------------------------------------

	//------------------------------------------------------------
	static inline void DestroyInstance()
	{
		SAFE_DELETE( s_instance );
	}
	//------------------------------------------------------------

	//------------------------------------------------------------
	static inline T* GetInstance()
	{
		return s_instance;
	}
	//------------------------------------------------------------

protected:

	//------------------------------------------------------------
	/*
	* Allow custom initializations
	*/
	virtual void OnInit()
	{
	}
	//------------------------------------------------------------

protected:

	Singleton(){}
	virtual ~Singleton(){}

private:
	static T* s_instance;
};

template<typename T> T* Singleton<T>::s_instance	=	nullptr;


#endif