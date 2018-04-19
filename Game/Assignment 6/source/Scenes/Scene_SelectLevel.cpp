#include "Scene_SelectLevel.h"

#include "Texture.h"
#include "InputHandler.h"
#include "DrawManager.h"
#include "ScreenResolution.h"
#include "XMLHandler.h"
#include "FontManager.h"
#include "DeltaTime.h"
#include "GameSystemInfo.h"


//===============================================
//	Constructor
//===============================================
Scene_SelectLevel::Scene_SelectLevel(SceneManager* p_Game)
{
	m_pSceneManager = p_Game;
}

//===============================================
//	Destructor
//===============================================
Scene_SelectLevel::~Scene_SelectLevel()
{

}










//===============================================
//	OnLoad
//===============================================
void Scene_SelectLevel::OnLoad()
{
	m_iBackgroundTextureID			= Texture::GetInstance()->LoadTexture("background1.jpg", "BG");
	m_sCurrentlyTypedCharacters		= "";
	m_bInformUserOfError			= false;
	m_bShowTextLine					= true;
	m_fTimerForTextLine				= 0.f;
}


//===============================================
//	OnUnload
//===============================================
void Scene_SelectLevel::OnUnload()
{

}





//===============================================
//	Scene Start
//===============================================
void Scene_SelectLevel::SceneStart()
{
	m_sCurrentlyTypedCharacters		= "";
	m_bInformUserOfError			= false;
}


//===============================================
//	Scene Terminate
//===============================================
void Scene_SelectLevel::SceneTerminate()
{

}









//===============================================
//	Update
//===============================================
void Scene_SelectLevel::Update()
{
	if( !m_bInformUserOfError )
	{
		// Add Character and DeltaTime
		m_sCurrentlyTypedCharacters  += InputHandler::GetInstance()->GetKeyPressedCharacter();
		m_fTimerForTextLine			 += DeltaTime::GetInstance()->GetDeltaTime();

		// Update TextLine
		if( m_fTimerForTextLine >= 0.7f )
		{
			m_bShowTextLine = !m_bShowTextLine;
			m_fTimerForTextLine = 0.f;
		}

		if(InputHandler::GetInstance()->GetKeyState(SDLK_BACKSPACE))
		{
			std::string temp = m_sCurrentlyTypedCharacters;
			m_sCurrentlyTypedCharacters = "";
			for( unsigned int i = 0; i < temp.length() - 1; i++ )
			{
				if(temp.length() == 0) { break; }
				m_sCurrentlyTypedCharacters += temp[i];
			}
		}

		// If Enter was Pressed, then attempt to open XML. If Successful go to character selection
		if( InputHandler::GetInstance()->GetKeyState( SDLK_RETURN ))
		{
			if( XMLHandler::GetInstance()->Get_LevelXMLExists( m_sCurrentlyTypedCharacters ))
			{
				GameSystemInfo::GetInstance()->SetCurrentLevel(m_sCurrentlyTypedCharacters);
				m_pSceneManager->ChangeState(SceneManager::eSELECT_CHARACTER_SCENE);
			}
			else
			{
				m_bInformUserOfError = true;
			}
		}
	}
	else
	{
		if(InputHandler::GetInstance()->GetKeyState(SDLK_SPACE) || InputHandler::GetInstance()->GetKeyState(SDLK_RETURN))
		{
			m_bInformUserOfError = false;
		}
	}
}








//===============================================
//	Draw
//===============================================
void Scene_SelectLevel::Draw()
{
	unsigned int iSWidth  = (unsigned int)ScreenResolution::GetInstance()->GetScreenWidth();
	unsigned int iSHeight = (unsigned int)ScreenResolution::GetInstance()->GetScreenHeight();
	DrawManager::GetInstance()->DrawTexturei(0, 0, iSWidth, iSHeight, m_iBackgroundTextureID, false);

	if( m_bInformUserOfError )
	{
		FontManager::GetInstance()->SetFont_Position( 100, 100 );
		FontManager::GetInstance()->SetFont_Width_Height(20, 20);
		FontManager::GetInstance()->SetFont_Colour( 100, 100, 255 );
		FontManager::GetInstance()->SetFont_Opacity(255);
		FontManager::GetInstance()->PrintFont("Error File Was Not Found!");

		FontManager::GetInstance()->SetFont_Position( 380, 500 );
		FontManager::GetInstance()->SetFont_Colour( 100, 255, 100 );
		FontManager::GetInstance()->PrintFont("OK");
	}
	else
	{
		FontManager::GetInstance()->SetFont_Position( 250, 100 );
		FontManager::GetInstance()->SetFont_Width_Height(20, 20);
		FontManager::GetInstance()->SetFont_Colour( 50, 50, 100 );
		FontManager::GetInstance()->SetFont_Opacity(255);
		FontManager::GetInstance()->PrintFont("Type in the name of the level \\nyou wish to select!");

		FontManager::GetInstance()->SetFont_Position( 100, 500 );
		FontManager::GetInstance()->SetFont_Colour( 150, 200, 255 );
		FontManager::GetInstance()->PrintFont(m_sCurrentlyTypedCharacters);

		if(m_bShowTextLine)
		{
			int XPos = (100 + (m_sCurrentlyTypedCharacters.length() * 20));
			DrawManager::GetInstance()->DrawLine2i(XPos, 500, XPos, 520);
		}
	}
}