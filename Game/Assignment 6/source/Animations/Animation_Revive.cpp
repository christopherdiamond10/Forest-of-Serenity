#include "Animation_Revive.h"


#include "AudioManager.h"
#include "DeltaTime.h"




Animation_Revive::Animation_Revive( Vector2 vAnimLocation, unsigned int iAnimID ) : AnimatedSprite( "Heal3.png", "Animation" )
	,	CONST_D_ONE_FRAME_OUT_OF_SIXTY	( 1.0 / 60.0 )
{
	/////////////////////////////////////////
	AudioManager::GetInstance()->ImportAudio( "Saint7.ogg", "Saint7", "SE" );
	AudioManager::GetInstance()->ImportAudio( "Flash3.ogg", "Flash3", "SE" );
	/////////////////////////////////////////
	m_v2AnimationLocation = vAnimLocation;
	m_iSelf_AnimationID	  = iAnimID;
	/////////////////////////////////////////
	SetupSelf();
	SetupAnimatedSprite();
	/////////////////////////////////////////
}

Animation_Revive::~Animation_Revive()
{
	AnimatedSprite::OnUnload();
}

void Animation_Revive::SetupSelf()
{
	m_iCurrentFrame = 0;
	m_fCurrentTime = 0.f;
	
	for( int i = 0; i < 20; i++ )
	{
		m_bCompletedFrame[i] = false;
	}

	m_v2ExtraAnimationOnePosition    = Vector2( 0, 0 );
	m_v2ExtraAnimationTwoPosition    = Vector2( 0, 0 );
	m_v2ExtraAnimationThreePosition  = Vector2( 0, 0 );
}


void Animation_Revive::SetupAnimatedSprite()
{
	//////////////////////////////////////////////////////////////
	AnimatedSprite::OnLoad();
	//////////////////////////////////////////////////////////////
	std::list<AnimatedSpriteInfoList>  Animated2DList;
	AnimatedSpriteInfoList			   RowOne, RowTwo, RowThree, RowFour, RowFive, RowSix;
	//////////////////////////////////////////////////////////////
	RowOne.DirectionList.push_back(	  "Left"  );		RowOne.DirectionList.push_back(   "Left"  );		RowOne.DirectionList.push_back(   "Left"  );		RowOne.DirectionList.push_back(   "Left"  );		RowOne.DirectionList.push_back(   "Left"  );
	RowTwo.DirectionList.push_back(   "Left"  );		RowTwo.DirectionList.push_back(   "Left"  );		RowTwo.DirectionList.push_back(   "Left"  );		RowTwo.DirectionList.push_back(   "Left"  );		RowTwo.DirectionList.push_back(   "Left"  );		
	RowThree.DirectionList.push_back( "Left"  );	    RowThree.DirectionList.push_back( "Left"  );	    RowThree.DirectionList.push_back( "Left"  );	    RowThree.DirectionList.push_back( "Left"  );	    RowThree.DirectionList.push_back( "Left"  );	    
	RowFour.DirectionList.push_back(  "Left"  );		RowFour.DirectionList.push_back(  "Left"  );		RowFour.DirectionList.push_back(  "Left"  );		RowFour.DirectionList.push_back(  "Left"  );		RowFour.DirectionList.push_back(  "Left"  );	
	RowFive.DirectionList.push_back(  "Left"  );		RowFive.DirectionList.push_back(  "Left"  );		RowFive.DirectionList.push_back(  "Left"  );		RowFive.DirectionList.push_back(  "Left"  );		RowFive.DirectionList.push_back(  "Left"  );		
	RowSix.DirectionList.push_back(   "Left"  );		RowSix.DirectionList.push_back(   "Left"  );		RowSix.DirectionList.push_back(   "Left"  );		RowSix.DirectionList.push_back(   "Left"  );		RowSix.DirectionList.push_back(   "Left"  );		
	//////////////////////////////////////////////////////////////
	Animated2DList.push_back( RowOne );		Animated2DList.push_back( RowTwo );		Animated2DList.push_back( RowThree );	Animated2DList.push_back( RowFour );	Animated2DList.push_back( RowFive );	Animated2DList.push_back( RowSix );	
	//////////////////////////////////////////////////////////////
	float fSecondsToWaitForUpdate = (float)CONST_D_ONE_FRAME_OUT_OF_SIXTY;
	//////////////////////////////////////////////////////////////
	AnimatedSprite::SetupAnimatedSprite( Animated2DList, fSecondsToWaitForUpdate );
	//////////////////////////////////////////////////////////////
}




bool Animation_Revive::Get_IsPartiallyCompleted()
{
	return m_bCompletedFrame[16];
}
bool Animation_Revive::Get_IsCompleted()
{
	return m_bCompletedFrame[19];
}


void Animation_Revive::Update()
{
	m_fCurrentTime += DeltaTime::GetInstance()->GetDeltaTime();

	UpdateSelf();
	UpdateAnimatedSprite();
}

void Animation_Revive::UpdateSelf()
{
	if( (m_fCurrentTime >= CONST_D_ONE_FRAME_OUT_OF_SIXTY) && (m_iCurrentFrame < 20) )
	{
		m_fCurrentTime = 0;
		m_iCurrentFrame++;
		m_bCompletedFrame[m_iCurrentFrame] = true;

		if( m_iCurrentFrame == 1 )
		{
			AudioManager::GetInstance()->PlaySound( "Saint7" );
		}
		else if( m_iCurrentFrame == 10 )
		{
			AudioManager::GetInstance()->PlaySound( "Flash3" );
		}
	}
}

void Animation_Revive::UpdateAnimatedSprite()
{
	if( m_iCurrentFrame == 1 )
	{
		AnimatedSprite::SetCurrentAnimationFrame( "Left", 0 );
	}
	else if( m_iCurrentFrame == 1 )
	{
		AnimatedSprite::SetCurrentAnimationFrame( "Left", 1 );
	}
	else if( m_iCurrentFrame == 1 )
	{
		AnimatedSprite::SetCurrentAnimationFrame( "Left", 2 );
	}
	else if( m_iCurrentFrame == 1 )
	{
		AnimatedSprite::SetCurrentAnimationFrame( "Left", 3 );
	}
}

void Animation_Revive::Draw( Vector2 vCamPosition )
{
	AnimatedSprite::Draw( m_v2AnimationLocation.X, m_v2AnimationLocation.Y, 32.f, 32.f );
}

