//\====================================================================================
//\ Author: Christopher Diamond
//\ About : Level.h - 
//\ 
//\ Defines the Functions/Pointers/Variables for the Level Class. 
//\ Tile Identities are created and handled at the bottom of the cpp (Wall of Text).
//\ The Level itself is loaded from XML files created via a level editor, which includes
//\ which audio to play, weather to use and background picture.
//\ Enemies are created and pushed into a list in the MakeLevelEnemy Function.
//\====================================================================================
#ifndef _LEVEL_H_
#define _LEVEL_H_

#include <list>
#include "Vector2.h"



//===============================================
//	Class Declarations
//===============================================
class AnimatedSprite;
class Enemy_Bunny;
class Enemy_Snake;
class Enemy_BlueSlime;
class Enemy_GreenSlime;
class Enemy_Imp;
class Enemy_Succubus;
class Camera;
class Weather;
class PlayGameState;









class Level
{
//////////////////////////////////////////
public:
//////////////////////////////////////////

	//===============================================
	//			Constructor & Destructor
	//===============================================
	Level( PlayGameState* pPlayGameState );
	~Level();


	//===============================================
	//			Public Functions
	//===============================================
	void OnLoad();
	void OnUnload();

	void LoadLevel();

	void Update( Vector2 vPlayerPos );
	void Draw();


	//===============================================
	//			Getter Functions
	//===============================================
	unsigned int GetTileWidth();
	unsigned int GetTileHeight();
	unsigned int GetLevelRows();
	unsigned int GetLevelCols();
	int			 GetLevelBlockIdentity( int XTile, int YTile );
	Vector2		 GetLevelBlockPosition( int XTile, int YTile );
	Vector2		 GetLevelBoundaries();
	Vector2		 GetCameraPosition();


	//===============================================
	//			Setter Functions
	//===============================================
	void		SetSpecificTileIdentity( unsigned int XTile, unsigned int YTile, unsigned int Identity );

//////////////////////////////////////////
private:
//////////////////////////////////////////

	//===============================================
	//			Private Structs
	//===============================================
	struct LevelData
	{
		std::list<int> LevelInfoList;
	};

	struct LevelIdentityTile
	{
		unsigned int Identity;
		unsigned int TextureID;
	};
	struct EnemyData
	{
		std::list<Enemy_Bunny*>		BunnyList;
		std::list<Enemy_Snake*>		SnakeList;
		std::list<Enemy_BlueSlime*>	BlueSlimeList;
		std::list<Enemy_GreenSlime*> GreenSlimeList;
		std::list<Enemy_Imp*>		ImpList;
		std::list<Enemy_Succubus*>	SuccubusList;
	};


	//===============================================
	//			Private Declarations
	//===============================================
	unsigned int m_iTileSize;
	unsigned int m_iTileWidth;
	unsigned int m_iTileHeight;
	
	float m_fTimeUntilBackgroundSEPlays;
	float m_fCurrentTimeForBackgroundSE;

	float m_fScreenDimensions[2];
	int** m_iLevelData;

	LevelIdentityTile m_LevelIdentityTileArray[226];

	unsigned int m_iLevelDataRows, m_iLevelDataCols;
	unsigned int m_iBackgroundTextureID;


	EnemyData m_EnemyData;

	//===============================================
	//			Private Functions
	//===============================================
	void SetupAllLevelTexturesAndTileIdentities();
	unsigned int SetupTileIdentity( std::string sIdentityName );
	void MakeLevelArray( int iRows, int iCols );
	void MakeLevelEnemy( std::string EnemyName, unsigned int XTile, unsigned int YTile );
	void ClearLevelArray();
	void ClearEnemyLists();
	void UpdateArrayDrawingSizeandCameraBoundaries();
	void UpdateLevelEnemies();

	void DrawLevelBlocks( float* fCameraPosArray );
	void DrawLevelEnemies();
	void FindLevelBlockSprite( int iBlockIdentity );	
	bool IsLevelBlockWithinCameraArea( float* fCameraPosArray, bool bCheckYPos, int iTileToCheck );


	//===============================================
	//			Pointers
	//===============================================
	AnimatedSprite	* m_pAnimatedSprite;
	Camera			* m_pCamera;
	Weather			* m_pWeather;
	PlayGameState	* m_pPlayGameState;
};

#endif