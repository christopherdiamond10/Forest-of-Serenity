//\==============================================================================
//\Author: Michael Cimino
//\About: Enemy_Bunny.h
//\Description: Contains code for the enemy (Bunny)
//\==============================================================================

#include "EnemyBase.h"

#ifndef _ENEMY_BUNNY_H_
#define _ENEMY_BUNNY_H_

class Enemy_Bunny : public Enemy
{
public:
	Enemy_Bunny();
	~Enemy_Bunny();

	void Onload();
	void OnUnload();

	void Update( Vector2 &v2CameraPos );

private:

};


#endif