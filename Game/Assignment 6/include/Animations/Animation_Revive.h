//\====================================================================================
//\ Author: Christopher Diamond
//\ About : Animation_Revive.h - 
//\ 
//\ Defines the Animation_Revive Class. This class is only a gateway into playing an 
//\ animation, there will be several classes which do this.
//\====================================================================================
#ifndef _ANIMATION_REVIVE_H_
#define _ANIMATION_REVIVE_H_


#include "AnimatedSprite.h"
#include "Vector2.h"


class Animation_Revive : public AnimatedSprite
{
public:

	Animation_Revive( Vector2 vAnimLocation, unsigned int iAnimID );
	~Animation_Revive();

	void Update();
	void Draw( Vector2 vCamPosition );

	bool Get_IsPartiallyCompleted();
	bool Get_IsCompleted();

private:

	void SetupSelf();
	void SetupAnimatedSprite();

	void UpdateSelf();
	void UpdateAnimatedSprite();

	

	const long double	CONST_D_ONE_FRAME_OUT_OF_SIXTY;

	unsigned int		m_iSelf_AnimationID;
	unsigned int		m_iCurrentFrame;
	float				m_fCurrentTime;

	bool				m_bCompletedFrame[20];

	Vector2				m_v2AnimationLocation;

	Vector2				m_v2ExtraAnimationOnePosition;
	Vector2				m_v2ExtraAnimationTwoPosition;
	Vector2				m_v2ExtraAnimationThreePosition;

};


#endif