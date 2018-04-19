#include "Camera.h"
#include "sdl_opengl.h"

#include "ScreenResolution.h"


//===============================================
//	Constructor
//===============================================
Camera::Camera()
{
	
}


//===============================================
//	Destructor
//===============================================
Camera::~Camera()
{

}





//===============================================
//	OnLoad
//===============================================
void Camera::OnLoad()
{
	ResetCamera();
}

//===============================================
//	OnUnload
//===============================================
void Camera::OnUnload()
{

}







//===============================================
//	Reset Camera
//===============================================
void Camera::ResetCamera()
{
	// Make everything NULL
	m_vCameraPos.X = m_vCameraPos.Y = m_fW = m_fH = m_fOutOfBoundsLeft = m_fOutOfBoundsRight = m_fOutOfBoundsTop = m_fOutOfBoundsBottom = 0.f;
}




//===============================================
//	Get Camera X Position
//===============================================
float Camera::GetCameraXPos()
{
	return m_vCameraPos.X;
}

//===============================================
//	Get Camera Y Position
//===============================================
float Camera::GetCameraYPos()
{
	return m_vCameraPos.Y;
}



//===============================================
//	Get Camera XY Position
//===============================================
Vector2 Camera::GetCamera_XY_Position()
{
	return m_vCameraPos;
}


//===============================================
//	Get Camera XYWH Position
//===============================================
float* Camera::GetCamera_XYWH_Position()
{
	float* ReturnArray = new float[4];
	ReturnArray[0] = m_vCameraPos.X;
	ReturnArray[1] = m_vCameraPos.Y;
	ReturnArray[2] = m_fW;
	ReturnArray[3] = m_fH;
	return ReturnArray;
}






//===============================================
//	Set Camera Position
//===============================================
void Camera::SetCameraPosition( float a_X, float a_Y )
{
	m_vCameraPos.X = a_X;
	m_vCameraPos.Y = a_Y;
}



//===============================================
//	Set Camera Dimensions
//===============================================
void Camera::SetCameraDimensions( float a_W, float a_H )
{
	m_fW = a_W;
	m_fH = a_H;
}



//===============================================
//	Set Out Of Bounds Area
//===============================================
void Camera::SetOutOfBoundsArea( float fLeft, float fRight, float fTop, float fBottom )
{
	m_fOutOfBoundsLeft		= fLeft;
	m_fOutOfBoundsRight		= fRight;
	m_fOutOfBoundsTop		= fTop;
	m_fOutOfBoundsBottom	= fBottom;
}









//===============================================
//		Update Camera
//===============================================
void Camera::Update( Vector2 vCamFocus )
{
	UpdateCameraTargetFocus( vCamFocus );
	UpdateCameraOutOfBounds();

	UpdateCamera();
}




//===============================================
//	Update Camera Focus On Target
//===============================================
void Camera::UpdateCameraTargetFocus( Vector2 vCamFocus )
{
	m_vCameraPos.X = ( vCamFocus.X - (m_fW * 0.5f) );
	m_vCameraPos.Y = ( vCamFocus.Y - (m_fH * 0.5f) );
}


//===============================================
//	Update Camera if Out of Bounds
//===============================================
void Camera::UpdateCameraOutOfBounds()
{
	// Make sure the Camera isn't out of bounds
	if( m_vCameraPos.X < m_fOutOfBoundsLeft )
	{
		m_vCameraPos.X = (m_fOutOfBoundsLeft);
	}
	else if( (m_vCameraPos.X + m_fW) > m_fOutOfBoundsRight )
	{
		m_vCameraPos.X = ((m_fOutOfBoundsRight - m_fW));
	}

	if( m_vCameraPos.Y < m_fOutOfBoundsTop )
	{
		m_vCameraPos.Y = (m_fOutOfBoundsTop);
	}
	else if( (m_vCameraPos.Y + m_fH) > m_fOutOfBoundsBottom )
	{
		m_vCameraPos.Y = ((m_fOutOfBoundsBottom - m_fH));
	}
}


//===============================================
//	Update Camera
//===============================================
void Camera::UpdateCamera()
{
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	glTranslatef( -m_vCameraPos.X, -m_vCameraPos.Y, 0.f );
}