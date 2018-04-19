//\==============================================================================
//\Author: Michael Cimino
//\About: Enemy_BlueSlime.h
//\Description: Contains code for the enemy (BlueSlime)
//\==============================================================================

#include "EnemyBase.h"

#ifndef _ENEMY_BLUESLIME_H_
#define _ENEMY_BLUESLIME_H_

class Enemy_BlueSlime : public Enemy
{
public:
	Enemy_BlueSlime();
	~Enemy_BlueSlime();

	void Onload();
	void OnUnload();

	void Update( Vector2 &v2CameraPos );

private:

};


#endif