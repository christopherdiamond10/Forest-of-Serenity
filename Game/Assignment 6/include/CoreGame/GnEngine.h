#ifndef _GNENGINE_H_
#define _GNENGINE_H_

#include "sdl_opengl.h"
#include "sdl.h"
#include "sdl_image.h"



			
class SceneManager;



class GnEngine
{
//////////////////////////////////////////
public:
//////////////////////////////////////////

	//===============================================
	//			Constructor & Destructor
	//===============================================
	GnEngine( SDL_Joystick *ptr_XboxController );
	~GnEngine();

	//===============================================
	//			Public Functions
	//===============================================
	void OnLoad();
	void OnUnload();

	bool Init();
	void Run();
	void Quit();

	void InitialiseShutdown();


//////////////////////////////////////////
private:
//////////////////////////////////////////

	//===============================================
	//			Private Declarations
	//===============================================
	bool			m_bEngineRunning;

	//===============================================
	//			Private Functions
	//===============================================
	void CheckInput();


	//===============================================
	//			Pointers
	//===============================================
	SceneManager  * m_pSceneManager;
};

#endif