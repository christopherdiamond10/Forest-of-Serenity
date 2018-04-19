//\==============================================================================
//\Author: Michael Cimino
//\About: Scene_PlayGame.h
//\Description: Contains all code in relation to the playgame scene.
//\==============================================================================

#ifndef _SCENE_PLAYGAME_H_
#define _SCENE_PLAYGAME_H_


#include <string>
#include "Scene_Base.h"


//===============================================
//	Class Declarations
//===============================================
class Level;
class CollisionHandler;
class Player;
class HUD;



class PlayGameState : public Scene_Base
{
//////////////////////////////////////////
public:
//////////////////////////////////////////

	//===============================================
	//			Constructor & Destructor
	//===============================================
	PlayGameState(SceneManager* p_Game);
	~PlayGameState();


	//===============================================
	//			Public Functions
	//===============================================
	void OnLoad();
	void OnUnload();
	
	void SceneStart();
	void SceneTerminate();

	void Update();
	void Draw();


	//===============================================
	//			Setter Functions
	//===============================================
	void SetPlayerPosition( Vector2 vPlayerPos );


//////////////////////////////////////////
private:
//////////////////////////////////////////

	//===============================================
	//			Pointers
	//===============================================
	SceneManager	 * m_pSceneManager;
	Level			 * m_pLevel;
	Player			 * m_pPlayer;
	HUD				 * m_pHUD;
	CollisionHandler * m_pCollisionHandler;
};

#endif