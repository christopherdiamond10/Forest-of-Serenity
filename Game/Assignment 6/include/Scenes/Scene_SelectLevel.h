//\====================================================================================
//\ Author: Christopher Diamond
//\ About : Scene_SelectLevel.h - creates the base for selecting custom levels							
//\====================================================================================
#ifndef _SCENE_SELECTLEVEL_H_
#define _SCENE_SELECTLEVEL_H_


#include "Scene_Base.h"
#include <string>



class Scene_SelectLevel : public Scene_Base
{
//////////////////////////////////////////
public:
//////////////////////////////////////////

	//===============================================
	//			Constructor & Destructor
	//===============================================
	Scene_SelectLevel( SceneManager* p_Game );
	~Scene_SelectLevel();


	//===============================================
	//			Public Functions
	//===============================================
	void OnLoad();
	void OnUnload();

	void SceneStart();	
	void SceneTerminate();

	void Update();
	void Draw();


//////////////////////////////////////////
private:
//////////////////////////////////////////

	//===============================================
	//			Private Functions
	//===============================================


	//===============================================
	//			Public Declarations
	//===============================================
	unsigned int	m_iBackgroundTextureID;
	float			m_fTimerForTextLine;
	std::string		m_sCurrentlyTypedCharacters;
	bool			m_bInformUserOfError;
	bool			m_bShowTextLine;


	//===============================================
	//			Pointers
	//===============================================
	SceneManager	* m_pSceneManager;

};


#endif