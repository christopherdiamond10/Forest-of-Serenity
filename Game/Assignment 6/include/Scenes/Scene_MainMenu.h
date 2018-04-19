//\====================================================================================
//\ Author: Declan.Corcoran
//\ About : Scene_TitleMenu.h - creates the MainMenu Scene class which contains member 
//\						  variables that are used to switch scenes in the SceneManager
//\						  and to draw pretty pictures for the background
//\====================================================================================

#ifndef _MENU_STATE_H_
#define _MENU_STATE_H_

#include "sdl.h"
#include "Scene_Base.h"


class Scene_TitleMenu : public Scene_Base
{
//////////////////////////////////////////
public:
//////////////////////////////////////////

	//////////////////////////////////////
	//	    Constructor & Destructor	//
	//////////////////////////////////////
	Scene_TitleMenu(SceneManager* p_Game);
	~Scene_TitleMenu();


	//////////////////////////////////////
	//		   Public Functions 		//
	//////////////////////////////////////
	void OnLoad();
	void OnUnload();

	void SceneStart();	
	void SceneTerminate();

	void Update();
	void Draw();


//////////////////////////////////////////
private:
//////////////////////////////////////////

	//////////////////////////////////////
	//		Private Declarations		//
	//////////////////////////////////////
	SDL_Rect Play_Game_AreaBox;
	SDL_Rect SelectLevel_AreaBox;
	SDL_Rect HighScores_AreaBox;
	SDL_Rect Options_AreaBox;
	SDL_Rect Instructions_AreaBox;
	SDL_Rect Credits_AreaBox;
	SDL_Rect Quit_AreaBox;


	//////////////////////////////////////
	//				Enum				//
	//////////////////////////////////////
	enum eMenu_Screen
	{
		ePlayGame,
		eSelectLevel,
		eHighScores,
		eOptions,
		eInstructions,
		eCredits,
		eQuit,
	};


	//////////////////////////////////////
	//				Values				//
	//////////////////////////////////////
	bool m_bSwitchtoNextScene;
	bool m_bClickable;
	bool m_bHighLightSelection;

	unsigned int m_iBackgroundTextureID;

	int	 m_iMenu_Selection;

	eMenu_Screen m_eTITLEMENU_STATE;

	float	m_fFrameWaiting;
	float	m_fWaitTimeAmount;
	
	//////////////////////////////////////
	//			Pointers				//
	//////////////////////////////////////
	SceneManager	* m_pSceneManager;
	


	//////////////////////////////////////
	//		   Private Functions		//
	//////////////////////////////////////
	void Input();
	void UpdateMenuSelectionBounds();
	void UpdateStateChanges();
	void UpdateMouseSelection();


	void DrawRect();

	void Draw_PlayGame_Selection();
	void Draw_SelectLevel_Selection();
	void Draw_Instructions_Selection();
	void Draw_HighScore_Selection();
	void Draw_Options_Selection();
	void Draw_Credits_Selection();
	void Draw_Exit_Selection();

};


#endif
