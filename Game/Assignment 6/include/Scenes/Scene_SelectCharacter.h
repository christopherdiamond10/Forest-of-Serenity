//\====================================================================================
//\ Author: Christopher Diamond
//\ About : Scene_SelectCharacter.h - 
//\ 
//\ Defines the Scene_SelectCharacter Class. This class is used to allow the user to 
//\ choose their character for the game, also provided images and info to help the 
//\ choice.
//\====================================================================================
#ifndef _SCENE_SELECTCHARACTER_H_
#define _SCENE_SELECTCHARACTER_H_

#include <list>
#include "Scene_Base.h"

class AnimatedSprite;



class Scene_SelectCharacter : public Scene_Base
{
public:

	Scene_SelectCharacter( SceneManager* pSceneManager );
	~Scene_SelectCharacter();

	void OnLoad();
	void OnUnload();

	void Update();
	void Draw();

private:

	enum eCharacterSelection
	{
		eRitaSelected,
		eEmilySelected,
		eNinoSelected
	};

	struct CharacterInfo
	{
		std::string Name;
		unsigned int TextureID;
		Vector2 TextureSize;
		std::list<std::string> ScreenMagicAttacks;
		std::list<std::string> IndividualMagicAttacks;
		std::list<std::string> PowerUpMagic;
		std::list<std::string> PowerDownMagic;
		unsigned int BackWindowColour[4];
		unsigned int CharacterNameFontColour[3];
		unsigned int LabelFontColour[3];
		unsigned int NormalFontColour[3];
	};

	struct CharacterTextureInfo
	{
		std::string		TextureName;
		Vector2			Size;
		unsigned int	ID;
	};




	const float CONST_M_F_TIMEUNTILTRANSITION; // In Seconds

	float m_fCurrentTime;
	float m_fCurrentAnimationTime;

	bool m_bClickable;

	unsigned int m_iCurrentHighlighted;
	unsigned int m_iPreviousHighlighted;

	float m_fPreviousTextureOpacity;
	float m_fCurrentTextureOpacity;

	unsigned int m_iPreviousTextureID;
	unsigned int m_iCurrentTextureID;


	Vector2 m_v2PreviousTexturePosition;
	Vector2 m_v2CurentTexturePosition;

	Vector2 m_v2PreviousTextureSize;
	Vector2 m_v2CurrentTextureSize;

	Vector2 m_v2AnimatedSpritePosiiton;
	Vector2 m_v2AnimatedSpriteSize;

	CharacterInfo m_RitaCharacterInfo;
	CharacterInfo m_EmilyCharacterInfo;
	CharacterInfo m_NinoCharacterInfo;

	std::list<CharacterTextureInfo> m_lRitaBackTextureInfoList;
	std::list<CharacterTextureInfo> m_lEmilyBackTextureInfoList;
	std::list<CharacterTextureInfo> m_lNinoBackTextureInfoList;


	CharacterTextureInfo m_iRitaCharacterTexture;
	CharacterTextureInfo m_iEmilyCharacterTexture;
	CharacterTextureInfo m_iNinoCharacterTexture;


	void SetupClassVariables();
	void SetupCharacterInfo();

	void SetupRitaBackgroundTextures();
	void SetupEmilyBackgroundTextures();
	void SetupNinoBackgroundTextures();
	void SetupBackgroundTexturesList( std::list<CharacterTextureInfo> &TextInfoList, std::list<std::string> lTextureNames );
	Vector2 SetupTextureSize( std::string sNameOfImage );

	void SetupRitaAnimatedSprite();
	void SetupEmilyAnimatedSprite();
	void SetupNinoAnimatedSprite();


	void CheckInput();
	void UpdateAnimatedSprites();
	void UpdateBackgroundTextures();


	void DrawBackgroundTextures();
	void DrawCharacter();
	void DrawBackgroundWindow( CharacterInfo &TempCharInfo, Vector2 &v2BackWindowPosition, Vector2 &v2BackWindowSize );
	void DrawBackgroundWindow( unsigned int iRed, unsigned int iGreen, unsigned int iBlue, unsigned int iOpacity, Vector2 &v2BackWindowPosition, Vector2 &v2BackWindowSize );
	void DrawFont( CharacterInfo &TempCharInfo, Vector2 &v2BackWindowPosition, Vector2 &v2BackWindowSize );
	void DrawCharacterSelectionOptions();




	
	AnimatedSprite		* m_pRitaAnimatedSprite;
	AnimatedSprite		* m_pEmilyAnimatedSprite;
	AnimatedSprite		* m_pNinoAnimatedSprite;

	SceneManager		* m_pSceneManager;
};



#endif