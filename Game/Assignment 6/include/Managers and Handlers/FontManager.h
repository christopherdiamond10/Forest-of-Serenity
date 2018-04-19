//\====================================================================================
//\ Author: Christopher Diamond
//\ About : Font.h - 
//\ 
//\ Defines the Font Singleton Class. This class is used to show font throughout the 
//\ game, this class is used for the menu, instruction, textboxes and highscores.
//\====================================================================================
#ifndef _FONT_H_
#define _FONT_H_
	
#include <list>


class FontManager
{
//=========================================
public:
//=========================================


	////////////////////////////////////
	//			Functions			  //
	////////////////////////////////////
	FontManager();
	~FontManager();

	static FontManager* GetInstance();

	void OnLoad();
	void OnUnload();

	int* GetFontColour();

	void SetFont_Position( float fStartX, float fStartY );
	void SetFont_Width_Height ( float fWidth, float fHeight );
	void SetFont_Colour( int iRed, int iGreen, int iBlue );
	void SetFont_Opacity( int iOpacity );


	void PrintFont( float fFloat );
	void PrintFont( std::string cString, float fFloat );
	void PrintFont( int iInt );
	void PrintFont( std::string cString, int iInt );
	void PrintFont( std::string cString, unsigned int UIint );
	void PrintFont( unsigned int UIint );
	void PrintFont( std::string cString );
	






//=========================================	
private:
//=========================================

	////////////////////////////////////
	//			Class Struct		  //
	////////////////////////////////////
	struct FontSheetCharacterInfo
	{
		char Character;
		float UvCoordStartx;
		float UvCoordStarty;
		float UvCoordEndx;
		float UvCoordEndy;
	};


	////////////////////////////////////
	//			Values				  //
	////////////////////////////////////
	unsigned int	m_iTextureID;

	int*			m_iReturnArray;

	float			m_fFont_Width;
	float			m_fFont_Height;

	float			m_fTextStartxPos;
	float			m_fTextStartyPos;
	float			m_fFont_xPos;
	float			m_fFont_yPos;

	int				m_iFontRed;
	int				m_iFontGreen;
	int				m_iFontBlue;
	int				m_iFontOpacity;

	std::list<FontSheetCharacterInfo> m_lFSCInfoList;

	////////////////////////////////////
	//			Functions			  //
	////////////////////////////////////
	template< class T >
	void Print( T AnyValue );


	float* GetUVCoords				  ( char cLetterNum );
	bool DoesCharacterNeedToBeAdjusted( char c );

	////////////////////////////////////
	//			Pointers			  //
	////////////////////////////////////
	static FontManager* m_Instance;
};


#endif