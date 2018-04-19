#include "FontManager.h"

#include "ScreenResolution.h"
#include "Texture.h"
#include "DrawManager.h"
#include "sdl_opengl.h"
#include <sstream>
#include <assert.h>


FontManager* FontManager::m_Instance = NULL;

FontManager* FontManager::GetInstance()
{
	return m_Instance;
}

//=============================================
//			Constructor / Destructor
//=============================================
FontManager::FontManager()
{
	if( m_Instance == NULL ){ m_Instance = this; }
	else					{ assert(0);		 }



	m_iTextureID = Texture::GetInstance()->LoadTexture( "FontSheet.png", "Other" );



	// Since it refuses to call OnLoad for some FUCKING REASON.

	const int PrimarySize	= 7;
	const int SecondarySize = 15;

	char cPushTempArray[PrimarySize][SecondarySize] =
	{
		{ 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', },
		{ 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', },
		{ 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', },
		{ 't', 'u', 'v', 'w', 'x', 'y', 'z', '`', '~', '!', '@', '#', '$', '%', '^', },
		{ '&', '*', '(', ')', '-', '_', '+', '=', '{', '}', 91,  93,  '|', 92,  ':', }, // 91 == '[', 92 == '\', 93 == ']'
		{ ';', '"', 39,  '<', '>', ',', '.', '?', '?', '?', '?', '?', '?', '?', '?', }, // 39 == ' (Quotation Mark)
		{ '?', '?', '?', '?', '?', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', },
	};


	// Push the Above 2D Array into the list
	for( int Y = 0; Y < PrimarySize; Y++ )
	{
		for( int X = 0; X < SecondarySize; X++ )
		{
			FontSheetCharacterInfo FSCI;
			FSCI.Character = cPushTempArray[Y][X];

			// Set the UV Coordinates
			FSCI.UvCoordStartx			= ((float)X					/			 (float)SecondarySize  );
			FSCI.UvCoordEndx			= ((FSCI.UvCoordStartx)		+	 (1.f /  (float)SecondarySize ));
			FSCI.UvCoordStarty			= ((float)Y					/			 (float)PrimarySize	   );
			FSCI.UvCoordEndy			= ((FSCI.UvCoordStarty)		+	 (1.f /  (float)PrimarySize   ));

			// Add it to the List
			m_lFSCInfoList.push_back( FSCI );
		}
	}
}



FontManager::~FontManager()
{
	
}





//=============================================
//				Load / Unload
//=============================================
void FontManager::OnLoad()
{
	m_fFont_Width			= 20;
	m_fFont_Height			= 20;


	m_fTextStartxPos		= 300;
	m_fTextStartyPos		= 50;


	m_iFontRed		= 100;
	m_iFontGreen	= 100;
	m_iFontBlue		= 100;
	m_iFontOpacity	= 100;
}


void FontManager::OnUnload()
{
	m_lFSCInfoList.clear();
}






//=============================================
//			Get Functions
//=============================================
int* FontManager::GetFontColour()
{
	m_iReturnArray[4]; 
	/////////////////////////////////////
	m_iReturnArray[0] = m_iFontRed;/////////
	m_iReturnArray[1] = m_iFontGreen;///////
	m_iReturnArray[2] = m_iFontBlue;////////
	m_iReturnArray[3] = m_iFontOpacity;/////
	/////////////////////////////////////
	return m_iReturnArray;
}










//=============================================
//			Set Functions
//=============================================
void FontManager::SetFont_Position( float fStartX, float fStartY )
{
	m_fTextStartxPos = fStartX;
	m_fTextStartyPos = fStartY;
}


void FontManager::SetFont_Width_Height( float fWidth, float fHeight )
{
	m_fFont_Width  = fWidth;
	m_fFont_Height = fHeight;
}


void FontManager::SetFont_Colour( int iRed, int iGreen, int iBlue )
{
	m_iFontRed		= iRed;
	m_iFontGreen	= iGreen;
	m_iFontBlue		= iBlue;
}


void FontManager::SetFont_Opacity( int iOpacity )
{
	m_iFontOpacity = iOpacity;
}










//=============================================
//			Print Font
//=============================================
template< class T >
void FontManager::Print( T AnyValue )
{
	// Converting from any non-string value to a string ...
	std::stringstream cString (std::stringstream::in | std::stringstream::out);
	cString << AnyValue;




	for( unsigned int i = 0; i < cString.str().length(); i++)
	{
		char cLetterNum = cString.str()[i];

		//===== If New Line Character =====// 
		// In the Text Argument, you can enter either "\\n"
		if( cLetterNum == 92 ) // 92 == '\'
		{
			if( ( cString.str()[i + 1] == 'n' || cString.str()[i + 1] == 'N' )) 
			{
				m_fFont_yPos += (m_fFont_Height + ( m_fFont_Height * 0.3f ));
				m_fFont_xPos = m_fTextStartxPos;
			}

			i++; continue;
		}
		//===== If New Line Character =====//



		// Skip the drawing of the font if the char is a space and only add to the text position.
		else if( cLetterNum != ' ' )
		{
			float* UV_Coords = GetUVCoords( cLetterNum );

			// Function Called will adjust character position if true 
			bool bAdjustCharPosition = DoesCharacterNeedToBeAdjusted( cLetterNum );

			// Draw Character
			DrawManager::GetInstance()->DrawTexturef( m_fFont_xPos, m_fFont_yPos, m_fFont_Width, m_fFont_Height, m_iFontRed, m_iFontGreen, m_iFontBlue, 
													  m_iFontOpacity, m_iTextureID, true, 1, UV_Coords );

			// Re-adjust Position if the other function adjusted it
			if( bAdjustCharPosition ){ m_fFont_yPos -= ( m_fFont_Height * 0.3f ); }
		}


		m_fFont_xPos += m_fFont_Width;
	}
}
//=============================================
//			Print Font
//=============================================
void FontManager::PrintFont( float fFloat )
{
	m_fFont_xPos = m_fTextStartxPos;
	m_fFont_yPos = m_fTextStartyPos;

	Print( fFloat );
}
void FontManager::PrintFont( std::string cString, float fFloat )
{
	m_fFont_xPos = m_fTextStartxPos;
	m_fFont_yPos = m_fTextStartyPos;

	Print( cString );
	Print( fFloat );
}
void FontManager::PrintFont( int iInt )
{
	m_fFont_xPos = m_fTextStartxPos;
	m_fFont_yPos = m_fTextStartyPos;

	Print( iInt );
}
void FontManager::PrintFont( std::string cString, int iInt )
{
	m_fFont_xPos = m_fTextStartxPos;
	m_fFont_yPos = m_fTextStartyPos;

	Print( cString );
	Print( iInt );
}
void FontManager::PrintFont( std::string cString, unsigned int UIint )
{
	m_fFont_xPos = m_fTextStartxPos;
	m_fFont_yPos = m_fTextStartyPos;

	Print( cString );
	Print( UIint );
}
void FontManager::PrintFont( unsigned int UIint )
{
	m_fFont_xPos = m_fTextStartxPos;
	m_fFont_yPos = m_fTextStartyPos;

	Print( UIint );
}
void FontManager::PrintFont( std::string cString )
{
	m_fFont_xPos = m_fTextStartxPos;
	m_fFont_yPos = m_fTextStartyPos;

	Print( cString );
}







float* FontManager::GetUVCoords( char cLetterNum )
{
	for( std::list<FontSheetCharacterInfo>::iterator iter = m_lFSCInfoList.begin(); iter != m_lFSCInfoList.end(); iter++ )
	{
		if( iter->Character == cLetterNum )
		{
			float* UV_Coords = new float[4];
			UV_Coords[0] = iter->UvCoordStartx; UV_Coords[1] = iter->UvCoordStarty; 
			UV_Coords[2] = iter->UvCoordEndx;	UV_Coords[3] = iter->UvCoordEndy;
			return UV_Coords;
		}
	}
	return nullptr;
}


bool FontManager::DoesCharacterNeedToBeAdjusted( char c )
{
	if( c == 'g' || c == 'j' || c == 'p' || c == 'q' || c == 'y' )
	{
		m_fFont_yPos += ( m_fFont_Height * 0.3f );
		return true;
	}

	return false;
}