//\====================================================================================
//\ Author: Christopher Diamond
//\ About : SceneManager.h -
//\
//\ Keeps track of current in-game scenes and update & draws them accordingly
//\====================================================================================
#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_


class GnEngine;
class Scene_Base;

#include <vector>

class SceneManager
{
//////////////////////////////////////////
public:
//////////////////////////////////////////

	//===============================================
	//			Scene Enum
	//===============================================
	enum eSTATE_TYPES
	{
		eSPLASH_SCREEN_STATE,
		eTITLEMENU_STATE,
		ePLAY_GAME_STATE,
		eSELECT_CHARACTER_SCENE,
		eSELECT_LEVEL_SCENE,

		eHIGH_SCORE_STATE,
		eINSTRUCTIONS_STATE,
		eOPTIONS_STATE,
		eCREDITS_STATE,
		
		eTOTAL_STATES, // Must Be Last Element in Enum
	};



	//===============================================
	//			Constructor & Destructor
	//===============================================
	SceneManager(GnEngine* p_GnEngine);
	~SceneManager();




	//===============================================
	//			Public Functions
	//===============================================
	void OnLoad();
	void OnUnload();

	void ProcessScene();

	void Shutdown();
	void ChangeState( eSTATE_TYPES eType );

	void FixCamera(); // Sets the Camera Back to 0, 0 Coords.

	//===============================================
	//			Getter Functions
	//===============================================
	Scene_Base* GetScene();
	Scene_Base* GetScene(eSTATE_TYPES eType);

	bool Get_IsCurrentScene( eSTATE_TYPES Scene );
	bool Get_DoesSceneExist( eSTATE_TYPES Scene );


//////////////////////////////////////////
private:
//////////////////////////////////////////
	
	//===============================================
	//			Private Declarations
	//===============================================
	eSTATE_TYPES m_eCurrentState;
	eSTATE_TYPES m_ePreviousState;

	//===============================================
	//			Private Declarations
	//===============================================
	void ProcessInput();
	Scene_Base* CreateScene(eSTATE_TYPES eType);

	//===============================================
	//			Pointers
	//===============================================
	GnEngine*					m_pOwningGame;
	std::vector<Scene_Base*>	m_apSceneArray;
};

#endif