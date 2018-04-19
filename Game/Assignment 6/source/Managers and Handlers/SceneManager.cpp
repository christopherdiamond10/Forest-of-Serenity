#include "SceneManager.h"


#include "ScreenResolution.h"
#include "FontManager.h"
#include "AudioManager.h"

#include "GnEngine.h"
#include "InputHandler.h"

#include "Scene_PlayGame.h"
#include "Scene_SplashScreen.h"
#include "Scene_MainMenu.h"
#include "Scene_SelectCharacter.h"
#include "Scene_SelectLevel.h"


//===============================================
//	Constructor
//===============================================
SceneManager::SceneManager(GnEngine* p_GnEngine)
{
	// Assign the Pointers
	m_pOwningGame = p_GnEngine;

	m_apSceneArray.resize(eTOTAL_STATES, NULL);
	for( int i = 0; i < eTOTAL_STATES; i++ )
	{
		m_apSceneArray[i] = CreateScene( (eSTATE_TYPES)i );
	}
		
}



//===============================================
//	Destructor
//===============================================
SceneManager::~SceneManager()
{	
	for( int i = 0; i < eTOTAL_STATES; i++ )
	{
		if( Get_DoesSceneExist( (eSTATE_TYPES)i ))
			delete m_apSceneArray[i];
	}
	m_apSceneArray.clear();
}



//===============================================
//	OnLoad
//===============================================
void SceneManager::OnLoad()
{			
	m_eCurrentState					= eSPLASH_SCREEN_STATE;
	m_ePreviousState				= eSPLASH_SCREEN_STATE;


	for( int i = 0; i < eTOTAL_STATES; i++ )
	{
		if( Get_DoesSceneExist( (eSTATE_TYPES)i ))
			m_apSceneArray[i]->OnLoad();
	}
}

//===============================================
//	OnUnload
//===============================================
void SceneManager::OnUnload()
{						
	for( int i = 0; i < eTOTAL_STATES; i++ )
	{
		if( Get_DoesSceneExist( (eSTATE_TYPES)i ))
			m_apSceneArray[i]->OnUnload();
	}
} 




//===============================================
//	Change State
//===============================================
void SceneManager::ChangeState( eSTATE_TYPES eType )
{
	if( Get_DoesSceneExist(eType) )
	{
		m_ePreviousState			= m_eCurrentState;
		m_eCurrentState				= eType;

		GetScene(m_ePreviousState)	->SceneTerminate();
		GetScene()					->SceneStart();
	}
}





//===============================================
//	Get Current Scene
//===============================================
Scene_Base* SceneManager::GetScene()
{
	return m_apSceneArray[m_eCurrentState];
}

Scene_Base* SceneManager::GetScene(eSTATE_TYPES eType)
{
	return (eType >= 0 && eType < eTOTAL_STATES) ? m_apSceneArray[eType] : nullptr;
}

bool SceneManager::Get_IsCurrentScene( eSTATE_TYPES Scene )
{
	return (m_eCurrentState == Scene);
}

bool SceneManager::Get_DoesSceneExist( eSTATE_TYPES Scene )
{
	return ((unsigned int)Scene < m_apSceneArray.size()) && (m_apSceneArray[Scene] != nullptr);
}



//===============================================
//	Process Scene
//===============================================
void SceneManager::ProcessScene()
{
	ProcessInput();
	GetScene()->Update();
	GetScene()->Draw();
}

	 

//===============================================
//	ShutDown
//===============================================
void SceneManager::Shutdown()
{
	m_pOwningGame->InitialiseShutdown();
}



//===============================================
//	Fix Camera
//===============================================
void SceneManager::FixCamera()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef( 0, 0, 0.f );
}



//===============================================
//	Process Input
//===============================================
void SceneManager::ProcessInput()
{
	if( InputHandler::GetInstance()->GetKeyState( SDLK_ESCAPE ) || InputHandler::GetInstance()->GetJoyButtonState( JoystickButtons_LB ) )
	{
		// If Escape is Pressed And We're not in the menu, then return to the menu
		if( m_eCurrentState != eTITLEMENU_STATE )
		{
			ChangeState( eTITLEMENU_STATE );
			FixCamera();
		}

		// Otherwise if we are in Scene_Menu, then Exit.
		else
		{
			Shutdown();
		}
	}	
}



//===============================================
//	Create Scene
//===============================================
Scene_Base* SceneManager::CreateScene(eSTATE_TYPES eType)
{
	switch(eType)
	{
	case eSPLASH_SCREEN_STATE:		return new Scene_SplashScreen(this); 
	case eTITLEMENU_STATE:			return new Scene_TitleMenu(this);
	case ePLAY_GAME_STATE:			return new PlayGameState(this);
	case eSELECT_CHARACTER_SCENE:	return new Scene_SelectCharacter(this);
	case eSELECT_LEVEL_SCENE:		return new Scene_SelectLevel(this);
	//case eHIGH_SCORE_STATE:		return new Scene_HighScores(this);
	//case eINSTRUCTIONS_STATE:		return new Scene_Options(this);
	//case eOPTIONS_STATE:			return new Scene_Options(this);
	//case eCREDITS_STATE:			return new Scene_Credits(this);
	default:						return nullptr;
	}
}