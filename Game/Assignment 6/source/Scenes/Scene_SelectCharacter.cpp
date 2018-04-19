#include "Scene_SelectCharacter.h"

#include "AnimatedSprite.h"
#include "DeltaTime.h"
#include "FontManager.h"
#include "InputHandler.h"
#include "ScreenResolution.h"
#include "GameSystemInfo.h"

#include "Texture.h"
#include "DrawManager.h"

#include "sdl_opengl.h"
#include <string>





//===============================================
//	Constructor
//===============================================
Scene_SelectCharacter::Scene_SelectCharacter( SceneManager* pSceneManager )
	:	CONST_M_F_TIMEUNTILTRANSITION	( 8.f )
{
	m_pSceneManager			= pSceneManager;

	
	m_pRitaAnimatedSprite	= new AnimatedSprite( "Rita_Sprite.png",  "Sprite" );
	m_pEmilyAnimatedSprite	= new AnimatedSprite( "Emily_Sprite.png", "Sprite" );
	m_pNinoAnimatedSprite	= new AnimatedSprite( "Nino_Sprite.png",  "Sprite" );
	m_bClickable            = false; 
}


//===============================================
//	Destructor
//===============================================
Scene_SelectCharacter::~Scene_SelectCharacter()
{	
	delete m_pRitaAnimatedSprite;	
	delete m_pEmilyAnimatedSprite;	
	delete m_pNinoAnimatedSprite;	
}








//===============================================
//	OnLoad
//===============================================
void Scene_SelectCharacter::OnLoad()
{							
	m_pRitaAnimatedSprite	->OnLoad();
	m_pEmilyAnimatedSprite	->OnLoad();
	m_pNinoAnimatedSprite	->OnLoad();

	///////////////////////////////////

	SetupRitaBackgroundTextures();
	SetupEmilyBackgroundTextures();
	SetupNinoBackgroundTextures();
	
	SetupRitaAnimatedSprite();
	SetupEmilyAnimatedSprite();
	SetupNinoAnimatedSprite();

	SetupClassVariables();
	SetupCharacterInfo();
}



//===============================================
//	OnUnload
//===============================================
void Scene_SelectCharacter::OnUnload()
{							
	m_pRitaAnimatedSprite	->OnUnload();
	m_pEmilyAnimatedSprite	->OnUnload();
	m_pNinoAnimatedSprite	->OnUnload();
}









//===============================================
//	Setup Class Variables
//===============================================
void Scene_SelectCharacter::SetupClassVariables()
{
	m_fCurrentTime				= 0.f;
	m_fCurrentAnimationTime		= 0.f;

	m_iCurrentHighlighted		= eRitaSelected;
	m_iPreviousHighlighted		= eNinoSelected;

	m_fPreviousTextureOpacity	= 0.f;
	m_fCurrentTextureOpacity	= 100.f;

	std::list<CharacterTextureInfo>::iterator iter = m_lRitaBackTextureInfoList.begin();
	m_iCurrentTextureID			= iter->ID;
	m_iPreviousTextureID		= m_iCurrentTextureID;

	
	m_v2CurrentTextureSize		= Vector2( 0, 0 );
	m_v2PreviousTextureSize		= m_v2CurrentTextureSize;

	m_v2AnimatedSpritePosiiton	= Vector2( 460.f, 160.f ); 
	m_v2AnimatedSpriteSize		= Vector2( 32.f, 32.f );
}




//===============================================
//	Setup Character Info
//===============================================
void Scene_SelectCharacter::SetupCharacterInfo()
{
	std::list<std::string>  TempStringList;
	
	// Rita
	m_RitaCharacterInfo.Name = "Rita";

			
	m_RitaCharacterInfo.TextureID = Texture::GetInstance()->LoadTexture( "Rita4.png", "Background" );
		m_RitaCharacterInfo.TextureSize = Vector2( 444.f, 768.f );

			TempStringList.push_back( "Flames" );
			TempStringList.push_back( "Burst Fire" );
			TempStringList.push_back( "Combust" );
			TempStringList.push_back( "Inferno" );
			TempStringList.push_back( "Meteor Herd" );
		m_RitaCharacterInfo.ScreenMagicAttacks = TempStringList;

			TempStringList.clear();
			TempStringList.push_back( "Flame" );
			TempStringList.push_back( "Erupt" );
			TempStringList.push_back( "Burst" );
		m_RitaCharacterInfo.IndividualMagicAttacks = TempStringList;

			TempStringList.clear();
			TempStringList.push_back( "Speed Increase" );
			TempStringList.push_back( "Health Increase" );
		m_RitaCharacterInfo.PowerUpMagic = TempStringList;

			TempStringList.clear();
			TempStringList.push_back( "Speed Decrease" );
			TempStringList.push_back( "Health Decrease" );
		m_RitaCharacterInfo.PowerDownMagic = TempStringList;

			m_RitaCharacterInfo.BackWindowColour[0] = 169; // Red
			m_RitaCharacterInfo.BackWindowColour[1] = 44;  // Green
			m_RitaCharacterInfo.BackWindowColour[2] = 44;  // Blue
			m_RitaCharacterInfo.BackWindowColour[3] = 127; // Opacity

			m_RitaCharacterInfo.CharacterNameFontColour[0] = 255;
			m_RitaCharacterInfo.CharacterNameFontColour[1] = 244;
			m_RitaCharacterInfo.CharacterNameFontColour[2] = 248;

			m_RitaCharacterInfo.LabelFontColour[0] = 255;
			m_RitaCharacterInfo.LabelFontColour[1] = 242;
			m_RitaCharacterInfo.LabelFontColour[2] = 0;

			m_RitaCharacterInfo.NormalFontColour[0] = 0;
			m_RitaCharacterInfo.NormalFontColour[1] = 242;
			m_RitaCharacterInfo.NormalFontColour[2] = 255;








	// Emily
	m_EmilyCharacterInfo.Name = "Emily";

			
		m_EmilyCharacterInfo.TextureID = Texture::GetInstance()->LoadTexture( "Emily3.png", "Background" );
		m_EmilyCharacterInfo.TextureSize = Vector2( 543.f, 768.f );

			TempStringList.clear();
			TempStringList.push_back( "Stone Grave" );
			TempStringList.push_back( "Furious Earth" );
		m_EmilyCharacterInfo.ScreenMagicAttacks = TempStringList;

			TempStringList.clear();
			TempStringList.push_back( "Rock Throw" );
		m_EmilyCharacterInfo.IndividualMagicAttacks = TempStringList;

			TempStringList.clear();
		m_EmilyCharacterInfo.PowerUpMagic = m_RitaCharacterInfo.PowerUpMagic;

		m_EmilyCharacterInfo.PowerDownMagic = m_RitaCharacterInfo.PowerDownMagic;

			m_EmilyCharacterInfo.BackWindowColour[0] = 166;  // Red
			m_EmilyCharacterInfo.BackWindowColour[1] = 128;  // Green
			m_EmilyCharacterInfo.BackWindowColour[2] = 53;   // Blue
			m_EmilyCharacterInfo.BackWindowColour[3] = 127;  // Opacity

			m_EmilyCharacterInfo.CharacterNameFontColour[0] = 12;
			m_EmilyCharacterInfo.CharacterNameFontColour[1] = 255;
			m_EmilyCharacterInfo.CharacterNameFontColour[2] = 255;

			m_EmilyCharacterInfo.LabelFontColour[0] = 250;
			m_EmilyCharacterInfo.LabelFontColour[1] = 255;
			m_EmilyCharacterInfo.LabelFontColour[2] = 0;

			m_EmilyCharacterInfo.NormalFontColour[0] = 89;
			m_EmilyCharacterInfo.NormalFontColour[1] = 0;
			m_EmilyCharacterInfo.NormalFontColour[2] = 255;







	// Nino
	m_NinoCharacterInfo.Name = "Nino";

			
		m_NinoCharacterInfo.TextureID = Texture::GetInstance()->LoadTexture( "Nino4.png", "Background" );
		m_NinoCharacterInfo.TextureSize = Vector2( 612.f, 768.f );

			TempStringList.clear();
			TempStringList.push_back( "Storm" );
			TempStringList.push_back( "Lightning Blitz" );
			TempStringList.push_back( "Purple Rain" );
		m_NinoCharacterInfo.ScreenMagicAttacks = TempStringList;

			TempStringList.clear();
			TempStringList.push_back( "Bolt" );
			TempStringList.push_back( "Spark" );
		m_NinoCharacterInfo.IndividualMagicAttacks = TempStringList;

			TempStringList.clear();
		m_NinoCharacterInfo.PowerUpMagic = m_RitaCharacterInfo.PowerUpMagic;

		m_NinoCharacterInfo.PowerDownMagic = m_RitaCharacterInfo.PowerDownMagic;

			m_NinoCharacterInfo.BackWindowColour[0] =  156;  // Red
			m_NinoCharacterInfo.BackWindowColour[1] =  24;   // Green
			m_NinoCharacterInfo.BackWindowColour[2] =  213;  // Blue
			m_NinoCharacterInfo.BackWindowColour[3] =  127;  // Opacity

			m_NinoCharacterInfo.CharacterNameFontColour[0] = 8;
			m_NinoCharacterInfo.CharacterNameFontColour[1] = 255;
			m_NinoCharacterInfo.CharacterNameFontColour[2] = 0;

			m_NinoCharacterInfo.LabelFontColour[0] = 0;
			m_NinoCharacterInfo.LabelFontColour[1] = 17;
			m_NinoCharacterInfo.LabelFontColour[2] = 255;

			m_NinoCharacterInfo.NormalFontColour[0] = 246;
			m_NinoCharacterInfo.NormalFontColour[1] = 255;
			m_NinoCharacterInfo.NormalFontColour[2] = 0;

}



//===============================================
//	Setup Rita's Background Textures
//===============================================
void Scene_SelectCharacter::SetupRitaBackgroundTextures()
{
	std::list<std::string> lTextureNames;
	lTextureNames.push_back( "Rita1.jpg" );
	lTextureNames.push_back( "Rita2.jpg" );
	lTextureNames.push_back( "Rita3.jpg" );
	SetupBackgroundTexturesList( m_lRitaBackTextureInfoList, lTextureNames );
	lTextureNames.clear();
	///////////////////////////////////////////////////
	m_iRitaCharacterTexture.TextureName = "Rita4.png";
	m_iRitaCharacterTexture.ID = Texture::GetInstance()->LoadTexture( m_iRitaCharacterTexture.TextureName, "Background" );
	m_iRitaCharacterTexture.Size = Vector2( 444.f, 768.f );
}



//===============================================
//	Setup Emily's Background Textures
//===============================================
void Scene_SelectCharacter::SetupEmilyBackgroundTextures()
{
	std::list<std::string> lTextureNames;
	lTextureNames.push_back( "Emily1.jpg" );
	lTextureNames.push_back( "Emily2.png" );
	SetupBackgroundTexturesList( m_lEmilyBackTextureInfoList, lTextureNames );	
	lTextureNames.clear();
	///////////////////////////////////////////////////
	m_iEmilyCharacterTexture.TextureName = "Emily3.png";
	m_iEmilyCharacterTexture.ID = Texture::GetInstance()->LoadTexture( m_iEmilyCharacterTexture.TextureName, "Background" );
	m_iEmilyCharacterTexture.Size = Vector2( 543.f, 768.f );
}


//===============================================
//	Setup Nino's Background Textures
//===============================================
void Scene_SelectCharacter::SetupNinoBackgroundTextures()
{
	std::list<std::string> lTextureNames;
	lTextureNames.push_back( "Nino1.jpg" );
	lTextureNames.push_back( "Nino2.png" );
	lTextureNames.push_back( "Nino3.jpg" );
	SetupBackgroundTexturesList( m_lNinoBackTextureInfoList, lTextureNames );	
	lTextureNames.clear();
	///////////////////////////////////////////////////
	m_iNinoCharacterTexture.TextureName = "Nino4.png";
	m_iNinoCharacterTexture.ID = Texture::GetInstance()->LoadTexture( m_iNinoCharacterTexture.TextureName, "Background" );
	m_iNinoCharacterTexture.Size = Vector2( 612.f, 768.f );
}



//===============================================
//	Setup Background Textures Lists
//===============================================
void Scene_SelectCharacter::SetupBackgroundTexturesList( std::list<CharacterTextureInfo> &TextInfoList, std::list<std::string> lTextureNames )
{
	for( std::list<std::string>::iterator iter = lTextureNames.begin(); iter != lTextureNames.end(); iter++ )
	{
		////////////////////////////////////////////
		CharacterTextureInfo CTI;
		////////////////////////////////////////////
		CTI.TextureName = *iter;
		////////////////////////////////////////////
		CTI.Size = SetupTextureSize( CTI.TextureName );
		////////////////////////////////////////////
		CTI.ID = Texture::GetInstance()->LoadTexture( CTI.TextureName, "Background" );
		////////////////////////////////////////////
		TextInfoList.push_back( CTI );
		////////////////////////////////////////////
	}
}


//===============================================
//	Setup Texture Size
//===============================================
Vector2 Scene_SelectCharacter::SetupTextureSize( std::string sNameOfImage )
{
	Vector2 TVec2;
	float ScreenWidth	= ScreenResolution::GetInstance()->GetScreenWidth();
	float ScreenHeight	= ScreenResolution::GetInstance()->GetScreenHeight();
	/////////////////////////////////////////////////////////////////////////
	if		( sNameOfImage == "Rita2.jpg" ) { TVec2 = Vector2( ScreenWidth, ScreenHeight + 30.f ); }
	else if	( sNameOfImage == "Rita3.jpg" )	{ TVec2 = Vector2( 419.f, 768.f ); }
	else if	( sNameOfImage == "Rita4.png" )	{ TVec2 = Vector2( 444.f, 768.f ); }
	else if ( sNameOfImage == "Emily2.png") { TVec2 = Vector2( 511.f, 768.f ); }
	else if ( sNameOfImage == "Nino2.png" ) { TVec2 = Vector2( 317.f, 768.f ); }
	else if ( sNameOfImage == "Nino3.jpg" ) { TVec2 = Vector2( 435.f, 768.f ); }
	else									{ TVec2 = Vector2( ScreenWidth, ScreenHeight ); }
	/////////////////////////////////////////////////////////////////////////
	return TVec2;
}


//===============================================
//	Setup Rita's Animated Sprite
//===============================================
void Scene_SelectCharacter::SetupRitaAnimatedSprite()
{
	//////////////////////////////////////////////////////////////
	std::list<AnimatedSpriteInfoList>  Animated2DList;
	AnimatedSpriteInfoList			   RowOne, RowTwo, RowThree, RowFour;
	//////////////////////////////////////////////////////////////
	RowOne.DirectionList.push_back(	  "Down"  );		RowOne.DirectionList.push_back(   "Down"  );		RowOne.DirectionList.push_back(   "Down"  );
	RowTwo.DirectionList.push_back(   "Left"  );		RowTwo.DirectionList.push_back(   "Left"  );		RowTwo.DirectionList.push_back(   "Left"  );
	RowThree.DirectionList.push_back( "Right" );	    RowThree.DirectionList.push_back( "Right" );	    RowThree.DirectionList.push_back( "Right" );
	RowFour.DirectionList.push_back(  "Up"    );		RowFour.DirectionList.push_back(  "Up"    );		RowFour.DirectionList.push_back(  "Up"    );
	//////////////////////////////////////////////////////////////
	Animated2DList.push_back( RowOne );		Animated2DList.push_back( RowTwo ); 
	Animated2DList.push_back( RowThree );	Animated2DList.push_back( RowFour );
	//////////////////////////////////////////////////////////////
	unsigned int iMainLeftFrame = 1;	unsigned int iMainRightFrame = 1;	unsigned int iMainUpFrame = 1;	unsigned int iMainDownFrame = 1;
	float fSecondsToWaitForUpdate = 0.20f;
	//////////////////////////////////////////////////////////////
	m_pRitaAnimatedSprite->SetupAnimatedSprite( Animated2DList, fSecondsToWaitForUpdate, iMainLeftFrame, iMainRightFrame, iMainUpFrame, iMainDownFrame );
	//////////////////////////////////////////////////////////////
}




//===============================================
//	Setup Emily's Animated Sprite
//===============================================
void Scene_SelectCharacter::SetupEmilyAnimatedSprite()
{
	// Get Emily's Texture ID
	unsigned int iEmilyTextureID = m_pEmilyAnimatedSprite->GetCurrentTextureID();

	// The only difference between her and Rita is the Texture, so make them both equal
	*m_pEmilyAnimatedSprite = *m_pRitaAnimatedSprite;

	// Now set the Texture to what it should be
	m_pEmilyAnimatedSprite->SetCurrentTexture( iEmilyTextureID );
}



//===============================================
//	Setup Nino's Animated Sprite
//===============================================
void Scene_SelectCharacter::SetupNinoAnimatedSprite()
{
	// Get Nino's Texture ID
	unsigned int iNinoTextureID = m_pNinoAnimatedSprite->GetCurrentTextureID();

	// The only difference between her and Rita is the Texture, so make them both equal
	*m_pNinoAnimatedSprite = *m_pRitaAnimatedSprite;

	// Now set the Texture to what it should be
	m_pNinoAnimatedSprite->SetCurrentTexture( iNinoTextureID );
}


//===============================================
//	Update
//===============================================
void Scene_SelectCharacter::Update()
{
	m_fCurrentTime			+= DeltaTime::GetInstance()->GetDeltaTime();
	m_fCurrentAnimationTime += DeltaTime::GetInstance()->GetDeltaTime();



	CheckInput();
	UpdateAnimatedSprites();
	UpdateBackgroundTextures();
}



//===============================================
//	Check Input
//===============================================
void Scene_SelectCharacter::CheckInput()
{
	InputHandler* pInput = InputHandler::GetInstance();

	if( pInput->GetKeyState( SDLK_RETURN ) || pInput->GetKeyState( SDLK_SPACE ) || pInput->GetJoyButtonState( JoystickButtons_Start ) || pInput->GetJoyButtonState( JoystickButtons_A ) ||
		( m_bClickable && pInput->GetMouseClicked() )) 
	{
		///////////////////////////////////////////////////////////////
		if		(m_iCurrentHighlighted == eRitaSelected)	{ GameSystemInfo::GetInstance()->SetCurrentCharacter( "RITA" );  }
		else if	(m_iCurrentHighlighted == eEmilySelected)	{ GameSystemInfo::GetInstance()->SetCurrentCharacter( "EMILY" ); }
		else												{ GameSystemInfo::GetInstance()->SetCurrentCharacter( "NINO" );  }
		///////////////////////////////////////////////////////////////
		m_pSceneManager->ChangeState( SceneManager::ePLAY_GAME_STATE );
	}

	else if( (m_iCurrentHighlighted != eNinoSelected) &&
		(pInput->GetKeyState( SDLK_DOWN ) || pInput->GetKeyState( SDLK_s ) || pInput->GetJoyDPadState( JoystickDPadButtons_Down )  || pInput->GetJoyDPadState( JoystickDPadButtons_Down_Right ) ||
		 pInput->GetKeyState( SDLK_RIGHT) || pInput->GetKeyState( SDLK_d ) || pInput->GetJoyDPadState( JoystickDPadButtons_Right ) || pInput->GetJoyDPadState( JoystickDPadButtons_Down_Left )  )) 
	{
		m_iCurrentHighlighted++;
	}

	else if( (m_iCurrentHighlighted != eRitaSelected) &&
		(pInput->GetKeyState( SDLK_UP )  || pInput->GetKeyState( SDLK_w ) || pInput->GetJoyDPadState( JoystickDPadButtons_Up )   || pInput->GetJoyDPadState( JoystickDPadButtons_Up_Left )  ||
		 pInput->GetKeyState( SDLK_LEFT) || pInput->GetKeyState( SDLK_a ) || pInput->GetJoyDPadState( JoystickDPadButtons_Left ) || pInput->GetJoyDPadState( JoystickDPadButtons_Up_Right ) ))                                                                                                                                           
	{
		m_iCurrentHighlighted--;
	}












	// Check if Mouse is hovering over one of their names
	Vector2 v2RitaMouseCoords( 150.f, 50.f );
	Vector2 v2EmilyMouseCoords( 400.f, 50.f );
	Vector2 v2NinoMouseCoords( 650.f, 50.f );

	unsigned int iMouseOffSet		= 30;
	unsigned int iNameFontSize		= 30;
	unsigned int iRitaNameLength	= 4;
	unsigned int iEmilyNameLength	= 5;
	unsigned int iNinoNameLength	= 4;

	float fRitaMouseEndX	= (v2RitaMouseCoords.X	+ (iNameFontSize * iRitaNameLength)	 );
	float fRitaMouseEndY	= (v2RitaMouseCoords.Y	+ iMouseOffSet						 );
	float fEmilyMouseEndX	= (v2EmilyMouseCoords.X + (iNameFontSize * iEmilyNameLength) );
	float fEmilyMouseEndY	= (v2EmilyMouseCoords.Y + iMouseOffSet						 );
	float fNinoMouseEndX	= (v2NinoMouseCoords.X	+ (iNameFontSize * iNinoNameLength)	 );
	float fNinoMouseEndY	= (v2NinoMouseCoords.Y	+ iMouseOffSet						 );

	bool bMouseWithinRitaXCoordinates	= (pInput->GetMousePos().X >= v2RitaMouseCoords.X && pInput->GetMousePos().X <= fRitaMouseEndX);
	bool bMouseWithinRitaYCoordinates	= (pInput->GetMousePos().Y >= v2RitaMouseCoords.Y && pInput->GetMousePos().Y <= fRitaMouseEndY);

	bool bMouseWithinEmilyXCoordinates	= (pInput->GetMousePos().X >= v2EmilyMouseCoords.X && pInput->GetMousePos().X <= fEmilyMouseEndX);
	bool bMouseWithinEmilyYCoordinates  = (pInput->GetMousePos().Y >= v2EmilyMouseCoords.Y && pInput->GetMousePos().Y <= fEmilyMouseEndY);
	
	bool bMouseWithinNinoXCoordinates   = (pInput->GetMousePos().X >= v2NinoMouseCoords.X && pInput->GetMousePos().X <= fNinoMouseEndX);
	bool bMouseWithinNinoYCoordinates   = (pInput->GetMousePos().Y >= v2NinoMouseCoords.Y && pInput->GetMousePos().Y <= fNinoMouseEndY);



	if( bMouseWithinRitaXCoordinates && bMouseWithinRitaYCoordinates )   
	{
		m_bClickable = true;
		m_iCurrentHighlighted = eRitaSelected;
	}
	else if( bMouseWithinEmilyXCoordinates && bMouseWithinEmilyYCoordinates )   
	{
		m_bClickable = true;
		m_iCurrentHighlighted = eEmilySelected;

	}
	else  if( bMouseWithinNinoXCoordinates && bMouseWithinNinoYCoordinates )   
	{
		m_bClickable = true;
		m_iCurrentHighlighted = eNinoSelected;
	}
	else
	{
		m_bClickable = false;
	}
}




//===============================================
//	Update Animated Sprites
//===============================================
void Scene_SelectCharacter::UpdateAnimatedSprites()
{
	float fSecondsTillSwitchDirection = 3.0f;

	AnimatedSprite* p_TempAnimSpritePtr = nullptr;

	// Get Correct Character Pointer
	if		( m_iCurrentHighlighted == eRitaSelected ) { p_TempAnimSpritePtr = m_pRitaAnimatedSprite;  }
	else if	( m_iCurrentHighlighted == eEmilySelected ){ p_TempAnimSpritePtr = m_pEmilyAnimatedSprite; }
	else										       { p_TempAnimSpritePtr = m_pNinoAnimatedSprite;  }

	// Fix Character Animation Direction (if necessary)
	if	   ( p_TempAnimSpritePtr->GetAnimationDirection() == "RIGHT" && p_TempAnimSpritePtr->GetCurrentAnimationFrame() == 2 ){ p_TempAnimSpritePtr->SetAnimationDirection( "LEFT" );  }
	else if( p_TempAnimSpritePtr->GetAnimationDirection() == "LEFT"  && p_TempAnimSpritePtr->GetCurrentAnimationFrame() == 0 ){	p_TempAnimSpritePtr->SetAnimationDirection( "RIGHT" ); }

	// Change Direction?
	if( m_fCurrentAnimationTime >= fSecondsTillSwitchDirection )
	{
		m_fCurrentAnimationTime = 0.f;

		if		( p_TempAnimSpritePtr->GetFacingDirection() == "LEFT" )	 { p_TempAnimSpritePtr->SetFacingDirection( "UP" );    }
		else if ( p_TempAnimSpritePtr->GetFacingDirection() == "UP" )	 { p_TempAnimSpritePtr->SetFacingDirection( "RIGHT" ); }
		else if ( p_TempAnimSpritePtr->GetFacingDirection() == "RIGHT" ) { p_TempAnimSpritePtr->SetFacingDirection( "DOWN" );  }
		else															 { p_TempAnimSpritePtr->SetFacingDirection( "LEFT" );  }
	}

	p_TempAnimSpritePtr->Update();
}




//===============================================
//	Update Background Textures
//===============================================
void Scene_SelectCharacter::UpdateBackgroundTextures()
{
	// Change Background Texture
	if( (m_fCurrentTime >= CONST_M_F_TIMEUNTILTRANSITION) || (m_iPreviousHighlighted != m_iCurrentHighlighted) )
	{
		// Make Adjustments
		m_fCurrentTime				= 0.0f;
		m_iPreviousHighlighted	    = m_iCurrentHighlighted;
		m_iPreviousTextureID		= m_iCurrentTextureID;
		m_fPreviousTextureOpacity	= m_fCurrentTextureOpacity;
		m_fCurrentTextureOpacity    = 0.f;
		m_v2PreviousTexturePosition = m_v2CurentTexturePosition;
		m_v2PreviousTextureSize		= m_v2CurrentTextureSize;

		// Create a new list
		std::list<CharacterTextureInfo> Temp_CTI_List;

		// Assign the appropriate list
		if		( m_iCurrentHighlighted == eRitaSelected ) { Temp_CTI_List = m_lRitaBackTextureInfoList;	}
		else if	( m_iCurrentHighlighted == eEmilySelected ){ Temp_CTI_List = m_lEmilyBackTextureInfoList;	}
		else										       { Temp_CTI_List = m_lNinoBackTextureInfoList;	}

		// Don't need the same texture twice
		while( m_iCurrentTextureID == m_iPreviousTextureID )
		{
			unsigned int iRandElement							= rand() % Temp_CTI_List.size();
			unsigned int iCurrentElement						= 0;
			std::list<CharacterTextureInfo>::iterator CTI_Iter	= Temp_CTI_List.begin();

			// Keep going till the Iterator is on the right memory address
			while( iCurrentElement < iRandElement )
			{
				iCurrentElement++;
				CTI_Iter++;
			}

			m_iCurrentTextureID			= CTI_Iter->ID;
			m_v2CurentTexturePosition.X = ((ScreenResolution::GetInstance()->GetScreenWidth() * 0.5f) - (CTI_Iter->Size.X * 0.5f)); // Either Centers the Image or makes it full screen depending on the size
			m_v2CurrentTextureSize		= CTI_Iter->Size;
		}
	}


	// Modify Texture Opacity
	float fTextureOpacitySpeed = 1.5f;
	if( m_fPreviousTextureOpacity > 0.1f )
	{ 
		m_fPreviousTextureOpacity -= (DeltaTime::GetInstance()->GetDeltaTimeNormalisedValue(fTextureOpacitySpeed) * DeltaTime::GetInstance()->GetDeltaTime()); 
		if( (m_fPreviousTextureOpacity - (DeltaTime::GetInstance()->GetDeltaTimeNormalisedValue(fTextureOpacitySpeed) * DeltaTime::GetInstance()->GetDeltaTime())) <= 0.f)
		{
			m_fPreviousTextureOpacity = 0.1f;
		}
	}
	if( m_fCurrentTextureOpacity < 255.f )
	{ 
		m_fCurrentTextureOpacity += (DeltaTime::GetInstance()->GetDeltaTimeNormalisedValue(fTextureOpacitySpeed) * DeltaTime::GetInstance()->GetDeltaTime());  
		if( (m_fCurrentTextureOpacity + (DeltaTime::GetInstance()->GetDeltaTimeNormalisedValue(fTextureOpacitySpeed) * DeltaTime::GetInstance()->GetDeltaTime())) >= 255.f)
		{
			m_fCurrentTextureOpacity = 255.f;
		}
	}
}














//===============================================
//	Draw
//===============================================
void Scene_SelectCharacter::Draw()
{
	////// Get Appropriate Values //////
	AnimatedSprite* p_TempAnimSprite = nullptr;
	CharacterInfo	TempCharInfo;

	if( m_iCurrentHighlighted == eRitaSelected ) 
	{ 
		TempCharInfo = m_RitaCharacterInfo;
		p_TempAnimSprite = m_pRitaAnimatedSprite; 
	}
	else if( m_iCurrentHighlighted == eEmilySelected )
	{ 
		TempCharInfo = m_EmilyCharacterInfo;
		p_TempAnimSprite = m_pEmilyAnimatedSprite;  
	}
	else
	{ 
		TempCharInfo = m_NinoCharacterInfo;
		p_TempAnimSprite = m_pNinoAnimatedSprite;  
	}
	//////////////////////////////////////////////




	unsigned int iFontLines = ( TempCharInfo.ScreenMagicAttacks.size() + TempCharInfo.IndividualMagicAttacks.size() + TempCharInfo.PowerUpMagic.size() + TempCharInfo.PowerDownMagic.size() );
	Vector2 v2BackWindowPosition( 50.f, 150.f );
	Vector2 v2BackWindowSize( 600.f, ((float)iFontLines * 42.f) + 100.f );




	// Draw a Tinted Screen for White Background Images, makes it blend
	DrawBackgroundWindow( 255, 255, 255, 255, Vector2( 0, 0 ), Vector2( ScreenResolution::GetInstance()->GetScreenWidth(), ScreenResolution::GetInstance()->GetScreenHeight() ));

	// Draw BackGround Textures
	DrawBackgroundTextures();

	// Draw a Tinted Screen
	DrawBackgroundWindow( TempCharInfo, Vector2( 0, 0 ), Vector2( ScreenResolution::GetInstance()->GetScreenWidth(), ScreenResolution::GetInstance()->GetScreenHeight() ));

	// Draw Character
	DrawCharacter();

	// Draw a Window Box
	DrawBackgroundWindow( TempCharInfo, v2BackWindowPosition, v2BackWindowSize );

	// Draw the Info Text
	DrawFont( TempCharInfo, v2BackWindowPosition, v2BackWindowSize );

	// Draw Animated Sprite
	p_TempAnimSprite->Draw( m_v2AnimatedSpritePosiiton.X, m_v2AnimatedSpritePosiiton.Y, m_v2AnimatedSpriteSize.X, m_v2AnimatedSpriteSize.Y, false );

	// Draw Character Selectable Options
	DrawCharacterSelectionOptions();
}





//===============================================
//	Draw Background Textures
//===============================================
void Scene_SelectCharacter::DrawBackgroundTextures()
{
	// Draw Current Texture First (causes a nice fade out effect)
	DrawManager::GetInstance()->DrawTexturef( m_v2CurentTexturePosition, m_v2CurrentTextureSize, (unsigned int)m_fCurrentTextureOpacity, m_iCurrentTextureID, false );

	// Draw Previous Texture
	DrawManager::GetInstance()->DrawTexturef( m_v2PreviousTexturePosition, m_v2PreviousTextureSize, (unsigned int)m_fPreviousTextureOpacity, m_iPreviousTextureID, false );
}


//===============================================
//	Draw Character
//===============================================
void Scene_SelectCharacter::DrawCharacter()
{
	CharacterTextureInfo TempCharTextInfo;

	if		( m_iCurrentHighlighted == eRitaSelected  ){ TempCharTextInfo = m_iRitaCharacterTexture;  }
	else if	( m_iCurrentHighlighted == eEmilySelected ){ TempCharTextInfo = m_iEmilyCharacterTexture; }
	else											   { TempCharTextInfo = m_iNinoCharacterTexture;  }

	DrawManager::GetInstance()->DrawTexturef( Vector2( 550.f, 150.f ), TempCharTextInfo.Size, TempCharTextInfo.ID, false );
}


//===============================================
//	Draw Background Window
//===============================================
void Scene_SelectCharacter::DrawBackgroundWindow( CharacterInfo &TempCharInfo, Vector2 &v2BackWindowPosition, Vector2 &v2BackWindowSize )
{
	DrawManager::GetInstance()->DrawQuad2f( v2BackWindowPosition, v2BackWindowSize, TempCharInfo.BackWindowColour[0], 
											TempCharInfo.BackWindowColour[1], TempCharInfo.BackWindowColour[2], TempCharInfo.BackWindowColour[3], false );
}

void Scene_SelectCharacter::DrawBackgroundWindow( unsigned int iRed, unsigned int iGreen, unsigned int iBlue, unsigned int iOpacity, Vector2 &v2BackWindowPosition, Vector2 &v2BackWindowSize )
{
	DrawManager::GetInstance()->DrawQuad2f( v2BackWindowPosition, v2BackWindowSize, iRed, iGreen, iBlue, iOpacity, false );
}


//===============================================
//	Draw Font
//===============================================
void Scene_SelectCharacter::DrawFont( CharacterInfo &TempCharInfo, Vector2 &v2BackWindowPosition, Vector2 &v2BackWindowSize )
{
	unsigned int iNameLength = TempCharInfo.Name.length();
	float fFontSize = 25.f;
	float fFont_XPos = ((v2BackWindowPosition.X + (v2BackWindowSize.X * 0.5f)) - (((float)iNameLength * fFontSize) *0.5f));
	float fFont_YPos = (v2BackWindowPosition.Y + 10.f);


	FontManager* pFont = FontManager::GetInstance();
	pFont->SetFont_Colour( TempCharInfo.CharacterNameFontColour[0], TempCharInfo.CharacterNameFontColour[1], TempCharInfo.CharacterNameFontColour[2] );
	pFont->SetFont_Opacity( 255 );

	pFont->SetFont_Width_Height( fFontSize, fFontSize );
	pFont->SetFont_Position( fFont_XPos, fFont_YPos );
	pFont->PrintFont( TempCharInfo.Name );


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	std::string sLabel = "Screen Attack Magic";
	iNameLength = sLabel.length();
	fFontSize = 18.f;

	fFont_XPos  = ((v2BackWindowPosition.X + (v2BackWindowSize.X * 0.5f)) - (((float)iNameLength * fFontSize) * 0.5f));
	fFont_YPos += 50.f;
	pFont->SetFont_Width_Height( fFontSize, fFontSize );
	pFont->SetFont_Position( fFont_XPos, fFont_YPos );
	pFont->SetFont_Colour( TempCharInfo.LabelFontColour[0], TempCharInfo.LabelFontColour[1], TempCharInfo.LabelFontColour[2] );
	pFont->PrintFont( sLabel );

	fFontSize = 12.f;
	pFont->SetFont_Colour( TempCharInfo.NormalFontColour[0], TempCharInfo.NormalFontColour[1], TempCharInfo.NormalFontColour[2] );
	fFont_XPos = v2BackWindowPosition.X + 30.f;

	for( std::list<std::string>::iterator iter = TempCharInfo.ScreenMagicAttacks.begin(); iter != TempCharInfo.ScreenMagicAttacks.end(); iter++ )
	{
		fFont_YPos += 20.f;
		pFont->SetFont_Position( fFont_XPos, fFont_YPos );
		pFont->PrintFont( *iter );
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	sLabel = "Individual Attack Magic";
	iNameLength = sLabel.length();
	fFontSize = 18.f;

	fFont_XPos  = ((v2BackWindowPosition.X + (v2BackWindowSize.X * 0.5f)) - (((float)iNameLength * fFontSize) * 0.5f));
	fFont_YPos += 50.f;
	pFont->SetFont_Width_Height( fFontSize, fFontSize );
	pFont->SetFont_Position( fFont_XPos, fFont_YPos );
	pFont->SetFont_Colour( TempCharInfo.LabelFontColour[0], TempCharInfo.LabelFontColour[1], TempCharInfo.LabelFontColour[2] );
	pFont->PrintFont( sLabel );

	fFontSize = 12.f;
	pFont->SetFont_Colour( TempCharInfo.NormalFontColour[0], TempCharInfo.NormalFontColour[1], TempCharInfo.NormalFontColour[2] );
	fFont_XPos = v2BackWindowPosition.X + 30.f;

	for( std::list<std::string>::iterator iter = TempCharInfo.IndividualMagicAttacks.begin(); iter != TempCharInfo.IndividualMagicAttacks.end(); iter++ )
	{
		fFont_YPos += 20.f;
		pFont->SetFont_Position( fFont_XPos, fFont_YPos );
		pFont->PrintFont( *iter );
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	sLabel = "Power Up Magic";
	iNameLength = sLabel.length();
	fFontSize = 18.f;

	fFont_XPos  = ((v2BackWindowPosition.X + (v2BackWindowSize.X * 0.5f)) - (((float)iNameLength * fFontSize) * 0.5f));
	fFont_YPos += 50.f;
	pFont->SetFont_Width_Height( fFontSize, fFontSize );
	pFont->SetFont_Position( fFont_XPos, fFont_YPos );
	pFont->SetFont_Colour( TempCharInfo.LabelFontColour[0], TempCharInfo.LabelFontColour[1], TempCharInfo.LabelFontColour[2] );
	pFont->PrintFont( sLabel );

	fFontSize = 12.f;
	pFont->SetFont_Colour( TempCharInfo.NormalFontColour[0], TempCharInfo.NormalFontColour[1], TempCharInfo.NormalFontColour[2] );
	fFont_XPos = v2BackWindowPosition.X + 30.f;

	for( std::list<std::string>::iterator iter = TempCharInfo.PowerUpMagic.begin(); iter != TempCharInfo.PowerUpMagic.end(); iter++ )
	{
		fFont_YPos += 20.f;
		pFont->SetFont_Position( fFont_XPos, fFont_YPos );
		pFont->PrintFont( *iter );
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	sLabel = "Power Down Magic";
	iNameLength = sLabel.length();
	fFontSize = 18.f;

	fFont_XPos  = ((v2BackWindowPosition.X + (v2BackWindowSize.X * 0.5f)) - (((float)iNameLength * fFontSize) * 0.5f));
	fFont_YPos += 50.f;
	pFont->SetFont_Width_Height( fFontSize, fFontSize );
	pFont->SetFont_Position( fFont_XPos, fFont_YPos );
	pFont->SetFont_Colour( TempCharInfo.LabelFontColour[0], TempCharInfo.LabelFontColour[1], TempCharInfo.LabelFontColour[2] );
	pFont->PrintFont( sLabel );

	fFontSize = 12.f;
	pFont->SetFont_Colour( TempCharInfo.NormalFontColour[0], TempCharInfo.NormalFontColour[1], TempCharInfo.NormalFontColour[2] );
	fFont_XPos = v2BackWindowPosition.X + 30.f;

	for( std::list<std::string>::iterator iter = TempCharInfo.PowerDownMagic.begin(); iter != TempCharInfo.PowerDownMagic.end(); iter++ )
	{
		fFont_YPos += 20.f;
		pFont->SetFont_Position( fFont_XPos, fFont_YPos );
		pFont->PrintFont( *iter );
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}


//===============================================
//	Draw Character Selection Options
//===============================================
void Scene_SelectCharacter::DrawCharacterSelectionOptions()
{
	Vector2 v2RitaSelectableOptionPosition( 150.f, 50.f );  
	Vector2 v2EmilySelectableOptionPosition( 400.f, 50.f ); 
	Vector2 v2NinoSelectableOptionPosition( 650.f, 50.f );  

	Vector2 v2SelectableOptionSize( 30.f, 30.f );


	FontManager* pFont = FontManager::GetInstance();
	pFont->SetFont_Opacity( 255 );
	pFont->SetFont_Width_Height( v2SelectableOptionSize.X, v2SelectableOptionSize.Y );





	// Draw Background WIndows
	DrawBackgroundWindow( 169, 44,  44,  255, v2RitaSelectableOptionPosition,  Vector2((v2SelectableOptionSize.X * 4.f), v2SelectableOptionSize.Y) );
	DrawBackgroundWindow( 166, 128, 53,  255, v2EmilySelectableOptionPosition, Vector2((v2SelectableOptionSize.X * 5.f), v2SelectableOptionSize.Y) );
	DrawBackgroundWindow( 156, 24,  213, 255, v2NinoSelectableOptionPosition,  Vector2((v2SelectableOptionSize.X * 4.f), v2SelectableOptionSize.Y) );







	// Draw Rita Selectable
	pFont->SetFont_Colour( 188, 139, 66 );
	pFont->SetFont_Position( v2RitaSelectableOptionPosition.X, v2RitaSelectableOptionPosition.Y );
	pFont->PrintFont( "Rita" );


	

	// Draw Emily Selectable
	pFont->SetFont_Colour( 66, 188, 86 );
	pFont->SetFont_Position( v2EmilySelectableOptionPosition.X, v2EmilySelectableOptionPosition.Y );
	pFont->PrintFont( "Emily" );




	// Draw Rita Selectable
	pFont->SetFont_Colour( 44, 172, 198 );
	pFont->SetFont_Position( v2NinoSelectableOptionPosition.X, v2NinoSelectableOptionPosition.Y );
	pFont->PrintFont( "Nino" );










	pFont->SetFont_Colour( 127, 127, 127 );

	if( m_iCurrentHighlighted == eRitaSelected ) 
	{ 
		pFont->SetFont_Position( v2RitaSelectableOptionPosition.X, v2RitaSelectableOptionPosition.Y );
		pFont->PrintFont( "Rita" );
	}
	else if( m_iCurrentHighlighted == eEmilySelected )
	{ 
		pFont->SetFont_Position( v2EmilySelectableOptionPosition.X, v2EmilySelectableOptionPosition.Y ); 
		pFont->PrintFont( "Emily" );
	}
	else
	{ 
		pFont->SetFont_Position( v2NinoSelectableOptionPosition.X, v2NinoSelectableOptionPosition.Y );
		pFont->PrintFont( "Nino" ); 
	}
}