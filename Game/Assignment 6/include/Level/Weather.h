//\====================================================================================
//\ Author: Christopher Diamond
//\ About : Weather.h - 
//\ 
//\ Defines the Weather Class. This class is used to create and handle weather effects
//\ for the level, Weather Effect Classes are also created in this Header File.
//\====================================================================================
#ifndef _WEATHER_H_
#define _WEATHER_H_

#include <list>
#include <string>
#include "Vector2.h"

class Rain;
class Wind;


class Weather
{
public:

	Weather();
	~Weather();

	void OnLoad();
	void OnUnload();

	void StartWeather( std::string sTypeOfWeatherEffect, int iPowerOfWeatherEffect, bool bPlayBGSforWeatherEffect = true );
	void CeaseWeather( std::string sTypeOfWeatherEffect );

	void Update( Vector2 vCamPosition );
	void Draw(int iWhichList );

private:

	void CreateWeatherEffect( std::string sTypeOfWeatherEffect, int iWhichList, unsigned int iHowManyToCreate );
	void ClearWeatherList( std::string sTypeOfWeatherEffect );
	std::list<Rain*> m_lRainWeatherEffectListBack, m_lRainWeatherEffectListFront;
	std::list<Wind*> m_lWindWeatherEffectListBack, m_lWindWeatherEffectListFront;
};









class Wind
{
public:

	Wind();
	~Wind();

	void Update( Vector2 vCamPosition );
	void Draw();

private:

	float X, Y, W, H;
	float m_fSpeed;
};

class Rain
{
public:

	Rain();
	~Rain();

	void Update( Vector2 vCamPosition );
	void Draw();

private:

	float X, Y, W, H, Opacity;
	float m_fSpeed;
};

#endif