//\====================================================================================
//\ Author: Christopher Diamond
//\ About : InputHandler.h - 
//\ 
//\ Defines the InputHandler Singleton Class. This class is used to process all inputs
//\ for the game, it is used to return boolean values to other classes about whether 
//\ or not a key/button has been pressed.
//\====================================================================================
#ifndef _INPUTHANDLER_H_
#define _INPUTHANDLER_H_


#include "sdl.h"
#include "Vector2.h"
#include <string>




// Global Definitions, so that the variables can be used in other .cpp files
// The defintions do not affect anything, instead just gives a name to these numbers
// which are used for joystick input.
#define JoystickButtons_A					0
#define JoystickButtons_B					1
#define JoystickButtons_X					2
#define JoystickButtons_Y					3
#define JoystickButtons_LB					4
#define JoystickButtons_RB					5
#define JoystickButtons_Select				6
#define JoystickButtons_Start				7
#define JoystickButtons_LeftStickClick		8
#define JoystickButtons_RightStickClick		9


#define JoystickDPadButtons_Up				1
#define JoystickDPadButtons_Right			2
#define JoystickDPadButtons_Up_Right		3
#define JoystickDPadButtons_Down			4
#define JoystickDPadButtons_Down_Right		6
#define JoystickDPadButtons_Left			8
#define JoystickDPadButtons_Up_Left			9
#define JoystickDPadButtons_Down_Left		12






class GnEngine;

class InputHandler
{
//////////////////////////////////////////
public:
//////////////////////////////////////////

	//===============================================
	//			Constructor & Destructor
	//===============================================
	InputHandler( GnEngine * p_Game, SDL_Joystick *ptr_SDLJoyStick );
	~InputHandler();




	//===============================================
	//			Static Functions
	//===============================================
	static InputHandler* GetInstance();
	

	//===============================================
	//			Public Functions
	//===============================================
	void OnLoad();
	void OnUnload();
	void Update();


	//===============================================
	//			Getter Functions
	//===============================================
	bool GetKeyState		( int key, bool SetKeyPressed = true );
	bool GetJoyButtonState	( int button );
	bool GetJoyDPadState	( int hat );
	bool GetMouseClicked	(		  );
	Vector2 GetMousePos		(		  );
	std::string GetKeyPressedCharacter();

	//===============================================
	//			Public Declarations
	//===============================================
	



//////////////////////////////////////////
private:
//////////////////////////////////////////

	//===============================================
	//			Private Array Declarations
	//===============================================
	bool KeyInputArray[SDLK_LAST];
	bool JoyButtonInputArray[JoystickButtons_RightStickClick + 1];
	bool JoyDPadInputArray[JoystickDPadButtons_Down_Left + 1];

	bool m_bMouseClicked;

	Vector2 m_v2MousePos;


	//===============================================
	//			Private Functions
	//===============================================
	std::string FindCharacterKeyPressed();
	std::string ShiftKeyCharacterUpdate( std::string sCharacter );
	void SetKeyInputArray_toFalse();
	void SetJoyHatArray_toFalse();
	void SetJoyButtonArray_toFalse();
	void XboxControllerConnected(); // ???


	//===============================================
	//			Private Pointers
	//===============================================
	SDL_Joystick			* ptr_XboxController;
	GnEngine				* m_pOwningGame;
	static InputHandler		* m_Instance;
};

#endif