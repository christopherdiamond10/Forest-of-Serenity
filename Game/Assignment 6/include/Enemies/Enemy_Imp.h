//\==============================================================================
//\Author: Michael Cimino
//\About: Enemy_Imp.h
//\Description: Contains code for the enemy (Imp)
//\==============================================================================

#include "EnemyBase.h"

#ifndef _ENEMY_IMP_H_
#define _ENEMY_IMP_H_

class Enemy_Imp : public Enemy
{
public:
	Enemy_Imp();
	~Enemy_Imp();

	void Onload();
	void OnUnload();

	void Update( Vector2 &v2CameraPos );

private:

};


#endif