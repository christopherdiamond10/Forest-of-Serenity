//\==============================================================================
//\Author: Michael Cimino
//\About: Enemy_Snake.h
//\Description: Contains code for the enemy (Snake)
//\==============================================================================

#include "EnemyBase.h"

#ifndef _ENEMY_SNAKE_H_
#define _ENEMY_SNAKE_H_

class Enemy_Snake : public Enemy
{
public:
	Enemy_Snake();
	~Enemy_Snake();

	void Onload();
	void OnUnload();

	void Update( Vector2 &v2CameraPos );

private:

};


#endif