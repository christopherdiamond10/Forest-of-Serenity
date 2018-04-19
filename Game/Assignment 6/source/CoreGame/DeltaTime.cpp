#include "DeltaTime.h"

#include "sdl.h"
#include <Windows.h>
#include <iostream>
#include <assert.h>




DeltaTime* DeltaTime::m_Instance = NULL;

//===================================
//		Get Class Instance
//===================================
DeltaTime* DeltaTime::GetInstance()
{
	return m_Instance;
}


//===================================
//		Constructor
//===================================
DeltaTime::DeltaTime() 
	: CONST_F_FIXED_FRAME_TIME			 ((1.f / 60.f))
	, CONST_F_EXPECTED_FRAMES_PER_SECOND ( 60.f )
{
	if( m_Instance == NULL )
	{
		m_Instance = this;
	}
	else
	{	assert(0);	}
}

//===================================
//		Destructor
//===================================
DeltaTime::~DeltaTime()
{

}






//===================================
//		OnLoad
//===================================
void DeltaTime::OnLoad()
{
	UpdateCurrent_Ticks();
}


//===================================
//		OnUnload
//===================================
void DeltaTime::OnUnload()
{

}








//===================================
//		Get Delta Time
//===================================
float DeltaTime::GetDeltaTime()
{
	return m_fDeltaTime;
}
//===================================
//	Get Delta Time Normalised Value
//===================================
float DeltaTime::GetDeltaTimeNormalisedValue( float fNormaliseThisValue )
{
	return( fNormaliseThisValue * CONST_F_EXPECTED_FRAMES_PER_SECOND );
}





//===================================
//		Update Current Ticks
//===================================
void DeltaTime::UpdateCurrent_Ticks()
{
	m_iCurr_Ticks = SDL_GetTicks();
}


//===================================
//		Update Previous Ticks
//===================================
void DeltaTime::UpdatePrevious_Ticks()
{
	m_iPrev_Ticks = m_iCurr_Ticks;
}


//===================================
//		Update Delta Time
//===================================
void DeltaTime::UpdateDeltaTime()
{
	UpdatePrevious_Ticks();
	UpdateCurrent_Ticks();

	m_fDeltaTime = (float)((m_iCurr_Ticks - m_iPrev_Ticks) * 0.001f); 
	
	// Don't OverExert DeltaTime... this can be caused by simply not using the program, thus blocking DeltaTime updates and spiking the results
	if( m_fDeltaTime > CONST_F_FIXED_FRAME_TIME )
	{
		// It's simply better to have everything not update for one frame if this is the case
		m_fDeltaTime = CONST_F_FIXED_FRAME_TIME;
	}
}






//===================================
//		Print Delta Time
//===================================
void DeltaTime::Print_DeltaTime()
{
	std::cout << "Current Ticks			= " << m_iCurr_Ticks << std::endl;
	std::cout << "Previous Ticks			= " << m_iPrev_Ticks << std::endl;
	std::cout << "Time Since last check		= ";
	std::cout << m_fDeltaTime << std::endl << std::endl;
}
