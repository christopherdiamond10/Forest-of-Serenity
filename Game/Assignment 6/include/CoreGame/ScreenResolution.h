//\====================================================================================
//\ Author: Christopher Diamond
//\ About : ScreenResolution.h - 
//\ 
//\ Defines the ScreenResolution Singleton Class. This class is used to keep record of 
//\ what the screen size is. Its initial purpose was to allow upscaling images if the 
//\ screen size was ever enlarged, but now it's more of a hub for the camera and drawing
//\ purposes.
//\====================================================================================
#ifndef _SCREENRESOLUTION_H_
#define _SCREENRESOLUTION_H_



class ScreenResolution
{
//////////////////////////////////////////
public:
//////////////////////////////////////////
	ScreenResolution( float fWidth, float fHeight );
	~ScreenResolution();

	static ScreenResolution* GetInstance();

	void OnLoad();
	void OnUnload();

	void SetScreenSize( float fwidth, float fheight );

	
	float GetScreenWidth();
	float GetScreenHeight();
	float* GetScreenSize();
	float GetScaleWidthForScreenSize( float a_fWidth );
	float GetScaleHeightForScreenSize( float a_fHeight );
	void GetScaleSizeForScreenSize( float &Width, float &Height, float fWidth = 0.f, float fHeight = 0.f );

//////////////////////////////////////////
private:
//////////////////////////////////////////

	float m_fWidth, m_fHeight;

	static ScreenResolution* m_Instance;
};



#endif