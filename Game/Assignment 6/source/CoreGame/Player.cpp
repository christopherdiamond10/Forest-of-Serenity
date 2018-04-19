#include "Player.h"

#include "AnimationHandler.h"
#include "AudioManager.h"
#include "InputHandler.h"
#include "CollisionHandler.h"
#include "DeltaTime.h"
#include "GameSystemInfo.h"
#include <string>


//===============================================
//	Constructor
//===============================================
Player::Player() : AnimatedSprite( "Nino_Sprite.png", "Sprite" )
{

}


//===============================================
//	Destructor
//===============================================
Player::~Player()
{

}



//===============================================
//	OnLoad
//===============================================
void Player::OnLoad()
{
	m_sCurrentPlayerName = "NINO";

	SetupAnimation();
	Reset();

	AudioManager::GetInstance()->ImportAudio( "Fall.ogg", "Fall_SE", "SE" );
	AudioManager::GetInstance()->ImportAudio( "Pick_Up_Diamond.ogg", "Pick_Up_Diamond", "SE" );
}


//===============================================
//	OnUnload
//===============================================
void Player::OnUnload()
{
	AnimatedSprite::OnUnload();
}





//===============================================
//	Setup Animation
//===============================================
void Player::SetupAnimation()
{
	//////////////////////////////////////////////////////////////
	AnimatedSprite::OnLoad();
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
	unsigned int iMainLeftFrame   = 1;
	unsigned int iMainRightFrame  = 1;
	unsigned int iMainUpFrame	  = 1;
	unsigned int iMainDownFrame	  = 1;
	float fSecondsToWaitForUpdate = 0.20f;
	//////////////////////////////////////////////////////////////
	AnimatedSprite::SetupAnimatedSprite( Animated2DList, fSecondsToWaitForUpdate, iMainLeftFrame, iMainRightFrame, iMainUpFrame, iMainDownFrame );
	//////////////////////////////////////////////////////////////
}


//===============================================
//	Setup Player
//===============================================
void Player::Reset()
{
	//////////////////////////////////////////////////////////////
	m_sPlayerFacingDirection				= "RIGHT";
	m_sCurrentPlayerName					= GameSystemInfo::GetInstance()->GetCurrentCharacter();
	//////////////////////////////////////////////////////////////
	if		(m_sCurrentPlayerName == "RITA")	{ AnimatedSprite::SetCurrentTexture("Rita_Sprite.png",  "Sprite"); }
	else if	(m_sCurrentPlayerName == "EMILY")	{ AnimatedSprite::SetCurrentTexture("Emily_Sprite.png", "Sprite"); }
	else										{ AnimatedSprite::SetCurrentTexture("Nino_Sprite.png",  "Sprite"); }
	//////////////////////////////////////////////////////////////
	m_v2PlayerPos							= CollisionHandler::GetInstance()->GetReservedPosition();
	m_v2PlayerSize.X						= 32.f;
	m_v2PlayerSize.Y						= 32.f;
	m_v2PlayerDead							= m_v2PlayerPos;
	//////////////////////////////////////////////////////////////
	m_bAlive								= true;
	m_bJumping								= false;
	m_bMoving								= false; 
	m_bRunning								= false;
	m_bUsingMagic							= false;
	m_bPlayingReviveAnimation				= false;
	m_bPlayingMagicAnimation				= false;
	m_bPlayLevelCompleteSequence			= false;
	m_bCompletedLevel						= false;
	//////////////////////////////////////////////////////////////
	m_fDefaultGravity						= DeltaTime::GetInstance()->GetDeltaTimeNormalisedValue( 9.0f );
	m_fDefaultJumpVel						= DeltaTime::GetInstance()->GetDeltaTimeNormalisedValue( 4.5f );
	m_fMaxSpeed								= 240.f;
	
	m_fJumpVel								= m_fDefaultJumpVel;
	m_fSpeed								= 0.f;
	m_fGravity								= m_fDefaultGravity;
	m_fCompleteLevelSequenceCurrentTime		= 0.f;
	//////////////////////////////////////////////////////////////
	m_fCurrentHealth						= 100.f;
	m_fCurrentMagic							= 100.f;
	m_iCurrentScore							= 0;
	m_iAnimationID							= 0;
}









//===============================================
//	Getters
//===============================================
Vector2 Player::GetPlayerPos()
{
	if(m_bAlive)
		return m_v2PlayerPos;
	else
		return m_v2PlayerDead;
}

std::string Player::GetCurrentPlayerName()
{
	return m_sCurrentPlayerName;
}

std::string Player::GetPlayerDirectionFacing()
{
	return m_sPlayerFacingDirection;
}

bool Player::Get_IsUsingMagic()
{
	return m_bUsingMagic;
}

bool Player::Get_HasCompletedLevel()
{
	return m_bCompletedLevel;
}

float Player::GetPlayerHealth()
{
	return m_fCurrentHealth;
}

float Player::GetPlayerMagic()
{
	return m_fCurrentMagic;
}

unsigned int Player::GetPlayerScore()
{
	return m_iCurrentScore;
}

//===============================================
//	Setters
//===============================================
void Player::SetPlayerPos( Vector2 vPlayerPos )
{
	m_v2PlayerPos = vPlayerPos;
}





//===============================================
//	Reset Jump
//===============================================
void Player::ResetJump()
{
	m_bJumping = false;
	m_fJumpVel = m_fDefaultJumpVel;
}
//===============================================
//	Slow Down
//===============================================
void Player::SlowDown()
{
	if( m_fSpeed > 5.f )
	{ m_fSpeed -= DeltaTime::GetInstance()->GetDeltaTimeNormalisedValue(5.f) * DeltaTime::GetInstance()->GetDeltaTime(); }
	else if( m_fSpeed > 0.f )
	{ m_fSpeed -= DeltaTime::GetInstance()->GetDeltaTimeNormalisedValue(1.f) * DeltaTime::GetInstance()->GetDeltaTime(); }
	else if( m_fSpeed < -5.f )
	{ m_fSpeed += DeltaTime::GetInstance()->GetDeltaTimeNormalisedValue(5.f) * DeltaTime::GetInstance()->GetDeltaTime(); }
	else
	{ m_fSpeed += DeltaTime::GetInstance()->GetDeltaTimeNormalisedValue(1.f) * DeltaTime::GetInstance()->GetDeltaTime(); }

	if( (m_fSpeed < 1.5f) && (m_fSpeed > -1.5f) )
	{
		m_fSpeed = 0.f;
	}
}








//===============================================
//	Update
//===============================================
void Player::Update()
{
	// Play Victor Sequence If Level Completed
	if( m_bPlayLevelCompleteSequence )
	{
		PerformVictorySequence(); 
		return;
	}
	
	// Play Magic Animation
	if( m_bPlayingMagicAnimation )
	{
		m_bPlayingMagicAnimation = !AnimationHandler::GetInstance()->Get_IsAnimationComplete(m_iAnimationID);
		return;
	}

	// Play Revive Animation
	if(m_bPlayingReviveAnimation)
	{
		m_bPlayingReviveAnimation = !AnimationHandler::GetInstance()->Get_IsAnimationComplete(m_iAnimationID);
		return;
	}




	// If Alive, update player functions
	if( m_bAlive )
	{
		//////////////////
		UpdateInput();
		//////////////////
		UpdateMovement();
		//////////////////
		UpdateCollision();
		//////////////////
		UpdateMovementAnimation();
		//////////////////
	}

	// Otherwise if not playing revive animation, update dead movement
	else if( !m_bPlayingMagicAnimation )
	{
		if( UpdateDeadMovement() )
		{
			m_v2PlayerPos = m_v2PlayerDead;
			m_bAlive = true;

			m_iAnimationID = AnimationHandler::GetInstance()->StartAnimation(AnimationHandler::eFire1, m_v2PlayerPos);
			m_bPlayingReviveAnimation = true;
		}
	}
}




//===============================================
//	Update Input
//===============================================
void Player::UpdateInput()
{
	InputHandler* pInput = InputHandler::GetInstance();

	/////////////////////////////////////////
	//////////////// Magic ////////////////

	// Holding 'X' or 'B' on Xbox Controller
	if( (pInput->GetKeyState( SDLK_x, false ) || pInput->GetJoyButtonState( JoystickButtons_B )) && !m_bJumping )
	{
		// Stop Moving Before Using Magic
		if( m_fSpeed != 0.f )
		{ 
			SlowDown(); 
		}
		m_bUsingMagic = true;
	}
	else
	{
		m_bUsingMagic = false;
	}




	if( !m_bUsingMagic && !m_bPlayingMagicAnimation )
	{
		/////////////////////////////////////////
		//////////////// Moving ////////////////

		// Holding Left
		if( (pInput->GetKeyState( SDLK_a, false )) || (pInput->GetKeyState( SDLK_LEFT, false )) || (pInput->GetJoyDPadState( JoystickDPadButtons_Left )) )
		{
			if( m_fSpeed > 5.f )
			{ m_fSpeed -= DeltaTime::GetInstance()->GetDeltaTimeNormalisedValue(5.f) * DeltaTime::GetInstance()->GetDeltaTime(); }
			else if( m_fSpeed > 0.f )
			{ m_fSpeed -= DeltaTime::GetInstance()->GetDeltaTimeNormalisedValue(1.f) * DeltaTime::GetInstance()->GetDeltaTime(); }



			if( m_bRunning )
			{
				m_fSpeed -= DeltaTime::GetInstance()->GetDeltaTimeNormalisedValue(1.f) * DeltaTime::GetInstance()->GetDeltaTime();
			}

			if( !m_bJumping )
			{
				m_sPlayerFacingDirection = "LEFT";
			}

			m_fSpeed -= DeltaTime::GetInstance()->GetDeltaTimeNormalisedValue(1.f) * DeltaTime::GetInstance()->GetDeltaTime();
		}

		// Holding Right
		else if( (pInput->GetKeyState( SDLK_d, false )) || (pInput->GetKeyState( SDLK_RIGHT, false )) || (pInput->GetJoyDPadState( JoystickDPadButtons_Right )) )
		{
			if( m_fSpeed < -5.f )
			{ m_fSpeed += DeltaTime::GetInstance()->GetDeltaTimeNormalisedValue(5.f) * DeltaTime::GetInstance()->GetDeltaTime(); }
			else if( m_fSpeed < 0.f )
			{ m_fSpeed += DeltaTime::GetInstance()->GetDeltaTimeNormalisedValue(1.f) * DeltaTime::GetInstance()->GetDeltaTime(); }



			if( m_bRunning )
			{
				m_fSpeed += DeltaTime::GetInstance()->GetDeltaTimeNormalisedValue(1.f) * DeltaTime::GetInstance()->GetDeltaTime();
			}

			if(!m_bJumping)
			{
				m_sPlayerFacingDirection = "RIGHT";
			}

			m_fSpeed += DeltaTime::GetInstance()->GetDeltaTimeNormalisedValue(1.f) * DeltaTime::GetInstance()->GetDeltaTime();
		}

		// Not Moving
		else 
		{
			SlowDown();
		}

		/////////////////////////////////////////
		//////////////// Jumping ////////////////

		// Pressing Up
		if( ((pInput->GetKeyState( SDLK_w, false )) || (pInput->GetKeyState( SDLK_UP ,false )) || (pInput->GetJoyDPadState( JoystickDPadButtons_Up ))) && !m_bJumping)
		{
			m_bJumping = true;
		}

		/////////////////////////////////////////
		//////////////// Running ////////////////

		// Pressing Shift
		if( (pInput->GetKeyState( SDLK_LSHIFT, false )  || pInput->GetKeyState( SDLK_RSHIFT, false ) || pInput->GetJoyButtonState( JoystickButtons_X )) && !m_bJumping )
		{
			m_bRunning = true;
		}
		else
		{
			m_bRunning = false;
		}
	}
}




//===============================================
//	Update Movement
//===============================================
void Player::UpdateMovement()
{
	float fDT = DeltaTime::GetInstance()->GetDeltaTime();


	if( m_fSpeed != 0.f )
	{ m_bMoving = true; }
	else
	{ m_bMoving = false; }

	if( m_fSpeed > m_fMaxSpeed )
	{ m_fSpeed = m_fMaxSpeed; }
	else if( m_fSpeed < -m_fMaxSpeed )
	{ m_fSpeed = -m_fMaxSpeed; }


	if( m_bMoving )
	{
		if( m_bRunning )
		{
			m_v2PlayerPos.X += (m_fSpeed * 2.f) * fDT;
		}
		else
		{
			m_v2PlayerPos.X += m_fSpeed * fDT;
		}
	}
	
	

	if( m_bJumping )
	{
		m_v2PlayerPos.Y -= m_fJumpVel * fDT;
		m_fJumpVel		-= m_fGravity * fDT;  
	}


	m_v2PlayerDead = m_v2PlayerPos;
}








//===============================================
//	Update Dead Movement
//===============================================
bool Player::UpdateDeadMovement()
{
	Vector2 v2ReservedPos	= CollisionHandler::GetInstance()->GetReservedPosition();
	float fDistance			= ( (m_fMaxSpeed * DeltaTime::GetInstance()->GetDeltaTime()) * 2.f );
	bool bX_Ok				= false;
	bool bY_Ok				= false;


	if( (m_v2PlayerDead.X + fDistance) < v2ReservedPos.X )
	{
		m_v2PlayerDead.X += fDistance;
	}
	else if( m_v2PlayerDead.X > (v2ReservedPos.X + fDistance))
	{
		m_v2PlayerDead.X -= fDistance;
	}
	else
	{
		bX_Ok = true;
	}

	if( (m_v2PlayerDead.Y + fDistance) < v2ReservedPos.Y )
	{
		m_v2PlayerDead.Y += fDistance;
	}
	else if( m_v2PlayerDead.Y > (v2ReservedPos.Y + fDistance) )
	{
		m_v2PlayerDead.Y -= fDistance;
	}
	else
	{
		bY_Ok = true;
	}


	return ( bX_Ok && bY_Ok );
}









//===============================================
//	Update Collision
//===============================================
void Player::UpdateCollision()
{
	UpdateLevelCollision();
	UpdateTileCollision();
	UpdateEnemyCollision();


	// Has the Player Touched a Crystal?
	unsigned int iPointsIncrement = CollisionHandler::GetInstance()->CheckCrystalCollision( m_v2PlayerPos );
	if( iPointsIncrement > 0 ) 
	{ 
		m_iCurrentScore += iPointsIncrement; 
		AudioManager::GetInstance()->PlaySound( "Pick_Up_Diamond" ); 
	}


	// Has the Player Touched the Level Finishing Star?
	if( CollisionHandler::GetInstance()->CheckStarLevelFinisherCollision( m_v2PlayerPos ))
	{
		m_bPlayLevelCompleteSequence = true;
	}
}




//===============================================
//	Update Level Collision
//===============================================
void Player::UpdateLevelCollision()
{
	CollisionHandler* p_CH = CollisionHandler::GetInstance();

	// Check Level Boundaries Collision
	if( p_CH->CheckLevelCollision( m_v2PlayerPos ))
	{
		if( p_CH->Get_IsObjectInDeadZone( m_v2PlayerPos ))
		{
			m_bAlive = false;
			m_fSpeed = 0.f;
			m_sPlayerFacingDirection = "RIGHT";
			AudioManager::GetInstance()->PlaySound( "Fall_SE" );
		}
		else
		{
			m_v2PlayerPos = p_CH->GetObjectCorrectionPosition();
		}
	}
}




//===============================================
//	Update Tile Collision
//===============================================
void Player::UpdateTileCollision()
{
	CollisionHandler* p_CH = CollisionHandler::GetInstance();

	int iPlayerXTile = p_CH->GetObjectCurrentXTilePosition( m_v2PlayerPos.X );
	int iPlayerYTile = p_CH->GetObjectCurrentYTilePosition( m_v2PlayerPos.Y );

	// Check Surrouding Tiles Collision
	if( p_CH->CheckTileCollision( m_v2PlayerPos, m_v2PlayerSize.X, m_v2PlayerSize.Y, false ) )
	{
		// Check Tile Above
		if( (m_bJumping) && (m_fJumpVel > 0.f) )
		{
			// Do Nothing, we don't need collision for when you're jumping
		}

		// Check Tile Below 
		else if( (m_bJumping) && (m_fJumpVel <= 0.f) && (!p_CH->Get_IsTilePassable( p_CH->GetSpecificTileIdentity( iPlayerXTile, (iPlayerYTile + 1 )))) )
		{
			ResetJump();
		}

		// Check Current Tile
		else if( !p_CH->Get_IsTilePassable( p_CH->GetSpecificTileIdentity( iPlayerXTile, iPlayerYTile )) )
		{
			if( p_CH->Get_IsTilePassable( p_CH->GetSpecificTileIdentity( iPlayerXTile, (iPlayerYTile - 1))) )
			{
				m_v2PlayerPos.Y -= (m_v2PlayerSize.Y * 0.5f);
			}
			else
			{
				m_v2PlayerPos.Y += (m_v2PlayerSize.Y * 0.5f);
			}
		}
		else
		{
			m_v2PlayerPos = p_CH->GetObjectCorrectionPosition();
		}
	}
	else
	{
		if( (!m_bJumping) && (p_CH->Get_IsTilePassable( p_CH->GetSpecificTileIdentity( iPlayerXTile, (iPlayerYTile + 1 )))) )
		{
			m_fJumpVel = -m_fDefaultJumpVel;
			m_bJumping = true;
		}
	}
}




//===============================================
//	Update Enemy Collision
//===============================================
void Player::UpdateEnemyCollision()
{

}






//===============================================
//	Update Animation
//===============================================
void Player::UpdateMovementAnimation()
{
	////////// NOT JUMPING //////////
	if( !m_bJumping )
	{
		AnimatedSprite::SetFacingDirection( m_sPlayerFacingDirection );

		if( m_bMoving )
		{
			if( AnimatedSprite::GetAnimationDirection() == "RIGHT" && AnimatedSprite::GetCurrentAnimationFrame() == (m_iNumRightAnimFrames - 1) )
			{
				AnimatedSprite::SetAnimationDirection( "LEFT" );
			}
			else if( AnimatedSprite::GetAnimationDirection() == "LEFT" && AnimatedSprite::GetCurrentAnimationFrame() == 0 )
			{
				AnimatedSprite::SetAnimationDirection( "RIGHT" );
			}

			if( m_bRunning )
			{
				AnimatedSprite::Update( false, (DeltaTime::GetInstance()->GetDeltaTime() * 2.f) );
			}
			else
			{
				AnimatedSprite::Update();
			}
		}
		else
		{
			AnimatedSprite::SetCurrentAnimationTime( 0.f );

			if( m_sPlayerFacingDirection == "LEFT" )
			{
				AnimatedSprite::SetCurrentAnimationFrame( m_sPlayerFacingDirection, AnimatedSprite::m_iMainLeftFrame );
			}
			else
			{
				AnimatedSprite::SetCurrentAnimationFrame( m_sPlayerFacingDirection, AnimatedSprite::m_iMainRightFrame );
			}
		}
	}
	////////// JUMPING //////////
	else
	{
		if( m_sPlayerFacingDirection == "LEFT" )
		{
			AnimatedSprite::SetCurrentAnimationFrame( m_sPlayerFacingDirection, AnimatedSprite::m_iMainLeftFrame + 1 );
		}
		else
		{
			AnimatedSprite::SetCurrentAnimationFrame( m_sPlayerFacingDirection, AnimatedSprite::m_iMainRightFrame - 1 );
		}
	}
}











//===============================================
//	Draw
//===============================================
void Player::Draw()
{
	if( m_bAlive && !m_bPlayingReviveAnimation )
	{
		AnimatedSprite::Draw( m_v2PlayerPos.X, m_v2PlayerPos.Y, m_v2PlayerSize.X, m_v2PlayerSize.Y );
	}
}





//===============================================
//	Perform Victory Sequence
//===============================================
void Player::PerformVictorySequence()
{
	m_fCompleteLevelSequenceCurrentTime += DeltaTime::GetInstance()->GetDeltaTime();

	if(m_fCompleteLevelSequenceCurrentTime > 0.f)
	{
		m_bCompletedLevel = true;
	}
}