#include "DrawManager.h"

#include "sdl_opengl.h"
#include <assert.h>


DrawManager* DrawManager::m_Instance = nullptr;

DrawManager* DrawManager::GetInstance()
{
	return m_Instance;
}
//=================================
//		Constructor	
//=================================
DrawManager::DrawManager()
{
	if( m_Instance == nullptr )
	{
		m_Instance = this; 
	}
	else
	{
		assert(0);
	}
}

//=================================
//		Destructor
//=================================
DrawManager::~DrawManager()
{

}


//=================================
//		OnLoad	
//=================================
void DrawManager::OnLoad()
{
	DrawManagerSetColour( 255, 255, 255, 255 );
	DrawManagerSetUVCoordinates();
}


//=================================
//		OnUnload	
//=================================
void DrawManager::OnUnload()
{

}


//=================================
//		Load Sprite Texture
//=================================
void DrawManager::LoadSpriteTexture( std::string Filename, std::string TextureType )
{

}



//=================================
//	  Privately Set Colour	
//=================================
void DrawManager::DrawManagerSetColour( unsigned int iRed, unsigned int iGreen, unsigned int iBlue, unsigned int iOpacity )
{
	m_iRedLevel = iRed;	m_iGreenLevel = iGreen;	m_iBlueLevel = iBlue; m_iOpacity = iOpacity;
}
void DrawManager::DrawManagerSetColour( unsigned int iRed, unsigned int iGreen, unsigned int iBlue )
{
	m_iRedLevel = iRed;	m_iGreenLevel = iGreen;	m_iBlueLevel = iBlue;
}
//=================================
//	  Privately Set Opacity	
//=================================
void DrawManager::DrawManagerSetOpacity( unsigned int iOpacity )
{
	m_iOpacity = iOpacity;
}
//=================================
//	 Privately Set UV Coordinates	
//=================================
void DrawManager::DrawManagerSetUVCoordinates( float fStartX, float fStartY, float fEndX, float fEndY )
{
	m_fUvCoordStartx = fStartX;	m_fUvCoordStarty = fStartY;	m_fUvCoordEndx = fEndX;	m_fUvCoordEndy = fEndY;
}




















//=================================
//	 Draw Texture	
//=================================
void DrawManager::DrawTexturei( int iXpos, int iYpos, unsigned int iWidth, unsigned int iHeight, unsigned int iTextureID, bool bUseGradient, unsigned int iHowManyGradients_OutOfThree, float* fUV_Coords )
{	
	//Enable the Texture to be drawn
	glEnable(GL_TEXTURE_2D);

	// Bind the texture
	glBindTexture(GL_TEXTURE_2D, iTextureID);
	
	// If UV_Coords is not a null pointer, set class UV coords to its values
	if( fUV_Coords != nullptr )	{ DrawManagerSetUVCoordinates( fUV_Coords[0], fUV_Coords[1], fUV_Coords[2], fUV_Coords[3] ); }

	// Draw the Texture
	this->DrawQuad2i( iXpos, iYpos, iWidth, iHeight, bUseGradient, iHowManyGradients_OutOfThree );

	// If UV_Coords was not a null pointer, set the class UV coords back to normal, delete the allocated heap memory and make the pointer a null pointer.
	if( fUV_Coords != nullptr )	{ DrawManagerSetUVCoordinates();		delete[] fUV_Coords;		fUV_Coords = nullptr; }

	// Disable the Texture to be drawn
	glDisable(GL_TEXTURE_2D);
}



void DrawManager::DrawTexturef( float fXpos, float fYpos, float fWidth, float fHeight, unsigned int iTextureID, bool bUseGradient, unsigned int iHowManyGradients_OutOfThree, float* fUV_Coords )
{
	//Enable the Texture to be drawn
	glEnable(GL_TEXTURE_2D);

	// Bind the texture
	glBindTexture(GL_TEXTURE_2D, iTextureID);
	
	// If UV_Coords is not a null pointer, set class UV coords to its values
	if( fUV_Coords != nullptr )	{ DrawManagerSetUVCoordinates( fUV_Coords[0], fUV_Coords[1], fUV_Coords[2], fUV_Coords[3] ); }

	// Draw the Texture
	this->DrawQuad2f( fXpos, fYpos, fWidth, fHeight, bUseGradient, iHowManyGradients_OutOfThree );

	// If UV_Coords was not a null pointer, set the class UV coords back to normal, delete the allocated heap memory and make the pointer a null pointer.
	if( fUV_Coords != nullptr )	{ DrawManagerSetUVCoordinates();		delete[] fUV_Coords;		fUV_Coords = nullptr; }

	// Disable the Texture to be drawn
	glDisable(GL_TEXTURE_2D);
}



void DrawManager::DrawTexturef( Vector2 vObjectPosition, Vector2 vObjectSize, unsigned int iTextureID, bool bUseGradient, unsigned int iHowManyGradients_OutOfThree, float* fUV_Coords )
{
	this->DrawTexturef( vObjectPosition.X, vObjectPosition.Y, vObjectSize.X, vObjectSize.Y, iTextureID, bUseGradient, iHowManyGradients_OutOfThree, fUV_Coords );
}



////////////////////////////////
// Colour & Opacity Overloads //
void DrawManager::DrawTexturei( int iXpos, int iYpos, unsigned int iWidth, unsigned int iHeight, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, unsigned int iOpacity, unsigned int iTextureID, bool bUseGradient, unsigned int iHowManyGradients_OutOfThree, float* fUV_Coords )
{
	unsigned int iCurrentColours[4] = { m_iRedLevel, m_iGreenLevel, m_iBlueLevel, m_iOpacity };
	DrawManagerSetColour( iRed, iGreen, iBlue, iOpacity );
	this->DrawTexturei( iXpos, iYpos, iWidth, iHeight, iTextureID, bUseGradient, iHowManyGradients_OutOfThree, fUV_Coords );
	DrawManagerSetColour( iCurrentColours[0], iCurrentColours[1], iCurrentColours[2], iCurrentColours[3] );
}



void DrawManager::DrawTexturef( float fXpos, float fYpos, float fWidth, float fHeight, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, unsigned int iOpacity, unsigned int iTextureID, bool bUseGradient, unsigned int iHowManyGradients_OutOfThree, float* fUV_Coords  )
{
	unsigned int iCurrentColours[4] = { m_iRedLevel, m_iGreenLevel, m_iBlueLevel, m_iOpacity };
	DrawManagerSetColour( iRed, iGreen, iBlue, iOpacity );
	this->DrawTexturef( fXpos, fYpos, fWidth, fHeight, iTextureID, bUseGradient, iHowManyGradients_OutOfThree, fUV_Coords );
	DrawManagerSetColour( iCurrentColours[0], iCurrentColours[1], iCurrentColours[2], iCurrentColours[3] );
}
	


void DrawManager::DrawTexturef( Vector2 vObjectPosition, Vector2 vObjectSize, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, unsigned int iOpacity, unsigned int iTextureID, bool bUseGradient, unsigned int iHowManyGradients_OutOfThree, float* fUV_Coords )
{
	this->DrawTexturef( vObjectPosition.X, vObjectPosition.Y, vObjectSize.X, vObjectSize.Y, iRed, iGreen, iBlue, iOpacity, iTextureID, bUseGradient, iHowManyGradients_OutOfThree, fUV_Coords );
}



//////////////////////
// Colour Overloads	// 
void DrawManager::DrawTexturei( int iXpos, int iYpos, unsigned int iWidth, unsigned int iHeight, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, unsigned int iTextureID, bool bUseGradient, unsigned int iHowManyGradients_OutOfThree, float* fUV_Coords )
{
	unsigned int iCurrentColours[3] = { m_iRedLevel, m_iGreenLevel, m_iBlueLevel };
	DrawManagerSetColour( iRed, iGreen, iBlue );
	this->DrawTexturei( iXpos, iYpos, iWidth, iHeight, iTextureID, bUseGradient, iHowManyGradients_OutOfThree, fUV_Coords );
	DrawManagerSetColour( iCurrentColours[0], iCurrentColours[1], iCurrentColours[2] );
}



void DrawManager::DrawTexturef( float fXpos, float fYpos, float fWidth, float fHeight, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, unsigned int iTextureID, bool bUseGradient, unsigned int iHowManyGradients_OutOfThree, float* fUV_Coords )
{
	unsigned int iCurrentColours[3] = { m_iRedLevel, m_iGreenLevel, m_iBlueLevel };
	DrawManagerSetColour( iRed, iGreen, iBlue );
	this->DrawTexturef( fXpos, fYpos, fWidth, fHeight, iTextureID, bUseGradient, iHowManyGradients_OutOfThree, fUV_Coords );
	DrawManagerSetColour( iCurrentColours[0], iCurrentColours[1], iCurrentColours[2] );
}



void DrawManager::DrawTexturef( Vector2 vObjectPosition, Vector2 vObjectSize, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, unsigned int iTextureID, bool bUseGradient, unsigned int iHowManyGradients_OutOfThree, float* fUV_Coords )
{
	this->DrawTexturef( vObjectPosition.X, vObjectPosition.Y, vObjectSize.X, vObjectSize.Y, iRed, iGreen, iBlue, iTextureID, bUseGradient, iHowManyGradients_OutOfThree, fUV_Coords );
}
	


///////////////////////
// Opacity Overloads //	 
void DrawManager::DrawTexturei( int iXpos, int iYpos, unsigned int iWidth, unsigned int iHeight, unsigned int iOpacity, unsigned int iTextureID, bool bUseGradient, unsigned int iHowManyGradients_OutOfThree, float* fUV_Coords )
{
	unsigned int iCurrentOpacity = m_iOpacity;
	DrawManagerSetOpacity( iOpacity );
	this->DrawTexturei( iXpos, iYpos, iWidth, iHeight, iTextureID, bUseGradient, iHowManyGradients_OutOfThree, fUV_Coords );
	DrawManagerSetOpacity( iCurrentOpacity );
}



void DrawManager::DrawTexturef( float fXpos, float fYpos, float fWidth, float fHeight, unsigned int iOpacity, unsigned int iTextureID, bool bUseGradient, unsigned int iHowManyGradients_OutOfThree, float* fUV_Coords )
{
	unsigned int iCurrentOpacity = m_iOpacity;
	DrawManagerSetOpacity( iOpacity );
	this->DrawTexturef( fXpos, fYpos, fWidth, fHeight, iTextureID, bUseGradient, iHowManyGradients_OutOfThree, fUV_Coords );
	DrawManagerSetOpacity( iCurrentOpacity );
}



void DrawManager::DrawTexturef( Vector2 vObjectPosition, Vector2 vObjectSize, unsigned int iOpacity, unsigned int iTextureID, bool bUseGradient, unsigned int iHowManyGradients_OutOfThree, float* fUV_Coords )
{
	this->DrawTexturef( vObjectPosition.X, vObjectPosition.Y, vObjectSize.X, vObjectSize.Y, iOpacity, iTextureID, bUseGradient, iHowManyGradients_OutOfThree, fUV_Coords );
}




















//===================================
//			Draw Point
//===================================
void DrawManager::DrawPoint2i( int iPosX, int iPosY )
{
	float fRed		=	m_iRedLevel		* 0.003921f; // <- ( m_iRedLevel / 255 )
	float fGreen	=	m_iGreenLevel	* 0.003921f;
	float fBlue		=	m_iBlueLevel 	* 0.003921f;
	float fOpacity	=	m_iOpacity		* 0.003921f;
	

	glBegin(GL_POINTS);
		glColor4f( fRed, fGreen, fBlue, fOpacity );
		glVertex2i( iPosX, iPosY );
	glEnd();
}



void DrawManager::DrawPoint2f( float fPosX, float fPosY )
{
	float fRed		=	m_iRedLevel		* 0.003921f; // <- ( m_iRedLevel / 255 )
	float fGreen	=	m_iGreenLevel	* 0.003921f;
	float fBlue		=	m_iBlueLevel 	* 0.003921f;
	float fOpacity	=	m_iOpacity		* 0.003921f;
	

	glBegin(GL_POINTS);
		glColor4f( fRed, fGreen, fBlue, fOpacity );
		glVertex2f( fPosX, fPosY );
	glEnd();
}



void DrawManager::DrawPoint2f( Vector2 v2PointPos )
{
	this->DrawPoint2f( v2PointPos.X, v2PointPos.Y );
}



////////////////////////////////
// Colour & Opacity Overloads //
void DrawManager::DrawPoint2i( int iPosX, int iPosY, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, unsigned int iOpacity )
{
	unsigned int iCurrentColours[4] = { m_iRedLevel, m_iGreenLevel, m_iBlueLevel, m_iOpacity };
	DrawManagerSetColour( iRed, iGreen, iBlue, iOpacity );
	this->DrawPoint2i( iPosX, iPosY );
	DrawManagerSetColour( iCurrentColours[0], iCurrentColours[1], iCurrentColours[2], iCurrentColours[3] );
}



void DrawManager::DrawPoint2f( float fPosX, float fPosY, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, unsigned int iOpacity )
{
	unsigned int iCurrentColours[4] = { m_iRedLevel, m_iGreenLevel, m_iBlueLevel, m_iOpacity };
	DrawManagerSetColour( iRed, iGreen, iBlue, iOpacity );
	this->DrawPoint2f( fPosX, fPosY );
	DrawManagerSetColour( iCurrentColours[0], iCurrentColours[1], iCurrentColours[2], iCurrentColours[3] );
}



void DrawManager::DrawPoint2f( Vector2 v2PointPos, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, unsigned int iOpacity )
{
	this->DrawPoint2f( v2PointPos.X, v2PointPos.Y, iRed, iGreen, iBlue, iOpacity );
}



//////////////////////
// Colour Overloads //
void DrawManager::DrawPoint2i( int iPosX, int iPosY, unsigned int iRed, unsigned int iGreen, unsigned int iBlue )
{
	unsigned int iCurrentColours[3] = { m_iRedLevel, m_iGreenLevel, m_iBlueLevel };
	DrawManagerSetColour( iRed, iGreen, iBlue );
	this->DrawPoint2i( iPosX, iPosY );
	DrawManagerSetColour( iCurrentColours[0], iCurrentColours[1], iCurrentColours[2] );
}



void DrawManager::DrawPoint2f( float fPosX, float fPosY, unsigned int iRed, unsigned int iGreen, unsigned int iBlue )
{
	unsigned int iCurrentColours[3] = { m_iRedLevel, m_iGreenLevel, m_iBlueLevel };
	DrawManagerSetColour( iRed, iGreen, iBlue );
	this->DrawPoint2f( fPosX, fPosY );
	DrawManagerSetColour( iCurrentColours[0], iCurrentColours[1], iCurrentColours[2] );
}



void DrawManager::DrawPoint2f( Vector2 v2PointPos, unsigned int iRed, unsigned int iGreen, unsigned int iBlue )
{
	this->DrawPoint2f( v2PointPos.X, v2PointPos.Y, iRed, iGreen, iBlue );
}



///////////////////////
// Opacity Overloads //
void DrawManager::DrawPoint2i( int iPosX, int iPosY, unsigned int iOpacity )
{
	unsigned int iCurrentOpacity = m_iOpacity;
	DrawManagerSetOpacity( iOpacity );
	this->DrawPoint2i( iPosX, iPosY );
	DrawManagerSetOpacity( iCurrentOpacity );
}



void DrawManager::DrawPoint2f( float fPosX, float fPosY, unsigned int iOpacity )
{
	unsigned int iCurrentOpacity = m_iOpacity;
	DrawManagerSetOpacity( iOpacity );
	this->DrawPoint2f( fPosX, fPosY );
	DrawManagerSetOpacity( iCurrentOpacity );
}



void DrawManager::DrawPoint2f( Vector2 v2PointPos, unsigned int iOpacity )
{
	this->DrawPoint2f( v2PointPos.X, v2PointPos.Y, iOpacity );
}




















//===================================
//			Draw Line
//===================================
void DrawManager::DrawLine2i( int iStartX, int iStartY, int iEndX, int iEndY )
{
	float fRed		=	m_iRedLevel		* 0.003921f; // <- ( m_iRedLevel / 255 )
	float fGreen	=	m_iGreenLevel	* 0.003921f;
	float fBlue		=	m_iBlueLevel 	* 0.003921f;
	float fOpacity	=	m_iOpacity		* 0.003921f;
	

	glBegin(GL_LINES);
		glColor4f( fRed, fGreen, fBlue, fOpacity );
		glVertex2i( iStartX, iStartY );
		glVertex2i( iEndX, iEndY );
	glEnd();
}



void DrawManager::DrawLine2f( float fStartX, float fStartY, float fEndX, float fEndY )
{
	float fRed		=	m_iRedLevel		* 0.003921f; // <- ( m_iRedLevel / 255 )
	float fGreen	=	m_iGreenLevel	* 0.003921f;
	float fBlue		=	m_iBlueLevel 	* 0.003921f;
	float fOpacity	=	m_iOpacity		* 0.003921f;
	

	glBegin(GL_LINES);
		glColor4f( fRed, fGreen, fBlue, fOpacity );
		glVertex2f( fStartX, fStartY );
		glVertex2f( fEndX, fEndY );
	glEnd();
}



void DrawManager::DrawLine2f( Vector2 v2LineStartPos, Vector2 v2LineEndPos )
{
	this->DrawLine2f( v2LineStartPos.X, v2LineStartPos.Y, v2LineEndPos.X, v2LineEndPos.Y );
}



////////////////////////////////
// Colour & Opacity Overloads //
void DrawManager::DrawLine2i( int iStartX, int iStartY, int iEndX, int iEndY, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, unsigned int iOpacity )
{
	unsigned int iCurrentColours[4] = { m_iRedLevel, m_iGreenLevel, m_iBlueLevel, m_iOpacity };
	DrawManagerSetColour( iRed, iGreen, iBlue, iOpacity );
	this->DrawLine2i( iStartX, iStartY, iEndX, iEndY );
	DrawManagerSetColour( iCurrentColours[0], iCurrentColours[1], iCurrentColours[2], iCurrentColours[3] );
}



void DrawManager::DrawLine2f( float fStartX, float fStartY, float fEndX, float fEndY, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, unsigned int iOpacity )
{
	unsigned int iCurrentColours[4] = { m_iRedLevel, m_iGreenLevel, m_iBlueLevel, m_iOpacity };
	DrawManagerSetColour( iRed, iGreen, iBlue, iOpacity );
	this->DrawLine2f( fStartX, fStartY, fEndX, fEndY );
	DrawManagerSetColour( iCurrentColours[0], iCurrentColours[1], iCurrentColours[2], iCurrentColours[3] );
}



void DrawManager::DrawLine2f( Vector2 v2LineStartPos, Vector2 v2LineEndPos, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, unsigned int iOpacity )
{
	this->DrawLine2f( v2LineStartPos.X, v2LineStartPos.Y, v2LineEndPos.X, v2LineEndPos.Y, iRed, iGreen, iBlue, iOpacity );
}



//////////////////////
// Colour Overloads //
void DrawManager::DrawLine2i( int iStartX, int iStartY, int iEndX, int iEndY, unsigned int iRed, unsigned int iGreen, unsigned int iBlue )
{
	unsigned int iCurrentColours[3] = { m_iRedLevel, m_iGreenLevel, m_iBlueLevel };
	DrawManagerSetColour( iRed, iGreen, iBlue );
	this->DrawLine2i( iStartX, iStartY, iEndX, iEndY );
	DrawManagerSetColour( iCurrentColours[0], iCurrentColours[1], iCurrentColours[2] );
}



void DrawManager::DrawLine2f( float fStartX, float fStartY, float fEndX, float fEndY, unsigned int iRed, unsigned int iGreen, unsigned int iBlue )
{
	unsigned int iCurrentColours[3] = { m_iRedLevel, m_iGreenLevel, m_iBlueLevel };
	DrawManagerSetColour( iRed, iGreen, iBlue );
	this->DrawLine2f( fStartX, fStartY, fEndX, fEndY );
	DrawManagerSetColour( iCurrentColours[0], iCurrentColours[1], iCurrentColours[2] );
}



void DrawManager::DrawLine2f( Vector2 v2LineStartPos, Vector2 v2LineEndPos, unsigned int iRed, unsigned int iGreen, unsigned int iBlue )
{
	this->DrawLine2f( v2LineStartPos.X, v2LineStartPos.Y, v2LineEndPos.X, v2LineEndPos.Y, iRed, iGreen, iBlue );
}



///////////////////////
// Opacity Overloads //
void DrawManager::DrawLine2i( int iStartX, int iStartY, int iEndX, int iEndY, unsigned int iOpacity )
{
	unsigned int iCurrentOpacity = m_iOpacity;
	DrawManagerSetOpacity( iOpacity );
	this->DrawLine2i( iStartX, iStartY, iEndX, iEndY );
	DrawManagerSetOpacity( iCurrentOpacity );
}



void DrawManager::DrawLine2f( float fStartX, float fStartY, float fEndX, float fEndY, unsigned int iOpacity )
{
	unsigned int iCurrentOpacity = m_iOpacity;
	DrawManagerSetOpacity( iOpacity );
	this->DrawLine2f( fStartX, fStartY, fEndX, fEndY );
	DrawManagerSetOpacity( iCurrentOpacity );
}



void DrawManager::DrawLine2f( Vector2 v2LineStartPos, Vector2 v2LineEndPos, unsigned int iOpacity )
{
	this->DrawLine2f( v2LineStartPos.X, v2LineStartPos.Y, v2LineEndPos.X, v2LineEndPos.Y, iOpacity );
}




















//===================================
//			Draw LineStrip
//===================================
void DrawManager::DrawLineStrip2i( std::list<i_XY_Coords> PosList )
{
	float fRed		=	m_iRedLevel		* 0.003921f; // <- ( m_iRedLevel / 255 )
	float fGreen	=	m_iGreenLevel	* 0.003921f;
	float fBlue		=	m_iBlueLevel 	* 0.003921f;
	float fOpacity	=	m_iOpacity		* 0.003921f;
	

	glBegin(GL_LINE_STRIP);
		glColor4f( fRed, fGreen, fBlue, fOpacity );
		for( std::list<i_XY_Coords>::iterator iter = PosList.begin(); iter != PosList.end(); iter++ )
		{
			glVertex2i( iter->X, iter->Y );
		}
	glEnd();
}



void DrawManager::DrawLineStrip2f( std::list<f_XY_Coords> PosList )
{
	float fRed		=	m_iRedLevel		* 0.003921f; // <- ( m_iRedLevel / 255 )
	float fGreen	=	m_iGreenLevel	* 0.003921f;
	float fBlue		=	m_iBlueLevel 	* 0.003921f;
	float fOpacity	=	m_iOpacity		* 0.003921f;
	

	glBegin(GL_LINE_STRIP);
		glColor4f( fRed, fGreen, fBlue, fOpacity );
		for( std::list<f_XY_Coords>::iterator iter = PosList.begin(); iter != PosList.end(); iter++ )
		{
			glVertex2f( iter->X, iter->Y );
		}
	glEnd();
}



void DrawManager::DrawLineStrip2f( std::list<Vector2> PosList )
{
	float fRed		=	m_iRedLevel		* 0.003921f; // <- ( m_iRedLevel / 255 )
	float fGreen	=	m_iGreenLevel	* 0.003921f;
	float fBlue		=	m_iBlueLevel 	* 0.003921f;
	float fOpacity	=	m_iOpacity		* 0.003921f;
	

	glBegin(GL_LINE_STRIP);
		glColor4f( fRed, fGreen, fBlue, fOpacity );
		for( std::list<Vector2>::iterator iter = PosList.begin(); iter != PosList.end(); iter++ )
		{
			glVertex2f( iter->X, iter->Y );
		}
	glEnd();
} 



////////////////////////////////
// Colour & Opacity Overloads //
void DrawManager::DrawLineStrip2i( std::list<i_XY_Coords> PosList, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, unsigned int iOpacity )
{
	unsigned int iCurrentColours[4] = { m_iRedLevel, m_iGreenLevel, m_iBlueLevel, m_iOpacity };
	DrawManagerSetColour( iRed, iGreen, iBlue, iOpacity );
	this->DrawLineStrip2i( PosList );
	DrawManagerSetColour( iCurrentColours[0], iCurrentColours[1], iCurrentColours[2], iCurrentColours[3] );
}



void DrawManager::DrawLineStrip2f( std::list<f_XY_Coords> PosList, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, unsigned int iOpacity )
{
	unsigned int iCurrentColours[4] = { m_iRedLevel, m_iGreenLevel, m_iBlueLevel, m_iOpacity };
	DrawManagerSetColour( iRed, iGreen, iBlue, iOpacity );
	this->DrawLineStrip2f( PosList );
	DrawManagerSetColour( iCurrentColours[0], iCurrentColours[1], iCurrentColours[2], iCurrentColours[3] );
}



void DrawManager::DrawLineStrip2f( std::list<Vector2> PosList, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, unsigned int iOpacity )
{
	unsigned int iCurrentColours[4] = { m_iRedLevel, m_iGreenLevel, m_iBlueLevel, m_iOpacity };
	DrawManagerSetColour( iRed, iGreen, iBlue, iOpacity );
	this->DrawLineStrip2f( PosList );
	DrawManagerSetColour( iCurrentColours[0], iCurrentColours[1], iCurrentColours[2], iCurrentColours[3] );
}



//////////////////////
// Colour Overloads //
void DrawManager::DrawLineStrip2i( std::list<i_XY_Coords> PosList, unsigned int iRed, unsigned int iGreen, unsigned int iBlue )
{
	unsigned int iCurrentColours[3] = { m_iRedLevel, m_iGreenLevel, m_iBlueLevel };
	DrawManagerSetColour( iRed, iGreen, iBlue );
	this->DrawLineStrip2i( PosList );
	DrawManagerSetColour( iCurrentColours[0], iCurrentColours[1], iCurrentColours[2] );
}



void DrawManager::DrawLineStrip2f( std::list<f_XY_Coords> PosList, unsigned int iRed, unsigned int iGreen, unsigned int iBlue )
{
	unsigned int iCurrentColours[3] = { m_iRedLevel, m_iGreenLevel, m_iBlueLevel };
	DrawManagerSetColour( iRed, iGreen, iBlue );
	this->DrawLineStrip2f( PosList );
	DrawManagerSetColour( iCurrentColours[0], iCurrentColours[1], iCurrentColours[2] );
}



void DrawManager::DrawLineStrip2f( std::list<Vector2> PosList, unsigned int iRed, unsigned int iGreen, unsigned int iBlue )
{
	unsigned int iCurrentColours[3] = { m_iRedLevel, m_iGreenLevel, m_iBlueLevel };
	DrawManagerSetColour( iRed, iGreen, iBlue );
	this->DrawLineStrip2f( PosList );
	DrawManagerSetColour( iCurrentColours[0], iCurrentColours[1], iCurrentColours[2] );
}



///////////////////////
// Opacity Overloads //
void DrawManager::DrawLineStrip2i( std::list<i_XY_Coords> PosList, unsigned int iOpacity )
{
	unsigned int iCurrentOpacity = m_iOpacity;
	DrawManagerSetOpacity( iOpacity );
	this->DrawLineStrip2i( PosList );
	DrawManagerSetOpacity( iCurrentOpacity );
}



void DrawManager::DrawLineStrip2f( std::list<f_XY_Coords> PosList, unsigned int iOpacity )
{
	unsigned int iCurrentOpacity = m_iOpacity;
	DrawManagerSetOpacity( iOpacity );
	this->DrawLineStrip2f( PosList );
	DrawManagerSetOpacity( iCurrentOpacity );
}



void DrawManager::DrawLineStrip2f( std::list<Vector2> PosList, unsigned int iOpacity )
{
	unsigned int iCurrentOpacity = m_iOpacity;
	DrawManagerSetOpacity( iOpacity );
	this->DrawLineStrip2f( PosList );
	DrawManagerSetOpacity( iCurrentOpacity );
}



















//===================================
//			Draw LineLoop
//===================================
void DrawManager::DrawLineLoop2i( std::list<i_XY_Coords> PosList )
{
	float fRed		=	m_iRedLevel		* 0.003921f; // <- ( m_iRedLevel / 255 )
	float fGreen	=	m_iGreenLevel	* 0.003921f;
	float fBlue		=	m_iBlueLevel 	* 0.003921f;
	float fOpacity	=	m_iOpacity		* 0.003921f;
	

	glBegin(GL_LINE_LOOP);
		glColor4f( fRed, fGreen, fBlue, fOpacity );
		for( std::list<i_XY_Coords>::iterator iter = PosList.begin(); iter != PosList.end(); iter++ )
		{
			glVertex2i( iter->X, iter->Y );
		}
	glEnd();
}



void DrawManager::DrawLineLoop2f( std::list<f_XY_Coords> PosList )
{
	float fRed		=	m_iRedLevel		* 0.003921f; // <- ( m_iRedLevel / 255 )
	float fGreen	=	m_iGreenLevel	* 0.003921f;
	float fBlue		=	m_iBlueLevel 	* 0.003921f;
	float fOpacity	=	m_iOpacity		* 0.003921f;
	

	glBegin(GL_LINE_LOOP);
		glColor4f( fRed, fGreen, fBlue, fOpacity );
		for( std::list<f_XY_Coords>::iterator iter = PosList.begin(); iter != PosList.end(); iter++ )
		{
			glVertex2f( iter->X, iter->Y );
		}
	glEnd();
}



void DrawManager::DrawLineLoop2f( std::list<Vector2> PosList )
{
	float fRed		=	m_iRedLevel		* 0.003921f; // <- ( m_iRedLevel / 255 )
	float fGreen	=	m_iGreenLevel	* 0.003921f;
	float fBlue		=	m_iBlueLevel 	* 0.003921f;
	float fOpacity	=	m_iOpacity		* 0.003921f;
	

	glBegin(GL_LINE_LOOP);
		glColor4f( fRed, fGreen, fBlue, fOpacity );
		for( std::list<Vector2>::iterator iter = PosList.begin(); iter != PosList.end(); iter++ )
		{
			glVertex2f( iter->X, iter->Y );
		}
	glEnd();
} 



////////////////////////////////
// Colour & Opacity Overloads //
void DrawManager::DrawLineLoop2i( std::list<i_XY_Coords> PosList, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, unsigned int iOpacity )
{
	unsigned int iCurrentColours[4] = { m_iRedLevel, m_iGreenLevel, m_iBlueLevel, m_iOpacity };
	DrawManagerSetColour( iRed, iGreen, iBlue, iOpacity );
	this->DrawLineLoop2i( PosList );
	DrawManagerSetColour( iCurrentColours[0], iCurrentColours[1], iCurrentColours[2], iCurrentColours[3] );
}



void DrawManager::DrawLineLoop2f( std::list<f_XY_Coords> PosList, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, unsigned int iOpacity )
{
	unsigned int iCurrentColours[4] = { m_iRedLevel, m_iGreenLevel, m_iBlueLevel, m_iOpacity };
	DrawManagerSetColour( iRed, iGreen, iBlue, iOpacity );
	this->DrawLineLoop2f( PosList );
	DrawManagerSetColour( iCurrentColours[0], iCurrentColours[1], iCurrentColours[2], iCurrentColours[3] );
}



void DrawManager::DrawLineLoop2f( std::list<Vector2> PosList, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, unsigned int iOpacity )
{
	unsigned int iCurrentColours[4] = { m_iRedLevel, m_iGreenLevel, m_iBlueLevel, m_iOpacity };
	DrawManagerSetColour( iRed, iGreen, iBlue, iOpacity );
	this->DrawLineLoop2f( PosList );
	DrawManagerSetColour( iCurrentColours[0], iCurrentColours[1], iCurrentColours[2], iCurrentColours[3] );
}



//////////////////////
// Colour Overloads //
void DrawManager::DrawLineLoop2i( std::list<i_XY_Coords> PosList, unsigned int iRed, unsigned int iGreen, unsigned int iBlue )
{
	unsigned int iCurrentColours[3] = { m_iRedLevel, m_iGreenLevel, m_iBlueLevel };
	DrawManagerSetColour( iRed, iGreen, iBlue );
	this->DrawLineLoop2i( PosList );
	DrawManagerSetColour( iCurrentColours[0], iCurrentColours[1], iCurrentColours[2] );
}



void DrawManager::DrawLineLoop2f( std::list<f_XY_Coords> PosList, unsigned int iRed, unsigned int iGreen, unsigned int iBlue )
{
	unsigned int iCurrentColours[3] = { m_iRedLevel, m_iGreenLevel, m_iBlueLevel };
	DrawManagerSetColour( iRed, iGreen, iBlue );
	this->DrawLineLoop2f( PosList );
	DrawManagerSetColour( iCurrentColours[0], iCurrentColours[1], iCurrentColours[2] );
}



void DrawManager::DrawLineLoop2f( std::list<Vector2> PosList, unsigned int iRed, unsigned int iGreen, unsigned int iBlue )
{
	unsigned int iCurrentColours[3] = { m_iRedLevel, m_iGreenLevel, m_iBlueLevel };
	DrawManagerSetColour( iRed, iGreen, iBlue );
	this->DrawLineLoop2f( PosList );
	DrawManagerSetColour( iCurrentColours[0], iCurrentColours[1], iCurrentColours[2] );
}



///////////////////////
// Opacity Overloads //
void DrawManager::DrawLineLoop2i( std::list<i_XY_Coords> PosList, unsigned int iOpacity )
{
	unsigned int iCurrentOpacity = m_iOpacity;
	DrawManagerSetOpacity( iOpacity );
	this->DrawLineLoop2i( PosList );
	DrawManagerSetOpacity( iCurrentOpacity );
}



void DrawManager::DrawLineLoop2f( std::list<f_XY_Coords> PosList, unsigned int iOpacity )
{
	unsigned int iCurrentOpacity = m_iOpacity;
	DrawManagerSetOpacity( iOpacity );
	this->DrawLineLoop2f( PosList );
	DrawManagerSetOpacity( iCurrentOpacity );
}



void DrawManager::DrawLineLoop2f( std::list<Vector2> PosList, unsigned int iOpacity )
{
	unsigned int iCurrentOpacity = m_iOpacity;
	DrawManagerSetOpacity( iOpacity );
	this->DrawLineLoop2f( PosList );
	DrawManagerSetOpacity( iCurrentOpacity );
}



















//===================================
//			Draw Polygon
//===================================
void DrawManager::DrawPolygon2i( std::list<i_XY_Coords> PosList )
{
	float fRed		=	m_iRedLevel		* 0.003921f; // <- ( m_iRedLevel / 255 )
	float fGreen	=	m_iGreenLevel	* 0.003921f;
	float fBlue		=	m_iBlueLevel 	* 0.003921f;
	float fOpacity	=	m_iOpacity		* 0.003921f;
	

	glBegin(GL_POLYGON);
		glColor4f( fRed, fGreen, fBlue, fOpacity );
		for( std::list<i_XY_Coords>::iterator iter = PosList.begin(); iter != PosList.end(); iter++ )
		{
			glVertex2i( iter->X, iter->Y );
		}
	glEnd();
}



void DrawManager::DrawPolygon2f( std::list<f_XY_Coords> PosList )
{
	float fRed		=	m_iRedLevel		* 0.003921f; // <- ( m_iRedLevel / 255 )
	float fGreen	=	m_iGreenLevel	* 0.003921f;
	float fBlue		=	m_iBlueLevel 	* 0.003921f;
	float fOpacity	=	m_iOpacity		* 0.003921f;
	

	glBegin(GL_POLYGON);
		glColor4f( fRed, fGreen, fBlue, fOpacity );
		for( std::list<f_XY_Coords>::iterator iter = PosList.begin(); iter != PosList.end(); iter++ )
		{
			glVertex2f( iter->X, iter->Y );
		}
	glEnd();
}



void DrawManager::DrawPolygon2f( std::list<Vector2> PosList )
{
	float fRed		=	m_iRedLevel		* 0.003921f; // <- ( m_iRedLevel / 255 )
	float fGreen	=	m_iGreenLevel	* 0.003921f;
	float fBlue		=	m_iBlueLevel 	* 0.003921f;
	float fOpacity	=	m_iOpacity		* 0.003921f;
	

	glBegin(GL_POLYGON);
		glColor4f( fRed, fGreen, fBlue, fOpacity );
		for( std::list<Vector2>::iterator iter = PosList.begin(); iter != PosList.end(); iter++ )
		{
			glVertex2f( iter->X, iter->Y );
		}
	glEnd();
} 



////////////////////////////////
// Colour & Opacity Overloads //
void DrawManager::DrawPolygon2i( std::list<i_XY_Coords> PosList, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, unsigned int iOpacity )
{
	unsigned int iCurrentColours[4] = { m_iRedLevel, m_iGreenLevel, m_iBlueLevel, m_iOpacity };
	DrawManagerSetColour( iRed, iGreen, iBlue, iOpacity );
	this->DrawPolygon2i( PosList );
	DrawManagerSetColour( iCurrentColours[0], iCurrentColours[1], iCurrentColours[2], iCurrentColours[3] );
}



void DrawManager::DrawPolygon2f( std::list<f_XY_Coords> PosList, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, unsigned int iOpacity )
{
	unsigned int iCurrentColours[4] = { m_iRedLevel, m_iGreenLevel, m_iBlueLevel, m_iOpacity };
	DrawManagerSetColour( iRed, iGreen, iBlue, iOpacity );
	this->DrawPolygon2f( PosList );
	DrawManagerSetColour( iCurrentColours[0], iCurrentColours[1], iCurrentColours[2], iCurrentColours[3] );
}



void DrawManager::DrawPolygon2f( std::list<Vector2> PosList, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, unsigned int iOpacity )
{
	unsigned int iCurrentColours[4] = { m_iRedLevel, m_iGreenLevel, m_iBlueLevel, m_iOpacity };
	DrawManagerSetColour( iRed, iGreen, iBlue, iOpacity );
	this->DrawPolygon2f( PosList );
	DrawManagerSetColour( iCurrentColours[0], iCurrentColours[1], iCurrentColours[2], iCurrentColours[3] );
}



//////////////////////
// Colour Overloads //
void DrawManager::DrawPolygon2i( std::list<i_XY_Coords> PosList, unsigned int iRed, unsigned int iGreen, unsigned int iBlue )
{
	unsigned int iCurrentColours[3] = { m_iRedLevel, m_iGreenLevel, m_iBlueLevel };
	DrawManagerSetColour( iRed, iGreen, iBlue );
	this->DrawPolygon2i( PosList );
	DrawManagerSetColour( iCurrentColours[0], iCurrentColours[1], iCurrentColours[2] );
}



void DrawManager::DrawPolygon2f( std::list<f_XY_Coords> PosList, unsigned int iRed, unsigned int iGreen, unsigned int iBlue )
{
	unsigned int iCurrentColours[3] = { m_iRedLevel, m_iGreenLevel, m_iBlueLevel };
	DrawManagerSetColour( iRed, iGreen, iBlue );
	this->DrawPolygon2f( PosList );
	DrawManagerSetColour( iCurrentColours[0], iCurrentColours[1], iCurrentColours[2] );
}



void DrawManager::DrawPolygon2f( std::list<Vector2> PosList, unsigned int iRed, unsigned int iGreen, unsigned int iBlue )
{
	unsigned int iCurrentColours[3] = { m_iRedLevel, m_iGreenLevel, m_iBlueLevel };
	DrawManagerSetColour( iRed, iGreen, iBlue );
	this->DrawPolygon2f( PosList );
	DrawManagerSetColour( iCurrentColours[0], iCurrentColours[1], iCurrentColours[2] );
}



///////////////////////
// Opacity Overloads //
void DrawManager::DrawPolygon2i( std::list<i_XY_Coords> PosList, unsigned int iOpacity )
{
	unsigned int iCurrentOpacity = m_iOpacity;
	DrawManagerSetOpacity( iOpacity );
	this->DrawPolygon2i( PosList );
	DrawManagerSetOpacity( iCurrentOpacity );
}



void DrawManager::DrawPolygon2f( std::list<f_XY_Coords> PosList, unsigned int iOpacity )
{
	unsigned int iCurrentOpacity = m_iOpacity;
	DrawManagerSetOpacity( iOpacity );
	this->DrawPolygon2f( PosList );
	DrawManagerSetOpacity( iCurrentOpacity );
}



void DrawManager::DrawPolygon2f( std::list<Vector2> PosList, unsigned int iOpacity )
{
	unsigned int iCurrentOpacity = m_iOpacity;
	DrawManagerSetOpacity( iOpacity );
	this->DrawPolygon2f( PosList );
	DrawManagerSetOpacity( iCurrentOpacity );
}



















//===================================
//			Draw Triangle
//===================================
void DrawManager::DrawTriangle2i( int iPointOneX, int iPointOneY, int iPointTwoX, int iPointTwoY, int iPointThreeX, int iPointThreeY, bool bUseGradient, unsigned int iHowManyGradients_OutOfTwo )
{
	// Getting the float values of our colour levels
	float fRed		=	m_iRedLevel		* 0.003921f; // <- ( m_iRedLevel / 255 )
	float fGreen	=	m_iGreenLevel	* 0.003921f;
	float fBlue		=	m_iBlueLevel 	* 0.003921f;
	float fOpacity	=	m_iOpacity		* 0.003921f;
	

	// Draw the texture
	glBegin(GL_TRIANGLES);

		glColor4f( fRed, fGreen, fBlue, fOpacity );

		glVertex2i( iPointOneX, iPointOneY);

		if( bUseGradient && iHowManyGradients_OutOfTwo > 1){ glColor4f( fRed * 0.66f, fGreen * 0.66f, fBlue * 0.66f, fOpacity ); }
		glVertex2i( iPointTwoX, iPointTwoY );

		if( bUseGradient && iHowManyGradients_OutOfTwo > 0){ glColor4f( fRed * 0.33f, fGreen * 0.33f, fBlue * 0.33f, fOpacity ); }
		glVertex2i( iPointThreeX, iPointThreeY );

	glEnd();
}



void DrawManager::DrawTriangle2f( float fPointOneX, float fPointOneY, float fPointTwoX, float fPointTwoY, float fPointThreeX, float fPointThreeY, bool bUseGradient, unsigned int iHowManyGradients_OutOfTwo  )
{
	// Getting the float values of our colour levels
	float fRed		=	m_iRedLevel		* 0.003921f; // <- ( m_iRedLevel / 255 )
	float fGreen	=	m_iGreenLevel	* 0.003921f;
	float fBlue		=	m_iBlueLevel 	* 0.003921f;
	float fOpacity	=	m_iOpacity		* 0.003921f;
	

	// Draw the texture
	glBegin(GL_TRIANGLES);

		glColor4f( fRed, fGreen, fBlue, fOpacity );

		glVertex2f( fPointOneX, fPointOneY);

		if( bUseGradient && iHowManyGradients_OutOfTwo > 1){ glColor4f( fRed * 0.66f, fGreen * 0.66f, fBlue * 0.66f, fOpacity ); }
		glVertex2f( fPointTwoX, fPointTwoY );

		if( bUseGradient && iHowManyGradients_OutOfTwo > 0){ glColor4f( fRed * 0.33f, fGreen * 0.33f, fBlue * 0.33f, fOpacity ); }
		glVertex2f( fPointThreeX, fPointThreeY );

	glEnd();
}



void DrawManager::DrawTriangle2f( Vector2 v2PointOne, Vector2 V2PointTwo, Vector2 v2PointThree, bool bUseGradient, unsigned int iHowManyGradients_OutOfTwo )
{
	this->DrawTriangle2f( v2PointOne.X, v2PointOne.Y, V2PointTwo.X, V2PointTwo.Y, v2PointThree.X, v2PointThree.Y, bUseGradient, iHowManyGradients_OutOfTwo );
}



////////////////////////////////
// Colour & Opacity Overloads //
void DrawManager::DrawTriangle2i( int iPointOneX, int iPointOneY, int iPointTwoX, int iPointTwoY, int iPointThreeX, int iPointThreeY, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, unsigned int iOpacity, bool bUseGradient, unsigned int iHowManyGradients_OutOfTwo )
{
	unsigned int iCurrentColours[4] = { m_iRedLevel, m_iGreenLevel, m_iBlueLevel, m_iOpacity };
	DrawManagerSetColour( iRed, iGreen, iBlue, iOpacity );
	this->DrawTriangle2i( iPointOneX, iPointOneY, iPointTwoX, iPointTwoY, iPointThreeX, iPointThreeY, bUseGradient, iHowManyGradients_OutOfTwo );
	DrawManagerSetColour( iCurrentColours[0], iCurrentColours[1], iCurrentColours[2], iCurrentColours[3] );
}



void DrawManager::DrawTriangle2f( float fPointOneX, float fPointOneY, float fPointTwoX, float fPointTwoY, float fPointThreeX, float fPointThreeY, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, unsigned int iOpacity, bool bUseGradient, unsigned int iHowManyGradients_OutOfTwo )
{
	unsigned int iCurrentColours[4] = { m_iRedLevel, m_iGreenLevel, m_iBlueLevel, m_iOpacity };
	DrawManagerSetColour( iRed, iGreen, iBlue, iOpacity );
	this->DrawTriangle2f( fPointOneX, fPointOneY, fPointTwoX, fPointTwoY, fPointThreeX, fPointThreeY, bUseGradient, iHowManyGradients_OutOfTwo );
	DrawManagerSetColour( iCurrentColours[0], iCurrentColours[1], iCurrentColours[2], iCurrentColours[3] );
}



void DrawManager::DrawTriangle2f( Vector2 v2PointOne, Vector2 V2PointTwo, Vector2 v2PointThree, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, unsigned int iOpacity, bool bUseGradient, unsigned int iHowManyGradients_OutOfTwo )
{
	this->DrawTriangle2f( v2PointOne.X, v2PointOne.Y, V2PointTwo.X, V2PointTwo.Y, v2PointThree.X, v2PointThree.Y, iRed, iGreen, iBlue, iOpacity, bUseGradient, iHowManyGradients_OutOfTwo );
}



//////////////////////
// Colour Overloads //
void DrawManager::DrawTriangle2i( int iPointOneX, int iPointOneY, int iPointTwoX, int iPointTwoY, int iPointThreeX, int iPointThreeY, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, bool bUseGradient, unsigned int iHowManyGradients_OutOfTwo )
{
	unsigned int iCurrentColours[3] = { m_iRedLevel, m_iGreenLevel, m_iBlueLevel };
	DrawManagerSetColour( iRed, iGreen, iBlue );
	this->DrawTriangle2i( iPointOneX, iPointOneY, iPointTwoX, iPointTwoY, iPointThreeX, iPointThreeY, bUseGradient, iHowManyGradients_OutOfTwo );
	DrawManagerSetColour( iCurrentColours[0], iCurrentColours[1], iCurrentColours[2] );
}



void DrawManager::DrawTriangle2f( float fPointOneX, float fPointOneY, float fPointTwoX, float fPointTwoY, float fPointThreeX, float fPointThreeY, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, bool bUseGradient, unsigned int iHowManyGradients_OutOfTwo )
{
	unsigned int iCurrentColours[3] = { m_iRedLevel, m_iGreenLevel, m_iBlueLevel };
	DrawManagerSetColour( iRed, iGreen, iBlue );
	this->DrawTriangle2f( fPointOneX, fPointOneY, fPointTwoX, fPointTwoY, fPointThreeX, fPointThreeY, bUseGradient, iHowManyGradients_OutOfTwo );
	DrawManagerSetColour( iCurrentColours[0], iCurrentColours[1], iCurrentColours[2] );
}



void DrawManager::DrawTriangle2f( Vector2 v2PointOne, Vector2 V2PointTwo, Vector2 v2PointThree, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, bool bUseGradient, unsigned int iHowManyGradients_OutOfTwo )
{
	this->DrawTriangle2f( v2PointOne.X, v2PointOne.Y, V2PointTwo.X, V2PointTwo.Y, v2PointThree.X, v2PointThree.Y, iRed, iGreen, iBlue, bUseGradient, iHowManyGradients_OutOfTwo );
}



///////////////////////
// Opacity Overloads // 
void DrawManager::DrawTriangle2i( int iPointOneX, int iPointOneY, int iPointTwoX, int iPointTwoY, int iPointThreeX, int iPointThreeY, unsigned int iOpacity, bool bUseGradient, unsigned int iHowManyGradients_OutOfTwo )
{
	unsigned int iCurrentOpacity = m_iOpacity;
	DrawManagerSetOpacity( iOpacity );
	this->DrawTriangle2i( iPointOneX, iPointOneY, iPointTwoX, iPointTwoY, iPointThreeX, iPointThreeY, bUseGradient, iHowManyGradients_OutOfTwo );
	DrawManagerSetOpacity( iCurrentOpacity );
}



void DrawManager::DrawTriangle2f( float fPointOneX, float fPointOneY, float fPointTwoX, float fPointTwoY, float fPointThreeX, float fPointThreeY, unsigned int iOpacity, bool bUseGradient, unsigned int iHowManyGradients_OutOfTwo )
{
	unsigned int iCurrentOpacity = m_iOpacity;
	DrawManagerSetOpacity( iOpacity );
	this->DrawTriangle2f( fPointOneX, fPointOneY, fPointTwoX, fPointTwoY, fPointThreeX, fPointThreeY, bUseGradient, iHowManyGradients_OutOfTwo );
	DrawManagerSetOpacity( iCurrentOpacity );
}



void DrawManager::DrawTriangle2f( Vector2 v2PointOne, Vector2 V2PointTwo, Vector2 v2PointThree, unsigned int iOpacity, bool bUseGradient, unsigned int iHowManyGradients_OutOfTwo )
{
	this->DrawTriangle2f( v2PointOne.X, v2PointOne.Y, V2PointTwo.X, V2PointTwo.Y, v2PointThree.X, v2PointThree.Y, iOpacity, bUseGradient, iHowManyGradients_OutOfTwo );
}




















//=================================
//	 Draw Quad	
//=================================
void DrawManager::DrawQuad2i( int iXpos, int iYpos, unsigned int iWidth, unsigned int iHeight, bool bUseGradient, unsigned int iHowManyGradients_OutOfThree )
{	
	// Getting the float values of our colour levels
	float fRed		=	m_iRedLevel		* 0.003921f; // <- ( m_iRedLevel / 255 )
	float fGreen	=	m_iGreenLevel	* 0.003921f;
	float fBlue		=	m_iBlueLevel 	* 0.003921f;
	float fOpacity	=	m_iOpacity		* 0.003921f;
	

	// Draw the texture
	glBegin(GL_QUADS);
	
		// Change the colour of the Drawing
		glColor4f( fRed, fGreen, fBlue, fOpacity );

		// Textures Top Left Coords
		glTexCoord2f(m_fUvCoordStartx, m_fUvCoordStarty);
		glVertex2i( iXpos, iYpos);
	

		// Make Upper Right Gradient
		if( bUseGradient && iHowManyGradients_OutOfThree > 1){ glColor4f( fRed * 0.75f, fGreen * 0.75f, fBlue * 0.75f, fOpacity ); }

		// Textures Top Right Coords
		glTexCoord2f(m_fUvCoordEndx, m_fUvCoordStarty);
		glVertex2i( iXpos + iWidth, iYpos);


		// Make Bottom Half Gradient
		if( bUseGradient && iHowManyGradients_OutOfThree > 0){ glColor4f( fRed * 0.5f, fGreen * 0.5f, fBlue * 0.5f, fOpacity ); }

		// Textures Bottom Right Coords
		glTexCoord2f(m_fUvCoordEndx, m_fUvCoordEndy);
		glVertex2i( iXpos + iWidth, iYpos + iHeight);
	

		// Make Lower Left Gradient
		if( bUseGradient && iHowManyGradients_OutOfThree > 2){ glColor4f( fRed * 0.25f, fGreen * 0.25f, fBlue * 0.25f, fOpacity ); }

		// Textures Bottom Left Coords
		glTexCoord2f(m_fUvCoordStartx, m_fUvCoordEndy);
		glVertex2i( iXpos, iYpos + iHeight);

	glEnd();
}



void DrawManager::DrawQuad2f( float fXpos, float fYpos, float fWidth, float fHeight, bool bUseGradient, unsigned int iHowManyGradients_OutOfThree )
{
	// Getting the float values of our colour levels
	float fRed		=	m_iRedLevel		* 0.003921f; // <- ( m_iRedLevel / 255 )
	float fGreen	=	m_iGreenLevel	* 0.003921f;
	float fBlue		=	m_iBlueLevel 	* 0.003921f;
	float fOpacity	=	m_iOpacity		* 0.003921f;
	

	// Draw the texture
	glBegin(GL_QUADS);
	
		// Change the colour of the Drawing
		glColor4f( fRed, fGreen, fBlue, fOpacity );

		// Textures Top Left Coords
		glTexCoord2f(m_fUvCoordStartx, m_fUvCoordStarty);
		glVertex2f( fXpos, fYpos);
	

		// Make Upper Right Gradient
		if( bUseGradient && iHowManyGradients_OutOfThree > 1){ glColor4f( fRed * 0.75f, fGreen * 0.75f, fBlue * 0.75f, fOpacity ); }

		// Textures Top Right Coords
		glTexCoord2f(m_fUvCoordEndx, m_fUvCoordStarty);
		glVertex2f( fXpos + fWidth, fYpos);


		// Make Bottom Half Gradient
		if( bUseGradient && iHowManyGradients_OutOfThree > 0){ glColor4f( fRed * 0.5f, fGreen * 0.5f, fBlue * 0.5f, fOpacity ); }

		// Textures Bottom Right Coords
		glTexCoord2f(m_fUvCoordEndx, m_fUvCoordEndy);
		glVertex2f( fXpos + fWidth, fYpos + fHeight);
	

		// Make Lower Left Gradient
		if( bUseGradient && iHowManyGradients_OutOfThree > 2){ glColor4f( fRed * 0.25f, fGreen * 0.25f, fBlue * 0.25f, fOpacity ); }

		// Textures Bottom Left Coords
		glTexCoord2f(m_fUvCoordStartx, m_fUvCoordEndy);
		glVertex2f( fXpos, fYpos + fHeight);

	glEnd();
}



void DrawManager::DrawQuad2f( Vector2 vObjectPosition, Vector2 vObjectSize, bool bUseGradient, unsigned int iHowManyGradients_OutOfThree )
{
	this->DrawQuad2f( vObjectPosition.X, vObjectPosition.Y, vObjectSize.X, vObjectSize.Y, bUseGradient, iHowManyGradients_OutOfThree );
}



////////////////////////////////
// Colour & Opacity Overloads //
void DrawManager::DrawQuad2i( int iXpos, int iYpos, unsigned int iWidth, unsigned int iHeight, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, unsigned int iOpacity, bool bUseGradient, unsigned int iHowManyGradients_OutOfThree )
{
	unsigned int iCurrentColours[4] = { m_iRedLevel, m_iGreenLevel, m_iBlueLevel, m_iOpacity };
	DrawManagerSetColour( iRed, iGreen, iBlue, iOpacity );
	this->DrawQuad2i( iXpos, iYpos, iWidth, iHeight, bUseGradient, iHowManyGradients_OutOfThree );
	DrawManagerSetColour( iCurrentColours[0], iCurrentColours[1], iCurrentColours[2], iCurrentColours[3] );
}



void DrawManager::DrawQuad2f( float fXpos, float fYpos, float fWidth, float fHeight, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, unsigned int iOpacity, bool bUseGradient, unsigned int iHowManyGradients_OutOfThree  )
{
	unsigned int iCurrentColours[4] = { m_iRedLevel, m_iGreenLevel, m_iBlueLevel, m_iOpacity };
	DrawManagerSetColour( iRed, iGreen, iBlue, iOpacity );
	this->DrawQuad2f( fXpos, fYpos, fWidth, fHeight, bUseGradient, iHowManyGradients_OutOfThree );
	DrawManagerSetColour( iCurrentColours[0], iCurrentColours[1], iCurrentColours[2], iCurrentColours[3] );
}
	


void DrawManager::DrawQuad2f( Vector2 vObjectPosition, Vector2 vObjectSize, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, unsigned int iOpacity, bool bUseGradient, unsigned int iHowManyGradients_OutOfThree )
{
	this->DrawQuad2f( vObjectPosition.X, vObjectPosition.Y, vObjectSize.X, vObjectSize.Y, iRed, iGreen, iBlue, iOpacity, bUseGradient, iHowManyGradients_OutOfThree );
}



//////////////////////
// Colour Overloads	// 
void DrawManager::DrawQuad2i( int iXpos, int iYpos, unsigned int iWidth, unsigned int iHeight, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, bool bUseGradient, unsigned int iHowManyGradients_OutOfThree )
{
	unsigned int iCurrentColours[3] = { m_iRedLevel, m_iGreenLevel, m_iBlueLevel };
	DrawManagerSetColour( iRed, iGreen, iBlue );
	this->DrawQuad2i( iXpos, iYpos, iWidth, iHeight, bUseGradient, iHowManyGradients_OutOfThree );
	DrawManagerSetColour( iCurrentColours[0], iCurrentColours[1], iCurrentColours[2] );
}



void DrawManager::DrawQuad2f( float fXpos, float fYpos, float fWidth, float fHeight, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, bool bUseGradient, unsigned int iHowManyGradients_OutOfThree )
{
	unsigned int iCurrentColours[3] = { m_iRedLevel, m_iGreenLevel, m_iBlueLevel };
	DrawManagerSetColour( iRed, iGreen, iBlue );
	this->DrawQuad2f( fXpos, fYpos, fWidth, fHeight, bUseGradient, iHowManyGradients_OutOfThree );
	DrawManagerSetColour( iCurrentColours[0], iCurrentColours[1], iCurrentColours[2] );
}



void DrawManager::DrawQuad2f( Vector2 vObjectPosition, Vector2 vObjectSize, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, bool bUseGradient, unsigned int iHowManyGradients_OutOfThree )
{
	this->DrawQuad2f( vObjectPosition.X, vObjectPosition.Y, vObjectSize.X, vObjectSize.Y, iRed, iGreen, iBlue, bUseGradient, iHowManyGradients_OutOfThree );
}
	


///////////////////////
// Opacity Overloads //	 
void DrawManager::DrawQuad2i( int iXpos, int iYpos, unsigned int iWidth, unsigned int iHeight, unsigned int iOpacity, bool bUseGradient, unsigned int iHowManyGradients_OutOfThree )
{
	unsigned int iCurrentOpacity = m_iOpacity;
	DrawManagerSetOpacity( iOpacity );
	this->DrawQuad2i( iXpos, iYpos, iWidth, iHeight, bUseGradient, iHowManyGradients_OutOfThree );
	DrawManagerSetOpacity( iCurrentOpacity );
}



void DrawManager::DrawQuad2f( float fXpos, float fYpos, float fWidth, float fHeight, unsigned int iOpacity, bool bUseGradient, unsigned int iHowManyGradients_OutOfThree )
{
	unsigned int iCurrentOpacity = m_iOpacity;
	DrawManagerSetOpacity( iOpacity );
	this->DrawQuad2f( fXpos, fYpos, fWidth, fHeight, bUseGradient, iHowManyGradients_OutOfThree );
	DrawManagerSetOpacity( iCurrentOpacity );
}



void DrawManager::DrawQuad2f( Vector2 vObjectPosition, Vector2 vObjectSize, unsigned int iOpacity, bool bUseGradient, unsigned int iHowManyGradients_OutOfThree )
{
	this->DrawQuad2f( vObjectPosition.X, vObjectPosition.Y, vObjectSize.X, vObjectSize.Y, iOpacity, bUseGradient, iHowManyGradients_OutOfThree );
}