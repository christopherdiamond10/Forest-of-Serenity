#ifndef _GAMESYSTEMNIFO_H_
#define _GAMESYSTEMNIFO_H_


#include <string>


class GameSystemInfo
{
//////////////////////////////////////////
public:
//////////////////////////////////////////

	static GameSystemInfo* GetInstance();
	
	//===============================================
	//			Constructor & Destructor
	//===============================================
	GameSystemInfo();
	~GameSystemInfo();


	//===============================================
	//			Public Functions
	//===============================================
	void OnLoad();
	void OnUnload();

	//===============================================
	//			Setter Functions
	//===============================================
	void SetCurrentCharacter	( std::string sCharacter );
	void SetCurrentLevel		( std::string sLevel	 );

	//===============================================
	//			Getter Functions
	//===============================================
	std::string GetCurrentCharacter();
	std::string GetCurrentLevel();


//////////////////////////////////////////
private:
//////////////////////////////////////////

	//===============================================
	//			Private Declarations
	//===============================================
	std::string m_sCurrentCharacter;
	std::string m_sCurrentLevel;


	//===============================================
	//			Private Functions
	//===============================================


	//===============================================
	//			Pointers
	//===============================================
	static GameSystemInfo* m_Instance;
};




#endif