//\====================================================================================
//\ Author: Christopher Diamond
//\ About : Texture.h - 
//\ 
//\ Defines the Texture Class. This class is used to Load up textures from file and put 
//\ them into memory for future use, the class also contains a list of loaded files, so 
//\ as not to load the same image twice.
//\====================================================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_


#include "sdl.h"
#include "sdl_image.h"
#include "sdl_opengl.h"

#include <iostream>
#include <list>



//=======================
//	TextureInfo Struct
//=======================
struct TextureInfo
{
	std::string Name;
	unsigned int ID;
};




class Texture
{
////////////////////////////////////////////////////////////
public:
////////////////////////////////////////////////////////////

	//===============================================
	//			Constructor & Destructor
	//===============================================
	Texture();	
	~Texture();
	




	//===============================================
	//				Static Functions
	//===============================================
	static Texture* GetInstance();


	//===============================================
	//			  Obligatory Functions
	//===============================================
	void OnLoad();
	void OnUnload();


	//===============================================
	//			 Load Texture Functions
	//===============================================
	int LoadTexture( std::string a_sFilename, std::string sTextureType );	




////////////////////////////////////////////////////////////	
protected:
////////////////////////////////////////////////////////////


	//===============================================
	//			Protected Declarations
	//===============================================
	unsigned int m_TextureHandle[1];
	unsigned int m_Width;
	unsigned int m_Height;




////////////////////////////////////////////////////////////
private:
////////////////////////////////////////////////////////////


	//===============================================
	//			   Private Declarations
	//===============================================
	const unsigned int MaxTextureSize;
	std::list<TextureInfo> m_lImportedTextureList;


	//===============================================
	//				Setup Functions
	//===============================================
	int ImportTexture(std::string File);
	int ChangeTextureSize(unsigned int H_W);
	int CheckImportedTextureList( std::string FileName );
	std::string GetTextureTypeFolder( std::string sTextureType );


	//===============================================
	//				Class Pointers
	//===============================================
	static Texture	* m_Instance;


	//===============================================
	//			   Operator Overloads
	//===============================================
	Texture& operator = (const Texture &tmp);
};


#endif