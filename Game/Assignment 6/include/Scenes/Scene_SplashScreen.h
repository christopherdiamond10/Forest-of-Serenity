//\====================================================================================
//\ Author: Declan.Corcoran
//\ About : Scene_SplashScreen.h - Creates the class structure for the SplashScreenState.							
//\====================================================================================
#ifndef _SPLASH_STATE_H_
#define _SPLASH_STATE_H_

#include "sdl_opengl.h"	
#include "sdl.h"		
#include "sdl_image.h"
#include "Scene_Base.h"



class Scene_SplashScreen : public Scene_Base
{
//////////////////////////////////////////
public:
//////////////////////////////////////////

	//===============================================
	//			Constructor & Destructor
	//===============================================
	Scene_SplashScreen( SceneManager* p_Game );
	~Scene_SplashScreen();


	//===============================================
	//			Public Functions
	//===============================================
	void OnLoad();
	void OnUnload();

	void SceneStart();	
	void SceneTerminate();

	void Update();
	void Draw();


//////////////////////////////////////////
private:
//////////////////////////////////////////

	//===============================================
	//			Private Functions
	//===============================================
	void ScreenScroll();


	//===============================================
	//			Public Declarations
	//===============================================
	unsigned int	m_iBackgroundTextureID;

	float			m_fFrameWaiting;
	float			m_fWaitTimeAmount;

	Vector2         m_v2BackGroundPos;
	Vector2         m_v2BackGroundSize;


	//===============================================
	//			Pointers
	//===============================================
	SceneManager	* m_pSceneManager;


};


#endif