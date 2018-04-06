#ifndef __INPUT_MANAGER_H__
#define __INPUT_MANAGER_H__

#include "../Core/CoreIncludes.h"


class KeyboardDevice;

class InputManager : public Singleton<InputManager>
{
	friend class Singleton<InputManager>;

private:

	InputManager();
	virtual ~InputManager();


public:

	/*
	* Get the Keyboard if there is one
	*/
	KeyboardDevice* GetKeyboard();


	/*
	* Update Input status
	*/
	void Update();

protected:

	/*
	* Allow custom initializations
	*/
	virtual void OnInit();

private:

	KeyboardDevice*	m_keyboard;

};

#endif