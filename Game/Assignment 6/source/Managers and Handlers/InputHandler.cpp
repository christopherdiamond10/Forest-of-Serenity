#include <assert.h>
#include "sdl.h"
#include "InputHandler.h"
#include "Utility_Functions.h"
#include "GnEngine.h"
#include <string>


InputHandler* InputHandler::m_Instance = NULL;
//=====================================
//			Get Instance
//=====================================
InputHandler* InputHandler::GetInstance()
{
	return m_Instance;
}


//=====================================
//			Constructor
//=====================================
InputHandler::InputHandler( GnEngine *p_Game, SDL_Joystick *ptr_SDLJoyStick )
{
	if( m_Instance == NULL )
	{
		m_pOwningGame			= p_Game;
		ptr_XboxController		= ptr_SDLJoyStick;
		m_Instance				= this;
	}
	else
	{	assert(0);	}
}


//=====================================
//			Deconstructor
//=====================================
InputHandler::~InputHandler()
{
	if( ptr_XboxController != NULL )
	{
		//Close the Joystick
		SDL_JoystickClose( ptr_XboxController );
	}
}




//=====================================
//			OnLoad
//=====================================
void InputHandler::OnLoad()
{
	// Make all Input values equal false before they are ever used.
	SetKeyInputArray_toFalse();
	SetJoyHatArray_toFalse();
	SetJoyButtonArray_toFalse();

	m_bMouseClicked = false;

}




//=====================================
//			OnUnload
//=====================================
void InputHandler::OnUnload()
{

}












//=====================================================
//					Getter Functions
//=====================================================
bool InputHandler::GetKeyState(int Key, bool SetKeyPressed )
{
	bool bReturnbool = KeyInputArray[ Key ];
	if( SetKeyPressed ){ KeyInputArray[ Key ] = false; }
	return bReturnbool;
}

bool InputHandler::GetJoyButtonState( int button )
{
	return JoyButtonInputArray[ button ];
}

bool InputHandler::GetJoyDPadState( int hat )
{
	bool bReturnBool = JoyDPadInputArray[ hat ];

	// Since JoyHatMotion doesn't have an SDL call to detect if the hat is released
	// We need to set it back to false after giving its value to whatever called it.
	//
	// The Input function will still do everything the same way it should even if we 
	// are sneakily setting the value to false.

	JoyDPadInputArray[ hat ] = false;

	return bReturnBool;
}

bool InputHandler::GetMouseClicked()
{
	return m_bMouseClicked;
}

Vector2 InputHandler::GetMousePos()
{
	return m_v2MousePos;
}

std::string InputHandler::GetKeyPressedCharacter()
{
	return ShiftKeyCharacterUpdate(FindCharacterKeyPressed());
}


#include <iostream>
//=====================================================
//						Update
//=====================================================
void InputHandler::Update()
{
	// This is so that the Xbox controller can be connected at anytime.
	if( !ptr_XboxController )
	{
		XboxControllerConnected();
	}
	
	
	
	
	
	
	
	
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		////////////////////////////////
		//			SDL Quit		  //
		////////////////////////////////
		if( event.type == SDL_QUIT )
		{
			m_pOwningGame->InitialiseShutdown();
			break;
		}


		////////////////////////////////////////
		//				Mouse				  //
		////////////////////////////////////////
		if( event.type == SDL_MOUSEBUTTONDOWN )
		{
			m_bMouseClicked = true;
		}
		else
		{
			m_bMouseClicked = false;
		}

		///////////////////////////////////////
		//				JoyStick			 //
		///////////////////////////////////////
		if( ptr_XboxController != NULL ) //No need to check the joystick if there isn't any there.
		{
			if( event.type == SDL_JOYBUTTONDOWN )
			{
				for ( int i = 0; i < JoystickButtons_RightStickClick; i++ )
				{
					if ( event.jbutton.button == i ) 
					{
						JoyButtonInputArray[i] = true;
					}
				}
			}


			else if( event.type == SDL_JOYBUTTONUP )
			{
				for ( int i = 0; i < JoystickButtons_RightStickClick; i++ )
				{
					if ( event.jbutton.button == i ) 
					{
						JoyButtonInputArray[i] = false;
					}
				}
			}


			else if( event.type == SDL_JOYHATMOTION )
			{
				for ( int i = 0; i < JoystickDPadButtons_Down_Left; i++ )
				{
					if ( event.jhat.value == i ) 
					{
						JoyDPadInputArray[i] = true;
					}
				}
			}

		}


		//////////////////////////////
		//			Keys			//
		//////////////////////////////
		if( event.type == SDL_KEYDOWN)
		{
			for( int i = 0; i < SDLK_LAST; i++ )
			{
				if ( event.key.keysym.sym == i )
				{
					KeyInputArray[i] = true;
				}
			}
		}


		else if( event.type == SDL_KEYUP)
		{
			for( int i = 0; i < SDLK_LAST; i++ )
			{
				if ( event.key.keysym.sym == i )
				{
					KeyInputArray[i] = false;
				}
			}
		}


		////////////////////////////
		//		Update Mouse	  //
		////////////////////////////
		m_v2MousePos.X = event.motion.x;
		m_v2MousePos.Y = event.motion.y;
	}
}











//////////////////////////////////////////////
//	Functions to Set all values to false	//
//////////////////////////////////////////////


//==========================================
//	Set Input Keys Array to False
//==========================================
void InputHandler::SetKeyInputArray_toFalse()
{
	for( int i = 0; i < SDLK_LAST; i++)
	{
		KeyInputArray[i] = false;
	}
}





//==========================================
//	Set Joystick Hat Array to False
//==========================================
void InputHandler::SetJoyHatArray_toFalse()
{
	for ( int i = 0; i < JoystickDPadButtons_Down_Left + 1; i++ )
	{
		JoyDPadInputArray[i] = false;
	}
}





//==========================================
//	Set Joystick Button Array to False
//==========================================
void InputHandler::SetJoyButtonArray_toFalse()
{
	for ( int i = 0; i < JoystickButtons_RightStickClick + 1; i++ )
	{
		JoyButtonInputArray[i] = false;
	}
}









//==========================================
//		Xbox Controller Connected?
//==========================================
void InputHandler::XboxControllerConnected()
{																							
	// Check if there's any joysticks														
	if( SDL_NumJoysticks() >= 1 )															
	{																						
		// Open the joystick																	
		ptr_XboxController = SDL_JoystickOpen( 0 ); 																								
	}																						
}












//==========================================
//		Find Character Key if Pressed
//==========================================
std::string InputHandler::FindCharacterKeyPressed()
{
	for(int i = 0; i < SDLK_LAST; i++)
	{
		if( i == 303 || i == 304 ) { continue; }

		if( KeyInputArray[i] )
		{
			char c = (char)i;
			if( i == 92 ) { c = '\\'; }
			if( Get_IsCharacterValid(c) )
			{
				KeyInputArray[i] = false;
				std::string str; 
				str += c;
				return str;
			}
		}
	}
	return "";
}



//==========================================
// Update Character if Shift Key if Pressed
//==========================================
std::string InputHandler::ShiftKeyCharacterUpdate( std::string str )
{
	if( str != "" )
	{
		if( GetKeyState( SDLK_LSHIFT, false ) || GetKeyState( SDLK_RSHIFT, false ))
		{
			char c = str[0];
			if( c == 92 ) { return "|"; }
			if( c == 91 ) { return "{"; }
			if( c == 93 ) { return "}"; }
			if( c == 39 ) { c = '"'; std::string s; s += c; return s; }
			if( c == ';') { return ":"; }
			if( c == '/') { return "?"; }
			if( c == '.') { return ">"; }
			if( c == ',') { return "<"; }
			if( c == '`') { return "~"; }
			if( c == '1') { return "!"; }
			if( c == '2') { return "@"; }
			if( c == '3') { return "#"; }
			if( c == '4') { return "$"; }
			if( c == '5') { return "%"; }
			if( c == '6') { return "^"; }
			if( c == '7') { return "&"; }
			if( c == '8') { return "*"; }
			if( c == '9') { return "("; }
			if( c == '0') { return ")"; }
			if( c == '-') { return "_"; }
			if( c == '=') { return "+"; }
			return String_To_UpperCase(str);
		}
	}
	return str;
}