//#################################
//								 ##
//			Main				 ##
//								 ##
//	Authors: Jamie.Stewart		 ##
//			 Christopher Diamond ##
//								 ##
//#################################
//================================
#include "sdl_opengl.h"	//		==
#include "sdl.h"		//		==
#include "sdl_image.h"	//		==
#include "GnEngine.h"	//		==
#include "ScreenResolution.h"// ==
//================================


#if defined(__WIN32__)
	#include <Windows.h>
#endif

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define BIT_DEPTH 24

// Function defined later in cpp
SDL_Joystick* UsingXboxController();





//===================================
//			     Main
//===================================
int SDL_main(int argc, char *argv[])
{
	if( !SDL_Init(SDL_INIT_EVERYTHING) )
	{
		//Set Up our colour bits for SDL and our Buffer size 
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, BIT_DEPTH );
		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8 );
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8 );
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8 );
		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 0 );
		
		bool bFullscreen = false;




		// Using an Xbox 360 controller? 
		SDL_Joystick* ptr_XboxController = UsingXboxController();



		unsigned int flags = SDL_OPENGL | SDL_HWSURFACE | (bFullscreen ? SDL_FULLSCREEN : 0 );

		SDL_WM_SetCaption( "Forest of Serenity", NULL );
		SDL_Surface * Screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, BIT_DEPTH, flags );



		ScreenResolution* pScreenResolution = new ScreenResolution( (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT );
		GnEngine* pEngine					= new GnEngine( ptr_XboxController );




		#if defined(__WIN32__)
			//This isn't really that messy
			//Typedef the API Entry point and the swap interval extension to an int
			typedef void (APIENTRY * WGLSWAPINTERVALEXT) (int);
			//This line is a nice way of asking windows if we can access the OpenGL Extension for changing the swap interval
			WGLSWAPINTERVALEXT wglSwapIntervalEXT = (WGLSWAPINTERVALEXT)wglGetProcAddress("WGLSWAPINTERVALEXT");
			//If the above call returned something that wasn't NULL then we can access this extension
			//This was just a safety check really to ensure that SwapIntervalEXT exists before we use it.
			if( wglSwapIntervalEXT )
			{
				wglSwapIntervalEXT(0);
			}
		#endif

		
		if( pEngine->Init() )
		{
			pEngine->OnLoad();
			pEngine->Run();
			pEngine->OnUnload();
		}

		pEngine->Quit();
		delete pEngine;
		delete pScreenResolution;

		SDL_Quit();
	}
	return 0;
}





//===================================
//	   Using an Xbox Controller?
//===================================
SDL_Joystick* UsingXboxController()
{
	SDL_Joystick *ptr_XboxController = nullptr;												
																							
	// Check if there's any joysticks														
	if( SDL_NumJoysticks() >= 1 )															
	{																						
		// Open the joystick																	
		ptr_XboxController = SDL_JoystickOpen( 0 ); 																							
	}																						
																							
	return ptr_XboxController;
}