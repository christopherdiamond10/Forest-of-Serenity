//\====================================================================================
//\ Author: Christopher Diamond
//\ About : AnimatedSprite.h - 
//\ 
//\ Defines the AnimatedSprite Class. This class is used to handle the animations of 
//\ SpriteSheets, it does not handle gif files.
//\====================================================================================
#ifndef _ANIMATEDSPRITE_H_
#define _ANIMATEDSPRITE_H_

#include <list>
#include <string>

struct AnimatedSpriteInfoList
{
	std::list<std::string> DirectionList;
};

struct AnimFrameStruct
{
	std::string sDirection;
	unsigned int iFrameIndex;
	
	// UV Coords
	float StartX, StartY, EndX, EndY;
};

class AnimatedSprite
{
public:

	AnimatedSprite();
	AnimatedSprite( std::string sFilename, std::string sTextureType );
	AnimatedSprite( const unsigned int iTextureID );

	~AnimatedSprite();

	void			OnLoad();
	void			OnUnload();
	
	void			Update( bool bUpdateTime_WithDT = true, float fUpdateTime_IncrementValue = 0.f );
	void			Reset();

	void			Draw( float fXpos, float fYpos, float fWidth, float fHeight, bool bUseGradient = true, unsigned int iHowManyGradients_OutOfThree = 1 );

	void SetupAnimatedSprite( std::list<AnimatedSpriteInfoList> Animated2DList, float fSecondsToWaitInBetweenAnimatons, unsigned int iMainLeftFrame_IfNotAnimating = 0, unsigned int iMainRightFrame_IfNotAnimating = 0, unsigned int iMainUpFrame_IfNotAnimating = 0, unsigned int iMainDownFrame_IfNotAnimating = 0 );

	
	std::string		GetFacingDirection();
	std::string		GetAnimationDirection();
	unsigned int	GetCurrentAnimationFrame();
	unsigned int	GetCurrentTextureID();


	void			SetFacingDirection( std::string a_sDirection );
	void			SetAnimationDirection( std::string a_sDirection );
	void			SetCurrentAnimationFrame( std::string sDirection, unsigned int iFrame );
	void			SetCurrentAnimationTime( float fAnimationTime );
	void			SetCurrentAnimationWaitTime( float fAnimationWaitTime );
	void			SetCurrentTexture( unsigned int uiTextureID );
	void			SetCurrentTexture( std::string sFilename, std::string sTextureType );

protected:

	unsigned int	m_iAnimatedSprite_TextureID;
	unsigned int	m_iNumLeftAnimFrames;
	unsigned int	m_iNumRightAnimFrames;
	unsigned int	m_iMainLeftFrame;
	unsigned int	m_iMainRightFrame;
	unsigned int	m_iMainUpFrame;
	unsigned int	m_iMainDownFrame;
	unsigned int	m_iCurrentAnimationFrame;
	std::string		m_sCurrentFacingDirection;
	std::string		m_sCurrentAnimationDirection;
	float			m_fSecondsToWaitTime;
	float			m_fCurrentSecondsTime;

private:

	std::list<AnimFrameStruct>	m_lAnimFrames;

};


#endif