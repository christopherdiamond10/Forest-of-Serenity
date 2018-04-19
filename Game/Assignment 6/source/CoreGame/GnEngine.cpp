//\====================================================================================
//\ Authors: Jamie.Stewart, Christopher Diamond
//\ About  : GnEngine.cpp - 
//\
//\ The main class for the whole game, in this cpp file we create and delete our 
//\ singleton classes, process scenes, seed random and Update the Game in general.
//\====================================================================================
#include "GnEngine.h"

// Singleton Classes
#include "AnimationHandler.h"
#include "ScreenResolution.h"
#include "Texture.h"
#include "DrawManager.h"
#include "AudioManager.h"
#include "FontManager.h"
#include "InputHandler.h"
#include "DeltaTime.h"
#include "XMLHandler.h"
#include "GameSystemInfo.h"

#include "SceneManager.h"
#include <time.h>

//===================================
//		Constructor
//===================================
GnEngine::GnEngine( SDL_Joystick *ptr_XboxController )
{
	// Create Singleton Classes
	new Texture();
	new DrawManager();
	new AnimationHandler();
	new AudioManager();
	new FontManager();
	new InputHandler( this, ptr_XboxController );
	new DeltaTime();
	new XMLHandler();
	new GameSystemInfo();
	
	// Assign Pointers
	m_pSceneManager = new SceneManager( this );

}



//===================================
//		Deconstructor
//===================================
GnEngine::~GnEngine()
{
	delete m_pSceneManager;
	delete AnimationHandler::GetInstance();
	delete Texture::GetInstance();
	delete DrawManager::GetInstance();
	delete AudioManager::GetInstance();
	delete FontManager::GetInstance();
	delete InputHandler::GetInstance();
	delete DeltaTime::GetInstance();
	delete XMLHandler::GetInstance();
	delete GameSystemInfo::GetInstance();
}





//===================================
//		OnLoad
//===================================
void GnEngine::OnLoad()
{
	// Seed Random with TIme
	srand((unsigned int)time(0));

	AudioManager::GetInstance()		->OnLoad();
	AudioManager::GetInstance()		->SetRootAudioFolderLocation("./bin/Audio/");

	ScreenResolution::GetInstance() ->OnLoad();
	AnimationHandler::GetInstance() ->OnLoad();
	Texture::GetInstance()			->OnLoad();
	DrawManager::GetInstance()		->OnLoad();
	FontManager::GetInstance()		->OnLoad();
	InputHandler::GetInstance()		->OnLoad();
	DeltaTime::GetInstance()		->OnLoad();
	XMLHandler::GetInstance()		->OnLoad();
	GameSystemInfo::GetInstance()	->OnLoad();
	m_pSceneManager					->OnLoad();
}


//===================================
//		OnUnload
//===================================
void GnEngine::OnUnload()
{
	m_pSceneManager					->OnUnload();
	ScreenResolution::GetInstance() ->OnUnload();
	AnimationHandler::GetInstance() ->OnUnload();
	Texture::GetInstance()			->OnUnload();
	DrawManager::GetInstance()		->OnUnload();
	AudioManager::GetInstance()		->OnUnload();
	FontManager::GetInstance()		->OnUnload();
	InputHandler::GetInstance()		->OnUnload();
	DeltaTime::GetInstance()		->OnUnload();
	XMLHandler::GetInstance()		->OnUnload();
	GameSystemInfo::GetInstance()	->OnUnload();
}








//===================================
//		Initialise
//===================================
bool GnEngine::Init()
{
	// Set up the Clear colour and the Draw Colour for OpenGL
	glClearColor( 0.f, 0.f, 0.f, 0.f);
	glColor4f( 0.f, 0.f, 0.f, 1.f );


	// Get Screen Size
	float* fScreenDimensions = ScreenResolution::GetInstance()->GetScreenSize();
	float fScreenWidth = fScreenDimensions[0];
	float fScreenHeight = fScreenDimensions[1];
	delete[] fScreenDimensions;

	//As we're going to draw in 2D set up an orthographic projection.
	//This type of projection has no perspective.  This projection is set up so that one pixel on the screen is one unit in 
	//world co-ordinates
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho( 0.f, fScreenWidth, fScreenHeight, 0.f, 0.f, 1.f );

	//Enable 2D textures
	glEnable(GL_TEXTURE_2D);

	//Enable Blending although to be fair blending is slow.
	glEnable(GL_BLEND);
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	
	glEnable(GL_DEPTH);
	glDepthFunc(GL_LEQUAL);

	m_bEngineRunning = true;

	// Delta Time Updates before entering Game Loop
	DeltaTime::GetInstance()->UpdateDeltaTime();


	return m_bEngineRunning;
}





//===================================
//		Run
//===================================
void GnEngine::Run()
{

	unsigned int iTime = (unsigned int)time(0);							// Only Seed Random If Time has Changed
	m_pSceneManager->ChangeState(SceneManager::eSPLASH_SCREEN_STATE);	// Change Scene to SplashScreen



	// Game Loop
	while( m_bEngineRunning )
	{
		//==========================================
		//		Clear Screen
		//==========================================
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		




		//==========================================
		//		Update
		//==========================================
		if( iTime != (unsigned int)time(0) )
		{
			iTime = (unsigned int)time(0);
			srand(iTime);
		}


		DeltaTime::GetInstance()	->UpdateDeltaTime();
		InputHandler::GetInstance()	->Update();
		AudioManager::GetInstance()	->Update();

		this						->CheckInput();
		m_pSceneManager				->ProcessScene();

		//==========================================
		//		Draw
		//==========================================
		SDL_GL_SwapBuffers();





		//==========================================
		//	   Delay ~ Let the processor breathe
		//==========================================
		SDL_Delay(1);
	}
}





//===================================
//		Check Input
//===================================
void GnEngine::CheckInput()
{
	if( !m_pSceneManager->Get_IsCurrentScene(SceneManager::eSELECT_LEVEL_SCENE) )
	{
		if( InputHandler::GetInstance()->GetKeyState( SDLK_p ) )
		{
			AudioManager::GetInstance()->SetMute( "SE" );
		}
		else if( InputHandler::GetInstance()->GetKeyState( SDLK_o ) )
		{
			AudioManager::GetInstance()->SetMute( "BGS" );
		}
		else if( InputHandler::GetInstance()->GetKeyState( SDLK_i ) )
		{
			AudioManager::GetInstance()->SetMute( "BGM" );
		}
	}
}




//===================================
//		Quit
//===================================
void GnEngine::Quit()
{

}

//===================================
//		Initialise ShutDown
//===================================
void GnEngine::InitialiseShutdown()
{
	m_bEngineRunning = false;
}

