//\====================================================================================
//\ Author: Christopher Diamond
//\ About : CollisionHandler.h - 
//\ 
//\ Defines the CollisionHandler Class. This class is used to process collision for all
//\ objects and helps with A.I to detect dangerous paths and avoid them.
//\ Collision itself comes in four forms, two are used for AI, all four are used for the
//\ Player. The four collisions are LevelCollision, TileCollision(Platforms), EnemyCollision
//\ & CrystalCollision(which is what makes you pick up crystals if you touch them).
//\====================================================================================
#ifndef _COLLISIONHANDLER_H_
#define _COLLISIONHANDLER_H_

#include "Vector2.h"
#include <string>


class Level;



class CollisionHandler
{
//////////////////////////////////////////
public:
//////////////////////////////////////////

	//===============================================
	//			Constructor & Destructor
	//===============================================
	CollisionHandler( Level* pLevel );
	~CollisionHandler();

	void OnLoad();
	void OnUnload();


	
	//===============================================
	//			Check Collission Functions
	//===============================================
	bool CheckLevelCollision(									   Vector2 &vObjectPos, float fObjectWidth = 32.f, float fObjectHeight = 32.f, bool bAutoFix = true );
	bool CheckTileCollision(									   Vector2 &vObjectPos, float fObjectWidth = 32.f, float fObjectHeight = 32.f, bool bAutoFix = true );
	unsigned int CheckCrystalCollision(							   Vector2 &vObjectPos, float fObjectWidth = 32.f, float fObjectHeight = 32.f );
	bool CheckStarLevelFinisherCollision(						   Vector2 &vObjectPos, float fObjectWidth = 32.f, float fObjectHeight = 32.f );

	//===============================================
	//			Getter Functions
	//===============================================
	int*	 GetObjectCurrentTilePosition(						   Vector2 vObjectPos, float fObjectWidth  = 32.f, float fObjectHeight = 32.f	);
	int		 GetObjectCurrentXTilePosition(						   float fObjectXPos,  float fObjectWidth  = 32.f								);
	int		 GetObjectCurrentYTilePosition(						   float fObjectYPos,  float fObjectHeight = 32.f								);
	int*	 GetSurroundingTiles(								   Vector2 vObjectPos, float fObjectWidth  = 32.f, float fObjectHeight = 32.f	);
	int		 GetSurroundingTile( std::string sDirectionChecking,   Vector2 vObjectPos, float fObjectWidth  = 32.f, float fObjectHeight = 32.f	);
	bool	 Get_IsTilePassable(								   int iIdentity																);
	bool     Get_IsObjectInDeadZone(							   Vector2 vObjectPos, float fObjectWidth  = 32.f, float fObjectHeight = 32.f	);
	int		 GetSpecificTileIdentity(							   int XTile,			int YTile												);
	Vector2  GetSpecificTilePosition(							   int XTile,			int YTile												);
	Vector2  GetObjectCorrectionPosition();
	Vector2	 GetReservedPosition();
	float	 GetTileWidth();
	float	 GetTileHeight();


	//===============================================
	//			Setter Functions
	//===============================================
	void	 SetObjectReservedPosition(							   int XTile, int YTile );

	//===============================================
	//			Static Functions
	//===============================================
	static CollisionHandler* GetInstance();



//////////////////////////////////////////
private:
//////////////////////////////////////////

	//===============================================
	//			Private Declarations
	//===============================================
	Vector2		m_vReservedPosition;
	Vector2		m_vCollisionCorrection;


	//===============================================
	//			Private Functions
	//===============================================
	int* PrivatelyGetSurroundingTilesOfObject( Vector2 vObjectPos, float fObjectWidth, float fObjectHeight );
	void PrivatelyGetSurroundingTileIdentities( int iObjectCurrentXTile, int iObjectCurrentYTile, int* p_iSurroundingTileIdentities );


	//===============================================
	//			Static Declarations
	//===============================================
	static CollisionHandler* m_Instance;


	//===============================================
	//			Pointers
	//===============================================
	Level	  * m_pLevel;
};


#endif