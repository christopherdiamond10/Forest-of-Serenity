//\====================================================================================
//\ Author: Christopher Diamond
//\ About : XMLHandler.h - 
//\ 
//\ Defines the XMLHandler Singleton Class. This class is used to handle the loading of 
//\ XML Files and given values back to other classes
//\====================================================================================
#ifndef _XML_H_
#define _XML_H_

#include <iostream>
#include "AnimationHandler.h"
#include <list>
#include "TinyXML.h"




class XMLHandler
{
/////////////////////////////////////////////////////////
public:
/////////////////////////////////////////////////////////

	XMLHandler();
	~XMLHandler();

	void OnLoad();
	void OnUnload();
	//===============================================
	//   Functions
	//===============================================
	void LoadLevelXMLDocument( std::string sFilename );
	void LoadAnimationXMLDocument( std::string sFilename );
	void LoadOptionsXMLDocument( std::string sFilename );
	void WriteOptionsXMLDocument( std::string sFilename );

	
	// Setters
	void SetXMLDocumentLocation( std::string sLocation );
	void SetClassVariablesToNil();

	// Getters
	int GetAnimationTotalFrames();
	int GetAnimationPartialAnimationCompleteFrame();
	bool Get_IsAnimationRelativeToScreen();
	std::list<AnimatedFrameInfo> GetAnimationAnimFrameInfoList();

	unsigned int GetLevelTileRowsCount();
	unsigned int GetLevelTileColsCount();
	std::list<std::string> GetLevelDataIdentityNames();
	std::string GetLevelBackGroundImageName();
	std::string GetLevelAudioFileName();
	unsigned int GetLevelAudioLoopStartPoint();
	unsigned int GetLevelAudioLoopEndPoint();
	std::string GetLevelWeatherEffectOneType();
	unsigned int GetLevelWeatherEffectOnePower();
	std::string GetLevelWeatherEffectTwoType();
	unsigned int GetLevelWeatherEffectTwoPower();
	bool Get_LevelXMLExists( std::string sFilename );


	static XMLHandler* GetInstance();


/////////////////////////////////////////////////////////
private:
/////////////////////////////////////////////////////////


	//   Variables
	std::string m_sLocation;
	std::string m_sFilename;

	//////// Animation ///////
	int m_iAnimationTotalFrames;
	int m_iPartialAnimationCompleteFrame;
	bool m_bAnimationRelativeToScreen;
	std::list<AnimatedFrameInfo> m_lAnimationAnimFrameInfoList;


	//////// Level ///////
	unsigned int m_iLevelTileRowsCount;
	unsigned int m_iLevelTileColsCount;
	std::list<std::string> m_lLevelDataIdentityNamesList;
	std::string m_sLevelBackgroundImageName;
	std::string m_sLevelAudioFileName;
	unsigned int m_iLevelAudioLoopStart;
	unsigned int m_iLevelAudioLoopEnd;
	std::string m_sLevelWeatherEffectOneType;
	unsigned int m_iLevelWeatherEffectOnePower;
	std::string m_sLevelWeatherEffectTwoType;
	unsigned int m_iLevelWeatherEffectTwoPower;






	static XMLHandler* m_Instance;
	
	
	//===============================================
	//   Functions
	//===============================================
	

};

#endif