#include "ScreenResolution.h"

#include <assert.h>


ScreenResolution* ScreenResolution::m_Instance = nullptr;

//===============================================
//	Get Class Instance
//===============================================
ScreenResolution* ScreenResolution::GetInstance()
{
	return m_Instance;
}


//===============================================
//	Constructor
//===============================================
ScreenResolution::ScreenResolution( float fWidth, float fHeight )
{
	if( m_Instance == nullptr )	{ m_Instance = this; }
	else						{ assert(0);		 }

	m_fWidth		= fWidth;
	m_fHeight		= fHeight;
}


//===============================================
//	Destructor
//===============================================
ScreenResolution::~ScreenResolution()
{

}


//===============================================
//	OnLoad
//===============================================
void ScreenResolution::OnLoad()
{

}


//===============================================
//	OnUnload
//===============================================
void ScreenResolution::OnUnload()
{

}







//===============================================
//	Set Screen Size
//===============================================
void ScreenResolution::SetScreenSize( float fWidth, float fHeight )
{
	m_fWidth  = fWidth;
	m_fHeight = fHeight;
}




//===============================================
//	Get Screen Width
//===============================================
float ScreenResolution::GetScreenWidth()
{
	return m_fWidth;
}

//===============================================
//	Get Screen Height
//===============================================
float ScreenResolution::GetScreenHeight()
{
	return m_fHeight;
}


//===============================================
//	Get Screen Size
//===============================================
float* ScreenResolution::GetScreenSize()
{
	float* ReturnArray = new float[2];
	ReturnArray[0] = m_fWidth;
	ReturnArray[1] = m_fHeight;

	return ReturnArray;
}


//===============================================
//	Get Scale Width for Screen Size
//===============================================
float ScreenResolution::GetScaleWidthForScreenSize( float a_fWidth )
{
	float fReturn = ((1.f / a_fWidth) * m_fWidth);
	if( (int)fReturn != 1 )
	{
		return fReturn;
	}
	else
	{
		return m_fWidth;
	}
}


//===============================================
//	Get Scale Height for Screen Size
//===============================================
float ScreenResolution::GetScaleHeightForScreenSize( float a_fHeight )
{
	float fReturn = ((1.f / a_fHeight) * m_fHeight);
	if( (int)fReturn != 1 )
	{
		return fReturn;
	}
	else
	{
		return m_fHeight;
	}
}


//===============================================
//	Get Scale Size for Screen Size
//===============================================
void ScreenResolution::GetScaleSizeForScreenSize( float &Width, float &Height, float fWidth, float fHeight )
{
	// Don't need null numbers
	if( fWidth == 0.f )		{ fWidth = Width;  }
	if( fHeight == 0.f )	{ fHeight = Height; }

	// Make the magic happen
	Width  = ((1.f / fWidth) * m_fWidth);
	Height = ((1.f / fHeight) * m_fHeight);

	// Hope it worked correctly
	if( (int)Width == 1 )
	{
		Width = m_fWidth;
	}
	if( (int)Height == 1 )
	{
		Height = m_fHeight;
	}
}