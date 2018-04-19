//\====================================================================================
//\ Author: Declan.Corcoran
//\ About : SplashScreenState.cpp - 
//\
//\ Creates the SplashScreenState source file. This cpp defines the Splash Screen that 
//\ is to be used just before the game takes you into the menu state.
//\
//\ This cpp file defines the waiting period until the transition occurs
//\====================================================================================
#include "Scene_SplashScreen.h"

#include "AudioManager.h"
#include "DeltaTime.h"
#include "DrawManager.h"
#include "FontManager.h"
#include "InputHandler.h"
#include "Texture.h"
#include "ScreenResolution.h"
#include "Texture.h"
#include "Weather.h"


#include <string>



Scene_SplashScreen::Scene_SplashScreen(SceneManager* p_Scene)
{
	m_pSceneManager = p_Scene;
}

Scene_SplashScreen::~Scene_SplashScreen()
{
	
}

void Scene_SplashScreen::OnLoad()
{
	m_v2BackGroundPos = Vector2(0,0);
	m_v2BackGroundSize  = Vector2( 4096, 768.f);

	m_fFrameWaiting	= 0;
	m_fWaitTimeAmount = 7.4f; // Seconds

	m_iBackgroundTextureID = Texture::GetInstance()->LoadTexture( "instruct.JPG", "BackGround" );
}

void Scene_SplashScreen::OnUnload()
{

}

void Scene_SplashScreen::SceneStart()
{
	AudioManager::GetInstance()->PlaySound( "MainMenu_Theme" );
}

void Scene_SplashScreen::SceneTerminate()
{

}

void Scene_SplashScreen::Update()
{
	ScreenScroll(); 

	m_fFrameWaiting += DeltaTime::GetInstance()->GetDeltaTime();




	InputHandler* pInput = InputHandler::GetInstance();

	bool bScene_Changing_Key_Was_Pressed = ( pInput->GetMouseClicked()						|| 
											 pInput->GetKeyState( SDLK_SPACE )				|| pInput->GetKeyState( SDLK_RETURN )					||
											 pInput->GetJoyButtonState( JoystickButtons_A ) || pInput->GetJoyButtonState( JoystickButtons_Start )	);

	

	if( (m_fFrameWaiting >= m_fWaitTimeAmount) || bScene_Changing_Key_Was_Pressed )
	{
		m_pSceneManager->ChangeState( SceneManager::eTITLEMENU_STATE );
	}
}

void Scene_SplashScreen::Draw()
{
	DrawManager::GetInstance()->DrawTexturef( m_v2BackGroundPos.X, m_v2BackGroundPos.Y, m_v2BackGroundSize.X, m_v2BackGroundSize.Y, m_iBackgroundTextureID, false );

	if( (m_v2BackGroundPos.X + m_v2BackGroundSize.X) < ScreenResolution::GetInstance()->GetScreenWidth() )
	{
		DrawManager::GetInstance()->DrawTexturef( (m_v2BackGroundPos.X + m_v2BackGroundSize.X), m_v2BackGroundPos.Y, m_v2BackGroundSize.X, m_v2BackGroundSize.Y, m_iBackgroundTextureID, false );
	}

	

	// Makes it Blink
	if( m_fFrameWaiting < 2.7f || m_fFrameWaiting > 3.6f)
	{				
		FontManager::GetInstance()->SetFont_Width_Height( 40, 40 );	
		FontManager::GetInstance()->SetFont_Colour( 225,237,207 );		
		FontManager::GetInstance()->SetFont_Opacity( 200 );			
		FontManager::GetInstance()->SetFont_Position( 130, 50 );		
		FontManager::GetInstance()->PrintFont( "Forest Of Serenity");
	}
}

void Scene_SplashScreen::ScreenScroll()
{
	m_v2BackGroundPos.X -= 150.0f * DeltaTime::GetInstance()->GetDeltaTime();
}
