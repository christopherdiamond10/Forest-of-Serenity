//\==============================================================================
//\Author: Michael Cimino
//\About: Enemy_Succubus.h
//\Description: Contains code for the enemy (Succubus)
//\==============================================================================

#include "EnemyBase.h"

#ifndef _ENEMY_SUCCUBUS_H_
#define _ENEMY_SUCCUBUS_H_

class Enemy_Succubus : public Enemy
{
public:
	Enemy_Succubus();
	~Enemy_Succubus();

	void Onload();
	void OnUnload();

	void Update( Vector2 &v2CameraPos );

private:

};


#endif