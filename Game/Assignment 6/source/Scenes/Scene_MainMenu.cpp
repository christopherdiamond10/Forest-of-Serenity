//\====================================================================================
//\ Author: Declan.Corcoran
//\ About : Scene_MainMenu.cpp - creates the menu source file that defines what the menu 
//\								 does, it's object locations and it's functions.
//\====================================================================================

#include "Scene_MainMenu.h"

#include "ScreenResolution.h"
#include "FontManager.h"
#include "AudioManager.h"
#include "InputHandler.h"

#include "Texture.h"
#include "DrawManager.h"

#include "sdl.h"
#include "sdl_opengl.h"


Scene_TitleMenu::Scene_TitleMenu(SceneManager* p_Game)
{
	m_pSceneManager = p_Game;
}

Scene_TitleMenu::~Scene_TitleMenu()
{

}

void Scene_TitleMenu::OnLoad()
{
	m_bSwitchtoNextScene	= false;
	m_bClickable            = false;
	m_bHighLightSelection	= false;

	

	m_iMenu_Selection		= ePlayGame;


	AudioManager::GetInstance()->ImportAudio( "023 - 223 Groovy BGM (Loop, 160kbps).mp3", "MainMenu_Theme", "BGM" );
	 
	m_iBackgroundTextureID = Texture::GetInstance()->LoadTexture( "background2.jpg", "BG" );
	
	

	//////////////////////////////////////////////////
	//			Set the Mouse Box Coordinates		//
	/*----------------------------------------------*/
	//This is used to check which box the mouse is	//
	//Currently hovering over and selecting it		//
	//////////////////////////////////////////////////

	Play_Game_AreaBox.x = 50;
	Play_Game_AreaBox.y = 30;
	Play_Game_AreaBox.w = 300;
	Play_Game_AreaBox.h = 100;

	SelectLevel_AreaBox.x = 50;
	SelectLevel_AreaBox.y = 130;
	SelectLevel_AreaBox.w = 300;
	SelectLevel_AreaBox.h = 100;

	HighScores_AreaBox.x = 50;
	HighScores_AreaBox.y = 230;
	HighScores_AreaBox.w = 300;
	HighScores_AreaBox.h = 100;

	Options_AreaBox.x = 50;
	Options_AreaBox.y = 330;
	Options_AreaBox.w = 300;
	Options_AreaBox.h = 100;

	Instructions_AreaBox.x = 50;
	Instructions_AreaBox.y = 430;
	Instructions_AreaBox.w = 360;
	Instructions_AreaBox.h = 100;

	Credits_AreaBox.x = 50;
	Credits_AreaBox.y = 530;
	Credits_AreaBox.w = 300;
	Credits_AreaBox.h = 100;

	Quit_AreaBox.x = 50;
	Quit_AreaBox.y = 630;
	Quit_AreaBox.w = 300;
	Quit_AreaBox.h = 100;

}


void Scene_TitleMenu::OnUnload()
{

}

void Scene_TitleMenu::SceneStart()
{
	AudioManager::GetInstance()->PlaySound( "MainMenu_Theme" );
}

void Scene_TitleMenu::SceneTerminate()
{

}

void Scene_TitleMenu::Update()
{
	Input();
	UpdateMenuSelectionBounds();
	UpdateMouseSelection();
	UpdateStateChanges();
}

//========================================
//		Update Menu Selection
//========================================
void Scene_TitleMenu::UpdateMenuSelectionBounds()
{
	if (m_iMenu_Selection < ePlayGame)
	{
		m_iMenu_Selection = eQuit;
	}
	else if (m_iMenu_Selection > eQuit)
	{
		m_iMenu_Selection = ePlayGame;
	}
}


//========================================
//		Update State Changes
//========================================
void Scene_TitleMenu::UpdateStateChanges()
{
	if ( m_bSwitchtoNextScene )
	{
		m_bSwitchtoNextScene = false; // Set back to false in case the player exits back to the menu.


		switch(m_iMenu_Selection)
		{
		case ePlayGame:
			{
				m_pSceneManager->ChangeState(SceneManager::eSELECT_CHARACTER_SCENE);
				break;
			}
		case eSelectLevel:
			{
				m_pSceneManager->ChangeState(SceneManager::eSELECT_LEVEL_SCENE);
				break;
			}
		case eHighScores:
			{
				m_pSceneManager->ChangeState(SceneManager::eHIGH_SCORE_STATE);
				break;
			}
		case eOptions:
			{
				m_pSceneManager->ChangeState(SceneManager::eOPTIONS_STATE);
				break;
			}
		case eInstructions:
			{
				m_pSceneManager->ChangeState(SceneManager::eINSTRUCTIONS_STATE);
				break;
			}
		case eCredits:
			{
				m_pSceneManager->ChangeState(SceneManager::eCREDITS_STATE);
				break;
			}
		case eQuit:
			{
				m_pSceneManager->Shutdown();
				break;
			}
		default:
			{
				break;
			} 
		}
	}
}








//========================================
//				Draw
//========================================
void Scene_TitleMenu::Draw()
{
	
	int iWidth  = (int)ScreenResolution::GetInstance()->GetScreenWidth();
	int iHeight = (int)ScreenResolution::GetInstance()->GetScreenHeight();

	DrawManager::GetInstance()->DrawTexturei( 0, 0, iWidth, iHeight, m_iBackgroundTextureID, false ); 
	

	FontManager::GetInstance()->SetFont_Width_Height( 30.f, 20.f );
	FontManager::GetInstance()->SetFont_Opacity( 200 );




	if( m_iMenu_Selection == ePlayGame )	 { FontManager::GetInstance()->SetFont_Colour( 30,  90, 290  ); }		else { FontManager::GetInstance()->SetFont_Colour(255, 255, 0); }	
	Draw_PlayGame_Selection();													  

	if( m_iMenu_Selection == eSelectLevel )  { FontManager::GetInstance()->SetFont_Colour( 30,  90, 290  ); }		else { FontManager::GetInstance()->SetFont_Colour(255, 255, 0); }	
	Draw_SelectLevel_Selection();	

	if( m_iMenu_Selection == eInstructions ) { FontManager::GetInstance()->SetFont_Colour( 30,  90, 290  ); }		else { FontManager::GetInstance()->SetFont_Colour(255, 255, 0); }	
	Draw_Instructions_Selection();												   

	if( m_iMenu_Selection == eHighScores )	 { FontManager::GetInstance()->SetFont_Colour( 30,  90, 290  ); }		else { FontManager::GetInstance()->SetFont_Colour(255, 255, 0); }	
	Draw_HighScore_Selection();													  

	if( m_iMenu_Selection == eOptions )		 { FontManager::GetInstance()->SetFont_Colour( 30,  90, 290  ); }		else { FontManager::GetInstance()->SetFont_Colour(255, 255, 0); }	
	Draw_Options_Selection();													  

	if( m_iMenu_Selection == eCredits )		 { FontManager::GetInstance()->SetFont_Colour( 30,  90, 290  ); }		else { FontManager::GetInstance()->SetFont_Colour(255, 255, 0); }	
	Draw_Credits_Selection();													 
																				 
	if( m_iMenu_Selection == eQuit )		 { FontManager::GetInstance()->SetFont_Colour( 30,  90, 290  ); }		else { FontManager::GetInstance()->SetFont_Colour(255, 255, 0); }	
	Draw_Exit_Selection();														    

	//DrawRect();
}





//////////////////////////////////////
//			Play Game				//
//////////////////////////////////////
void Scene_TitleMenu::Draw_PlayGame_Selection()
{
	FontManager::GetInstance()->SetFont_Position( 50, 50 );
	FontManager::GetInstance()->PrintFont( "Play Game" );
}

void Scene_TitleMenu::Draw_SelectLevel_Selection()
{
	FontManager::GetInstance()->SetFont_Position( 50, 150 );
	FontManager::GetInstance()->PrintFont( "Select Level" );
}
//////////////////////////////////////
//			HighScores				//
//////////////////////////////////////
void Scene_TitleMenu::Draw_HighScore_Selection()
{
	FontManager::GetInstance()->SetFont_Position( 50, 250 );
	FontManager::GetInstance()->PrintFont( "HighScores" );
}

//////////////////////////////////////
//			Options					//
//////////////////////////////////////
void Scene_TitleMenu::Draw_Options_Selection()
{
	FontManager::GetInstance()->SetFont_Position( 50, 350 );
	FontManager::GetInstance()->PrintFont( "Options" );
}

//////////////////////////////////////
//			Instructions			//
//////////////////////////////////////
void Scene_TitleMenu::Draw_Instructions_Selection()
{
	FontManager::GetInstance()->SetFont_Position( 50, 450 );
	FontManager::GetInstance()->PrintFont( "Instructions" );
}

//////////////////////////////////////
//			Credits					//
//////////////////////////////////////
void Scene_TitleMenu::Draw_Credits_Selection()
{
	FontManager::GetInstance()->SetFont_Position( 50, 550 );
	FontManager::GetInstance()->PrintFont( "Credits" );
}

//////////////////////////////////////
//			Exit					//
//////////////////////////////////////
void Scene_TitleMenu::Draw_Exit_Selection()
{
	FontManager::GetInstance()->SetFont_Position( 50, 650 );
	FontManager::GetInstance()->PrintFont( "Exit" );
}





//========================================
//		Draw Rect
//========================================
void Scene_TitleMenu::DrawRect()
{
#if _DEBUG // If DEBUGGING

	DrawManager::GetInstance()->DrawQuad2i( Play_Game_AreaBox.x,	Play_Game_AreaBox.y,	Play_Game_AreaBox.w,	Play_Game_AreaBox.h,	 100,	false);
	DrawManager::GetInstance()->DrawQuad2i( SelectLevel_AreaBox.x,	SelectLevel_AreaBox.y,	SelectLevel_AreaBox.w,  SelectLevel_AreaBox.h,	 100,	false);
	DrawManager::GetInstance()->DrawQuad2i( HighScores_AreaBox.x,	HighScores_AreaBox.y,	HighScores_AreaBox.w,	HighScores_AreaBox.h,	 100,	false);
	DrawManager::GetInstance()->DrawQuad2i( Options_AreaBox.x,		Options_AreaBox.y,		Options_AreaBox.w,		Options_AreaBox.h,		 100,	false);
	DrawManager::GetInstance()->DrawQuad2i( Instructions_AreaBox.x,	Instructions_AreaBox.y, Instructions_AreaBox.w, Instructions_AreaBox.h,  100,	false);
	DrawManager::GetInstance()->DrawQuad2i( Credits_AreaBox.x,		Credits_AreaBox.y,		Credits_AreaBox.w,		Credits_AreaBox.h,		 100,	false);
	DrawManager::GetInstance()->DrawQuad2i( Quit_AreaBox.x,			Quit_AreaBox.y,			Quit_AreaBox.w,			Quit_AreaBox.h,			 100,	false);

#endif
}












//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//												-=
//					Input						=-
//												-= 
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void Scene_TitleMenu::Input()
{
	InputHandler* pInputHandler = InputHandler::GetInstance();


	//There are a whole bunch of else ifs in this function because there is no point 
	//in checking other keys if we've already determined that one has been pressed.


	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	//												-=
	//					Action Keys					=-
	//												-= 
	//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=



	//================================================
	//					ESC / ESCAPE
	//================================================
	// If The Escape Key is Pressed and it hasn't already been pressed
	//
	if( pInputHandler->GetKeyState( SDLK_ESCAPE ) || ( pInputHandler->GetJoyButtonState( JoystickButtons_LB )) )
	{
		m_pSceneManager->Shutdown();
	}




	//================================================
	//	  Enter / Return / MouseClick / A / Start
	//================================================
	if(	( pInputHandler->GetKeyState( SDLK_RETURN ))					   ||		// OR
		( pInputHandler->GetJoyButtonState( JoystickButtons_A ))		   ||		// OR
		( InputHandler::GetInstance()->GetMouseClicked() && m_bClickable ) ||
		( pInputHandler->GetJoyButtonState( JoystickButtons_Start )        ))
	{
		m_bSwitchtoNextScene = true;
	}
	//================================================




	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	//												-=
	//				Directional Keys				=-
	//												-=
	//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=


	//================================================
	//					UP
	//================================================
	else if( pInputHandler->GetKeyState( SDLK_UP ) ||  pInputHandler->GetJoyDPadState( JoystickDPadButtons_Up ))
	{
		m_iMenu_Selection--;
	}
	//================================================






	//================================================
	//					DOWN
	//================================================
	else if( pInputHandler->GetKeyState( SDLK_DOWN ) || ( pInputHandler->GetJoyDPadState( JoystickDPadButtons_Down )))
	{
		m_iMenu_Selection++;
	}
	//================================================








	//================================================
	//					LEFT
	//================================================
	else if( pInputHandler->GetKeyState( SDLK_LEFT ) || pInputHandler->GetJoyDPadState( JoystickDPadButtons_Left ))
	{
		// Do Shit
	}





	//================================================
	//					RIGHT
	//================================================
	else if( pInputHandler->GetKeyState( SDLK_RIGHT ) || pInputHandler->GetJoyDPadState( JoystickDPadButtons_Right ))
	{
		// Do Shit
	}




	//================================================
	//				No Key is Pressed
	//================================================
	else //No Key is pressed
	{
		
	}
	//================================================
}



//========================================
//		Update Mouse Selection
//========================================
void Scene_TitleMenu::UpdateMouseSelection()
{
	InputHandler* pInput = InputHandler::GetInstance();
	//////////////////////////////////////
	//	Play Game	Mouse Selection		//
	//////////////////////////////////////
	if((pInput->GetMousePos().X >= Play_Game_AreaBox.x && pInput->GetMousePos().X <= (Play_Game_AreaBox.x + Play_Game_AreaBox.w))  && 
	   (pInput->GetMousePos().Y >= Play_Game_AreaBox.y && pInput->GetMousePos().Y <= (Play_Game_AreaBox.y + Play_Game_AreaBox.h)   ))
	{
		m_bClickable = true;
		m_iMenu_Selection = ePlayGame;
	}

	//////////////////////////////////////
	//	Select Level  Mouse Selection	//
	//////////////////////////////////////
	else if((pInput->GetMousePos().X >= SelectLevel_AreaBox.x && pInput->GetMousePos().X <= (SelectLevel_AreaBox.x + SelectLevel_AreaBox.w))  && 
	        (pInput->GetMousePos().Y >= SelectLevel_AreaBox.y && pInput->GetMousePos().Y <= (SelectLevel_AreaBox.y + SelectLevel_AreaBox.h)   ))
	{
		m_bClickable = true;
		m_iMenu_Selection = eSelectLevel;
	}

	//////////////////////////////////////
	//	HighScores	Mouse Selection		//
	//////////////////////////////////////
	else if((pInput->GetMousePos().X >= HighScores_AreaBox.x && pInput->GetMousePos().X <= (HighScores_AreaBox.x + HighScores_AreaBox.w))  && 
	        (pInput->GetMousePos().Y >= HighScores_AreaBox.y && pInput->GetMousePos().Y <= (HighScores_AreaBox.y + HighScores_AreaBox.h)   ))
	{
		m_bClickable = true;
		m_iMenu_Selection = eHighScores;
	}

	//////////////////////////////////////
	//	Options	Mouse Selection			//
	//////////////////////////////////////
	else if((pInput->GetMousePos().X >= Options_AreaBox.x && pInput->GetMousePos().X <= (Options_AreaBox.x + Options_AreaBox.w))  && 
	        (pInput->GetMousePos().Y >= Options_AreaBox.y && pInput->GetMousePos().Y <= (Options_AreaBox.y + Options_AreaBox.h)   ))
	{
		m_bClickable = true;
		m_iMenu_Selection = eOptions;
	}

	//////////////////////////////////////
	//	Instructions	Mouse Selection	//
	//////////////////////////////////////
	else if((pInput->GetMousePos().X >= Instructions_AreaBox.x && pInput->GetMousePos().X <= (Instructions_AreaBox.x + Instructions_AreaBox.w))  && 
	        (pInput->GetMousePos().Y >= Instructions_AreaBox.y && pInput->GetMousePos().Y <= (Instructions_AreaBox.y + Instructions_AreaBox.h)   ))
	{
		m_bClickable = true;
		m_iMenu_Selection = eInstructions;
	}

	//////////////////////////////////////
	//	Credits	Mouse Selection			//
	//////////////////////////////////////
	else if((pInput->GetMousePos().X >= Credits_AreaBox.x && pInput->GetMousePos().X <= (Credits_AreaBox.x + Credits_AreaBox.w))  && 
	        (pInput->GetMousePos().Y >= Credits_AreaBox.y && pInput->GetMousePos().Y <= (Credits_AreaBox.y + Credits_AreaBox.h)   ))
	{
		m_bClickable = true;
		m_iMenu_Selection = eCredits;
	}

	//////////////////////////////////////
	//	Exit	Mouse Selection			//
	//////////////////////////////////////
	else if((pInput->GetMousePos().X >= Quit_AreaBox.x && pInput->GetMousePos().X <= (Quit_AreaBox.x + Quit_AreaBox.w))  && 
	        (pInput->GetMousePos().Y >= Quit_AreaBox.y && pInput->GetMousePos().Y <= (Quit_AreaBox.y + Quit_AreaBox.h)   ))
	{
		m_bClickable = true;
		m_iMenu_Selection = eQuit;
	}

	else
	{
		m_bClickable = false;
	}
}