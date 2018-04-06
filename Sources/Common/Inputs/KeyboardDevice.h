#ifndef __INPUT_KEYBOARD_DEVICE_H__
#define __INPUT_KEYBOARD_DEVICE_H__

#include <vector>

#include "InputMacros.h"

class InputManager;

struct KeyboardKey
{
	//Key State
	InputState	m_state;

	//keyboard ke code
	int			m_keyCode;
};


class KeyboardDevice
{
	friend class InputManager;


public:

	KeyboardDevice();
	~KeyboardDevice();

	/*
	* Get the Key State
	*/
	InputState GetKeyState( KeyboardInputs a_key );

	/*
	* Is the Given Key Pressed. return true while the key is pressed
	*/
	bool IsPressed( KeyboardInputs a_key );

	/*
	* is the Key Just Presssed
	*
	* @return true if it's the 1st tick the key is pressed, else false until it's released then pressed again
	*/
	bool IsJustPressed( KeyboardInputs a_key );

	/*
	* is the Key Just Released
	*
	* @return true if it's the 1st tick after the key is released, else false
	*/
	bool IsJustReleased( KeyboardInputs a_key );


protected:

	/*
	* perform the Init
	*/
	void Init( );

	void InitKey( KeyboardInputs a_key , int a_keyCode );

	/*
	* Update the Key status
	*/
	void Update();

	/*
	* Update the Status of a Key
	*/
	void UpdateKeyStatus( KeyboardKey& a_key );

private:

	// the different Keys supported
	KeyboardKey*	m_keys;


};


#endif