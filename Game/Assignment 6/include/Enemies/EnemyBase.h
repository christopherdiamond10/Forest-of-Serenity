//\==============================================================================
//\Author: Michael Cimino
//\About: EnemyBase.h
//\Description: Contains all the code for each enemy class
//\Is the base class (uses this stuff)
//\==============================================================================

#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "AnimatedSprite.h"
#include "Vector2.h"

class Enemy : public AnimatedSprite
{
public:
	Enemy();
	Enemy( Enemy& CpyEnemy );
	~Enemy();

	void OnLoad();
	void OnUnload();

	void Update();
	void Draw();

	Vector2 GetEnemyPos();
	bool GetAlive();

	void SetPosition( Vector2 v2ReservedPos );

protected:
	
	void UpdateAnimationDirection();

	std::string		m_sPlayerFacingDirection,	m_sDirectionFacingWhenJumped;
	Vector2			m_v2EnemyPos,				m_v2EnemySize;
	bool			m_bAlive,					m_bMoving,			m_bWithinCamera;
	float			m_fDefaultGravity,			m_fGravity,	 		m_fSpeed;

private:

	void UpdateMovement();
	void UpdateArtificialIntelligence();
	void UpdateCollision();
	void UpdateLevelCollision();
	void UpdateTileCollision();
	void UpdateAnimation();
};

#endif