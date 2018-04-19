//\====================================================================================
//\ Author: Christopher Diamond
//\ About : DeltaTime.h - 
//\ 
//\ Defines the DeltaTime Singleton Class. This class is used to give frame independent 
//\ movement to the game, it is more or less a hub for giving you a timer and a method 
//\ for slowing down speed using time.
//\====================================================================================
#ifndef _DELTA_TIME_H_
#define _DELTA_TIME_H_

class DeltaTime
{
//////////////////////////////////////////
public:
//////////////////////////////////////////
	DeltaTime();
	~DeltaTime();

	static DeltaTime* GetInstance();

	float GetDeltaTime();
	float GetDeltaTimeNormalisedValue( float fNormaliseThisValue );

	void OnLoad();
	void OnUnload();
	
	void Print_DeltaTime();
	void UpdateDeltaTime();


//////////////////////////////////////////
private:
//////////////////////////////////////////
	
	static DeltaTime* m_Instance;

	const float CONST_F_FIXED_FRAME_TIME;
	const float CONST_F_EXPECTED_FRAMES_PER_SECOND;
	unsigned int m_iCurr_Ticks;
	unsigned int m_iPrev_Ticks;
	float m_fDeltaTime;
	


	void UpdateCurrent_Ticks();
	void UpdatePrevious_Ticks();
};


#endif