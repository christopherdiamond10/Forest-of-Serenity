#include "Level.h"

#include "AudioManager.h"
#include "XMLHandler.h"
#include "Scene_PlayGame.h"
#include "ScreenResolution.h"
#include "Camera.h"
#include "AnimatedSprite.h"
#include "Texture.h"
#include "Weather.h"
#include "CollisionHandler.h"
#include "DeltaTime.h"
#include "DrawManager.h"
#include "GameSystemInfo.h"

#include "Enemy_Bunny.h"
#include "Enemy_Snake.h"
#include "Enemy_BlueSlime.h"
#include "Enemy_GreenSlime.h"
#include "Enemy_Imp.h"
#include "Enemy_Succubus.h"

#include <time.h>


//===============================================
//	Constructor
//===============================================
Level::Level( PlayGameState* pPlayGameState )
{
	m_pAnimatedSprite	= new AnimatedSprite();
	m_pCamera			= new Camera();
	m_pWeather			= new Weather();
	m_pPlayGameState	= pPlayGameState;
}


//===============================================
//	Destructor
//===============================================
Level::~Level()
{
	ClearLevelArray();
	ClearEnemyLists();	

	delete m_pAnimatedSprite;
	delete m_pCamera;
	delete m_pWeather;
}



//===============================================
//	OnLoad
//===============================================
void Level::OnLoad()
{
	SetupAllLevelTexturesAndTileIdentities();
	
	m_iTileSize = 20;
	m_iTileWidth = 32;
	m_iTileHeight = 32;

	AudioManager::GetInstance()->ImportAudio( "Darkness5 (Low-Pitched).ogg", "Darkness5 (Low-Pitched)", "SE" );
	m_fTimeUntilBackgroundSEPlays = (float)(rand() % 50) + 3.f;
	m_fCurrentTimeForBackgroundSE = 0.f;

	m_iLevelDataRows = 0;
	m_iLevelDataCols = 0;
	m_iLevelData = nullptr;

	m_iBackgroundTextureID = 0;

	m_fScreenDimensions[0] = 0.f;
	m_fScreenDimensions[1] = 0.f;
	

	//////////////////////////////////////////////////////////////
	m_pAnimatedSprite->OnLoad();
	//////////////////////////////////////////////////////////////
	std::list<AnimatedSpriteInfoList>  Animated2DList;	AnimatedSpriteInfoList RowOne;
	//////////////////////////////////////////////////////////////
	RowOne.DirectionList.push_back( "Right" ); RowOne.DirectionList.push_back( "Right" ); RowOne.DirectionList.push_back( "Right" ); RowOne.DirectionList.push_back( "Right" );
	//////////////////////////////////////////////////////////////
	Animated2DList.push_back( RowOne );
	//////////////////////////////////////////////////////////////
	unsigned int iMainLeftFrame = 1; unsigned int iMainRightFrame = 1; unsigned int iMainUpFrame = 1; unsigned int iMainDownFrame = 1; float fSecondsToWaitForUpdate = 0.15f;
	//////////////////////////////////////////////////////////////
	m_pAnimatedSprite->SetupAnimatedSprite( Animated2DList, fSecondsToWaitForUpdate, iMainLeftFrame, iMainRightFrame, iMainUpFrame, iMainDownFrame );
	//////////////////////////////////////////////////////////////


	m_pCamera			->OnLoad();
	m_pWeather			->OnLoad();
}


//===============================================
//	OnUnload
//===============================================
void Level::OnUnload()
{
	m_pAnimatedSprite	->OnUnload();
	m_pCamera			->OnUnload();
	m_pWeather			->OnUnload();
}


//===============================================
//	Getters
//===============================================
unsigned int Level::GetTileWidth()
{
	return m_iTileWidth;
}

unsigned int Level::GetTileHeight()
{
	return m_iTileHeight;
}

unsigned int Level::GetLevelRows()
{
	return m_iLevelDataRows;
}

unsigned int Level::GetLevelCols()
{
	return m_iLevelDataCols;
}

Vector2 Level::GetLevelBoundaries()
{
	return Vector2( ((float)m_iLevelDataCols * (float)m_iTileWidth), (((float)m_iLevelDataRows * (float)m_iTileHeight) + (float)m_iTileHeight) );
}

int	Level::GetLevelBlockIdentity( int XTile, int YTile )
{
	if( XTile < 0 || XTile >= (int)m_iLevelDataCols || YTile < 0 )
	{ 
		return 0; // Level Collision Will prevent the object from stepping on it anyway
	} 
	else if( YTile >= (int)m_iLevelDataRows )
	{
		return -1; // Death Zone
	}
	else
	{ 
		return m_iLevelData[YTile][XTile]; 
	}
}

Vector2	Level::GetLevelBlockPosition( int XTile, int YTile )
{
	Vector2 TVec2;
	TVec2.X = (float)(XTile * m_iTileWidth);
	TVec2.Y = (float)(YTile * m_iTileHeight);
	return TVec2;
}

Vector2	Level::GetCameraPosition()
{
	return m_pCamera->GetCamera_XY_Position();
}





//===============================================
//	Setters
//===============================================
void Level::SetSpecificTileIdentity( unsigned int XTile, unsigned int YTile, unsigned int Identity )
{
	m_iLevelData[YTile][XTile] = Identity;
}





//===============================================
//	Load Level
//===============================================
void Level::LoadLevel()
{
	// Clear Everything the Level has already loaded
	ClearLevelArray();
	ClearEnemyLists();
	m_pCamera->ResetCamera();
	

	// Load an XML Document and Get the necessary variables loaded
	XMLHandler::GetInstance()->LoadLevelXMLDocument( GameSystemInfo::GetInstance()->GetCurrentLevel() );

	unsigned int iRows						= XMLHandler::GetInstance()->GetLevelTileRowsCount();
	unsigned int iCols						= XMLHandler::GetInstance()->GetLevelTileColsCount();
	std::list<std::string> TempStringList	= XMLHandler::GetInstance()->GetLevelDataIdentityNames();
	std::string sAudioFileName				= XMLHandler::GetInstance()->GetLevelAudioFileName();
	unsigned int iAudioLoopStart			= XMLHandler::GetInstance()->GetLevelAudioLoopStartPoint();
	unsigned int iAudioLoopEnd				= XMLHandler::GetInstance()->GetLevelAudioLoopEndPoint();
	std::string sBackgroundImageFileName	= XMLHandler::GetInstance()->GetLevelBackGroundImageName();
	std::string sWeatherEffectOneType		= XMLHandler::GetInstance()->GetLevelWeatherEffectOneType();
	unsigned int iWeatherEffectOnePower		= XMLHandler::GetInstance()->GetLevelWeatherEffectOnePower();
	std::string sWeatherEffectTwoType		= XMLHandler::GetInstance()->GetLevelWeatherEffectTwoType();
	unsigned int iWeatherEffectTwoPower		= XMLHandler::GetInstance()->GetLevelWeatherEffectTwoPower();
	int iPlayerPos[2];						// Defined in a moment


	// May As Well Clear The XML Variables; We've got what we need
	XMLHandler::GetInstance()->SetClassVariablesToNil();



	//////////////////////////////////////////////
	// This Function Just Creates the Level Array
	MakeLevelArray( iRows, iCols );
	//////////////////////////////////////////////
	// Iterate through the entire Level Data array from the XML and set things as appropriate.
	std::list<std::string>::iterator TempStringList_Iter = TempStringList.begin();
	for( unsigned int Y = 0; Y < m_iLevelDataRows; Y++ )
	{
		for( unsigned int X = 0; X < m_iLevelDataCols; X++ )
		{
			if( TempStringList_Iter != TempStringList.end() )
			{
				if( *TempStringList_Iter == "Player_Start" )
				{
					// Save Player Specific Start Tile (As The Enemy class may change it and it is important to remember it for the Player).
					iPlayerPos[0] = X; iPlayerPos[1] = Y;
				}
				else if( *TempStringList_Iter == "Enemy_Bunny" || *TempStringList_Iter == "Enemy_Snake" || *TempStringList_Iter == "Enemy_BlueSlime" || *TempStringList_Iter == "Enemy_GreenSlime" || *TempStringList_Iter == "Enemy_Imp" || *TempStringList_Iter == "Enemy_Succubus" )
				{
					MakeLevelEnemy( *TempStringList_Iter, X, Y );
				}
				
				// Gets the Identity for the tile, which will be Zero if one of the 'if' statements is true
				unsigned int TileIdentity = SetupTileIdentity( *TempStringList_Iter );
				SetSpecificTileIdentity( X, Y, TileIdentity ); 

				TempStringList_Iter++;
			}
		}
	}
	//////////////////////////////////////////////
	// Set Player Position (Relative to a Tile)
	CollisionHandler::GetInstance()->SetObjectReservedPosition( iPlayerPos[0], iPlayerPos[1] );
	m_pPlayGameState->SetPlayerPosition( CollisionHandler::GetInstance()->GetReservedPosition() );
	//////////////////////////////////////////////
	// Setup Background Image
	if( sBackgroundImageFileName != "" )
	{
		m_iBackgroundTextureID = Texture::GetInstance()->LoadTexture( sBackgroundImageFileName, "BG" );
	}
	else
	{
		m_iBackgroundTextureID = 0;
	}
	//////////////////////////////////////////////
	// Create Weather Effects
	m_pWeather->StartWeather( sWeatherEffectTwoType, iWeatherEffectTwoPower );
	m_pWeather->StartWeather( sWeatherEffectOneType, iWeatherEffectOnePower ); // Create Effect One after effect two because it'll give sound emphasis on it.
	/////////////////////////////////////////////
	// Play Level BGM
	AudioManager::GetInstance()->ImportAudio( sAudioFileName, sAudioFileName, "bgm", 80, 100, iAudioLoopStart, iAudioLoopEnd );
	AudioManager::GetInstance()->PlaySound( sAudioFileName );
	/////////////////////////////////////////////
	// Setup Camera
	m_pCamera->SetCameraPosition(0, 0);
	m_pCamera->SetCameraDimensions( ScreenResolution::GetInstance()->GetScreenWidth(), ScreenResolution::GetInstance()->GetScreenHeight() );

	float fLeft = 0.f; float fRight  = ( (float)m_iLevelDataCols * (float)m_iTileWidth  );
	float fTop  = 0.f; float fBottom = ( (float)m_iLevelDataRows * (float)m_iTileHeight );
	m_pCamera->SetOutOfBoundsArea( fLeft, fRight, fTop, fBottom );
}



//===============================================
//	Make Level Array
//===============================================
void Level::MakeLevelArray( int iRows, int iCols )
{
	m_iLevelData = new int*[iRows];

	for( int i = 0; i < iRows; i++ )
	{
		m_iLevelData[i] = new int[iCols];
	}

	m_iLevelDataRows = iRows;
	m_iLevelDataCols = iCols;
}

//===============================================
//	Make Level Enemy
//===============================================
void Level::MakeLevelEnemy( std::string EnemyName, unsigned int XTile, unsigned int YTile )
{
	CollisionHandler::GetInstance()->SetObjectReservedPosition( XTile, YTile );


	if( EnemyName == "Enemy_Bunny" ) 
	{
		Enemy_Bunny* Bunny = new Enemy_Bunny();
		Bunny->SetPosition( CollisionHandler::GetInstance()->GetReservedPosition() );
		m_EnemyData.BunnyList.push_back( Bunny );
	}
	else if( EnemyName == "Enemy_Snake" )
	{
		Enemy_Snake* Snake = new Enemy_Snake();
		Snake->SetPosition( CollisionHandler::GetInstance()->GetReservedPosition() );
		m_EnemyData.SnakeList.push_back( Snake );
	}
	else if( EnemyName == "Enemy_BlueSlime" )
	{
		Enemy_BlueSlime* BlueSlime = new Enemy_BlueSlime();
		BlueSlime->SetPosition( CollisionHandler::GetInstance()->GetReservedPosition() );
		m_EnemyData.BlueSlimeList.push_back( BlueSlime );
	}
	else if( EnemyName == "Enemy_GreenSlime" ) 
	{
		Enemy_GreenSlime* GreenSlime = new Enemy_GreenSlime();
		GreenSlime->SetPosition( CollisionHandler::GetInstance()->GetReservedPosition() );
		m_EnemyData.GreenSlimeList.push_back( GreenSlime );
	}
	else if( EnemyName == "Enemy_Imp" )
	{
		Enemy_Imp* Imp = new Enemy_Imp();
		Imp->SetPosition( CollisionHandler::GetInstance()->GetReservedPosition() );
		m_EnemyData.ImpList.push_back( Imp );
	}
	else if( EnemyName == "Enemy_Succubus" )
	{
		Enemy_Succubus* Succubus = new Enemy_Succubus();
		Succubus->SetPosition( CollisionHandler::GetInstance()->GetReservedPosition() );
		m_EnemyData.SuccubusList.push_back( Succubus );
	}
}
//===============================================
//	Clear Level Array
//===============================================
void Level::ClearLevelArray()
{
	for ( unsigned int i = 0; i < m_iLevelDataRows; i++ )
	{
		// Delete the Arrays Within an Array
		delete[] m_iLevelData[i];
	}
	if( m_iLevelData )
	{
		// Now Delete the Mother Array
		delete[] m_iLevelData;
		m_iLevelData = nullptr;
	}

	m_iLevelDataRows = 0;
	m_iLevelDataCols = 0;
}

//===============================================
//	Clear Enemy List
//===============================================
void Level::ClearEnemyLists()
{
	// Delete Bunny
	for( std::list<Enemy_Bunny*>::iterator iter = m_EnemyData.BunnyList.begin(); iter != m_EnemyData.BunnyList.end(); iter++ )					{ delete (*iter); }

	// Delete Snake
	for( std::list<Enemy_Snake*>::iterator iter = m_EnemyData.SnakeList.begin(); iter != m_EnemyData.SnakeList.end(); iter++ )					{ delete (*iter); }

	// Delete BlueSlime
	for( std::list<Enemy_BlueSlime*>::iterator iter = m_EnemyData.BlueSlimeList.begin(); iter != m_EnemyData.BlueSlimeList.end(); iter++ )		{ delete (*iter); }

	// Delete GreenSlime
	for( std::list<Enemy_GreenSlime*>::iterator iter = m_EnemyData.GreenSlimeList.begin(); iter != m_EnemyData.GreenSlimeList.end(); iter++ )	{ delete (*iter); }

	// Delete Imp
	for( std::list<Enemy_Imp*>::iterator iter = m_EnemyData.ImpList.begin(); iter != m_EnemyData.ImpList.end(); iter++ )						{ delete (*iter); }

	// Delete Succubus
	for( std::list<Enemy_Succubus*>::iterator iter = m_EnemyData.SuccubusList.begin(); iter != m_EnemyData.SuccubusList.end(); iter++ )			{ delete (*iter); }

	// Clear Lists 
	m_EnemyData.BunnyList.clear();	m_EnemyData.SnakeList.clear();	m_EnemyData.BlueSlimeList.clear(); m_EnemyData.GreenSlimeList.clear(); m_EnemyData.ImpList.clear();
}














//===============================================
//	Update
//===============================================
void Level::Update( Vector2 vPlayerPos )
{
	if((m_fCurrentTimeForBackgroundSE += DeltaTime::GetInstance()->GetDeltaTime()) >= m_fTimeUntilBackgroundSEPlays)
	{
		m_fCurrentTimeForBackgroundSE = 0.f;
		m_fTimeUntilBackgroundSEPlays = (float)(rand() % 30) + 20.f;
		AudioManager::GetInstance()->PlaySound( "Darkness5 (Low-Pitched)" );
	}

	m_pCamera->Update( vPlayerPos );
	m_pWeather->Update( m_pCamera->GetCamera_XY_Position() );
	m_pAnimatedSprite->Update();
	UpdateLevelEnemies();
}




void Level::UpdateLevelEnemies()
{
	// Update Bunny
	for( std::list<Enemy_Bunny*>::iterator iter = m_EnemyData.BunnyList.begin(); iter != m_EnemyData.BunnyList.end(); iter++ )
	{
		if( (*iter)->GetAlive() )
		{
			(*iter)->Update( m_pCamera->GetCamera_XY_Position() );
		}
	}

	// Update Snake
	for( std::list<Enemy_Snake*>::iterator iter = m_EnemyData.SnakeList.begin(); iter != m_EnemyData.SnakeList.end(); iter++ )
	{
		if( (*iter)->GetAlive() )
		{
			(*iter)->Update( m_pCamera->GetCamera_XY_Position() );
		}
	}

	// Update BlueSlime
	for( std::list<Enemy_BlueSlime*>::iterator iter = m_EnemyData.BlueSlimeList.begin(); iter != m_EnemyData.BlueSlimeList.end(); iter++ )
	{
		if( (*iter)->GetAlive() )
		{
			(*iter)->Update( m_pCamera->GetCamera_XY_Position() );
		}
	}

	// Update GreenSlime
	for( std::list<Enemy_GreenSlime*>::iterator iter = m_EnemyData.GreenSlimeList.begin(); iter != m_EnemyData.GreenSlimeList.end(); iter++ )
	{
		if( (*iter)->GetAlive() )
		{
			(*iter)->Update( m_pCamera->GetCamera_XY_Position() );
		}
	}

	// Update Imp
	for( std::list<Enemy_Imp*>::iterator iter = m_EnemyData.ImpList.begin(); iter != m_EnemyData.ImpList.end(); iter++ )
	{
		if( (*iter)->GetAlive() )
		{
			(*iter)->Update( m_pCamera->GetCamera_XY_Position() );
		}
	}

	// Update Succubus
	for( std::list<Enemy_Succubus*>::iterator iter = m_EnemyData.SuccubusList.begin(); iter != m_EnemyData.SuccubusList.end(); iter++ )
	{
		if( (*iter)->GetAlive() )
		{
			(*iter)->Update( m_pCamera->GetCamera_XY_Position() );
		}
	}
}






//===============================================
//	Update Array Size
//===============================================
void Level::UpdateArrayDrawingSizeandCameraBoundaries()
{
	//////////////// Update Screen Dimensions Array //////////////// 
	m_fScreenDimensions[0] = ScreenResolution::GetInstance()->GetScreenWidth();
	m_fScreenDimensions[1] = ScreenResolution::GetInstance()->GetScreenHeight();



	//////////////// Update Array Size ////////////////
	float fTempTileWidth  = (float)m_iTileWidth;
	float fTempTileHeight = (float)m_iTileHeight;

	ScreenResolution::GetInstance()->GetScaleSizeForScreenSize( fTempTileWidth, fTempTileHeight, (float)m_iTileSize, (float)m_iTileSize );

	m_iTileWidth  = (int)fTempTileWidth;
	m_iTileHeight = (int)fTempTileHeight;



	//////////////// Update Camera Boundaries ////////////////
	float fLeft = 0.f; float fRight  = ( (float)m_iLevelDataCols * (float)m_iTileWidth  );
	float fTop  = 0.f; float fBottom = ( (float)m_iLevelDataRows * (float)m_iTileHeight );
	m_pCamera->SetOutOfBoundsArea( fLeft, fRight, fTop, fBottom );
}








//===============================================
//	Draw
//===============================================
void Level::Draw()
{
	
	// Get Camera Position
	float* fCameraPos = m_pCamera->GetCamera_XYWH_Position();

	// Draw BackGround Image
	if( m_iBackgroundTextureID > 0 ) { DrawManager::GetInstance()->DrawTexturef( fCameraPos[0], fCameraPos[1], fCameraPos [2], fCameraPos[3], m_iBackgroundTextureID, false ); }
	
	// Draw Weather Behind Level
	m_pWeather->Draw(1);

	// Draw the Blocks that are within the Camera Area
	DrawLevelBlocks( fCameraPos );

	// Draw Enemies
	DrawLevelEnemies();

	// Draw Weather In Front of Level
	m_pWeather->Draw(2);

	delete[] fCameraPos;


}


//===============================================
//	Draw Level Blocks
//===============================================
void Level::DrawLevelBlocks( float* fCameraPosArray )
{
	// Iterate through the Level Array
	for( unsigned int Y = 0; Y < m_iLevelDataRows; Y++ )
	{
		// If Y is not within the Camera Range, skip to next
		if( IsLevelBlockWithinCameraArea( fCameraPosArray, true, Y )) 
		{
			// Now Iterate Through the X Arrays
			for( unsigned int X = 0; X < m_iLevelDataCols; X++ )
			{
				// No need to worry about drawing it, if its identity is Zero
				if( m_iLevelData[Y][X] != 0 )
				{
					// Again, skip if not within Camera Range
					if( IsLevelBlockWithinCameraArea( fCameraPosArray, false, X ))
					{
						// Crystal Identities are 223, 224, 225 & 226, So draw animated crystal if this is the case
						if( m_iLevelData[Y][X] > 222 && m_iLevelData[Y][X] < 227 )
						{
							m_pAnimatedSprite->SetCurrentTexture( m_LevelIdentityTileArray[(m_iLevelData[Y][X] - 1)].TextureID );
							m_pAnimatedSprite->Draw( (float)(X * m_iTileWidth), (float)(Y * m_iTileHeight), (float)m_iTileWidth, (float)m_iTileHeight, false, 0 );
						}
						// Level Finishing Star Identity is 222, forcing it to change colours so that it looks more unique and easier to notice
						else if( m_iLevelData[Y][X] == 222 )
						{
							static unsigned int Time = 0;
							static int R, G, B;
							if( Time != (unsigned int)time(0) )
							{
								Time = (unsigned int)time(0);
								R = rand() % 256;
								G = rand() % 256;
								B = rand() % 256;
							}
							DrawManager::GetInstance()->DrawTexturei( (X * m_iTileWidth), (Y * m_iTileHeight), m_iTileWidth, m_iTileHeight, R, G, B, m_LevelIdentityTileArray[(m_iLevelData[Y][X] - 1)].TextureID, false);
						}
						else
						{
							// Now draw the level block
							DrawManager::GetInstance()->DrawTexturei( (X * m_iTileWidth), (Y * m_iTileHeight), m_iTileWidth, m_iTileHeight, m_LevelIdentityTileArray[(m_iLevelData[Y][X] - 1)].TextureID, false, 0 );
						}
					}
				}
			}
		}
	}
}




//===============================================
//	Draw Level Enemies
//===============================================
void Level::DrawLevelEnemies()
{
	// Draw Bunny
	for( std::list<Enemy_Bunny*>::iterator iter = m_EnemyData.BunnyList.begin(); iter != m_EnemyData.BunnyList.end(); iter++ )
	{
		if( (*iter)->GetAlive() )
		{
			(*iter)->Draw();
		}
	}

	// Draw Snake
	for( std::list<Enemy_Snake*>::iterator iter = m_EnemyData.SnakeList.begin(); iter != m_EnemyData.SnakeList.end(); iter++ )
	{
		if( (*iter)->GetAlive() )
		{
			(*iter)->Draw();
		}
	}

	// Draw BlueSlime
	for( std::list<Enemy_BlueSlime*>::iterator iter = m_EnemyData.BlueSlimeList.begin(); iter != m_EnemyData.BlueSlimeList.end(); iter++ )
	{
		if( (*iter)->GetAlive() )
		{
			(*iter)->Draw();
		}
	}

	// Draw GreenSlime
	for( std::list<Enemy_GreenSlime*>::iterator iter = m_EnemyData.GreenSlimeList.begin(); iter != m_EnemyData.GreenSlimeList.end(); iter++ )
	{
		if( (*iter)->GetAlive() )
		{
			(*iter)->Draw();
		}
	}

	// Draw Imp
	for( std::list<Enemy_Imp*>::iterator iter = m_EnemyData.ImpList.begin(); iter != m_EnemyData.ImpList.end(); iter++ )
	{
		if( (*iter)->GetAlive() )
		{
			(*iter)->Draw();
		}
	}

	// Draw Succubus
	for( std::list<Enemy_Succubus*>::iterator iter = m_EnemyData.SuccubusList.begin(); iter != m_EnemyData.SuccubusList.end(); iter++ )
	{
		if( (*iter)->GetAlive() )
		{
			(*iter)->Draw();
		}
	}
}




//===============================================
//	 Is Level Block Within Camera Area?
//===============================================
bool Level::IsLevelBlockWithinCameraArea( float* fCameraPosArray, bool CheckYPos, int iTileToCheck )
{
	//----------------------------------------------------------------------
	// fCameraPosArray[0] == XPos, [1] == YPos, [2] == Width, [3] == Height
	//----------------------------------------------------------------------

	if( CheckYPos )
	{
		if( (((iTileToCheck * m_iTileHeight) + m_iTileHeight) > fCameraPosArray[1]) && ((iTileToCheck * m_iTileHeight) < (fCameraPosArray[1] + fCameraPosArray[3])) ) 
		{
			return true;
		}
	}

	else
	{
		if( (((iTileToCheck * m_iTileWidth) + m_iTileWidth) > fCameraPosArray[0]) && ((iTileToCheck * m_iTileWidth) < (fCameraPosArray[0] + fCameraPosArray[2])) )
		{
			return true;
		}
	}

	return false;
}







//=================================
//	Setup All Level Textures And Tile Identities
//=================================
void Level::SetupAllLevelTexturesAndTileIdentities()
{
	// This May Take awhile, go get some coffee ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
	unsigned int iCurrentElement = 0;
	/////////////////////////////////////////////
	// Platforms
	/////////////////////////////////////////////
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Platform1A.png",		"Platform" );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Platform1B.png",		"Platform" );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Platform1C.png",		"Platform" );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Platform1H.png",		"Platform" );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Platform1J.png",		"Platform" );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Platform1K.png",		"Platform" );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Platform1L.png",		"Platform" );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Platform1M.png",		"Platform" );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Log.png",				"Platform" );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Log1A.png",				"Platform" );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Log1B.png",				"Platform" );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Log1C.png",				"Platform" );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Log2A.png",				"Platform" );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Log2B.png",				"Platform" );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Log2C.png",				"Platform" );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Rock.png",				"Platform" );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Special1A.png" ,		"Platform" );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Special1B.png" ,		"Platform" );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Special1C.png" ,		"Platform" );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Special1D.png" ,		"Platform" );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Platform2A.png",		"Platform" );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Platform2B.png",		"Platform" );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Platform2C.png",		"Platform" );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Platform2D.png",		"Platform" );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Platform2E.png",		"Platform" );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Platform2F.png",		"Platform" );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Platform2G.png",		"Platform" );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Platform3A.png",		"Platform" );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Platform3B.png",		"Platform" );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Platform3C.png",		"Platform" );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Platform3D.png",		"Platform" );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Platform3E.png",		"Platform" );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Platform3F.png",		"Platform" );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Platform3G.png",		"Platform" );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Platform3H.png",		"Platform" );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Platform3I.png",		"Platform" );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Platform3J.png",		"Platform" );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Platform3K.png",		"Platform" );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Platform3L.png",		"Platform" );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Platform4A.png",		"Platform" );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Platform4B.png",		"Platform" );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Platform4C.png",		"Platform" );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Platform5A.png",		"Platform" );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Platform5B.png",		"Platform" );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Platform5C.png",		"Platform" );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Platform5D.png",		"Platform" );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Platform5E.png",		"Platform" );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Platform6A.png",		"Platform" );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Platform6B.png",		"Platform" );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Platform7A.png",		"Platform" );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Platform7B.png",		"Platform" );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Platform7C.png",		"Platform" );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Platform8A.png",		"Platform" );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Platform8B.png",		"Platform" );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Platform8C.png",		"Platform" );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
																						 
																																					 
																																					 
																																					 
	/////////////////////////////////////////////																									 
	// Walls																																		 
	/////////////////////////////////////////////																									 
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Platform1WallA.png",	"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Platform1WallB.png",	"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Platform1WallC.png",	"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Platform1WallD.png",	"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wood1A.png",			"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wood1B.png",			"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wood1C.png",			"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wood2A.png",			"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wood2B.png",			"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wood2C.png",			"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wood3A.png",			"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wood3B.png",			"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wood3C.png",			"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wood3D.png",			"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wood4A.png",			"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wood4B.png",			"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wood4C.png",			"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wood4D.png",			"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wood4E.png",			"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wood4F.png",			"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wall2P.png",			"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wall2Q.png",			"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wall2R.png",			"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wall2S.png",			"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wall2T.png",			"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wall2K.png",			"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wall2L.png",			"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wall2M.png",			"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wall2N.png",			"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wall2O.png",			"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wall2F.png",			"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wall2G.png",			"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wall2H.png",			"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wall2I.png",			"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wall2J.png",			"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wall2B.png",			"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wall2C.png",			"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wall2D.png",			"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wall2E.png",			"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wall2A.png",			"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wall1F.png",			"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wall1G.png",			"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wall1L.png",			"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wall1C.png",			"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wall1B.png",			"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wall1D.png",			"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wall1I.png",			"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wall1H.png",			"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wall1K.png",			"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wall1J.png",			"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wall1O.png",			"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wall1N.png",			"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wall1M.png",			"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wall1P.png",			"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wall1Q.png",			"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wall1E.png",			"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wall1A.png",			"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wall2EdgeL.png",		"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wall2EdgeK.png",		"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wall2EdgeF.png",		"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wall2EdgeG.png",		"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wall2EdgeH.png",		"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wall2EdgeI.png",		"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wall2EdgeJ.png",		"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wall2EdgeB.png",		"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wall2EdgeC.png",		"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wall2EdgeD.png",		"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wall2EdgeE.png",		"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wall2EdgeA.png",		"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wall2X.png",			"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wall2U.png",			"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wall2V.png",			"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Wall2W.png",			"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Platform5WallD.png",	"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Platform5WallC.png",	"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Platform5WallB.png",	"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Platform5WallA.png",	"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Platform4WallA.png",	"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Platform4WallB.png",	"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Platform4WallC.png",	"Wall"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
																						 
																																					 
																																					 
																																					 
	/////////////////////////////////////////////																									 
	// Others																																		 
	/////////////////////////////////////////////																									 
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Flower.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Special1E.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Special1F.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Special1G.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Special1H.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Special1I.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Special1J.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Special1K.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Special1L.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Special1M.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Special1N.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Statue1A.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Statue1B.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Statue1C.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Statue1D.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Statue1E.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Statue1F.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Statue2A.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Statue2B.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Statue2C.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Statue2D.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Vines1A.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Vines1B.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Vines1C.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Vines2A.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Vines2B.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Vines2C.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Snowman1A.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Snowman1B.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Snowman1C.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Snowman1D.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Shading4P.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Shading4K.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Shading4L.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Shading4M.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Shading4N.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Shading4O.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Shading4F.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Shading4G.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Shading4H.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Shading4I.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Shading4J.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Shading4E.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Shading4C.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Shading4B.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Shading4A.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Shading4D.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Shading3B.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Shading3C.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Shading3D.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Shading3E.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Shading3F.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Shading3G.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Shading3H.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Shading3I.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Shading3J.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Shading3K.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Shading3A.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Shading2F.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Shading2K.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Shading2M.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Shading2H.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Shading2C.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Shading2E.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Shading2J.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Shading2I.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Shading2D.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Shading2G.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Shading2L.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Shading2B.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Shading2A.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Shading1N.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Shading1M.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Shading1E.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Shading1K.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Shading1B.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Shading1C.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Shading1D.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Shading1G.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Shading1F.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Shading1H.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Shading1I.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Shading1J.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Shading1L.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Shading1A.png",			"Other"	   );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
																																					 
																																					 
	/////////////////////////////////////////////																									 
	// Events																																		 
	/////////////////////////////////////////////																									 
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Checkpoint1A.png",		 "Sprite"  );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Star_LevelFinisher.png", "Sprite"  );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Green_Crystal.png",		 "Sprite"  );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Blue_Crystal.png",		 "Sprite"  );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Red_Crystal.png",		 "Sprite"  );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
	m_LevelIdentityTileArray[iCurrentElement].TextureID = Texture::GetInstance()->LoadTexture( "Purple_Crystal.png",	 "Sprite"  );			m_LevelIdentityTileArray[iCurrentElement].Identity = iCurrentElement + 1;	iCurrentElement++;
}








//=================================
//	Setup Tile Identities
//=================================
unsigned int Level::SetupTileIdentity( std::string sIdentityName )
{
	unsigned int iElementID = 0;

	if( sIdentityName == "Platform1A"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Platform1B"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Platform1C"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Platform1H"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Platform1J"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Platform1K"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Platform1L"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Platform1M"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Log"				   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Log1A"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Log1B"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Log1C"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Log2A"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Log2B"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Log2C"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
	if( sIdentityName == "Rock"				   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Special1A"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Special1B"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Special1C"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Special1D"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Platform2A"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Platform2B"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Platform2C"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Platform2D"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Platform2E"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Platform2F"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Platform2G"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Platform3A"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Platform3B"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Platform3C"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Platform3D"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Platform3E"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Platform3F"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Platform3G"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Platform3H"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Platform3I"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Platform3J"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Platform3K"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Platform3L"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Platform4A"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Platform4B"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Platform4C"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Platform5A"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Platform5B"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Platform5C"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Platform5D"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Platform5E"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Platform6A"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Platform6B"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Platform7A"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Platform7B"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Platform7C"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
	if( sIdentityName == "Platform8A"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Platform8B"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Platform8C"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
											   									   
											   									   
            								   									   
    if( sIdentityName == "Platform1WallA"	   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Platform1WallB"	   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Platform1WallC"	   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Platform1WallD"	   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wood1A"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wood1B"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wood1C"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wood2A"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wood2B"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wood2C"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wood3A"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wood3B"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wood3C"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wood3D"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wood4A"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wood4B"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wood4C"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wood4D"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wood4E"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wood4F"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wall2P"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wall2Q"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wall2R"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wall2S"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wall2T"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wall2K"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wall2L"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wall2M"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wall2N"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wall2O"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wall2F"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wall2G"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wall2H"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wall2I"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wall2J"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wall2B"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wall2C"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wall2D"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wall2E"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wall2A"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wall1F"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wall1G"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wall1L"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wall1C"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wall1B"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wall1D"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wall1I"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wall1H"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wall1K"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wall1J"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wall1O"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wall1N"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wall1M"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wall1P"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wall1Q"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wall1E"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wall1A"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wall2EdgeL"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wall2EdgeK"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wall2EdgeF"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wall2EdgeG"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wall2EdgeH"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wall2EdgeI"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wall2EdgeJ"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wall2EdgeB"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wall2EdgeC"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wall2EdgeD"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wall2EdgeE"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wall2EdgeA"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wall2X"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wall2U"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wall2V"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Wall2W"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Platform5WallD"	   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Platform5WallC"	   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Platform5WallB"	   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Platform5WallA"	   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Platform4WallA"	   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Platform4WallB"	   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Platform4WallC"	   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
											   									   
											   									   
           									   									   
    if( sIdentityName == "Flower"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Special1E"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Special1F"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Special1G"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Special1H"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Special1I"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Special1J"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Special1K"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Special1L"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Special1M"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Special1N"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Statue1A"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Statue1B"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Statue1C"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Statue1D"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Statue1E"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Statue1F"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Statue2A"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Statue2B"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Statue2C"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Statue2D"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Vines1A"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Vines1B"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Vines1C"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Vines2A"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Vines2B"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Vines2C"			   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Snowman1A"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Snowman1B"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Snowman1C"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Snowman1D"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Shading4P"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Shading4K"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Shading4L"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Shading4M"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Shading4N"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Shading4O"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Shading4F"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Shading4G"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Shading4H"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Shading4I"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Shading4J"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Shading4E"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Shading4C"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Shading4B"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Shading4A"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Shading4D"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Shading3B"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Shading3C"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Shading3D"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Shading3E"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Shading3F"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Shading3G"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Shading3H"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Shading3I"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Shading3J"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Shading3K"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Shading3A"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Shading2F"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Shading2K"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Shading2M"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Shading2H"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Shading2C"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Shading2E"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Shading2J"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Shading2I"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Shading2D"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Shading2G"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Shading2L"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Shading2B"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Shading2A"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Shading1N"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Shading1M"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Shading1E"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Shading1K"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Shading1B"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Shading1C"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Shading1D"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Shading1G"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Shading1F"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Shading1H"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Shading1I"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Shading1J"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Shading1L"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
    if( sIdentityName == "Shading1A"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
											   									   
											   									   
																				   
    if( sIdentityName == "Checkpoint1A"		   )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
	if( sIdentityName == "Star_LevelFinisher"  )		{ return m_LevelIdentityTileArray[iElementID].Identity; }	       iElementID++;
	if( sIdentityName == "Green_Crystal"       )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
	if( sIdentityName == "Blue_Crystal"        )		{ return m_LevelIdentityTileArray[iElementID].Identity; }	       iElementID++;
	if( sIdentityName == "Red_Crystal"	       )		{ return m_LevelIdentityTileArray[iElementID].Identity; }		   iElementID++;
	if( sIdentityName == "Purple_Crystal"      )		{ return m_LevelIdentityTileArray[iElementID].Identity; }	       iElementID++;





	// Otherwise you are NULL
	return 0;
}