#include "EnemyBase.h"
#include "AudioManager.h"
#include "InputHandler.h"
#include "CollisionHandler.h"
#include "ScreenResolution.h"
#include "DeltaTime.h"
#include <string>

Enemy::Enemy() : AnimatedSprite( "AIDS", "Background" )
{
	OnLoad();
}

Enemy::Enemy( Enemy& CpyEnemy )
{
	m_v2EnemySize				= CpyEnemy.m_v2EnemySize;	
	m_v2EnemySize.X				= CpyEnemy.m_v2EnemySize.X;	
	m_v2EnemySize.Y				= CpyEnemy.m_v2EnemySize.Y;	
	m_fSpeed					= CpyEnemy.m_fSpeed;	
	m_bWithinCamera				= CpyEnemy.m_bWithinCamera;	

	AnimatedSprite::OnLoad();
}

Enemy::~Enemy()
{

}


//===============================================
//	OnLoad
//===============================================
void Enemy::OnLoad()
{
	m_v2EnemySize				= CollisionHandler::GetInstance()->GetReservedPosition();
	m_v2EnemySize.X				= 32;
	m_v2EnemySize.Y				= 32; 
	m_fSpeed					= DeltaTime::GetInstance()->GetDeltaTimeNormalisedValue(2.5);
	m_bWithinCamera				= false;
}


//===============================================
//	OnUnload
//===============================================
void Enemy::OnUnload()
{
	AnimatedSprite::OnUnload();
}


//===============================================
//	Getters
//===============================================
Vector2 Enemy::GetEnemyPos()
{
	return m_v2EnemyPos;
}

bool Enemy::GetAlive()
{
	return m_bAlive;
}

void Enemy::SetPosition( Vector2 v2ReservedPos )
{
	m_v2EnemyPos = v2ReservedPos;
}


//===============================================
//	Update
//===============================================
void Enemy::Update()
{
	UpdateMovement();
	UpdateCollision();
	UpdateArtificialIntelligence();	
	UpdateAnimation();
}

//===============================================
//	Update Movement
//===============================================
void Enemy::UpdateMovement()
{
	m_v2EnemyPos.X += m_fSpeed * DeltaTime::GetInstance()->GetDeltaTime();
} 

void Enemy::UpdateArtificialIntelligence()
{
	CollisionHandler* p_CH = CollisionHandler::GetInstance();

	int* p_CurrentTile = p_CH->GetObjectCurrentTilePosition( m_v2EnemyPos );
	int iCurrentXTile = p_CurrentTile[0]; int iCurrentYTile = p_CurrentTile[1]; delete[] p_CurrentTile;

	// Checking Tiles Ahead
	// if facing Right
	if( !p_CH->Get_IsTilePassable( p_CH->GetSpecificTileIdentity( iCurrentXTile + 1, iCurrentYTile ) ))
	{
		m_fSpeed = -m_fSpeed;
	}
	else if( !p_CH->Get_IsTilePassable( p_CH->GetSpecificTileIdentity( iCurrentXTile - 1, iCurrentYTile ) ))
	{
		m_fSpeed = -m_fSpeed;
	}

	if( p_CH->Get_IsTilePassable( p_CH->GetSpecificTileIdentity( iCurrentXTile + 1, iCurrentYTile + 1) ))
	{
		m_fSpeed = -m_fSpeed;
	}

	if ( p_CH->Get_IsTilePassable( p_CH->GetSpecificTileIdentity( iCurrentXTile - 1, iCurrentYTile + 1) ))
	{ 
		m_fSpeed = -m_fSpeed;
	}
}


void Enemy::UpdateAnimation()
{
	if( m_fSpeed < 0.f ) 
	{
		AnimatedSprite::SetFacingDirection( "LEFT" );
	}
	else
	{
		AnimatedSprite::SetFacingDirection( "RIGHT" );
	}
	AnimatedSprite::Update();
}

void Enemy::UpdateAnimationDirection()
{
	if( AnimatedSprite::GetAnimationDirection() == "RIGHT" && AnimatedSprite::GetCurrentAnimationFrame() == (m_iNumRightAnimFrames - 1) )
	{
		AnimatedSprite::SetAnimationDirection( "LEFT" );
	}
	else if( AnimatedSprite::GetAnimationDirection() == "LEFT" && AnimatedSprite::GetCurrentAnimationFrame() == 0 )
	{
		AnimatedSprite::SetAnimationDirection( "RIGHT" );
	}
}
//===============================================
//	Update Collision
//===============================================
void Enemy::UpdateCollision()
{
	UpdateLevelCollision();
	UpdateTileCollision();
}

//===============================================
//	Update Level Collision
//===============================================
void Enemy::UpdateLevelCollision()
{
	CollisionHandler* p_CH = CollisionHandler::GetInstance();

	// Check Level Boundaries Collision
	if( p_CH->CheckLevelCollision( m_v2EnemyPos ) )
	{
		m_fSpeed = -m_fSpeed;
	}

	if( p_CH->Get_IsObjectInDeadZone( m_v2EnemyPos ))
	{
		m_bAlive = false;
	}


	p_CH->CheckTileCollision( m_v2EnemyPos );
	
}

//===============================================
//	Update Tile Collision
//===============================================
void Enemy::UpdateTileCollision()
{
	
}

//===============================================
//	Draw
//===============================================
void Enemy::Draw()
{
	if( m_bWithinCamera )
	{
		AnimatedSprite::Draw(m_v2EnemyPos.X, m_v2EnemyPos.Y, m_v2EnemySize.X, m_v2EnemySize.Y);
	}
}