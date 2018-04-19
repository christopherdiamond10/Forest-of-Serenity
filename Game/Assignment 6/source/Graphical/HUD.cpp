#include "HUD.h"

#include "sdl_opengl.h"
#include "InputHandler.h"
#include "FontManager.h"
#include "ScreenResolution.h"
#include "Player.h"

#include "Texture.h"
#include "DrawManager.h"
#include <string>


//===============================================
//	Constructor
//===============================================
HUD::HUD( Player* pPlayer )
{
	m_pPlayer = pPlayer;
}


//===============================================
//	Destructor
//===============================================
HUD::~HUD()
{
	
}





//===============================================
//	OnLoad
//===============================================
void HUD::OnLoad()
{
	//////////////////////////////////////////////////////////
	m_v2HealthDisplayPosition			= Vector2( 0.f, 0.f );			
	m_v2HealthDisplaySize				= Vector2( 150.f, 15.f );			
	m_v2HealthDisplayCurrentSize		= m_v2HealthDisplaySize;
	//////////////////////////////////////////////////////////
	m_v2HighScoreDisplayPosition		= Vector2( 0.f, 0.f );		
	m_v2HighScoreDisplaySize			= Vector2( 20.f, 20.f );
	//////////////////////////////////////////////////////////
	m_v2MagicDisplayPosition			= Vector2( 0.f, 0.f );			
	m_v2MagicDisplaySize				= Vector2( 150.f, 15.f );			
	m_v2MagicDisplayCurrentSize			= m_v2MagicDisplaySize;
	//////////////////////////////////////////////////////////
	m_v2MagicOptionsDisplayPosition		= Vector2( 0.f, 0.f );	
	m_v2MagicOptionsDisplaySize			= Vector2( 200.f, 200.f );
	//////////////////////////////////////////////////////////
	m_iMagicOptionsOpacity				= 0;
	//////////////////////////////////////////////////////////
	

	
	m_iHealthIconTextureID			= Texture::GetInstance()->LoadTexture( "Health_Icon.png",			"Others" );
	m_iFireMagicIconTextureID		= Texture::GetInstance()->LoadTexture( "FireMagic_Icon.png",		"Others" );
	m_iLightningMagicIconTextureID	= Texture::GetInstance()->LoadTexture( "LightningMagic_Icon.png",	"Others" );
	m_iEarthMagicIconTextureID		= Texture::GetInstance()->LoadTexture( "EarthMagic_Icon.png",		"Others" );
	m_iMagicOptionsTextureID		= Texture::GetInstance()->LoadTexture( "D-Pad_Icon.png",			"Others" );
}



//===============================================
//	OnUnload
//===============================================
void HUD::OnUnload()
{

}









//===============================================
//	Update
//===============================================
void HUD::Update( Vector2 vCamPosition )
{
	UpdateHealthDisplay			( vCamPosition );
	UpdateHighScoreDisplay		( vCamPosition );
	UpdateMagicDisplay			( vCamPosition );
	UpdateMagicOptionsDisplay	( vCamPosition );
}



//===============================================
//	Update Health Display
//===============================================
void HUD::UpdateHealthDisplay( Vector2 vCamPosition )
{
	m_v2HealthDisplayPosition			 = vCamPosition;
	m_v2HealthDisplayPosition.X		    += 100.f;
	m_v2HealthDisplayPosition.Y		    += 50.f;

	m_v2HealthDisplayCurrentSize.X = (m_pPlayer->GetPlayerHealth() * 1.5f);
}


//===============================================
//	Update HighScore Display
//===============================================
void HUD::UpdateHighScoreDisplay( Vector2 vCamPosition )
{
	m_v2HighScoreDisplayPosition	 	 = vCamPosition;
	m_v2HighScoreDisplayPosition.X	    += ((ScreenResolution::GetInstance()->GetScreenWidth() * 0.5f) - (m_v2HighScoreDisplaySize.X * 0.5f)) - 80.f;
	m_v2HighScoreDisplayPosition.Y	    += 50.f;
}


//===============================================
//	Update Magic Display
//===============================================
void HUD::UpdateMagicDisplay( Vector2 vCamPosition )
{
	m_v2MagicDisplayPosition			 = vCamPosition;
	m_v2MagicDisplayPosition.X			+= ((ScreenResolution::GetInstance()->GetScreenWidth() - m_v2MagicDisplaySize.X) - 100.f);
	m_v2MagicDisplayPosition.Y			+= 50.f;

	m_v2MagicDisplayCurrentSize.X = m_pPlayer->GetPlayerMagic();
}


//===============================================
//	Update Magic Options Display
//===============================================
void HUD::UpdateMagicOptionsDisplay( Vector2 vCamPosition )
{
	if( m_pPlayer->Get_IsUsingMagic() )
	{
		m_v2MagicOptionsDisplayPosition			 = vCamPosition;
		m_v2MagicOptionsDisplayPosition.X		+= ((ScreenResolution::GetInstance()->GetScreenWidth()  - m_v2MagicOptionsDisplaySize.X) - 50.f);
		m_v2MagicOptionsDisplayPosition.Y		+= ((ScreenResolution::GetInstance()->GetScreenHeight() - m_v2MagicOptionsDisplaySize.Y) - 100.f);

		if( m_iMagicOptionsOpacity != 255 )
		{	m_iMagicOptionsOpacity++;	}
	}
	else
	{
		if( m_iMagicOptionsOpacity != 0 )
		{	m_iMagicOptionsOpacity--;	}
	}
}









//===============================================
//	Draw
//===============================================
void HUD::Draw()
{
	DrawHealthDisplay();
	DrawHighScoreDisplay();
	DrawMagicDisplay();
	DrawMagicOptionsDisplay();
}



//===============================================
//	Draw Health Display
//===============================================
void HUD::DrawHealthDisplay()
{
	// Draw the Health Icon
	float fIconWidth  = 30.f;
	float fIconHeight = 25.f;

	DrawManager::GetInstance()->DrawTexturef( (m_v2HealthDisplayPosition.X - fIconWidth), (m_v2HealthDisplayPosition.Y - 5.f), fIconWidth, fIconHeight, m_iHealthIconTextureID, true, 3 );


	// Draw the Health Bar
	unsigned int iRed		= 0;
	unsigned int iGreen		= 255;
	unsigned int iBlue		= 0;
	unsigned int iOpacity	= 255;

	DrawManager::GetInstance()->DrawQuad2f( m_v2HealthDisplayPosition, m_v2HealthDisplaySize, iRed, iGreen, iBlue, (unsigned int)(iOpacity * 0.5f), true, 1 );
	

	// Draw the Remaining Health
	DrawManager::GetInstance()->DrawQuad2f( m_v2HealthDisplayPosition, m_v2MagicDisplayCurrentSize, iRed, iGreen, iBlue, iOpacity, true, 1 );

}


//===============================================
//	Draw HighScore Display
//===============================================
void HUD::DrawHighScoreDisplay()
{
	FontManager::GetInstance()->SetFont_Colour( 100, 200, 100 );
	FontManager::GetInstance()->SetFont_Opacity( 200 );
	FontManager::GetInstance()->SetFont_Position( m_v2HighScoreDisplayPosition.X, m_v2HighScoreDisplayPosition.Y - 20.f );
	FontManager::GetInstance()->SetFont_Width_Height( m_v2HighScoreDisplaySize.X, m_v2HighScoreDisplaySize.Y );
	FontManager::GetInstance()->PrintFont( "HighScore" );
	FontManager::GetInstance()->SetFont_Position( m_v2HighScoreDisplayPosition.X, m_v2HighScoreDisplayPosition.Y );
	FontManager::GetInstance()->PrintFont( m_pPlayer->GetPlayerScore() );
}


//===============================================
//	Draw Magic Display
//===============================================
void HUD::DrawMagicDisplay()
{
	unsigned int iTextureID;
	unsigned int iRed, iGreen, iBlue;
	int iOpacity = 255;

	if( m_pPlayer->GetCurrentPlayerName() == "RITA" )
	{
		iTextureID  = m_iFireMagicIconTextureID;
		iRed		= 148;
		iGreen		= 44;
		iBlue		= 44;
	}
	else if( m_pPlayer->GetCurrentPlayerName() == "EMILY" )
	{
		iTextureID  = m_iEarthMagicIconTextureID;
		iRed		= 153;
		iGreen		= 117;
		iBlue		= 35;
	}
	else
	{
		iTextureID	= m_iLightningMagicIconTextureID;
		iRed		= 158;
		iGreen		= 10;
		iBlue		= 195;
	}


	// Draw the Magic Icon
	float fIconWidth  = 30.f;
	float fIconHeight = 25.f;
	
	DrawManager::GetInstance()->DrawTexturef( (m_v2MagicDisplayPosition.X - fIconWidth), (m_v2MagicDisplayPosition.Y - 5.f), fIconWidth, fIconHeight, iTextureID, true, 3 );

	// Draw the Magic Bar
	DrawManager::GetInstance()->DrawQuad2f( m_v2MagicDisplayPosition, m_v2MagicDisplaySize, iRed, iGreen, iBlue, (unsigned int)(iOpacity * 0.5f), true, 1 );
	

	// Draw the Remaining Magic
	DrawManager::GetInstance()->DrawQuad2f( m_v2MagicDisplayPosition, m_v2MagicDisplayCurrentSize, iRed, iGreen, iBlue, iOpacity, true, 1 );
}


//===============================================
//	Draw Magic Options Display
//===============================================
void HUD::DrawMagicOptionsDisplay()
{
	DrawManager::GetInstance()->DrawTexturef( m_v2MagicOptionsDisplayPosition, m_v2MagicOptionsDisplaySize, m_iMagicOptionsOpacity, m_iMagicOptionsTextureID, false );
}