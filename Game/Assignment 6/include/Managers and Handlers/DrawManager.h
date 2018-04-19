#ifndef _DRAWMANAGER_H_
#define _DRAWMANAGER_H_


#include "Vector2.h"
#include <string>
#include <list>



struct i_XY_Coords { int X, Y; };
struct f_XY_Coords { float X, Y; };




class DrawManager
{
////////////////////////////////////////////////////////////
public:
////////////////////////////////////////////////////////////

	DrawManager();
	~DrawManager();

	static DrawManager* GetInstance();

	void OnLoad();
	void OnUnload();

	void LoadSpriteTexture( std::string Filename, std::string TextureType );


	//===================================
	//			Draw Point
	//===================================
	// Colour & Opacity Overloads
	void DrawPoint2i( int iPosX, int iPosY, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, unsigned int iOpacity );
	void DrawPoint2f( float fPosX, float fPosY, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, unsigned int iOpacity );
	void DrawPoint2f( Vector2 v2PointPos, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, unsigned int iOpacity );

	// Colour Overloads
	void DrawPoint2i( int iPosX, int iPosY, unsigned int iRed, unsigned int iGreen, unsigned int iBlue );
	void DrawPoint2f( float fPosX, float fPosY, unsigned int iRed, unsigned int iGreen, unsigned int iBlue );
	void DrawPoint2f( Vector2 v2PointPos, unsigned int iRed, unsigned int iGreen, unsigned int iBlue );

	// Opacity Overloads
	void DrawPoint2i( int iPosX, int iPosY, unsigned int iOpacity );
	void DrawPoint2f( float fPosX, float fPosY, unsigned int iOpacity );
	void DrawPoint2f( Vector2 v2PointPos, unsigned int iOpacity );

	// Regular Position Overloads
	void DrawPoint2i( int iPosX, int iPosY );
	void DrawPoint2f( float fPosX, float fPosY );
	void DrawPoint2f( Vector2 v2PointPos );





	//===================================
	//			Draw Line
	//===================================
	// Colour & Opacity Overloads
	void DrawLine2i( int iStartX, int iStartY, int iEndX, int iEndY, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, unsigned int iOpacity );
	void DrawLine2f( float fStartX, float fStartY, float fEndX, float fEndY, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, unsigned int iOpacity );
	void DrawLine2f( Vector2 v2LineStartPos, Vector2 v2LineEndPos, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, unsigned int iOpacity );

	// Colour Overloads
	void DrawLine2i( int iStartX, int iStartY, int iEndX, int iEndY, unsigned int iRed, unsigned int iGreen, unsigned int iBlue );
	void DrawLine2f( float fStartX, float fStartY, float fEndX, float fEndY, unsigned int iRed, unsigned int iGreen, unsigned int iBlue );
	void DrawLine2f( Vector2 v2LineStartPos, Vector2 v2LineEndPos, unsigned int iRed, unsigned int iGreen, unsigned int iBlue );

	// Opacity Overloads
	void DrawLine2i( int iStartX, int iStartY, int iEndX, int iEndY, unsigned int iOpacity );
	void DrawLine2f( float fStartX, float fStartY, float fEndX, float fEndY, unsigned int iOpacity );
	void DrawLine2f( Vector2 v2LineStartPos, Vector2 v2LineEndPos, unsigned int iOpacity );

	// Regular Position Overloads
	void DrawLine2i( int iStartX, int iStartY, int iEndX, int iEndY );
	void DrawLine2f( float fStartX, float fStartY, float fEndX, float fEndY );
	void DrawLine2f( Vector2 v2LineStartPos, Vector2 v2LineEndPos );




	//===================================
	//			Draw LineStrip
	//===================================
	// Colour & Opacity Overloads
	void DrawLineStrip2i( std::list<i_XY_Coords> PosList, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, unsigned int iOpacity );
	void DrawLineStrip2f( std::list<f_XY_Coords> PosList, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, unsigned int iOpacity );
	void DrawLineStrip2f( std::list<Vector2> PosList, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, unsigned int iOpacity );

	// Colour Overloads
	void DrawLineStrip2i( std::list<i_XY_Coords> PosList, unsigned int iRed, unsigned int iGreen, unsigned int iBlue );
	void DrawLineStrip2f( std::list<f_XY_Coords> PosList, unsigned int iRed, unsigned int iGreen, unsigned int iBlue );
	void DrawLineStrip2f( std::list<Vector2> PosList, unsigned int iRed, unsigned int iGreen, unsigned int iBlue );

	// Opacity Overloads
	void DrawLineStrip2i( std::list<i_XY_Coords> PosList, unsigned int iOpacity );
	void DrawLineStrip2f( std::list<f_XY_Coords> PosList, unsigned int iOpacity );
	void DrawLineStrip2f( std::list<Vector2> PosList, unsigned int iOpacity );

	// Regular Position Overloads
	void DrawLineStrip2i( std::list<i_XY_Coords> PosList );
	void DrawLineStrip2f( std::list<f_XY_Coords> PosList );
	void DrawLineStrip2f( std::list<Vector2> PosList );




	//===================================
	//			Draw LineLoop
	//===================================
	// Colour & Opacity Overloads
	void DrawLineLoop2i( std::list<i_XY_Coords> PosList, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, unsigned int iOpacity );
	void DrawLineLoop2f( std::list<f_XY_Coords> PosList, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, unsigned int iOpacity );
	void DrawLineLoop2f( std::list<Vector2> PosList, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, unsigned int iOpacity );

	// Colour Overloads
	void DrawLineLoop2i( std::list<i_XY_Coords> PosList, unsigned int iRed, unsigned int iGreen, unsigned int iBlue );
	void DrawLineLoop2f( std::list<f_XY_Coords> PosList, unsigned int iRed, unsigned int iGreen, unsigned int iBlue );
	void DrawLineLoop2f( std::list<Vector2> PosList, unsigned int iRed, unsigned int iGreen, unsigned int iBlue );

	// Opacity Overloads
	void DrawLineLoop2i( std::list<i_XY_Coords> PosList, unsigned int iOpacity );
	void DrawLineLoop2f( std::list<f_XY_Coords> PosList, unsigned int iOpacity );
	void DrawLineLoop2f( std::list<Vector2> PosList, unsigned int iOpacity );

	// Regular Position Overloads
	void DrawLineLoop2i( std::list<i_XY_Coords> PosList );
	void DrawLineLoop2f( std::list<f_XY_Coords> PosList );
	void DrawLineLoop2f( std::list<Vector2> PosList );





	//===================================
	//			Draw Polygon
	//===================================
	// Colour & Opacity Overloads
	void DrawPolygon2i( std::list<i_XY_Coords> PosList, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, unsigned int iOpacity );
	void DrawPolygon2f( std::list<f_XY_Coords> PosList, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, unsigned int iOpacity );
	void DrawPolygon2f( std::list<Vector2> PosList, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, unsigned int iOpacity );

	// Colour Overloads
	void DrawPolygon2i( std::list<i_XY_Coords> PosList, unsigned int iRed, unsigned int iGreen, unsigned int iBlue );
	void DrawPolygon2f( std::list<f_XY_Coords> PosList, unsigned int iRed, unsigned int iGreen, unsigned int iBlue );
	void DrawPolygon2f( std::list<Vector2> PosList, unsigned int iRed, unsigned int iGreen, unsigned int iBlue );

	// Opacity Overloads
	void DrawPolygon2i( std::list<i_XY_Coords> PosList, unsigned int iOpacity );
	void DrawPolygon2f( std::list<f_XY_Coords> PosList, unsigned int iOpacity );
	void DrawPolygon2f( std::list<Vector2> PosList, unsigned int iOpacity );

	// Regular Position Overloads
	void DrawPolygon2i( std::list<i_XY_Coords> PosList );
	void DrawPolygon2f( std::list<f_XY_Coords> PosList );
	void DrawPolygon2f( std::list<Vector2> PosList );





	//===================================
	//			Draw Triangle
	//===================================
	// Colour & Opacity Overloads
	void DrawTriangle2i( int iPointOneX, int iPointOneY, int iPointTwoX, int iPointTwoY, int iPointThreeX, int iPointThreeY, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, unsigned int iOpacity, bool bUseGradient, unsigned int iHowManyGradients_OutOfTwo = 1 );
	void DrawTriangle2f( float fPointOneX, float fPointOneY, float fPointTwoX, float fPointTwoY, float fPointThreeX, float fPointThreeY, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, unsigned int iOpacity, bool bUseGradient = true, unsigned int iHowManyGradients_OutOfTwo = 1 );
	void DrawTriangle2f( Vector2 v2PointOne, Vector2 V2PointTwo, Vector2 v2PointThree, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, unsigned int iOpacity, bool bUseGradient, unsigned int iHowManyGradients_OutOfTwo = 1 );
					 
	// Colour Overloads	 
	void DrawTriangle2i( int iPointOneX, int iPointOneY, int iPointTwoX, int iPointTwoY, int iPointThreeX, int iPointThreeY, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, bool bUseGradient, unsigned int iHowManyGradients_OutOfTwo = 1 );
	void DrawTriangle2f( float fPointOneX, float fPointOneY, float fPointTwoX, float fPointTwoY, float fPointThreeX, float fPointThreeY, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, bool bUseGradient, unsigned int iHowManyGradients_OutOfTwo = 1 );
	void DrawTriangle2f( Vector2 v2PointOne, Vector2 V2PointTwo, Vector2 v2PointThree, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, bool bUseGradient, unsigned int iHowManyGradients_OutOfTwo = 1 );
					 
	// Opacity Overloads	 
	void DrawTriangle2i( int iPointOneX, int iPointOneY, int iPointTwoX, int iPointTwoY, int iPointThreeX, int iPointThreeY, unsigned int iOpacity, bool bUseGradient, unsigned int iHowManyGradients_OutOfTwo = 1 );
	void DrawTriangle2f( float fPointOneX, float fPointOneY, float fPointTwoX, float fPointTwoY, float fPointThreeX, float fPointThreeY, unsigned int iOpacity, bool bUseGradient, unsigned int iHowManyGradients_OutOfTwo = 1 );
	void DrawTriangle2f( Vector2 v2PointOne, Vector2 V2PointTwo, Vector2 v2PointThree, unsigned int iOpacity, bool bUseGradient, unsigned int iHowManyGradients_OutOfTwo = 1 );
	
	// Regular Size Dimension Overloads
	void DrawTriangle2i( int iPointOneX, int iPointOneY, int iPointTwoX, int iPointTwoY, int iPointThreeX, int iPointThreeY, bool bUseGradient, unsigned int iHowManyGradients_OutOfTwo = 1 );
	void DrawTriangle2f( float fPointOneX, float fPointOneY, float fPointTwoX, float fPointTwoY, float fPointThreeX, float fPointThreeY, bool bUseGradient, unsigned int iHowManyGradients_OutOfTwo = 1 );
	void DrawTriangle2f( Vector2 v2PointOne, Vector2 V2PointTwo, Vector2 v2PointThree, bool bUseGradient, unsigned int iHowManyGradients_OutOfTwo = 1 );





	//===================================
	//			Draw Quad
	//===================================
	// Colour & Opacity Overloads
	void DrawQuad2i( int iXpos, int iYpos, unsigned int iWidth, unsigned int iHeight, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, unsigned int iOpacity, bool bUseGradient, unsigned int iHowManyGradients_OutOfThree = 1 );
	void DrawQuad2f( float fXpos, float fYpos, float fWidth, float fHeight, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, unsigned int iOpacity, bool bUseGradient = true, unsigned int iHowManyGradients_OutOfThree = 1 );
	void DrawQuad2f( Vector2 vObjectPosition, Vector2 vObjectSize, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, unsigned int iOpacity, bool bUseGradient, unsigned int iHowManyGradients_OutOfThree = 1 );
					 
	// Colour Overloads	 
	void DrawQuad2i( int iXpos, int iYpos, unsigned int iWidth, unsigned int iHeight, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, bool bUseGradient, unsigned int iHowManyGradients_OutOfThree = 1 );
	void DrawQuad2f( float fXpos, float fYpos, float fWidth, float fHeight, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, bool bUseGradient, unsigned int iHowManyGradients_OutOfThree = 1 );
	void DrawQuad2f( Vector2 vObjectPosition, Vector2 vObjectSize, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, bool bUseGradient, unsigned int iHowManyGradients_OutOfThree = 1 );
					 
	// Opacity Overloads	 
	void DrawQuad2i( int iXpos, int iYpos, unsigned int iWidth, unsigned int iHeight, unsigned int iOpacity, bool bUseGradient, unsigned int iHowManyGradients_OutOfThree = 1 );
	void DrawQuad2f( float fXpos, float fYpos, float fWidth, float fHeight, unsigned int iOpacity, bool bUseGradient, unsigned int iHowManyGradients_OutOfThree = 1 );
	void DrawQuad2f( Vector2 vObjectPosition, Vector2 vObjectSize, unsigned int iOpacity, bool bUseGradient, unsigned int iHowManyGradients_OutOfThree = 1 );
	
	// Regular Size Dimension Overloads
	void DrawQuad2i( int iXpos, int iYpos, unsigned int iWidth, unsigned int iHeight, bool bUseGradient, unsigned int iHowManyGradients_OutOfThree = 1 );
	void DrawQuad2f( float fXpos, float fYpos, float fWidth, float fHeight, bool bUseGradient, unsigned int iHowManyGradients_OutOfThree = 1 );
	void DrawQuad2f( Vector2 vObjectPosition, Vector2 vObjectSize, bool bUseGradient, unsigned int iHowManyGradients_OutOfThree = 1 );





	//===================================
	//			Draw Texture
	//===================================
	// Colour & Opacity Overloads
	void DrawTexturei( int iXpos, int iYpos, unsigned int iWidth, unsigned int iHeight, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, unsigned int iOpacity, unsigned int iTextureID, bool bUseGradient, unsigned int iHowManyGradients_OutOfThree = 1, float* UV_Coords = nullptr );
	void DrawTexturef( Vector2 vObjectPosition, Vector2 vObjectSize, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, unsigned int iOpacity, unsigned int iTextureID, bool bUseGradient, unsigned int iHowManyGradients_OutOfThree = 1, float* UV_Coords = nullptr );
	void DrawTexturef( float fXpos, float fYpos, float fWidth, float fHeight, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, unsigned int iOpacity, unsigned int iTextureID, bool bUseGradient, unsigned int iHowManyGradients_OutOfThree = 1, float* UV_Coords = nullptr );
					 
	// Colour Overloads	 
	void DrawTexturei( int iXpos, int iYpos, unsigned int iWidth, unsigned int iHeight, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, unsigned int iTextureID, bool bUseGradient, unsigned int iHowManyGradients_OutOfThree = 1, float* UV_Coords = nullptr );
	void DrawTexturef( Vector2 vObjectPosition, Vector2 vObjectSize, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, unsigned int iTextureID, bool bUseGradient, unsigned int iHowManyGradients_OutOfThree = 1, float* UV_Coords = nullptr );
	void DrawTexturef( float fXpos, float fYpos, float fWidth, float fHeight, unsigned int iRed, unsigned int iGreen, unsigned int iBlue, unsigned int iTextureID, bool bUseGradient, unsigned int iHowManyGradients_OutOfThree = 1, float* UV_Coords = nullptr );
					 
	// Opacity Overloads	 
	void DrawTexturei( int iXpos, int iYpos, unsigned int iWidth, unsigned int iHeight, unsigned int iOpacity, unsigned int iTextureID, bool bUseGradient, unsigned int iHowManyGradients_OutOfThree = 1, float* UV_Coords = nullptr );
	void DrawTexturef( Vector2 vObjectPosition, Vector2 vObjectSize, unsigned int iOpacity, unsigned int iTextureID, bool bUseGradient, unsigned int iHowManyGradients_OutOfThree = 1, float* UV_Coords = nullptr );
	void DrawTexturef( float fXpos, float fYpos, float fWidth, float fHeight, unsigned int iOpacity, unsigned int iTextureID, bool bUseGradient, unsigned int iHowManyGradients_OutOfThree = 1, float* UV_Coords = nullptr );
	
	// Regular Size Dimension Overloads
	void DrawTexturei( int iXpos, int iYpos, unsigned int iWidth, unsigned int iHeight, unsigned int iTextureID, bool bUseGradient, unsigned int iHowManyGradients_OutOfThree = 1, float* UV_Coords = nullptr );
	void DrawTexturef( Vector2 vObjectPosition, Vector2 vObjectSize, unsigned int iTextureID, bool bUseGradient, unsigned int iHowManyGradients_OutOfThree = 1, float* UV_Coords = nullptr );
	void DrawTexturef( float fXpos, float fYpos, float fWidth, float fHeight, unsigned int iTextureID, bool bUseGradient, unsigned int iHowManyGradients_OutOfThree = 1, float* UV_Coords = nullptr );





	





	





	




	
	


	//=======================================
	//				Getters
	//=======================================
	unsigned int	GetTextureID();

	


////////////////////////////////////////////////////////////
private: 
////////////////////////////////////////////////////////////	


	void			DrawManagerSetColour( unsigned int iRed, unsigned int iGreen, unsigned int iBlue, unsigned int iOpacity );
	void			DrawManagerSetColour( unsigned int iRed, unsigned int iGreen, unsigned int iBlue );
	void			DrawManagerSetOpacity( unsigned int iOpacity );
	void			DrawManagerSetUVCoordinates( float fStartX = 0.f, float fStartY = 0.f, float fEndX = 1.f, float fEndY = 1.f );




	float			m_fUvCoordStartx;
	float			m_fUvCoordStarty;
	float			m_fUvCoordEndx;
	float			m_fUvCoordEndy;

	unsigned int	m_iRedLevel;	// Out of 255
	unsigned int	m_iGreenLevel; // Out of 255
	unsigned int	m_iBlueLevel; // Out of 255
	unsigned int	m_iOpacity;	 // Out of 255	




	static DrawManager* m_Instance;

};




#endif