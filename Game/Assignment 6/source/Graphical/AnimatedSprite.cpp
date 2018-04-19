#include "AnimatedSprite.h"

#include "Utility_Functions.h"
#include "DeltaTime.h"
#include "Texture.h"
#include "DrawManager.h"



//=================================
//		Constructors	
//=================================
AnimatedSprite::AnimatedSprite()
{

}

AnimatedSprite::AnimatedSprite( std::string sFilename, std::string sTextureType )
{
	m_iAnimatedSprite_TextureID = Texture::GetInstance()->LoadTexture( sFilename, sTextureType );
}

AnimatedSprite::AnimatedSprite( const unsigned int iTextureID )
{
	m_iAnimatedSprite_TextureID = iTextureID;
}


//=================================
//		Destructor	
//=================================
AnimatedSprite::~AnimatedSprite()
{

}





//=================================
//		OnLoad
//=================================
void AnimatedSprite::OnLoad()
{
	m_iNumLeftAnimFrames = m_iNumRightAnimFrames = m_iCurrentAnimationFrame = 0;
	m_fSecondsToWaitTime = m_fCurrentSecondsTime = 0.f;
	m_sCurrentAnimationDirection = m_sCurrentFacingDirection = "RIGHT";
}


//=================================
//		OnUnload
//=================================
void AnimatedSprite::OnUnload()
{
	m_lAnimFrames.clear();
}




//=================================
//		Reset
//=================================
void AnimatedSprite::Reset()
{
	m_sCurrentAnimationDirection = m_sCurrentFacingDirection = "RIGHT";
	m_iCurrentAnimationFrame = m_iMainRightFrame;
}









//=================================
//	   Setup Animated Sprite
//=================================
void AnimatedSprite::SetupAnimatedSprite( std::list<AnimatedSpriteInfoList> Animated2DList, float fSecondsToWaitInBetweenAnimatons, unsigned int iMainLeftFrame_IfNotAnimating, unsigned int iMainRightFrame_IfNotAnimating, unsigned int iMainUpFrame_IfNotAnimating, unsigned int iMainDownFrame_IfNotAnimating )
{
	int iCurrentLeftDirectionFrame  = 0;
	int iCurrentRightDirectionFrame = 0;
	int iCurrentUpDirectionFrame	= 0;
	int iCurrentDownDirectionFrame  = 0;

	// Iterate through the 2D Array (Lists within a List)
	int iCurrentRow = 0; 
	for( std::list<AnimatedSpriteInfoList>::iterator MasterIterator = Animated2DList.begin(); MasterIterator != Animated2DList.end(); MasterIterator++ )
	{
		int iCurrentCollumn = 0;
		for( std::list<std::string>::iterator SlaveIterator = MasterIterator->DirectionList.begin(); SlaveIterator != MasterIterator->DirectionList.end(); SlaveIterator++)
		{
			std::string sDirection = String_To_UpperCase( *SlaveIterator );

			// No need to create an Animated Frame unless it's a Left or Right Direction Frame
			if( sDirection == "LEFT" || sDirection == "RIGHT" || sDirection == "UP" || sDirection == "DOWN" )
			{
				AnimFrameStruct AnimFrame;
				AnimFrame.sDirection = sDirection;


				if( sDirection == "LEFT" )
				{
					AnimFrame.iFrameIndex = iCurrentLeftDirectionFrame;
					iCurrentLeftDirectionFrame++;
				}
				else if( sDirection == "RIGHT" )
				{
					AnimFrame.iFrameIndex = iCurrentRightDirectionFrame;
					iCurrentRightDirectionFrame++;
				}
				else if( sDirection == "UP" )
				{
					AnimFrame.iFrameIndex = iCurrentUpDirectionFrame;
					iCurrentUpDirectionFrame++;
				}
				else
				{
					AnimFrame.iFrameIndex = iCurrentDownDirectionFrame;
					iCurrentDownDirectionFrame++;
				}

				int iThisListSize = MasterIterator->DirectionList.size();
				// Set the UV Coordinates
				AnimFrame.StartX			= ((float)iCurrentCollumn	/			 (float)iThisListSize			);
				AnimFrame.EndX				= ((AnimFrame.StartX)		+	 (1.f /  (float)iThisListSize			));
				AnimFrame.StartY			= ((float)iCurrentRow       /			 (float)Animated2DList.size()	);
				AnimFrame.EndY				= ((AnimFrame.StartY)		+	 (1.f /  (float)Animated2DList.size()	));


				// Add it to the List
				m_lAnimFrames.push_back( AnimFrame );
			}
			iCurrentCollumn++;
		}
		iCurrentRow++;
	}

	// Set up the Values
	m_iNumLeftAnimFrames	   = iCurrentLeftDirectionFrame;
	m_iNumRightAnimFrames	   = iCurrentRightDirectionFrame;
	m_iMainLeftFrame		   = iMainLeftFrame_IfNotAnimating;
	m_iMainRightFrame		   = iMainRightFrame_IfNotAnimating;
	m_iMainUpFrame			   = iMainUpFrame_IfNotAnimating;
	m_iMainDownFrame		   = iMainDownFrame_IfNotAnimating;
	m_iCurrentAnimationFrame   = m_iMainRightFrame;
	m_fSecondsToWaitTime	   = fSecondsToWaitInBetweenAnimatons;
}







//=================================
//	   Get Facing Direction
//=================================
std::string	AnimatedSprite::GetFacingDirection()
{
	return m_sCurrentFacingDirection;
}
//=================================
//	   Get Animation Direction	
//=================================
std::string	AnimatedSprite::GetAnimationDirection()
{
	return m_sCurrentAnimationDirection;
}
//=================================
//	   Get Animation Frame
//=================================
unsigned int AnimatedSprite::GetCurrentAnimationFrame()
{
	return m_iCurrentAnimationFrame;
}
//=================================
//	   Get Texture ID
//=================================
unsigned int AnimatedSprite::GetCurrentTextureID()
{
	return m_iAnimatedSprite_TextureID;
}




//=================================
//	   Set Facing Direction
//=================================
void AnimatedSprite::SetFacingDirection( std::string a_sDirection )
{
	std::string sDirection = String_To_UpperCase( a_sDirection );

	if( sDirection == "LEFT" || sDirection == "RIGHT" || sDirection == "UP" || sDirection == "DOWN" )
	{
		m_sCurrentFacingDirection = sDirection;
	}
}
//=================================
//	   Set Animation Direction	
//=================================
void AnimatedSprite::SetAnimationDirection( std::string a_sDirection )
{
	std::string sDirection = String_To_UpperCase( a_sDirection );

	if( sDirection == "LEFT" || sDirection == "RIGHT" )
	{
		m_sCurrentAnimationDirection = sDirection;
	}
}
//=================================
//	  Set Current Animation Frame
//=================================
void AnimatedSprite::SetCurrentAnimationFrame(std::string a_sDirection, unsigned int iFrame )
{
	std::string sDirection = String_To_UpperCase( a_sDirection );

	if( sDirection == "LEFT" || sDirection == "RIGHT" || sDirection == "UP" || sDirection == "DOWN" )
	{
		m_sCurrentFacingDirection = sDirection;
		m_iCurrentAnimationFrame = iFrame;
	}
}
//=================================
//	  Set Current Animation Frame
//=================================
void AnimatedSprite::SetCurrentAnimationTime( float fAnimationTime )
{
	if( fAnimationTime < 0.0f ) { return; }

	m_fCurrentSecondsTime = fAnimationTime;
}
//=================================
// Set Current Animation Wait Time
//=================================
void AnimatedSprite::SetCurrentAnimationWaitTime( float fAnimationWaitTime )
{
	if( fAnimationWaitTime < 0.0f ) { return; }

	m_fSecondsToWaitTime = fAnimationWaitTime;
}
//=================================
//	  Set Current Texture
//=================================
void AnimatedSprite::SetCurrentTexture( unsigned int uiTextureID )
{
	m_iAnimatedSprite_TextureID = uiTextureID;
}

void AnimatedSprite::SetCurrentTexture( std::string sFilename, std::string sTextureType )
{
	m_iAnimatedSprite_TextureID = Texture::GetInstance()->LoadTexture( sFilename, sTextureType );
}





void AnimatedSprite::Update( bool bUpdateTime_WithDT, float fUpdateTime_IncrementValue )
{
	////////////////////////////////////////////////////
	if( bUpdateTime_WithDT )
	{
		m_fCurrentSecondsTime += DeltaTime::GetInstance()->GetDeltaTime();
	}

	m_fCurrentSecondsTime += fUpdateTime_IncrementValue;
	////////////////////////////////////////////////////

	if( m_fCurrentSecondsTime >= m_fSecondsToWaitTime )
	{
		for( std::list<AnimFrameStruct>::iterator iter = m_lAnimFrames.begin(); iter != m_lAnimFrames.end(); iter++ )
		{
			// Find the next Frame in the Animation Queue
			if( iter->sDirection == m_sCurrentFacingDirection ) 
			{
				if( ((m_sCurrentAnimationDirection == "RIGHT") && (iter->iFrameIndex > m_iCurrentAnimationFrame))		||
					((m_sCurrentAnimationDirection == "LEFT")  && (iter->iFrameIndex == (m_iCurrentAnimationFrame - 1))) )
				{
					m_iCurrentAnimationFrame = iter->iFrameIndex;
					m_fCurrentSecondsTime = 0.f;
					return;
				}

			}
		}

		// Otherwise if one cannot be found, then reset the the current frame to the front of the queue
		if( m_sCurrentAnimationDirection == "RIGHT" )
		{
			m_iCurrentAnimationFrame = 0;
		}
		else
		{
			m_iCurrentAnimationFrame = m_iNumLeftAnimFrames;
		}

		m_fCurrentSecondsTime = 0.f;
	}
}


void AnimatedSprite::Draw( float fXpos, float fYpos, float fWidth, float fHeight, bool bUseGradient, unsigned int iHowManyGradients_OutOfThree )
{
	for( std::list<AnimFrameStruct>::iterator iter = m_lAnimFrames.begin(); iter != m_lAnimFrames.end(); iter++ )
	{
		if( (iter->sDirection == m_sCurrentFacingDirection) && (iter->iFrameIndex == m_iCurrentAnimationFrame) )
		{
			float* UV_Coords = new float[4];
			UV_Coords[0] = iter->StartX; UV_Coords[1] = iter->StartY; UV_Coords[2] = iter->EndX; UV_Coords[3] = iter->EndY;

			DrawManager::GetInstance()->DrawTexturef( fXpos, fYpos, fWidth, fHeight, m_iAnimatedSprite_TextureID, bUseGradient, iHowManyGradients_OutOfThree, UV_Coords );
			break;
		}
	}
}