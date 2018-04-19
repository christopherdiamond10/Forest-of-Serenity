#include "CollisionHandler.h"

#include "Utility_Functions.h"
#include "Level.h"


CollisionHandler* CollisionHandler::m_Instance = nullptr;


//===============================================
//	Get Instance
//===============================================
CollisionHandler* CollisionHandler::GetInstance()
{
	return m_Instance;
}



//===============================================
//	Constructor
//===============================================
CollisionHandler::CollisionHandler( Level* pLevel )
{
	m_Instance = this;
	m_pLevel = pLevel;
}


//===============================================
//	Destructor
//===============================================
CollisionHandler::~CollisionHandler()
{

}




//===============================================
//	OnLoad
//===============================================
void CollisionHandler::OnLoad()
{
	m_vReservedPosition.X		= m_vReservedPosition.Y		= 0.f;
	m_vCollisionCorrection.X	= m_vCollisionCorrection.Y	= 0.f;
}


//===============================================
//	OnUnload
//===============================================
void CollisionHandler::OnUnload()
{

}










//===============================================
//	Get Object Current Tile Position
//===============================================
int* CollisionHandler::GetObjectCurrentTilePosition( Vector2 vObjectPos, float fObjectWidth, float fObjectHeight )
{
	// Whatever called this is responsible for deleting it
	int* p_iCurrentTilePosition = new int[2];
	p_iCurrentTilePosition[0] = GetObjectCurrentXTilePosition( vObjectPos.X, fObjectWidth );
	p_iCurrentTilePosition[1] = GetObjectCurrentYTilePosition( vObjectPos.Y, fObjectHeight );
	return p_iCurrentTilePosition;
}
//===============================================
//	Get Object Current XTile Position
//===============================================
int CollisionHandler::GetObjectCurrentXTilePosition( float fObjectXPos, float fObjectWidth )
{
	int iAmountOf_XTiles				= m_pLevel->GetLevelCols();
	int iCompleteLevelWidth				= iAmountOf_XTiles * m_pLevel->GetTileWidth();
	float fObjectMiddleX				= fObjectXPos + (fObjectWidth  * 0.5f);

	return (int)( (fObjectMiddleX / iCompleteLevelWidth)  * iAmountOf_XTiles );
}
//===============================================
//	Get Object Current YTile Position
//===============================================
int CollisionHandler::GetObjectCurrentYTilePosition( float fObjectYPos, float fObjectHeight )
{
	int iAmountOf_YTiles				= m_pLevel->GetLevelRows();
	int iCompleteLevelHeight			= iAmountOf_YTiles * m_pLevel->GetTileHeight();
	float fObjectMiddleY				= fObjectYPos + (fObjectHeight * 0.5f);

	return (int)( (fObjectMiddleY / iCompleteLevelHeight) * iAmountOf_YTiles );
}
//===============================================
//	Get Surrounding Tiles
//===============================================
int* CollisionHandler::GetSurroundingTiles( Vector2 vObjectPos, float fObjectWidth, float fObjectHeight )
{
	return PrivatelyGetSurroundingTilesOfObject( vObjectPos, fObjectWidth, fObjectHeight );
}
//===============================================
//	Get Surrounding Tile
//===============================================
int CollisionHandler::GetSurroundingTile( std::string sDirectionChecking, Vector2 vObjectPos, float fObjectWidth, float fObjectHeight )
{
	//------------------------------------
	int* p_iSurroundingTileIdentities	= PrivatelyGetSurroundingTilesOfObject( vObjectPos, fObjectWidth, fObjectHeight );

	int iAboveObjectTileIdentity		= p_iSurroundingTileIdentities[0];
	int iLeftOfObjectTileIdentity		= p_iSurroundingTileIdentities[1];
	int iRightOfObjectTileIdentity		= p_iSurroundingTileIdentities[2];
	int iBelowObjectTileIdentity		= p_iSurroundingTileIdentities[3];

	delete[] p_iSurroundingTileIdentities;
	//------------------------------------

	std::string sDirection = String_To_UpperCase( sDirectionChecking );

	if( sDirection == "UP" || sDirection == "UPPER" || sDirection == "NORTH" || sDirection == "NORTHERN" )
	{
		return iAboveObjectTileIdentity;
	}
	else if( sDirection == "LEFT" || sDirection == "WEST" || sDirection == "WESTERN" )
	{
		return iLeftOfObjectTileIdentity;
	}
	else if( sDirection == "RIGHT" || sDirection == "EAST" || sDirection == "EASTERN" )
	{
		return iRightOfObjectTileIdentity;
	}
	else
	{
		return iBelowObjectTileIdentity;
	}
}
//===============================================
//	Get 'Is Tile Passable'?
//===============================================
bool CollisionHandler::Get_IsTilePassable( int iIdentity )
{
	// Platform Identities are 1 - 55
	if( iIdentity > 0 && iIdentity < 56 )
	{
		return false;
	} 

	return true;
}
//===============================================
//	Get 'Is Object In a Dead Zone'?
//===============================================
bool CollisionHandler::Get_IsObjectInDeadZone( Vector2 vObjectPos, float fObjectWidth, float fObjectHeight )
{
	int X  = GetObjectCurrentXTilePosition( vObjectPos.X, fObjectWidth );
	int Y  = GetObjectCurrentYTilePosition( vObjectPos.Y, fObjectHeight );
	int ID = GetSpecificTileIdentity( X, Y );

	if( ID < 0 )
	{
		return true;
	}

	return false;
}
//===============================================
//	Get Specific Tile Identity
//===============================================
int CollisionHandler::GetSpecificTileIdentity( int XTile, int YTile )
{
	return m_pLevel->GetLevelBlockIdentity( XTile, YTile );
}
//===============================================
//	Get Specific Tile Position
//===============================================
Vector2 CollisionHandler::GetSpecificTilePosition( int XTile, int YTile )
{
	return m_pLevel->GetLevelBlockPosition( XTile, YTile );
}
//===============================================
//	Get Object Correction Position
//===============================================
Vector2 CollisionHandler::GetObjectCorrectionPosition()
{
	return m_vCollisionCorrection;
}
//===============================================
//	Get Reserved Position
//===============================================
Vector2	 CollisionHandler::GetReservedPosition()
{
	return m_vReservedPosition;
}
//===============================================
//	Get Tile Width
//===============================================
float CollisionHandler::GetTileWidth()
{
	return (float)m_pLevel->GetTileWidth();
}
//===============================================
//	Get Tile Height
//===============================================
float CollisionHandler::GetTileHeight()
{
	return (float)m_pLevel->GetTileHeight();
}








//===============================================
//	Setters
//===============================================
void CollisionHandler::SetObjectReservedPosition( int XTile, int YTile )
{
	m_vReservedPosition = GetSpecificTilePosition( XTile, YTile );
}













//===============================================
//	Check Level Collision
//===============================================
bool CollisionHandler::CheckLevelCollision( Vector2 &vObjectPos, float fObjectWidth, float fObjectHeight, bool bAutoFix )
{
	Vector2 vBoundaries		= m_pLevel->GetLevelBoundaries();
	m_vCollisionCorrection	= vObjectPos;

	bool bCollision = false;

	if( vObjectPos.X < 0.f )
	{
		m_vCollisionCorrection.X = 0.f;
		bCollision =  true;
	}
	else if( (vObjectPos.X + fObjectWidth) > vBoundaries.X )
	{
		m_vCollisionCorrection.X = (vBoundaries.X - fObjectWidth);
		bCollision =  true;
	}
	else if( (vObjectPos.Y + fObjectHeight) > vBoundaries.Y )
	{
		m_vCollisionCorrection.Y = (vBoundaries.Y - fObjectHeight);
		bCollision =  true;
	}

	if( bAutoFix )
	{
		vObjectPos = m_vCollisionCorrection;
	}

	return bCollision;
}





//===============================================
//	Check Tile Collision
//===============================================
bool CollisionHandler::CheckTileCollision( Vector2 &vObjectPos, float fObjectWidth, float fObjectHeight, bool bAutoFix )
{
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	m_vCollisionCorrection = vObjectPos;
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	int iObjectCurrentXTile				= GetObjectCurrentXTilePosition( vObjectPos.X, fObjectWidth ); 
	int iObjectCurrentYTile				= GetObjectCurrentYTilePosition( vObjectPos.Y, fObjectHeight );

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	int iCurrentTileIdentity			= GetSpecificTileIdentity( (iObjectCurrentXTile),	  (iObjectCurrentYTile)     );
	int iUpperLeftTileIdentity			= GetSpecificTileIdentity( (iObjectCurrentXTile - 1), (iObjectCurrentYTile - 1) );
	int iUpperTileIdentity				= GetSpecificTileIdentity( (iObjectCurrentXTile),	  (iObjectCurrentYTile - 1) );
	int iUpperRightTileIdentity			= GetSpecificTileIdentity( (iObjectCurrentXTile + 1), (iObjectCurrentYTile - 1) );
	int iMiddleLeftTileIdentity			= GetSpecificTileIdentity( (iObjectCurrentXTile - 1), (iObjectCurrentYTile)		);
	int iMiddleRightTileIdentity		= GetSpecificTileIdentity( (iObjectCurrentXTile + 1), (iObjectCurrentYTile )    );
	int iLowerLeftTileIdentity			= GetSpecificTileIdentity( (iObjectCurrentXTile - 1), (iObjectCurrentYTile + 1) );
	int iLowerTileIdentity				= GetSpecificTileIdentity( (iObjectCurrentXTile),	  (iObjectCurrentYTile + 1) );
	int iLowerRightTileIdentity			= GetSpecificTileIdentity( (iObjectCurrentXTile + 1), (iObjectCurrentYTile + 1) );
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	bool bCollision = false;


	//////////////////////////////// CHECK CURRENT TILE //////////////////////////////////////////////////
	if( iCurrentTileIdentity < 0 ) // This means you've died...
	{
		return false; 
	}

	//////////////////////////////// CHECK LEFT & RIGHT TILES //////////////////////////////////////////////////
	// Check Middle Left Tile
	if( !Get_IsTilePassable( iMiddleLeftTileIdentity ))
	{
		Vector2 vMiddleLeftTile_Position = GetSpecificTilePosition( (iObjectCurrentXTile - 1), (iObjectCurrentYTile)	);

		if( (m_vCollisionCorrection.X < (vMiddleLeftTile_Position.X + GetTileWidth())) && ((m_vCollisionCorrection.Y + fObjectHeight) > vMiddleLeftTile_Position.Y ))
		{ 
			m_vCollisionCorrection.X = vMiddleLeftTile_Position.X + GetTileWidth();
			bCollision = true;
		}
	}

	// Check Middle Right Tile
	if( !Get_IsTilePassable( iMiddleRightTileIdentity ))
	{
		Vector2 vMiddleRightTile_Position = GetSpecificTilePosition( (iObjectCurrentXTile + 1), (iObjectCurrentYTile)   );

		if( ((m_vCollisionCorrection.X + fObjectWidth) > vMiddleRightTile_Position.X) && ((m_vCollisionCorrection.Y + fObjectHeight) > vMiddleRightTile_Position.Y ))
		{
			m_vCollisionCorrection.X = vMiddleRightTile_Position.X - fObjectWidth;
			bCollision =  true;
		}
	}

	//////////////////////////////// CHECK TILES ABOVE //////////////////////////////////////////////////
	// Check Upper Tile
	if( !Get_IsTilePassable( iUpperTileIdentity ))
	{
		Vector2 vUpperTile_Position = GetSpecificTilePosition( (iObjectCurrentXTile), (iObjectCurrentYTile - 1));

		if( m_vCollisionCorrection.Y < (vUpperTile_Position.Y + GetTileHeight()) )
		{
			m_vCollisionCorrection.Y = vUpperTile_Position.Y + GetTileHeight();
			bCollision = true;
		}
	}

	// Check Upper Left Tile
	if( !Get_IsTilePassable( iUpperLeftTileIdentity ))
	{
		Vector2 vUpperLeftTile_Position = GetSpecificTilePosition( (iObjectCurrentXTile - 1), (iObjectCurrentYTile - 1));

		if( (m_vCollisionCorrection.X < (vUpperLeftTile_Position.X + GetTileWidth())) && (m_vCollisionCorrection.Y < (vUpperLeftTile_Position.Y + GetTileHeight())) )
		{ 
			m_vCollisionCorrection.X = vUpperLeftTile_Position.X + GetTileWidth();
			bCollision = true;
		}
	}

	// Check Upper Right Tile
	if( !Get_IsTilePassable( iUpperRightTileIdentity ))
	{
		Vector2 vUpperRightTile_Position = GetSpecificTilePosition( (iObjectCurrentXTile + 1), (iObjectCurrentYTile - 1));

		if( ((m_vCollisionCorrection.X + fObjectWidth) > vUpperRightTile_Position.X) && (m_vCollisionCorrection.Y < (vUpperRightTile_Position.Y + GetTileHeight())) )
		{
			m_vCollisionCorrection.X = (vUpperRightTile_Position.X - fObjectWidth) - 1.f;
			bCollision = true;
		}
	}


	//////////////////////////////// CHECK TILES BELOW //////////////////////////////////////////////////
	// Check Lower Tile
	if( !Get_IsTilePassable( iLowerTileIdentity ))
	{
		Vector2 vLowerTile_Position = GetSpecificTilePosition( (iObjectCurrentXTile), (iObjectCurrentYTile + 1) );

		if( (m_vCollisionCorrection.Y + fObjectHeight) > vLowerTile_Position.Y )
		{
			m_vCollisionCorrection.Y = vLowerTile_Position.Y - fObjectHeight;
			bCollision =  true;
		}
	}


	// Check Lower Left Tile
	if( !Get_IsTilePassable( iLowerLeftTileIdentity ))
	{
		Vector2 vLowerLeftTile_Position = GetSpecificTilePosition( (iObjectCurrentXTile - 1), (iObjectCurrentYTile + 1) );

		if( (m_vCollisionCorrection.X < (vLowerLeftTile_Position.X + GetTileWidth())) && (m_vCollisionCorrection.Y + (fObjectHeight * 0.7f)) > vLowerLeftTile_Position.Y )
		{
			m_vCollisionCorrection.X = vLowerLeftTile_Position.X + GetTileWidth();
			m_vCollisionCorrection.Y = vLowerLeftTile_Position.Y - fObjectHeight;
			bCollision =  true;
		}
	}


	// Check Lower Right Tile
	if( !Get_IsTilePassable( iLowerRightTileIdentity ))
	{
		Vector2 vLowerRightTile_Position = GetSpecificTilePosition( (iObjectCurrentXTile + 1), (iObjectCurrentYTile + 1) );

		if( ((m_vCollisionCorrection.X + fObjectWidth) > vLowerRightTile_Position.X ) && (m_vCollisionCorrection.Y + (fObjectHeight * 0.3f)) > vLowerRightTile_Position.Y )
		{
			m_vCollisionCorrection.X = vLowerRightTile_Position.X - fObjectWidth;
			m_vCollisionCorrection.Y = vLowerRightTile_Position.Y - fObjectHeight;
			bCollision =  true;
		}
	}





	////////////////////////////////////////////////////////////////////////////////
	if( bAutoFix )
	{
		vObjectPos = m_vCollisionCorrection;
	}
	////////////////////////////////////////////////////////////////////////////////
	return bCollision;
}




//===============================================
//	Check Crystal Collision
//===============================================
unsigned int CollisionHandler::CheckCrystalCollision( Vector2 &vObjectPos, float fObjectWidth, float fObjectHeight )
{
	int iObjectCurrentXTile = GetObjectCurrentXTilePosition( vObjectPos.X, fObjectWidth  ); 
	int iObjectCurrentYTile = GetObjectCurrentYTilePosition( vObjectPos.Y, fObjectHeight );

	unsigned int TileIdentity = GetSpecificTileIdentity( iObjectCurrentXTile, iObjectCurrentYTile );

	if( TileIdentity > 222 && TileIdentity < 227 ) // Crystal Identity Numbers
	{
		// Set the tile identity to Zero
		m_pLevel->SetSpecificTileIdentity( iObjectCurrentXTile, iObjectCurrentYTile, 0 );

		// Return Points
		if( TileIdentity == 223 ) { return 1;  } // Green Crystal
		if( TileIdentity == 224 ) { return 3;  } // Blue Crystal
		if( TileIdentity == 225 ) { return 5;  } // Red Crystal
		if( TileIdentity == 226 ) { return 10; } // Purple Crystal
	}

	return 0;
}




//===============================================
//	Check Star Level_Finisher Collision
//===============================================
bool CollisionHandler::CheckStarLevelFinisherCollision( Vector2 &vObjectPos, float fObjectWidth, float fObjectHeight )
{
	int iObjectCurrentXTile = GetObjectCurrentXTilePosition( vObjectPos.X, fObjectWidth  ); 
	int iObjectCurrentYTile = GetObjectCurrentYTilePosition( vObjectPos.Y, fObjectHeight );

	unsigned int TileIdentity = GetSpecificTileIdentity( iObjectCurrentXTile, iObjectCurrentYTile );

	if( TileIdentity == 222 ) // Star Level_Finsher Identity
	{
		return true;
	}

	return false;
}












//===============================================
//	Get Surrounding Tile Identities from Object
//===============================================
int* CollisionHandler::PrivatelyGetSurroundingTilesOfObject( Vector2 vObjectPos, float fObjectWidth, float fObjectHeight )
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Whatever called this is responsible for deleting it
	int* p_iSurroundingTileIdentities	= new int[4];
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	int iObjectCurrentXTile = GetObjectCurrentXTilePosition( vObjectPos.X, fObjectWidth );
	int iObjectCurrentYTile = GetObjectCurrentYTilePosition( vObjectPos.Y, fObjectHeight );
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	PrivatelyGetSurroundingTileIdentities( iObjectCurrentXTile, iObjectCurrentYTile, p_iSurroundingTileIdentities );
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	return p_iSurroundingTileIdentities;
}




//===============================================
//	Iterate Through Tiles and Get The Identities
//===============================================
void CollisionHandler::PrivatelyGetSurroundingTileIdentities( int iObjectCurrentXTile, int iObjectCurrentYTile, int* p_iSurroundingTileIdentities )
{
	p_iSurroundingTileIdentities[0] = m_pLevel->GetLevelBlockIdentity(  iObjectCurrentXTile,		(iObjectCurrentYTile - 1)	); // Above Tile
	p_iSurroundingTileIdentities[1] = m_pLevel->GetLevelBlockIdentity( (iObjectCurrentXTile - 1),	 iObjectCurrentYTile		); // Left  Tile
	p_iSurroundingTileIdentities[2] = m_pLevel->GetLevelBlockIdentity( (iObjectCurrentXTile + 1),	 iObjectCurrentYTile	    ); // Right Tile
	p_iSurroundingTileIdentities[3] = m_pLevel->GetLevelBlockIdentity(  iObjectCurrentXTile,		(iObjectCurrentYTile + 1)	); // Below Tile
}