#include "Enemy_Snake.h"
#include "screenResolution.h"

Enemy_Snake::Enemy_Snake()  : Enemy()
{
	Onload();
	Enemy::OnLoad();
}

Enemy_Snake::~Enemy_Snake()
{

}

void Enemy_Snake::Onload()
{
	AnimatedSprite::SetCurrentTexture("Enemy_Snake.png", "Sprites");

	//////////////////////////////////////////////////////////////
	AnimatedSprite::OnLoad();
	//////////////////////////////////////////////////////////////
	std::list<AnimatedSpriteInfoList>  Animated2DList;
	AnimatedSpriteInfoList			   RowOne, RowTwo;
	//////////////////////////////////////////////////////////////
	RowOne.DirectionList.push_back( "Right" ); RowOne.DirectionList.push_back( "Right" ); RowOne.DirectionList.push_back( "Right" ); RowOne.DirectionList.push_back( "Right" );
	RowTwo.DirectionList.push_back( "Left" ); RowTwo.DirectionList.push_back( "Left" ); RowTwo.DirectionList.push_back( "Left" ); RowTwo.DirectionList.push_back( "Left" );
	//////////////////////////////////////////////////////////////
	Animated2DList.push_back( RowOne );		Animated2DList.push_back( RowTwo ); 
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

void Enemy_Snake::OnUnload()
{

}

void Enemy_Snake::Update( Vector2 &v2CameraPos )
{
	if( m_v2EnemyPos.X > ( v2CameraPos.X - 100) && m_v2EnemyPos.X < (v2CameraPos.X + ScreenResolution::GetInstance()->GetScreenWidth() + 100)  &&
	  ( m_v2EnemyPos.Y > ( v2CameraPos.Y - 100) && m_v2EnemyPos.Y < (v2CameraPos.Y + ScreenResolution::GetInstance()->GetScreenHeight() + 100) ))
	{
		Enemy::Update();
		m_bWithinCamera = true;
	}
	else
	{
		m_bWithinCamera = false;
	}	
	
}