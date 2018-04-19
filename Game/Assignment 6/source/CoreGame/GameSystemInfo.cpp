#include "GameSystemInfo.h"


GameSystemInfo* GameSystemInfo::m_Instance = nullptr;


GameSystemInfo* GameSystemInfo::GetInstance()
{
	return m_Instance;
} 



//===============================================
//			Constructor & Destructor
//===============================================
GameSystemInfo::GameSystemInfo()
{
	m_Instance = this;
}
GameSystemInfo::~GameSystemInfo()
{

}




//===============================================
//			OnLoad
//===============================================
void GameSystemInfo::OnLoad()
{
	m_sCurrentCharacter = "NINO";
	m_sCurrentLevel		= "Level.xml";
}
//===============================================
//			OnUnload
//===============================================
void GameSystemInfo::OnUnload()
{

}

//===============================================
//			Setter Functions
//===============================================
void GameSystemInfo::SetCurrentCharacter( std::string sCharacter )
{
	m_sCurrentCharacter = sCharacter;
}
void GameSystemInfo::SetCurrentLevel( std::string sLevel )
{
	m_sCurrentLevel = sLevel;
}

//===============================================
//			Getter Functions
//===============================================
std::string GameSystemInfo::GetCurrentCharacter()
{
	return m_sCurrentCharacter;
}
std::string GameSystemInfo::GetCurrentLevel()
{
	return m_sCurrentLevel;
}