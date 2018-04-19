//\====================================================================================
//\ Author: Christopher Diamond
//\ About : Audio.cpp - 
//\
//\ Creates the Audio source file. This cpp defines the music files that will be used 
//\ in the game.
//\====================================================================================


//===============================================
//	UpCase an Entire String ~ 
//			This Function is Not Bound to the Audio Class, 
//			but is used for Uppercasing strings to match with identifiers. 
//			IE: you can say 'bgs' and it will match the check for 'BGS'
//===============================================
#include <locale>
static std::string String_To_UpperCase( std::string cString )
{
	std::locale loc;
	std::string sReturnString;
	int iStringLength = cString.length();

	for( int i = 0; i < iStringLength; i++)
	{
		unsigned char c = std::toupper( (unsigned char)cString[i], loc );
		sReturnString += c;
	}

	return sReturnString;
}




//////////////////////////////////////////////////
//	Includes some header files which we will  ////
//	be using in this .cpp file				  ////
//////////////////////////////////////////////////
#include "AudioManager.h"					  ////
#include <assert.h>							  ////
#include <iostream>							  ////
#include "DeltaTime.h"						  ////
//////////////////////////////////////////////////


AudioManager* AudioManager::m_Instance = NULL;

//===============================================
//	Get Class Instance ~ Singleton
//===============================================
AudioManager* AudioManager::GetInstance()
{
	return m_Instance;
}


//===============================================
//	Constructor
//===============================================
AudioManager::AudioManager()
{
	if( m_Instance == NULL )	
	{ 
		m_Instance = this; 
	}
	else						
	{ 
		std::cout << "ERROR: Only One Instance of the AudioManager can exist at any one time! \n\n\n\n\n";
		assert(0); 
	}
}


//===============================================
//	Destructor
//===============================================
AudioManager::~AudioManager()
{
	m_Instance = NULL;
}

//===============================================
//	Initialise Sound
//===============================================
void AudioManager::InitSound()
{
	FMOD_Result = System_Create( &m_pFMODSystem );
	FMOD_Result = m_pFMODSystem->init( _NUM_CHANNELS_, FMOD_INIT_NORMAL, 0 );	


}


//===============================================
//	Load Sound(s)
//===============================================
void AudioManager::OnLoad()
{
	InitSound();

	m_bMuteSoundEffects  = false;


	for(int i = 0; i < 3; i++)
	{
		m_ChannelInfos[i].Volume			= 0.8f;
		m_ChannelInfos[i].Paused			= false;
		m_ChannelInfos[i].Fadein			= false;
		m_ChannelInfos[i].Fadeout			= false;
		m_ChannelInfos[i].FadeTime			= 0.f;
		m_ChannelInfos[i].CurrentFadeTime	= 0.f;
		m_ChannelInfos[i].CurrentSound		= nullptr;
	}

	m_ChannelInfos[0].ChannelPTR = &m_pBGMChannel;
	m_ChannelInfos[1].ChannelPTR = &m_pBGSChannel;
	m_ChannelInfos[2].ChannelPTR = &m_pSEChannel;


	m_sBGMReservedAudio  = "";
	m_sBGSReservedAudio  = "";
	m_sDirectoryLocation = "./";
}


//===============================================
//	Unload Sound
//===============================================
void AudioManager::OnUnload()
{

}





//===============================================
//	Get Volume
//===============================================
unsigned int AudioManager::GetVolume( std::string NameofSound, std::string sSoundType )
{
	AudioInfo* AudInfo = ConvertStringIntoAudioInfoObject(NameofSound, sSoundType);
	if(AudInfo != NULL)
	{
		return (unsigned int)(AudInfo->Volume * 100.f); 
	}

	return 80; // 80 is default volume sound, return this if the Sound cannot be found
}
//===============================================
//	Get Tempo
//===============================================
unsigned int AudioManager::GetTempo( std::string NameofSound, std::string sSoundType )
{
	AudioInfo* AudInfo = ConvertStringIntoAudioInfoObject(NameofSound, sSoundType);
	if(AudInfo != NULL)
	{
		return (unsigned int)(AudInfo->Tempo * 100.f); 
	}

	return 100; // 100 is default Tempo of sound, return this if the Sound cannot be found
}
//===============================================
//	Get 'Is Mute'
//===============================================
bool AudioManager::Get_IsMute( std::string sChannelType )
{
	sChannelType = ConvertStringToChannelIdentifier(sChannelType);
	bool bMute = false;
	/////////////////////////////////////////
	if( sChannelType == "BGM" )
	{ m_pBGMChannel->getMute( &bMute ); }
	/////////////////////////////////////////
	else if( sChannelType == "BGS" )
	{ m_pBGSChannel->getMute( &bMute ); }
	/////////////////////////////////////////
	else if( sChannelType == "SE" )
	{ bMute = m_bMuteSoundEffects; }
	/////////////////////////////////////////
	return bMute;
}





//===============================================
//	Set Audio Folder Root Location
//===============================================
void AudioManager::SetRootAudioFolderLocation( std::string sLocation )
{
	m_sDirectoryLocation = sLocation;
}
//===============================================
//	Set Master Volume
//===============================================
void AudioManager::SetMasterVolume( unsigned int iVolume )
{
	float fVolume = CheckVolumeIsValid( iVolume );

	m_ChannelInfos[0].Volume = fVolume;
	m_ChannelInfos[1].Volume = fVolume;
	m_ChannelInfos[2].Volume = fVolume;

	// Correct Volume for all Channels
	CorrectChannelVolume(m_ChannelInfos[0], fVolume);
	CorrectChannelVolume(m_ChannelInfos[1], fVolume);
	CorrectChannelVolume(m_ChannelInfos[2], fVolume);
}
//===============================================
//	Set Channel Volume
//===============================================
void AudioManager::SetChannelVolume( std::string sChannelType, unsigned int iVolume )
{
	ChannelInfo* CI = ConvertStringIntoChannelInfoIndex(ConvertStringToChannelIdentifier(sChannelType));
	if(CI != NULL)
	{
		CorrectChannelVolume(*CI, ((float)iVolume * 0.01f) );
	}
}
//===============================================
//	Set Sound Volume
//===============================================
void AudioManager::SetSoundVolume( std::string NameofSound, unsigned int iVolume, std::string sSoundType )
{
	AudioInfo* AudInfo = ConvertStringIntoAudioInfoObject(NameofSound, sSoundType);
	if(AudInfo != NULL)
	{
		AudInfo->Volume = CheckVolumeIsValid( iVolume );
	}
}
//===============================================
//	Set Sound Tempo
//===============================================
void AudioManager::SetSoundTempo( std::string NameofSound, unsigned int iTempo, std::string sSoundType )
{
	AudioInfo* AudInfo = ConvertStringIntoAudioInfoObject(NameofSound, sSoundType);
	if(AudInfo != NULL)
	{
		AudInfo->Volume = CheckTempoIsValid( iTempo );
	}
}
//===============================================
//	Set Channel Pause
//===============================================
void AudioManager::SetChannelPause( std::string sChannelType, bool bSoundPaused )
{
	ChannelInfo* CI = ConvertStringIntoChannelInfoIndex(ConvertStringToChannelIdentifier(sChannelType));
	if(CI != NULL)
	{
		CI->Paused = bSoundPaused;
		(*CI->ChannelPTR)->setPaused(bSoundPaused);
	}
}
//===============================================
//	Set Mute
//=============================================
void AudioManager::SetMute( std::string sChannelType )
{
	sChannelType = ConvertStringToChannelIdentifier( sChannelType );

	bool bMute = false;
	/////////////////////////////////////////
	if( sChannelType == "BGM" )
	{
		m_pBGMChannel->getMute( &bMute );

		if( !bMute )
		{ m_pBGMChannel->setMute( true ); }
		else
		{ 
			m_pBGMChannel->setMute( false ); 

			// Play Reserved Sound if you're no longer mute
			if( m_sBGMReservedAudio != "" )
			{
				PlaySound( m_sBGMReservedAudio );
				m_sBGMReservedAudio = "";
			}
		}
	}
	/////////////////////////////////////////
	else if( sChannelType == "BGS" )
	{
		m_pBGSChannel->getMute( &bMute );

		if( !bMute )
		{ m_pBGSChannel->setMute( true ); }
		else
		{ 
			m_pBGSChannel->setMute( false ); 

			if( m_sBGSReservedAudio != "" )
			{
				PlaySound( m_sBGSReservedAudio );
				m_sBGSReservedAudio = "";
			}
		}
	}
	/////////////////////////////////////////
	else if( sChannelType == "SE" )
	{
		if( !m_bMuteSoundEffects )
		{ m_bMuteSoundEffects = true; }
		else
		{ m_bMuteSoundEffects = false; }
	}
	/////////////////////////////////////////
}



//===============================================
//	Restore Defaults
//===============================================
void AudioManager::RestoreDefaults()
{
	// Correct Volume for all Channels
	CorrectChannelVolume(m_ChannelInfos[0], 0.8f);
	CorrectChannelVolume(m_ChannelInfos[1], 0.8f);
	CorrectChannelVolume(m_ChannelInfos[2], 0.8f);
}










//===============================================
//	Update Sound
//===============================================
void AudioManager::Update()
{
	// Update Sound Fade
	for(int i = 0; i < 3; i++)
	{
		if(m_ChannelInfos[i].Fadein || m_ChannelInfos[i].Fadeout)
		{
			UpdateChannelFade( m_ChannelInfos[i] );
		}
	}

	// Update SoundSystem
	FMOD_Result = m_pFMODSystem->update();
}




//===============================================
//	Update Channel Fade
//===============================================
void AudioManager::UpdateChannelFade( ChannelInfo& a_Channel )
{
	a_Channel.CurrentFadeTime += DeltaTime::GetInstance()->GetDeltaTime();

	// Get Current Channel Volume
	float fVolume;
	(*a_Channel.ChannelPTR)->getVolume(&fVolume);


	// Get Update Volume Via DeltaTime
	float fTempVolume = ((DeltaTime::GetInstance()->GetDeltaTime() * a_Channel.Volume * a_Channel.CurrentSound->Volume) / a_Channel.FadeTime);
	
	// Add or Deduct Volume from Current Channel Volume
	fVolume += a_Channel.Fadein ? fTempVolume : -fTempVolume;

	// Set Volume
	(*a_Channel.ChannelPTR)->setPaused(true);
	(*a_Channel.ChannelPTR)->setVolume(fVolume);
	(*a_Channel.ChannelPTR)->setPaused(false);

	// If Fully Faded in/out, set fade to false
	if(a_Channel.CurrentFadeTime >= a_Channel.FadeTime)
	{
		a_Channel.Fadein = false;
		a_Channel.Fadeout = false;
		a_Channel.CurrentFadeTime = 0.0f;
	}
}




//===============================================
//	Print Out Audio Loop Info
//===============================================
void AudioManager::PrintOutAudioLoopInfo()
{
	//////////////////////////////////////
	unsigned int iSoundPosition, iLoopStart, iLoopEnd;
	//////////////////////////////////////
	m_pBGMChannel->getPosition( &iSoundPosition, FMOD_TIMEUNIT_PCM );
	m_pBGMChannel->getLoopPoints( &iLoopStart, FMOD_TIMEUNIT_PCM, &iLoopEnd, FMOD_TIMEUNIT_PCM );
	//////////////////////////////////////
	std::cout << "\n\nCurrent Sound Position: " << iSoundPosition << std::endl;
	//////////////////////////////////////
	if( iSoundPosition > iLoopStart )
		std::cout << "Sound has Entered LoopStart\n";	
	else
		std::cout << "Sound has not Entered LoopStart\n";
	//////////////////////////////////////
	if( iSoundPosition == iLoopEnd )
		std::cout << "Sound has hit LoopEnd\n";	
	else
		std::cout << "Sound has not hit LoopEnd\n";
	//////////////////////////////////////
	std::cout << "LoopStart = " << iLoopStart << std::endl;
	std::cout << "LoopEnd = " << iLoopEnd << "\n\n\n\n\n";
	//////////////////////////////////////
}




//===============================================
//	Import Audio
//===============================================
void AudioManager::ImportAudio( std::string sFileName, std::string sAudioName, std::string sAudioType, unsigned int iVolume, unsigned int iTempo, unsigned int iSampleRate_LoopStart, unsigned int iSampleRate_LoopEnd )
{
	std::string sPathtoFile = m_sDirectoryLocation;
	sAudioType = ConvertStringToChannelIdentifier( sAudioType );
	//-----------------------------------------------------------------------------------------------------------------------------------------
	if(sAudioType != "BGM" && sAudioType != "BGS" && sAudioType != "SE" )
	{
		#if defined(__WIN32__)
			MessageBox(NULL, L"Mate... Gotta define the type of the Sound, it's either a 'BGM', 'BGS' or a 'SFX'.", L"Import_Failed", MB_ERROR);
		#endif
		
		std::cout << "\n\nImport Sound Failed: Mate... Gotta define the type of the Sound, it's either a 'BGM', 'BGS' or a 'SFX'.\n\n\n\n\n";
		return;
	}
	//-----------------------------------------------------------------------------------------------------------------------------------------
	sPathtoFile += sAudioType;
	sPathtoFile += "/";
	sPathtoFile += sFileName;
	
	// Check to make sure the Audio hasn't already been imported
	if( CheckIfAlreadyImported( sPathtoFile ))
	{
		return;
	}

	// Create Info for the Sound
	AudioInfo AudInfo;
	AudInfo.FilePath	= sPathtoFile;
	AudInfo.SoundName	= sAudioName;
	AudInfo.SoundType	= sAudioType;
	AudInfo.Volume		= ((float)iVolume * 0.01f);
	AudInfo.Tempo		= ((float)iTempo * 0.01f);
	AudInfo.LoopStart	= iSampleRate_LoopStart;
	AudInfo.LoopEnd		= iSampleRate_LoopEnd;

	// Create either Stream or Memory for the sound
	if( AudInfo.SoundType == "BGM" )
	{
		FMOD_Result = m_pFMODSystem->createStream( AudInfo.FilePath.c_str(), FMOD_LOOP_NORMAL, 0, &AudInfo.Sound_ptr );
		m_ChannelInfos[0].ImportedAudioList.push_back(AudInfo);
	}
	else if( AudInfo.SoundType == "BGS" )
	{
		FMOD_Result = m_pFMODSystem->createSound( AudInfo.FilePath.c_str(), FMOD_LOOP_NORMAL, 0, &AudInfo.Sound_ptr);
		m_ChannelInfos[1].ImportedAudioList.push_back(AudInfo);
	}
	else
	{
		FMOD_Result = m_pFMODSystem->createSound( AudInfo.FilePath.c_str(), FMOD_DEFAULT, 0, &AudInfo.Sound_ptr);
		m_ChannelInfos[2].ImportedAudioList.push_back(AudInfo);
	}
}






//===============================================
//	Fadein Sound
//===============================================
void AudioManager::FadeinSound(std::string sChannelType, float fSecondsToFadeIn)
{
	ChannelInfo* CI = ConvertStringIntoChannelInfoIndex(ConvertStringToChannelIdentifier(sChannelType));
	if(CI != NULL)
	{
		CI->Paused		= false;
		CI->Fadein		= true;
		CI->Fadeout		= false;
		CI->FadeTime	= fSecondsToFadeIn;

		// Set Low Volume
		(*CI->ChannelPTR)->setPaused(true);
		(*CI->ChannelPTR)->setVolume(0.001f);
		(*CI->ChannelPTR)->setPaused(false);
	}
}


//===============================================
//	Fadeout Sound
//===============================================
void AudioManager::FadeoutSound(std::string sChannelType, float fSecondsToFadeOut)
{
	ChannelInfo* CI = ConvertStringIntoChannelInfoIndex(ConvertStringToChannelIdentifier(sChannelType));
	if(CI != NULL)
	{
		CI->Paused		= false;
		CI->Fadein		= false;
		CI->Fadeout		= true;
		CI->FadeTime	= fSecondsToFadeOut;
	}
}


//===============================================
//	Stop Sound
//===============================================
void AudioManager::StopSound(std::string sChannelType)
{
	ChannelInfo* CI = ConvertStringIntoChannelInfoIndex(ConvertStringToChannelIdentifier(sChannelType));
	if(CI != NULL)
	{
		FMOD_Result = (*CI->ChannelPTR)->stop();
	}
}


//===============================================
//	Play Sound
//===============================================
void AudioManager::PlaySound( std::string NameofSound, std::string sSoundType )
{
	if(sSoundType != "")
	{
		sSoundType = ConvertStringToChannelIdentifier(sSoundType);
		if(sSoundType == "BGM" && BGMWasFoundAndPlaying(NameofSound)) { return; }
		if(sSoundType == "BGS" && BGSWasFoundAndPlaying(NameofSound)) { return; }
		if(sSoundType == "SE"  && SEWasFoundAndPlaying(NameofSound))  { return; }
	}

	// If We Got Up to this point, then no SoundType was Defined, we'll just have to go through each list until we find the sound
	if(BGMWasFoundAndPlaying(NameofSound) || BGSWasFoundAndPlaying(NameofSound) || SEWasFoundAndPlaying(NameofSound)) 
	{
		// Sound was Found, Exit Function
		return;
	}

	// Sound Was Not Found, Show Error in Console
	std::cout << "Alias SoundFileName: " << NameofSound << " was not found. It either does not exist or you have not imported it.\n" 
														<< "Please note that the alias name is case sensitive and that you cannot import a sound file twice, if you believe you have imported it"
														<< "correctly please check your project to be sure you have not done so twice. \n\n\n\n\n";
}



//===============================================
//	BGM Was Found and Playing?
//===============================================
bool AudioManager::BGMWasFoundAndPlaying(std::string NameofSound)
{
	AudioInfo* TempAudioInfo = FindAudioInfoInBGMImportedList(NameofSound);
	if(TempAudioInfo != NULL)
	{
		if( Get_IsMute("BGM") ) 
		{ 
			m_sBGMReservedAudio = TempAudioInfo->SoundName;
			return true; 
		}

		// Return true if already playing this sound
		FMOD::Sound* FSound;
		m_pBGMChannel->getCurrentSound(&FSound);
		if(FSound == TempAudioInfo->Sound_ptr) { return true; }


		// Setup Sound: Stop Whatever is currently playing, set loop points, play sound, then adjust volume & tempo 
		// (FMOD reconfigures volume and Tempo when it begins playing a sound, so to modify it we have to set it after we start playing)
		FMOD_Result = m_pBGMChannel->stop();
		
		// Set Loop Points (If Any)
		if( TempAudioInfo->LoopEnd > TempAudioInfo->LoopStart )
		{ 
			FMOD_Result = TempAudioInfo->Sound_ptr->setLoopPoints( TempAudioInfo->LoopStart, FMOD_TIMEUNIT_PCM, TempAudioInfo->LoopEnd, FMOD_TIMEUNIT_PCM ); 
		}
		
		FMOD_Result = m_pFMODSystem->playSound( FMOD_CHANNEL_REUSE, TempAudioInfo->Sound_ptr, false, &m_pBGMChannel );

		FMOD_Result = m_pBGMChannel->setPaused(true);
		FMOD_Result = m_pBGMChannel->setVolume(TempAudioInfo->Volume * m_ChannelInfos[0].Volume);
		FMOD_Result = TempAudioInfo->Sound_ptr->setMusicSpeed(TempAudioInfo->Tempo);
		FMOD_Result = m_pBGMChannel->setPaused(false);
		
		m_ChannelInfos[0].Paused = false;
		m_ChannelInfos[0].CurrentSound = TempAudioInfo;

		// Found Sound in this List
		return true;
	}
	// Didn't find Sound in this List
	return false;
}
//===============================================
//	BGS Was Found and Playing?
//===============================================
bool AudioManager::BGSWasFoundAndPlaying(std::string NameofSound)
{
	AudioInfo* TempAudioInfo = FindAudioInfoInBGSImportedList(NameofSound);
	if(TempAudioInfo != NULL)
	{
		if( Get_IsMute("BGS")) 
		{ 
			m_sBGSReservedAudio = TempAudioInfo->SoundName;
			return true; 
		}

		FMOD_Result = m_pBGSChannel->stop();
		FMOD_Result = m_pFMODSystem->playSound( FMOD_CHANNEL_REUSE, TempAudioInfo->Sound_ptr, false, &m_pBGSChannel );
		FMOD_Result = m_pBGSChannel->setVolume( TempAudioInfo->Volume * m_ChannelInfos[1].Volume);
		FMOD_Result = TempAudioInfo->Sound_ptr->setMusicSpeed(TempAudioInfo->Tempo);
		
		m_ChannelInfos[1].Paused = false;
		m_ChannelInfos[1].CurrentSound = TempAudioInfo;

		// Found Sound in this List
		return true;
	}
	// Didn't find Sound in this List
	return false;
}
//===============================================
//	SE Was Found and Playing?
//===============================================
bool AudioManager::SEWasFoundAndPlaying(std::string NameofSound)
{
	AudioInfo* TempAudioInfo = FindAudioInfoInSEImportedList(NameofSound);
	if(TempAudioInfo != NULL)
	{
		if( Get_IsMute("SE") ) { return true; }

		FMOD_Result = m_pFMODSystem->playSound( FMOD_CHANNEL_FREE, TempAudioInfo->Sound_ptr, false, &m_pSEChannel );
		FMOD_Result = m_pSEChannel->setVolume( TempAudioInfo->Volume * m_ChannelInfos[2].Volume);
		FMOD_Result = TempAudioInfo->Sound_ptr->setMusicSpeed(TempAudioInfo->Tempo);
		
		m_ChannelInfos[2].Paused = false;
		m_ChannelInfos[2].CurrentSound = TempAudioInfo;

		// Found Sound in this List
		return true;
	}
	// Didn't find Sound in this List
	return false;
}








//===============================================
//	Check if Audio is already Imported
//===============================================
bool AudioManager::CheckIfAlreadyImported( std::string sFilePath )
{
	// If the filename matches up to one that's already been imported, return true
	for( std::list<AudioInfo>::iterator iter = m_ChannelInfos[0].ImportedAudioList.begin(); iter != m_ChannelInfos[0].ImportedAudioList.end(); iter++ )
	{
		if( iter->FilePath == sFilePath )
		{
			return true;
		}
	}

	for( std::list<AudioInfo>::iterator iter = m_ChannelInfos[1].ImportedAudioList.begin(); iter != m_ChannelInfos[1].ImportedAudioList.end(); iter++ )
	{
		if( iter->FilePath == sFilePath )
		{
			return true;
		}
	}

	for( std::list<AudioInfo>::iterator iter = m_ChannelInfos[2].ImportedAudioList.begin(); iter != m_ChannelInfos[2].ImportedAudioList.end(); iter++ )
	{
		if( iter->FilePath == sFilePath )
		{
			return true;
		}
	}

	return false;
}

//===============================================
//	Check if Volume is Valid
//===============================================
float AudioManager::CheckVolumeIsValid( unsigned int iVolume )
{
	float fVolume = ((float)iVolume * 0.01f);    // iVolume / 100
	fVolume = fVolume > 1.0f  ? 1.0f  : fVolume; // Volume not greater than 100?
	fVolume = fVolume < 0.05f ? 0.05f : fVolume; // Volume not lower than 5? Mute Channels if you want no volume

	return fVolume;
}

//===============================================
//	Check if Speed is Valid
//===============================================
float AudioManager::CheckTempoIsValid( unsigned int iTempo )
{
	float fTempo = ((float)iTempo * 0.01f);    // iTempo / 100
	fTempo = fTempo > 2.0f  ? 2.0f  : fTempo;  // Tempo not greater than 200?
	fTempo = fTempo < 0.05f ? 0.05f : fTempo;  // Tempo not lower than 5?

	return fTempo;
}

//===============================================
//	Find Sound from PTR
//===============================================
AudioManager::AudioInfo AudioManager::FindSoundFromPTR( FMOD::Sound* pSound )
{
	for( std::list<AudioInfo>::iterator iter = m_ChannelInfos[0].ImportedAudioList.begin(); iter != m_ChannelInfos[0].ImportedAudioList.end(); iter++ )
	{
		if( iter->Sound_ptr == pSound )
		{
			return *iter;
		}
	}

	for( std::list<AudioInfo>::iterator iter = m_ChannelInfos[1].ImportedAudioList.begin(); iter != m_ChannelInfos[1].ImportedAudioList.end(); iter++ )
	{
		if( iter->Sound_ptr == pSound )
		{
			return *iter;
		}
	}

	for( std::list<AudioInfo>::iterator iter = m_ChannelInfos[2].ImportedAudioList.begin(); iter != m_ChannelInfos[2].ImportedAudioList.end(); iter++ )
	{
		if( iter->Sound_ptr == pSound )
		{
			return *iter;
		}
	}

	return AudioInfo(); // Won't Reach This
}

//===============================================
//	Correct Channel Volume
//===============================================
void AudioManager::CorrectChannelVolume( ChannelInfo& a_Channel, float fVolume )
{
	FMOD::Sound* TempSoundPTR = NULL;
	FMOD_Result = (*a_Channel.ChannelPTR)->getCurrentSound(&TempSoundPTR);
	
	// If Sound is playing, adjust volume to the sound's individual volume combined with the channel's volume
	if( TempSoundPTR != NULL ) 
	{ 
		FMOD_Result = (*a_Channel.ChannelPTR)->setPaused(true);
		FMOD_Result = (*a_Channel.ChannelPTR)->setVolume( FindSoundFromPTR(TempSoundPTR).Volume * fVolume ); 
		FMOD_Result = (*a_Channel.ChannelPTR)->setPaused(a_Channel.Paused);
	}
	// Otherwise just set the channel straight to that specific volume
	else
	{
		FMOD_Result = (*a_Channel.ChannelPTR)->setVolume( fVolume ); 
	}
}

//===============================================
//	Convert String to Channel Identifier
//===============================================
std::string AudioManager::ConvertStringToChannelIdentifier( std::string sChannelType )
{
	sChannelType = String_To_UpperCase( sChannelType );
	//-----------------------------------------------------------------------------------------------------------------------------------------
	if( sChannelType == "BGM" || sChannelType == "BACKGROUNDMUSIC" )
	{
		return "BGM";
	}
	else if( sChannelType == "BGS" || sChannelType == "BACKGROUNDSOUND" || sChannelType == "BGSFX" || sChannelType == "BGSE" )
	{
		return "BGS";
	}
	else if( sChannelType == "SE" || sChannelType == "SFX" || sChannelType == "SOUNDEFFECT" || sChannelType == "SOUNDEFFECTS" )
	{
		return "SE";
	}
	else
	{
		return "";
	}
	//-----------------------------------------------------------------------------------------------------------------------------------------
}


//===============================================
//	Convert String to ChannelInfo Index
//===============================================
AudioManager::ChannelInfo* AudioManager::ConvertStringIntoChannelInfoIndex( std::string sChannelType )
{
	if(sChannelType == "BGM") { return &m_ChannelInfos[0]; }
	if(sChannelType == "BGS") { return &m_ChannelInfos[1]; }
	else					  { return &m_ChannelInfos[2]; }
}



//===============================================
//	Find AudioInfo Object in BGM Imported List
//===============================================
AudioManager::AudioInfo* AudioManager::FindAudioInfoInBGMImportedList( std::string NameofSound )
{
	for( std::list<AudioInfo>::iterator iter = m_ChannelInfos[0].ImportedAudioList.begin(); iter != m_ChannelInfos[0].ImportedAudioList.end(); iter++ )
	{
		if( iter->SoundName == NameofSound )
		{
			return &(*iter);
		}
	}
	return NULL;
}
//===============================================
//	Find AudioInfo Object in BGS Imported List
//===============================================
AudioManager::AudioInfo* AudioManager::FindAudioInfoInBGSImportedList( std::string NameofSound )
{
	for( std::list<AudioInfo>::iterator iter = m_ChannelInfos[1].ImportedAudioList.begin(); iter != m_ChannelInfos[1].ImportedAudioList.end(); iter++ )
	{
		if( iter->SoundName == NameofSound )
		{
			return &(*iter);
		}
	}
	return NULL;
}
//===============================================
//	Find AudioInfo Object in SE Imported List
//===============================================
AudioManager::AudioInfo* AudioManager::FindAudioInfoInSEImportedList( std::string NameofSound )
{
	for( std::list<AudioInfo>::iterator iter = m_ChannelInfos[2].ImportedAudioList.begin(); iter != m_ChannelInfos[2].ImportedAudioList.end(); iter++ )
	{
		if( iter->SoundName == NameofSound )
		{
			return &(*iter);
		}
	}
	return NULL;
}

//===============================================
//	Convert String into AudioInfo Object
//===============================================
AudioManager::AudioInfo* AudioManager::ConvertStringIntoAudioInfoObject( std::string NameOfSound, std::string sSoundType )
{
	AudioInfo* AudInfo = NULL;
	if(sSoundType != "")
	{
		sSoundType = ConvertStringToChannelIdentifier(sSoundType);
		if(sSoundType == "BGM") { AudInfo = FindAudioInfoInBGMImportedList(NameOfSound); }
		if(sSoundType == "BGS") { AudInfo = FindAudioInfoInBGSImportedList(NameOfSound); }
		if(sSoundType == "SE")  { AudInfo = FindAudioInfoInSEImportedList(NameOfSound);  }
	}

	if(AudInfo != NULL) { return AudInfo; }

	// Search through all three lists if it has not been found
	AudInfo = FindAudioInfoInBGMImportedList(NameOfSound);
	if(AudInfo != NULL) { return AudInfo; }

	AudInfo = FindAudioInfoInBGSImportedList(NameOfSound);
	if(AudInfo != NULL) { return AudInfo; }

	return FindAudioInfoInSEImportedList(NameOfSound);
}