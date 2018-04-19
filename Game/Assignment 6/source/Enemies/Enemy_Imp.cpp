#include "Enemy_Imp.h"
#include "screenResolution.h"

Enemy_Imp::Enemy_Imp()  : Enemy()
{
	Onload();
	Enemy::OnLoad();
}

Enemy_Imp::~Enemy_Imp()
{

}

void Enemy_Imp::Onload()
{
	AnimatedSprite::SetCurrentTexture("Enemy_Imp.png", "Sprites");

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

void Enemy_Imp::OnUnload()
{

}

void Enemy_Imp::Update( Vector2 &v2CameraPos )
{
	if( m_v2EnemyPos.X > ( v2CameraPos.X - 100) && m_v2EnemyPos.X < (v2CameraPos.X + ScreenResolution::GetInstance()->GetScreenWidth() + 100)  &&
	  ( m_v2EnemyPos.Y > ( v2CameraPos.Y - 100) && m_v2EnemyPos.Y < (v2CameraPos.Y + ScreenResolution::GetInstance()->GetScreenHeight() + 100) ))
	{
		Enemy::UpdateAnimationDirection();
		Enemy::Update();
		m_bWithinCamera = true;
	}
	else
	{
		m_bWithinCamera = false;
	}	
	
}