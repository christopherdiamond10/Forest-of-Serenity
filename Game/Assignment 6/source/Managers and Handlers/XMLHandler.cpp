#include "XMLHandler.h"
#include <assert.h>
#include <sstream>

#include "Texture.h"
#include "AudioManager.h"


XMLHandler* XMLHandler::m_Instance = nullptr;
//==============================================
//			Get XMLHandler Instance
//==============================================
XMLHandler* XMLHandler::GetInstance()
{
	return m_Instance;
}


//==============================================
//		   Constructor & Destructor
//==============================================
XMLHandler::XMLHandler()
{
	if( m_Instance == nullptr)
	{ 
		m_Instance = this; 

		m_sLocation = "./bin/XML/";
		m_sFilename = " ";
	} 
	else 
	{ 
		assert(0); 
	}
}

XMLHandler::~XMLHandler()
{

}



//==============================================
//			OnLoad
//==============================================
void XMLHandler::OnLoad()
{
	SetClassVariablesToNil();
}

//==============================================
//			OnUnload
//==============================================
void XMLHandler::OnUnload()
{

}










//==============================================
//			Get Animation Variables
//==============================================
int XMLHandler::GetAnimationTotalFrames()										{  return m_iAnimationTotalFrames;		    }
int XMLHandler::GetAnimationPartialAnimationCompleteFrame()						{  return m_iPartialAnimationCompleteFrame; }
bool XMLHandler::Get_IsAnimationRelativeToScreen()								{  return m_bAnimationRelativeToScreen;	    }
std::list<AnimatedFrameInfo> XMLHandler::GetAnimationAnimFrameInfoList()		{  return m_lAnimationAnimFrameInfoList;	}
//==============================================
//			Get Level Variables
//==============================================
unsigned int XMLHandler::GetLevelTileRowsCount()								{  return m_iLevelTileRowsCount;		    }
unsigned int XMLHandler::GetLevelTileColsCount()								{  return m_iLevelTileColsCount;		    }
unsigned int XMLHandler::GetLevelAudioLoopStartPoint()							{  return m_iLevelAudioLoopStart;		    }
unsigned int XMLHandler::GetLevelAudioLoopEndPoint()							{  return m_iLevelAudioLoopEnd;			    }
std::list<std::string> XMLHandler::GetLevelDataIdentityNames()					{  return m_lLevelDataIdentityNamesList;    }
std::string XMLHandler::GetLevelBackGroundImageName()							{  return m_sLevelBackgroundImageName;	    }
std::string XMLHandler::GetLevelAudioFileName()									{  return m_sLevelAudioFileName;		    }
std::string XMLHandler::GetLevelWeatherEffectOneType()							{  return m_sLevelWeatherEffectOneType;	    }
std::string XMLHandler::GetLevelWeatherEffectTwoType()							{  return m_sLevelWeatherEffectTwoType;	    }
unsigned int XMLHandler::GetLevelWeatherEffectOnePower()						{  return m_iLevelWeatherEffectOnePower;    }
unsigned int XMLHandler::GetLevelWeatherEffectTwoPower()						{  return m_iLevelWeatherEffectTwoPower;    }

bool XMLHandler::Get_LevelXMLExists( std::string sFilename )
{
	std::string sXML  = m_sLocation;
	sXML			 += "Levels/";
	sXML			 += sFilename;


	TiXmlDocument* pXMLDoc		= new TiXmlDocument( sXML.c_str() );
	bool bXML_Exists			= pXMLDoc->LoadFile();

	delete pXMLDoc;
	return bXML_Exists;
}







//==============================================
//			Set Document Location
//==============================================
void XMLHandler::SetXMLDocumentLocation( std::string sLocation )
{
	m_sLocation = sLocation;
}

//==============================================
//		  Set Class Variables To Nil
//==============================================
void XMLHandler::SetClassVariablesToNil()
{
	m_iAnimationTotalFrames				= 0;
	m_iPartialAnimationCompleteFrame	= 0;
	m_bAnimationRelativeToScreen		= false;
	////////////////////////////////////////////////////////////////////////
	for( std::list<AnimatedFrameInfo>::iterator iter = m_lAnimationAnimFrameInfoList.begin(); iter != m_lAnimationAnimFrameInfoList.end(); iter++ )
	{
		delete[] iter->SprInfoList;
	}
	m_lAnimationAnimFrameInfoList.clear();
	////////////////////////////////////////////////////////////////////////


	m_iLevelTileRowsCount				= NULL;
	m_iLevelTileColsCount				= NULL;
	m_lLevelDataIdentityNamesList.clear();
	m_sLevelBackgroundImageName			= "";
	m_sLevelAudioFileName				= "";
	m_iLevelAudioLoopStart				= NULL;
	m_iLevelAudioLoopEnd				= NULL;
	m_sLevelWeatherEffectOneType		= "";
	m_iLevelWeatherEffectOnePower		= NULL;
	m_sLevelWeatherEffectTwoType		= "";
	m_iLevelWeatherEffectTwoPower		= NULL;
}





//==============================================
//		   Load Animation XML Document
//==============================================
void XMLHandler::LoadAnimationXMLDocument( std::string sFilename )
{
	m_sFilename  = sFilename;
	sFilename	 = m_sLocation;
	sFilename	+= "Animations/";
	sFilename	+= m_sFilename;


	TiXmlDocument* pXMLDoc				 = new TiXmlDocument( sFilename.c_str() );
	TiXmlElement*  pRoot				 = nullptr;
	TiXmlElement*  pCurrentChild		 = nullptr;
	TiXmlElement*  pCurrentChildElement	 = nullptr;



	// Load XML
	if( pXMLDoc && pXMLDoc->LoadFile() )
	{
		

		pRoot = pXMLDoc->FirstChildElement( "Animation" );
		if ( pRoot )
		{
			////////////////////////////////////////////////////////
			// Get Animaiton Info
			pCurrentChild = pRoot->FirstChildElement( "AnimationInfo" );
			if( pCurrentChild )
			{
				m_iAnimationTotalFrames			  = atoi(pCurrentChild->Attribute("TotalFrames"));
				m_iPartialAnimationCompleteFrame  = atoi(pCurrentChild->Attribute("PartialAnimationCompletionFrame"));
				m_bAnimationRelativeToScreen      = atoi(pCurrentChild->Attribute("PartialAnimationCompletionFrame")) == 1;
			}


			////////////////////////////////////////////////////////
			// Get All Elements in the LevelData Array
			for( int i = 0; i < m_iAnimationTotalFrames; i++ )
			{
				// Settling In
				std::stringstream IntToString (std::stringstream::in | std::stringstream::out); IntToString << (i + 1);
				std::string sElementName = "Frame"; sElementName += IntToString.str();
				pCurrentChild = pRoot->FirstChildElement(sElementName.c_str());


				// Making the New Element For the List
				AnimatedFrameInfo AFI;
				AFI.iTotalSprites			= atoi(pCurrentChild->Attribute("TotalSprites"));
				AFI.fWaitTimeTillNextFrame	= (float)(atof(pCurrentChild->Attribute("WaitTillNextFrame")) * 0.001);
				AFI.bTintScreen				= atoi(pCurrentChild->Attribute("TintScreen")) == 1;
				AFI.iTintScreenColour[0]	= atoi(pCurrentChild->Attribute("ScreenTintRed"));
				AFI.iTintScreenColour[1]	= atoi(pCurrentChild->Attribute("ScreenTintGreen"));
				AFI.iTintScreenColour[2]	= atoi(pCurrentChild->Attribute("ScreenTintBlue"));
				AFI.iTintScreenColour[3]	= atoi(pCurrentChild->Attribute("ScreenTintAlpha"));
				AFI.bTintCharacter			= atoi(pCurrentChild->Attribute("TintCharacter")) == 1;
				AFI.iTintScreenColour[0]	= atoi(pCurrentChild->Attribute("CharacterTintRed"));
				AFI.iTintScreenColour[1]	= atoi(pCurrentChild->Attribute("CharacterTintGreen"));
				AFI.iTintScreenColour[2]	= atoi(pCurrentChild->Attribute("CharacterTintBlue"));
				AFI.sSoundFilename			= pCurrentChild->Attribute("SoundFilename");

				// Setting Up Sound
				if(AFI.sSoundFilename != "" && AFI.sSoundFilename != "(No Sound)")
				{
					AFI.sSoundFilename += ".ogg";
					AudioManager::GetInstance()->ImportAudio(AFI.sSoundFilename, AFI.sSoundFilename, "SE");
				}
				else
				{
					AFI.sSoundFilename = "";
				}


				////////////// Make Sprite List ///////////////
				AFI.SprInfoList = new SpriteInfo[AFI.iTotalSprites];
				for( int j = 0; j < AFI.iTotalSprites; j++ )
				{
					// Settling in Again
					std::stringstream sElementToString (std::stringstream::in | std::stringstream::out); sElementToString << (j + 1);
					std::string sChildElementName = "Sprite"; sChildElementName += sElementToString.str();
					pCurrentChildElement = pCurrentChild->FirstChildElement(sChildElementName.c_str());
					
					// Making New Sprite Info Element for AFI Sprite List
					SpriteInfo SprInfo;
					SprInfo.TextureID	= Texture::GetInstance()->LoadTexture(pCurrentChildElement->Attribute("TextureName"), "Animation");
					SprInfo.X			= atoi(pCurrentChildElement->Attribute("X"));
					SprInfo.Y			= atoi(pCurrentChildElement->Attribute("Y"));
					SprInfo.W			= atoi(pCurrentChildElement->Attribute("W"));
					SprInfo.H			= atoi(pCurrentChildElement->Attribute("H"));
					SprInfo.UvStartX	= (float)atof(pCurrentChildElement->Attribute("UVCoordStartX"));
					SprInfo.UvStartY	= (float)atof(pCurrentChildElement->Attribute("UVCoordStartY"));
					SprInfo.UvEndX		= (float)atof(pCurrentChildElement->Attribute("UVCoordEndX"));
					SprInfo.UvEndY		= (float)atof(pCurrentChildElement->Attribute("UVCoordEndY"));

					// Add to the AFI Sprite List
					AFI.SprInfoList[j] = SprInfo;
				}

				// Add to the List
				m_lAnimationAnimFrameInfoList.push_back(AFI);
			}
		}
	}
	delete pXMLDoc;
}


//==============================================
//		   Load Level XML Document
//==============================================
void XMLHandler::LoadLevelXMLDocument( std::string sFilename )
{
	m_sFilename  = sFilename;
	sFilename	 = m_sLocation;
	sFilename	+= "Levels/";
	sFilename	+= m_sFilename;


	TiXmlDocument* pXMLDoc				 = new TiXmlDocument( sFilename.c_str() );
	TiXmlElement*  pRoot				 = nullptr;
	TiXmlElement*  pCurrentChild		 = nullptr;
	TiXmlElement*  pCurrentChildElement	 = nullptr;


	// Load XML
	if( pXMLDoc && pXMLDoc->LoadFile() )
	{
		pRoot = pXMLDoc->FirstChildElement( "LevelInfo" );

		if ( pRoot )
		{
			////////////////////////////////////////////////////////
			// Get Total Level Rows/Cols
			pCurrentChild = pRoot->FirstChildElement( "LevelSize" );
			if( pCurrentChild )
			{
				m_iLevelTileRowsCount = atoi(pCurrentChild->Attribute("Rows"));
				m_iLevelTileColsCount = atoi(pCurrentChild->Attribute("Cols"));
			}
			////////////////////////////////////////////////////////
			// Get All Elements in the LevelData Array
			pCurrentChild = pRoot->FirstChildElement( "LevelData" );
			pCurrentChildElement = pCurrentChild->FirstChildElement( "Row" );

			while( pCurrentChildElement )
			{
				for( unsigned int j = 0; j < m_iLevelTileColsCount; j++ )
				{
					int iCurrentColPosition = (j + 1);
					std::stringstream IntToString (std::stringstream::in | std::stringstream::out);
					IntToString << iCurrentColPosition;
					std::string sAttributeName = "Col"; sAttributeName += IntToString.str();

					m_lLevelDataIdentityNamesList.push_back(pCurrentChildElement->Attribute(sAttributeName.c_str()));
				}
				pCurrentChildElement = pCurrentChildElement->NextSiblingElement( "Row" );
			}
			////////////////////////////////////////////////////////
			// Get Background image info
			pCurrentChild = pRoot->FirstChildElement( "BackgroundImage" );
			if( pCurrentChild )
			{
				m_sLevelBackgroundImageName = pCurrentChild->Attribute("Name");
			}
			////////////////////////////////////////////////////////
			// Get Audio Info
			pCurrentChild = pRoot->FirstChildElement( "AudioName" );
			if( pCurrentChild )
			{
				m_sLevelAudioFileName  = pCurrentChild->Attribute("Name");
				m_iLevelAudioLoopStart = atoi(pCurrentChild->Attribute("LoopStart"));
				m_iLevelAudioLoopEnd   = atoi(pCurrentChild->Attribute("LoopEnd"));
			}
			////////////////////////////////////////////////////////
			// Get Weather Info
			pCurrentChild = pRoot->FirstChildElement( "Weather" );
			if( pCurrentChild )
			{
				pCurrentChildElement = pCurrentChild->FirstChildElement( "EffectOne" );
				if( pCurrentChildElement )
				{
					m_sLevelWeatherEffectOneType = pCurrentChildElement->Attribute("Type");
					m_iLevelWeatherEffectOnePower = atoi(pCurrentChildElement->Attribute("Power"));
				}

				pCurrentChildElement = pCurrentChild->FirstChildElement( "EffectTwo" );
				if( pCurrentChildElement )
				{
					m_sLevelWeatherEffectTwoType = pCurrentChildElement->Attribute("Type");
					m_iLevelWeatherEffectTwoPower = atoi(pCurrentChildElement->Attribute("Power"));
				}
			}
		} // If pRoot
	}
	delete pXMLDoc;
}




//==============================================
//		   Load Options XML Document
//==============================================
void XMLHandler::LoadOptionsXMLDocument( std::string sFilename )
{

}

//==============================================
//		   Write Options XML Document
//==============================================
void XMLHandler::WriteOptionsXMLDocument( std::string sFilename )
{

}