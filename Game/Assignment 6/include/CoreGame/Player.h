//\====================================================================================
//\ Author: Christopher Diamond
//\ About : Player.h - 
//\ 
//\ Defines the Player Class. This class is used to handle the player input, movement,
//\ collision and hud related variables.
//\====================================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_


#include "AnimatedSprite.h"
#include "Vector2.h"


class Player : public AnimatedSprite
{
public:
	Player();
	~Player();

	void OnLoad();
	void OnUnload();

	void Reset();

	void Update();
	void Draw();

	Vector2			GetPlayerPos();
	std::string		GetCurrentPlayerName();
	std::string		GetPlayerDirectionFacing();
	bool			Get_IsUsingMagic();
	bool			Get_HasCompletedLevel();
	float			GetPlayerHealth();
	float			GetPlayerMagic();
	unsigned int	GetPlayerScore();

	void SetPlayerPos( Vector2 vPlayerPos );
	

private:


	void SetupAnimation();

	void UpdateInput();
	void UpdateMovement();
	bool UpdateDeadMovement();
	void UpdateCollision();
	void UpdateLevelCollision();
	void UpdateTileCollision();
	void UpdateEnemyCollision();
	void UpdateMovementAnimation();


	void ResetJump();
	void SlowDown();
	void PerformVictorySequence();

	std::string		m_sCurrentPlayerName,		m_sPlayerFacingDirection;
	Vector2			m_v2PlayerPos,				m_v2PlayerSize,		m_v2PlayerDead;
	bool			m_bAlive,					m_bJumping,			m_bMoving,		  m_bRunning,	 m_bUsingMagic,	 m_bPlayingReviveAnimation,			m_bPlayingMagicAnimation,	m_bPlayLevelCompleteSequence,	m_bCompletedLevel;
	float			m_fDefaultGravity,			m_fDefaultJumpVel,  m_fMaxSpeed,	  m_fGravity,	 m_fJumpVel,	 m_fSpeed,		m_fCurrentHealth,	m_fCurrentMagic,	m_fCompleteLevelSequenceCurrentTime;
	unsigned int	m_iCurrentScore,			m_iAnimationID;
};

#endif