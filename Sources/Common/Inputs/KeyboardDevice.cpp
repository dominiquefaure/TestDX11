#include "KeyboardDevice.h"

#include "../Core/CoreMacros.h"

#include <Windows.h>

//---------------------------------------------------------------------------------------------------
KeyboardDevice::KeyboardDevice()
{
	m_keys													=	NULL;
}
//---------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------
KeyboardDevice::~KeyboardDevice()
{
	SAFE_DELETE_ARRAY( m_keys );
}
//---------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------
InputState KeyboardDevice::GetKeyState( KeyboardInputs a_key )
{
	return m_keys[ a_key ].m_state;
}
//---------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------
bool KeyboardDevice::IsPressed( KeyboardInputs a_key )
{
	// Get the Key State
	InputState t_state										=	GetKeyState( a_key );

	return ( ( t_state == INPUT_STATE_JUST_PRESSED ) || ( t_state == INPUT_STATE_PRESSED ) );
}
//---------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------
bool KeyboardDevice::IsJustPressed( KeyboardInputs a_key )
{
	// Get the Key State
	InputState t_state										=	GetKeyState( a_key );

	return ( t_state == INPUT_STATE_JUST_PRESSED );
}
//---------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------
bool KeyboardDevice::IsJustReleased( KeyboardInputs a_key )
{
	// Get the Key State
	InputState t_state										=	GetKeyState( a_key );

	return ( t_state == INPUT_STATE_JUST_RELEASED );
}
//---------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------
void KeyboardDevice::Init( )
{
	m_keys													=	new KeyboardKey[ KEY_COUNT ];

	InitKey( KEY_UP , VK_UP );
	InitKey( KEY_DOWN , VK_DOWN );
	InitKey( KEY_LEFT , VK_LEFT );
	InitKey( KEY_RIGHT , VK_RIGHT );
	InitKey( KEY_SPACE , VK_SPACE );

	InitKey( KEY_HOME , VK_HOME );
	InitKey( KEY_END , VK_END );

	InitKey( KEY_A , 0x41 );
	InitKey( KEY_D , 0x44 );
	InitKey( KEY_S , 0x53 );
	InitKey( KEY_W , 0x57 );
}
//---------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------
void KeyboardDevice::InitKey( KeyboardInputs a_key , int a_keyCode )
{
	KeyboardKey* t_key										=	&m_keys[ a_key ];

	t_key->m_state											=	INPUT_STATE_RELEASED;
	t_key->m_keyCode										=	a_keyCode;
}
//---------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------
void KeyboardDevice::Update()
{
	// update the Status of each ley
	for( int i = 0 ; i < KEY_COUNT ; i ++ )
	{
		UpdateKeyStatus( m_keys[ i ] );
	}
}
//---------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------
void KeyboardDevice::UpdateKeyStatus( KeyboardKey& a_key )
{
	// if the Key is Pressed
	if( GetAsyncKeyState( a_key.m_keyCode ) )
	{
		if( a_key.m_state >= INPUT_STATE_JUST_PRESSED )
		{
			a_key.m_state									=	INPUT_STATE_PRESSED;
		}
		else
		{
			a_key.m_state									=	INPUT_STATE_JUST_PRESSED;
		}
	}
	else
	{
		if( a_key.m_state >= INPUT_STATE_JUST_PRESSED )
		{
			a_key.m_state									=	INPUT_STATE_JUST_RELEASED;
		}
		else
		{
			a_key.m_state									=	INPUT_STATE_JUST_RELEASED;
		}
	}
}
//---------------------------------------------------------------------------------------------------
