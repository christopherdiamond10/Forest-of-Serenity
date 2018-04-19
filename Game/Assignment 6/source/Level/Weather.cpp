#include "Weather.h"

#include "sdl_opengl.h"

#include <time.h>

#include "AudioManager.h"
#include "DeltaTime.h"
#include "ScreenResolution.h"
#include "Utility_Functions.h"


//===============================================
//	Constructor
//===============================================
Weather::Weather()
{

}


//===============================================
//	Destructor
//===============================================
Weather::~Weather()
{

}


//===============================================
//	OnLoad
//===============================================
void Weather::OnLoad()
{
	AudioManager::GetInstance()->ImportAudio( "Rain_BGS.ogg", "Rain_BGS", "BGS" );
	AudioManager::GetInstance()->ImportAudio( "Wind_BGS.ogg", "Wind_BGS", "BGS" );
	
}


//===============================================
//	OnUnload
//===============================================
void Weather::OnUnload()
{
	ClearWeatherList( "RAIN" );
	ClearWeatherList( "WIND" );
}

//===============================================
//	Create Weather Effect
//===============================================
void Weather::CreateWeatherEffect( std::string sTypeOfWeatherEffect, int iWhichList, unsigned int iHowManyToCreate )
{
	if( sTypeOfWeatherEffect == "RAIN" )
	{
		if( (iWhichList == 1 ? m_lRainWeatherEffectListBack : m_lRainWeatherEffectListFront).size() < iHowManyToCreate )
		{
			Rain* pRain = new Rain();
			(iWhichList == 1 ? m_lRainWeatherEffectListBack : m_lRainWeatherEffectListFront).push_back( pRain );

			// Recursive Function 
			CreateWeatherEffect( "RAIN", iWhichList, iHowManyToCreate );
		}
		else if( (iWhichList == 1 ? m_lRainWeatherEffectListBack : m_lRainWeatherEffectListFront).size() > iHowManyToCreate )
		{
			ClearWeatherList( sTypeOfWeatherEffect );
			CreateWeatherEffect( "RAIN", iWhichList, iHowManyToCreate );
		}
	}


	if( sTypeOfWeatherEffect == "WIND" )
	{
		if( (iWhichList == 1 ? m_lWindWeatherEffectListBack : m_lWindWeatherEffectListFront).size() < iHowManyToCreate )
		{
			Wind* pWind = new Wind();
			(iWhichList == 1 ? m_lWindWeatherEffectListBack : m_lWindWeatherEffectListFront).push_back( pWind );

			// Recursive Function
			CreateWeatherEffect( "WIND", iWhichList, iHowManyToCreate );
		}
		else if( (iWhichList == 1 ? m_lWindWeatherEffectListBack : m_lWindWeatherEffectListFront).size() > iHowManyToCreate )
		{
			ClearWeatherList( sTypeOfWeatherEffect );
			CreateWeatherEffect( "WIND", iWhichList, iHowManyToCreate );
		}
	}
}


//===============================================
//	Clear Weather List
//===============================================
void Weather::ClearWeatherList( std::string sTypeOfWeatherEffect )
{
	if( sTypeOfWeatherEffect == "RAIN" )
	{
		for( std::list<Rain*>::iterator iter = m_lRainWeatherEffectListBack.begin(); iter != m_lRainWeatherEffectListBack.end(); iter++)
		{
			delete (*iter);
		}
		for( std::list<Rain*>::iterator iter = m_lRainWeatherEffectListFront.begin(); iter != m_lRainWeatherEffectListFront.end(); iter++)
		{
			delete (*iter);
		}

		m_lRainWeatherEffectListBack.clear();
		m_lRainWeatherEffectListFront.clear();
	
	}

	else if( sTypeOfWeatherEffect == "WIND" )
	{
		for( std::list<Wind*>::iterator iter = m_lWindWeatherEffectListBack.begin(); iter != m_lWindWeatherEffectListBack.end(); iter++)
		{
			delete (*iter);
		}
		for( std::list<Wind*>::iterator iter = m_lWindWeatherEffectListFront.begin(); iter != m_lWindWeatherEffectListFront.end(); iter++)
		{
			delete (*iter);
		}

		m_lWindWeatherEffectListBack.clear();
		m_lWindWeatherEffectListFront.clear();
	}
}


//===============================================
//	Start Weather
//===============================================
void Weather::StartWeather( std::string sTypeOfWeatherEffect, int iPowerOfWeatherEffect, bool bPlayBGSforWeatherEffect )
{
	sTypeOfWeatherEffect = String_To_UpperCase( sTypeOfWeatherEffect );

	int iMinimumPowerOfWeather = 1;
	int iMaximumPowerOfWeather = 10;

	if( iPowerOfWeatherEffect < iMinimumPowerOfWeather )
	{
		iPowerOfWeatherEffect = iMinimumPowerOfWeather;
	}
	else if( iPowerOfWeatherEffect > iMaximumPowerOfWeather )
	{
		iPowerOfWeatherEffect = iMaximumPowerOfWeather;
	}

	



	if( sTypeOfWeatherEffect == "RAIN" )
	{
		unsigned int iAmountOfWeather = 5 * iPowerOfWeatherEffect;
		CreateWeatherEffect( sTypeOfWeatherEffect, 1, iAmountOfWeather );
		CreateWeatherEffect( sTypeOfWeatherEffect, 2, iAmountOfWeather );

		if( bPlayBGSforWeatherEffect ){	AudioManager::GetInstance()->PlaySound( "Rain_BGS" ); }
	}
			
	else if( sTypeOfWeatherEffect == "WIND" )
	{ 
		if( iPowerOfWeatherEffect == 1 ) 
		{ 
			CreateWeatherEffect( sTypeOfWeatherEffect, 2, iPowerOfWeatherEffect ); // Put Wind In Front
		}
		else
		{
			CreateWeatherEffect( sTypeOfWeatherEffect, 1, (int)(iPowerOfWeatherEffect * 0.5f) );
			CreateWeatherEffect( sTypeOfWeatherEffect, 2, (int)(iPowerOfWeatherEffect * 0.5f) );
		}

		if( bPlayBGSforWeatherEffect ){ AudioManager::GetInstance()->PlaySound( "Wind_BGS" ); }
	}
}


//===============================================
//	Cease Weather
//===============================================
void Weather::CeaseWeather( std::string sTypeOfWeatherEffect )
{
	ClearWeatherList( String_To_UpperCase( sTypeOfWeatherEffect ));
}


//===============================================
//	Update
//===============================================
void Weather::Update( Vector2 vCamPosition )
{
	////////// Update Rain //////////
	for( std::list<Rain*>::iterator iter = m_lRainWeatherEffectListBack.begin(); iter != m_lRainWeatherEffectListBack.end(); iter++ )
	{
		(*iter)->Update( vCamPosition );
	}
	for( std::list<Rain*>::iterator iter = m_lRainWeatherEffectListFront.begin(); iter != m_lRainWeatherEffectListFront.end(); iter++ )
	{
		(*iter)->Update( vCamPosition );
	}


	////////// Update Wind //////////
	for( std::list<Wind*>::iterator iter = m_lWindWeatherEffectListBack.begin(); iter != m_lWindWeatherEffectListBack.end(); iter++ )
	{
		(*iter)->Update( vCamPosition );
	}
	for( std::list<Wind*>::iterator iter = m_lWindWeatherEffectListFront.begin(); iter != m_lWindWeatherEffectListFront.end(); iter++ )
	{
		(*iter)->Update( vCamPosition );
	}
}



//===============================================
//	Draw
//===============================================
void Weather::Draw(int iWhichList )
{
	std::list<Rain*> TempRainList = (iWhichList == 1 ? m_lRainWeatherEffectListBack : m_lRainWeatherEffectListFront);
	for( std::list<Rain*>::iterator iter = TempRainList.begin(); iter != TempRainList.end(); iter++ )
	{
		(*iter)->Draw();
	}

	std::list<Wind*> TempWindList = (iWhichList == 1 ? m_lWindWeatherEffectListBack : m_lWindWeatherEffectListFront );
	for( std::list<Wind*>::iterator iter = TempWindList.begin(); iter != TempWindList.end(); iter++ )
	{
		(*iter)->Draw();
	}
}





















//===============================================
//	Rain Constructor
//===============================================
Rain::Rain()
{
	X = -1.f;
	Y = 0.f;
	W = 10.f;
	H = 32.f;
	m_fSpeed = DeltaTime::GetInstance()->GetDeltaTimeNormalisedValue( (float)(rand() % 10 + 10) );
	Opacity = (float)(rand() % 225 + 25) / 255;
}

//===============================================
//	Rain Destructor
//===============================================
Rain::~Rain()
{

}

//===============================================
//	Rain Update
//===============================================
void Rain::Update( Vector2 vCamPosition )
{
	/////////////////////////////////////////////////////////
	int iStartNorthOrEast = 0; // Which means neither
	DeltaTime* pDT = DeltaTime::GetInstance();
	/////////////////////////////////////////////////////////
	if( (X < vCamPosition.X) || (Y > (vCamPosition.Y + ScreenResolution::GetInstance()->GetScreenHeight())) )
	{
		iStartNorthOrEast = rand() % 2 + 1;
	}
	/////////////////////////////////////////////////////////
	if( iStartNorthOrEast == 1 ) // Start North
	{
		X = ( ((rand() % (int)ScreenResolution::GetInstance()->GetScreenWidth()) + 1) + vCamPosition.X );
		Y = (vCamPosition.Y - (H + 10.f));
		m_fSpeed = pDT->GetDeltaTimeNormalisedValue( (float)(rand() % 10 + 10) );
		Opacity = (float)(rand() % 225 + 25) * 0.0039215f; // Dividing by 255
	}
	else if( iStartNorthOrEast == 2 ) // Start East
	{
		X = ((vCamPosition.X + ScreenResolution::GetInstance()->GetScreenWidth()) + W) + 10;
		Y = ((rand() % (int)ScreenResolution::GetInstance()->GetScreenHeight()) + (vCamPosition.Y - (H + 10.f)));
		m_fSpeed = pDT->GetDeltaTimeNormalisedValue( (float)(rand() % 10 + 10) );
		Opacity = (float)(rand() % 225 + 25) * 0.0039215f; // Dividing by 255
	}
	/////////////////////////////////////////////////////////
	X -= (m_fSpeed * 0.3f) * pDT->GetDeltaTime();
	Y += m_fSpeed * pDT->GetDeltaTime();
	/////////////////////////////////////////////////////////
}

//===============================================
//	Rain Draw
//===============================================
void Rain::Draw()
{
	glBegin( GL_LINES );
	glColor4f(1.0, 1.0, 1.0, Opacity); // Make it White
	glVertex2f( X, Y );
	glVertex2f( X - (W * 0.5f), Y + H );
	glEnd();
}




















//===============================================
//	Wind Constructor
//===============================================
Wind::Wind()
{
	X = -1.f;
	Y = 0.f;
	W = 10.f;
	H = 16;
	m_fSpeed = DeltaTime::GetInstance()->GetDeltaTimeNormalisedValue( (float)(rand() % 10 + 10) );
}
//===============================================
//	Wind Destructor
//===============================================
Wind::~Wind()
{

}
//===============================================
//	Wind Update
//===============================================
void Wind::Update( Vector2 vCamPosition )
{
	/////////////////////////////////////////////////////////
	if( (X < vCamPosition.X) )
	{
		X = ((vCamPosition.X + ScreenResolution::GetInstance()->GetScreenWidth()) + W) + 10;
		Y = ((rand() % (int)ScreenResolution::GetInstance()->GetScreenHeight()) + (vCamPosition.Y - (H + 5)));
		m_fSpeed = DeltaTime::GetInstance()->GetDeltaTimeNormalisedValue( (float)(rand() % 5 + 10) );
	}
	/////////////////////////////////////////////////////////
	X -= m_fSpeed * DeltaTime::GetInstance()->GetDeltaTime();
	/////////////////////////////////////////////////////////
}
//===============================================
//	Wind Draw
//===============================================
void Wind::Draw()
{
	glBegin( GL_LINE_STRIP );
	glColor3f( 0.5f, 0.5f, 0.5f); // Make it gray
	
	float fY = Y;
	float fDist = 30;
	for (float fAngle = 0; fAngle <= 30; ++fAngle)
	{
		glVertex2f(X + cos(fAngle) * fDist, fY);
		fY += 1.0f;
	}

	//float fX = X;
	//float fDist = 8;
	//float fSin = -1.0f;
	//for (int iCount = 0; iCount < 20; ++iCount)
	//{
	//	glVertex2f(fX, Y + sin(fSin) * fDist);
	//	fX += 5;
	//	fSin += 0.5f;
	//}


	//glVertex2f( X, Y );
	//glVertex2f( X - W, Y + H );

	//glVertex2f((X + 5), (Y + 5)); 
 //   glVertex2f((X + 15) - W, (Y + 15)+ H );  

	//glVertex2f((X + 20), (Y + 20)); 
 //   glVertex2f((X + 30) - W, (Y + 30)+ H );  


	glEnd();
}