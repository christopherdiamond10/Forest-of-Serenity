//\==============================================================================
//\Author: Michael Cimino
//\About: Enemy_GreenSlime.h
//\Description: Contains code for the enemy (GreenSlime)
//\==============================================================================

#include "EnemyBase.h"

#ifndef _ENEMY_GREENSLIME_H_
#define _ENEMY_GREENSLIME_H_

class Enemy_GreenSlime : public Enemy
{
public:
	Enemy_GreenSlime();
	~Enemy_GreenSlime();

	void Onload();
	void OnUnload();

	void Update( Vector2 &v2CameraPos );

private:

};


#endif