//\====================================================================================
//\ Author: Christopher Diamond
//\ About : Camera.h - 
//\ 
//\ Defines the Camera Class. This class handles the camera that follows a target.
//\ During the Level this target is the player, but if any cutscenes are ever to be used, 
//\ that target may become something else
//\====================================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Vector2.h"
#include <string>
#include "sdl.h"

class Camera
{
//////////////////////////////////////////
public:
//////////////////////////////////////////

	//===============================================
	//			Constructor & Destructor
	//===============================================
	Camera							(					);
	~Camera							(					);


	//===============================================
	//			Public Functions
	//===============================================
	void OnLoad						(					);
	void OnUnload					(					);
	void Update						( Vector2 vCamFocus );
	void ResetCamera				(					);


	//===============================================
	//			Getter Functions
	//===============================================
	float  GetCameraXPos			(					);
	float  GetCameraYPos			(					);
	Vector2 GetCamera_XY_Position	(					);
	float* GetCamera_XYWH_Position	(					);


	//===============================================
	//			Setter Functions
	//===============================================
	void SetCameraPosition			( float a_X,	float a_Y	);
	void SetCameraDimensions		( float a_W,	float a_H	);
	void SetOutOfBoundsArea			( float fLeft,	float fRight, float fTop, float fBottom );


//////////////////////////////////////////
private:
//////////////////////////////////////////

	//===============================================
	//			Private Functions
	//===============================================
	void UpdateCameraTargetFocus	( Vector2 vCamFocus	);
	void UpdateCameraOutOfBounds	(					);
	void UpdateCamera				(					);


	//===============================================
	//			Private Declarations
	//===============================================
	Vector2 m_vCameraPos; // Follows FocusTarget
	float m_fW, m_fH;
	float m_fOutOfBoundsLeft, m_fOutOfBoundsRight; 
	float m_fOutOfBoundsTop, m_fOutOfBoundsBottom;

};



#endif