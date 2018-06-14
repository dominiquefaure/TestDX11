#ifndef __GAME_APPLICATION_H__
#define __GAME_APPLICATION_H__

#include<Windows.h>

#include "WindowsAppConfig.h"

#include "../Core/CoreIncludes.h"

class WinMainLauncher;

class GameApplication
{
	friend class WinMainLauncher;

public:

	GameApplication();
	virtual ~GameApplication();

	/*
	* Initialize the Game
	*/
	void Init( HWND a_handle );

	/*
	 * Close the Game
	 */
	void Close();

	/*
	 * Called every ticks by the main loop perform all the frame operations
 	 */
	void OnFrame();

// pure Virtual methods to be overrided
protected:

	/*
	 * Called at Application initialization, allow to start loading custom data
	 */
	virtual void OnInit(){}

	/*
	 * Called at Application initialization, allow to start loading custom data
	 */
	virtual void OnClose(){}

	/*
	 * Called every ticks to perform the update operations
	 * 
	 * @a_deltaTime	Time eleapsed since last frame
	 */
	virtual void OnUpdate( TFloat32 a_deltaTime ){}

	/*
	 *  called every ticks to perform the custom draw operations
	 */
	virtual void OnDraw(){}


	virtual void DrawDebugUI(){}

	/*
	 * Allow custom config of the Windows creation
	 */
	virtual void OnSetWindowConfig( WinAppConfig& a_config ){}

	/*
	 * Set the max FPS, if 0 , no limit
	 */
	FORCE_INLINE void SetMaxFPS( TUint32 a_maxFps);

// Methodss
private:

	/*
	 * Configure the Windows Dialog
	 */
	void SetWindowConfig( WinAppConfig& a_config );

	/*
	 * Perform all the Frame Updates
	 */
	void PerformUpdates();

	/*
	 * PErform all the Draw Operations
	 *
	 */
	void PerformDraw();

	/*
	 * Process the Frametime management
	 */
	void ProcessFPS();

protected:

	Timer		m_timer;

	TFloat64	m_lastFrameDuration;

	// number ax of FPS
	TUint32		m_maxFPS;

};

// The inline is included in the Header only if not in debug mode
#ifndef _DEBUG
#include "GameApplication.inl"
#endif


#endif