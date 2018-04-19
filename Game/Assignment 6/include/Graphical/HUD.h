//\====================================================================================
//\ Author: Christopher Diamond
//\ About : Hud.h - 
//\ 
//\ Defines the Hud Class. This class is used to inform the player about their remaining 
//\ health and magic.  
//\====================================================================================
#ifndef _HUD_H_
#define _HUD_H_


#include "Vector2.h"

class Player;



class HUD
{
public:

	HUD( Player* pPlayer );
	~HUD();


	void OnLoad();
	void OnUnload();

	void Update( Vector2 vCamPosition );
	void Draw();



private:

	Vector2 m_v2HealthDisplayPosition;			Vector2 m_v2HealthDisplaySize;			Vector2 m_v2HealthDisplayCurrentSize;
	Vector2 m_v2HighScoreDisplayPosition;		Vector2 m_v2HighScoreDisplaySize;		
	Vector2 m_v2MagicDisplayPosition;			Vector2 m_v2MagicDisplaySize;			Vector2 m_v2MagicDisplayCurrentSize;
	Vector2 m_v2MagicOptionsDisplayPosition;	Vector2 m_v2MagicOptionsDisplaySize;

	unsigned int m_iMagicOptionsOpacity;
	unsigned int m_iMagicOptionsTextureID;

	unsigned int m_iHealthIconTextureID;
	unsigned int m_iFireMagicIconTextureID;
	unsigned int m_iLightningMagicIconTextureID;
	unsigned int m_iEarthMagicIconTextureID;
	//////////////////////////////////////////////////

	void UpdateHealthDisplay( Vector2 vCamPosition );
	void UpdateHighScoreDisplay( Vector2 vCamPosition );
	void UpdateMagicDisplay( Vector2 vCamPosition );
	void UpdateMagicOptionsDisplay( Vector2 vCamPosition );

	void DrawHealthDisplay();
	void DrawHighScoreDisplay();
	void DrawMagicDisplay();
	void DrawMagicOptionsDisplay();



	Player*    m_pPlayer;

};



#endif