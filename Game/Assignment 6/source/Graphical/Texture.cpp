#include "Texture.h"

#include "assert.h"
#include "Utility_Functions.h"


Texture* Texture::m_Instance = nullptr;
//=================================
//		Get Instance	
//=================================
Texture* Texture::GetInstance()
{
	return m_Instance;
}



//==================================================
//		Constructor	
//==================================================
Texture::Texture()	
	: MaxTextureSize		(4096)
{
	if( m_Instance == nullptr)
	{ m_Instance = this; }
	else
	{ assert(0); }
}


//==================================================
//		Destructor	
//==================================================
Texture::~Texture()
{

}




//==================================================
//		OnLoad	
//==================================================
void Texture::OnLoad()
{

}

//==================================================
//		OnUnload
//==================================================
void Texture::OnUnload()
{
	m_lImportedTextureList.clear();
}










//==================================================
//				Load Texture
//==================================================
int Texture::LoadTexture( std::string a_sFilename, std::string sTextureType )
{
	std::string sPathtoFile = "./bin/Images/";
	sPathtoFile += GetTextureTypeFolder( sTextureType );
	sPathtoFile += a_sFilename;
	return ImportTexture( sPathtoFile );
}




//==================================================
//				Get Texture Type Folder
//==================================================
std::string Texture::GetTextureTypeFolder( std::string sTextureType )
{
	std::string sType = String_To_UpperCase( sTextureType );
	if	   ( sType == "ANIMATIONS" || sType == "ANIMATION" || sType == "ANIM" )						{ return "Animations/";  }
	else if( sType == "BACKGROUND" || sType == "BACKGROUNDS" || sType == "BG" || sType == "BGI" )	{ return "BackGrounds/"; }
	else if( sType == "OTHER"      || sType == "OTHERS"      )										{ return "Others/";		 }
	else if( sType == "PLATFORM"   || sType == "PLATFORMS"   )										{ return "Platforms/";	 }
	else if( sType == "SPRITE"     || sType == "SPRITES"     )										{ return "Sprites/"; 	 }
	else if( sType == "WALL"       || sType == "WALLS"       )										{ return "Walls/";		 }
	else																						    { return NULL;			 }
}




//==================================================
//					Load
//==================================================
int Texture::ImportTexture(std::string File )
{
	//------------------------------------------------------------------
	int iAlreadyImportedTextureID = CheckImportedTextureList( File );
	if( iAlreadyImportedTextureID != 0 )
	{	return iAlreadyImportedTextureID;	}
	//------------------------------------------------------------------

	SDL_Surface *ImageFile = IMG_Load(File.c_str());
	if ( ImageFile == 0 ) //if image failed to load
	{
		return -1; //return negative one to let SDL know that something went wrong.
	}

	

	// Standard OpenGL texture creation code
	glPixelStorei(GL_UNPACK_ALIGNMENT,4);

	//Create the Texture
	glGenTextures( 1, m_TextureHandle );

	//Binds the texture, simply this is the current texture being worked on in OpenGL
	glBindTexture( GL_TEXTURE_2D, m_TextureHandle[0] );


	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// Now the Image file may not be in a nice friendly format											////		=-
	// This Format structure stores format information													////		=-
	// This will be used to gurantee that the image is in a 32bit format								////		=-
	////////////////////////////////////////////////////////////////////////////////////////////////////////		=-
	SDL_PixelFormat Format;																				////		=-
	Format.Aloss = Format.Rloss = Format.Bloss = Format.Gloss = 0;										////		=-
																										////		=-
	// 32 Bit per pixel																					////		=-
	Format.BitsPerPixel = 32; 																			////		=-
																										////		=-
	// That makes it 4 bytes per pixel																	////		=-
	Format.BytesPerPixel = 4; 																			////		=-
																										////		=-
	// The Bit locations for each channel																////		=-
	Format.Rshift = 0; Format.Gshift = 8; Format.Bshift = 16; Format.Ashift = 24; 						////		=-
																										////		=-
	// a Mask you can use to access each channel														////		=-
	Format.Rmask = 0xFF; Format.Gmask = 0xFF00; Format.Bmask = 0xFF0000; Format.Amask = 0xFF000000; 	////		=-
																										////		=-
	// Transparent colour key, ignored																	////		=-
	Format.colorkey = 0;																				////		=-
																										////		=-
	// Max Alpha																						////		=-
	Format.alpha = 255; 																				////		=-
																										////		=-
	// Palette Info, ignored																			////		=-
	Format.palette = NULL; 																				////		=-
																										////		=-
	// Convert the file we have loaded, into the current Image format									////		=-
	SDL_Surface *Image = SDL_ConvertSurface( ImageFile, &Format, 0 );									////		=-
																										////		=-
	// Now we are storing it in a good format known format, 											////		=-
	// we can Free the old one, and get the memory back													////		=-
	SDL_FreeSurface( ImageFile );																		////		=-
																										////		=-
	// Get the Images Width and Height																	////		=-
	int NewWidth = Image->w;																			////		=-
	int NewHeight = Image->h;																			////		=-
																										////		=-
	// Will it need to be rescaled?																		////		=-
	bool Rescale = false;																				////		=-
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-


	//Is the Width and the Height of the image powers of 2, if not
	//What is the next largest power of 2 that will work
	if ( ChangeTextureSize( Image->w ) != 0 )
	{
		Rescale = true;
		NewWidth = ChangeTextureSize( Image->w );
	}
	if ( ChangeTextureSize( Image->h ) != 0 )
	{
		Rescale = true;
		NewHeight = ChangeTextureSize( Image->h );
	}
	//If the image needs to be rescaled then...
	if ( Rescale )
	{
		//Create a new blank Image large enough to take in new resized image in the correct format
		SDL_Surface *ReScaleImage = SDL_CreateRGBSurface
			(	Image->flags, NewWidth, NewHeight, 
			Image->format->BitsPerPixel, Image->format->Rmask, 
			Image->format->Gmask, Image->format->Bmask, Image->format->Amask );


		//Lock the surfaces, this grabs the memory to make sure the graphics card doesnt have it, and we can get
		//True write access to it
		SDL_LockSurface( ReScaleImage );
		SDL_LockSurface( Image );

		//SDL has no scaling of images, so we have to use GL ulity function scale image
		//Does exactly what it says on the tin, it scales the contents of Image into ReScale Image
		gluScaleImage( GL_RGBA, Image->w, Image->h, GL_UNSIGNED_BYTE, Image->pixels, ReScaleImage->w, ReScaleImage->h, GL_UNSIGNED_BYTE, ReScaleImage->pixels );

		//Unlock the memory back for normal use
		SDL_UnlockSurface( ReScaleImage );
		SDL_UnlockSurface( Image );

		//Free the old Unscaled Image
		SDL_FreeSurface(Image);

		//Set the Image to be the new rescaled image.
		Image = ReScaleImage;

	}


	//This copies the SDL image in our known format into our openGL texture.
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, Image->w, Image->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, Image->pixels );

	//Free the Image now OpenGL has it
	SDL_FreeSurface(Image);

	//This sets up the filtering parameters for the texture
	//GL_NEAREST makes it look old, as no filtering is used, makes it all look pixelated
	//GL_LINEAR filters the image and makes it look all smooth.
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Linear Filtering
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Linear Filtering


	// Add the Texture to the List
	TextureInfo TextInfo;
	TextInfo.Name = File;
	TextInfo.ID = m_TextureHandle[0];
	m_lImportedTextureList.push_back( TextInfo );


	//Return the openGL image
	return m_TextureHandle[0];
}





//==================================================
//				 Change Texture Size
//==================================================
int Texture::ChangeTextureSize(unsigned int H_W )
{
	unsigned int i = 2;
	for (; i <= MaxTextureSize; i*=2)
	{
		// If the texture size is equal to the value, we're all good; no need to change anything
		if ( H_W == i )
		{	return 0;	}

		//If the texture size is bigger than the value, then we have gone past it. Return the value to upscale to.
		else if ( H_W < i )
		{	return i;	}
	}

	//If we have not found a good size, this texture must be huge, return our largest size allowed, it will be downscaled
	return i;
}



//==================================================
//			 Check Imported Texture List
//==================================================
int Texture::CheckImportedTextureList( std::string FileName )
{
	// If the filename matches up to one that's already been imported, return the ID
	for( std::list<TextureInfo>::iterator iter = m_lImportedTextureList.begin(); iter != m_lImportedTextureList.end(); iter++ )
	{
		if( FileName == iter->Name )
		{	return iter->ID;	}
	}

	// Otherwise Return Zero
	return 0;
}