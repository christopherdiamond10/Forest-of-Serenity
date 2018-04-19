//\====================================================================================
//\ Author: Christopher Diamond
//\ About : Audio.h - 
//\
//\ creates a class that will be used as a template for defining the the Audio aspects
//\ of the game.
//\ 
//\ The class uses a lot of context from the FMOD Library and header files.
//\====================================================================================
#ifndef _AUDIOMANAGER_H_
#define _AUDIOMANAGER_H_

#ifndef _NUM_CHANNELS_
#define _NUM_CHANNELS_ 3
#endif

#include <fmod.hpp>
#include <string>
#include <list>



//=======================
//	Audio Manager
//=======================
class AudioManager
{
//////////////////////////////////////////
public:
//////////////////////////////////////////	

	//===============================================
	//			Constructor & Destructor
	//===============================================
	AudioManager();
	~AudioManager();




	//===============================================
	//			Static Functions
	//===============================================

	// Get the one time instance of the AudioManager class
	static AudioManager* GetInstance();


	//===============================================
	//			Public Functions
	//===============================================
	void OnLoad();
	void OnUnload();

	// As a rule, update must be called every frame
	void Update();

	// Play a Sound, pass in the alias name of a sound you have imported, if you know what soundtype it is (BGM, BGS, SFX) you can pass that in as an argument to speed up the process
	void PlaySound( std::string NameofSound, std::string sSoundType = "" );

	// Stop a Channel (including any and all sounds it is playing), pass in the alias name of a sound you have imported, Channel Types: BGM, BGS, SFX
	void StopSound(std::string sChannelType);

	// Fadein Sound, pass in the amount of time you want to use until the sound is fully faded in. Use this function after using the PlaySound function
	void FadeinSound(std::string sChannelType, float fSecondsToFadeIn);

	// Fadeout Sound, pass in the amount of time you want to use until the sound is fully faded in. Use this function after using the PlaySound function
	void FadeoutSound(std::string sChannelType, float fSecondsToFadeOut);

	// Import New Audio Files into the AudioManager
	// Filename: Filename (including extension) of the Audio File you are importing, path is included with the directory string you have set earlier
	// AudioName: You may give this sound file an alias name, this alias name will be used to identify the sound for other functions. For Example name the file "Title Theme"
	// Volume: Volume of the sound file, can be between 5..100. The volume is offset by the channel volume, so 80 volume for this sound and 80 volume for the channel volume will yield a 64 total volume when played
	// Speed: Speed of the Sound File, can be between 5..200. This ONLY affects MIDI files, does not affect other sound types, they will still play at normal speeds
	// LoopStart: Position to start Looping Audio via SampleRates, if you don't know what this is, best leave it as 0
	// LoopEnd: Position to end Audio and restart from Loopstart, again if you don't know what this is, leave it as 0
	void ImportAudio( std::string sFileName, std::string sAudioName, std::string sAudioType, unsigned int iVolume = 80, unsigned int iSpeed = 100, unsigned int iSampleRate_LoopStart = 0, unsigned int iSampleRate_LoopEnd = 0 );
	
	// Restore Default Sound Options, sets all channel volumes back to 80
	void RestoreDefaults();

	// Prints out Audio Loop Information. Use for debugging
	void PrintOutAudioLoopInfo();

	//===============================================
	//			Getter Functions
	//===============================================

	// Get Volume for a Sound, pass in the alias name of a sound you have imported, if you know what soundtype it is (BGM, BGS, SFX) you can pass that in as an argument to speed up the process
	unsigned int GetVolume( std::string NameofSound, std::string sSoundType = "" );

	// Get Tempo for a Sound, pass in the alias name of a sound you have imported, if you know what soundtype it is (BGM, BGS, SFX) you can pass that in as an argument to speed up the process
	unsigned int GetTempo( std::string NameofSound, std::string sSoundType = "" );

	// See if a channel is mute. Channel Types: BGM, BGS, SFX
	bool Get_IsMute( std::string sChannelType );

	//===============================================
	//			Setter Functions
	//===============================================

	// Set Root Folder Location, this folder will now be where the Manager will look for sounds
	void SetRootAudioFolderLocation( std::string sLocation );

	// Set Volume For Entire System, including BGM, BGS & SFX
	void SetMasterVolume( unsigned int iVolume );	

	// Set Individual Channel Volume, Channel Types: BGM, BGS, SFX
	void SetChannelVolume( std::string sChannelType, unsigned int iVolume );

	// Set Volume for an individual sound, the channel sound still reflects off of this, so an 80 volume sound mixed in with an 80 channel volume sound will yield a 64 volume sound when played
	// If you know what soundtype it is (BGM, BGS, SFX) you can pass that in as an argument to speed up the process
	void SetSoundVolume( std::string NameofSound, unsigned int iVolume, std::string sSoundType = "" );

	// Set Tempo for an individual sound, only works for MIDI Files, if you know what soundtype it is (BGM, BGS, SFX) you can pass that in as an argument to speed up the process
	void SetSoundTempo( std::string NameofSound, unsigned int iTempo, std::string sSoundType = "" );
	
	// Set Sound Pause for a Channel, basically you can mute all sounds in that channel
	void SetChannelPause( std::string sChannelType, bool bSoundPaused );

	// Set Mute, you may mute a channel with this function. Channel Types: BGM, BGS, SFX
	void SetMute( std::string sChannelType );



//////////////////////////////////////////
private:
//////////////////////////////////////////
	
	struct AudioInfo
	{
		std::string				FilePath;
		std::string				SoundName;
		std::string				SoundType; // BGM, BGS, SFX
		float					Volume;
		float					Tempo;
		unsigned int			LoopStart;
		unsigned int			LoopEnd;
		FMOD::Sound*			Sound_ptr;
	};

	struct ChannelInfo
	{
		FMOD::Channel**			ChannelPTR;
		AudioInfo*				CurrentSound;
		float					Volume;
		bool					Paused;
		bool					Fadein;
		bool					Fadeout;
		float					FadeTime;
		float					CurrentFadeTime;
		std::list<AudioInfo>	ImportedAudioList;
	};

	//===============================================
	//			Private Declarations
	//===============================================
	ChannelInfo			 m_ChannelInfos[3];

	std::string			 m_sBGMReservedAudio;
	std::string			 m_sBGSReservedAudio;

	std::string			 m_sDirectoryLocation;

	bool				 m_bMuteSoundEffects;


	FMOD_RESULT			 FMOD_Result;
	FMOD::System*		 m_pFMODSystem;
	FMOD::Channel*		 m_pBGMChannel;
	FMOD::Channel*		 m_pBGSChannel;
	FMOD::Channel*		 m_pSEChannel;


	//===============================================
	//			Static Declarations
	//===============================================
	static AudioManager* m_Instance;


	//===============================================
	//			Private Functions
	//===============================================
	void		 InitSound();
	void		 CorrectChannelVolume( ChannelInfo& a_Channel, float fVolume );
	void		 UpdateChannelFade( ChannelInfo& a_Channel );
	bool		 BGMWasFoundAndPlaying(std::string NameofSound);
	bool		 BGSWasFoundAndPlaying(std::string NameofSound);
	bool		 SEWasFoundAndPlaying(std::string NameofSound);
	bool		 CheckIfAlreadyImported( std::string sFilePath );
	float		 CheckVolumeIsValid( unsigned int iVolume );
	float		 CheckTempoIsValid( unsigned int iTempo );
	AudioInfo	 FindSoundFromPTR( FMOD::Sound* pSound );
	AudioInfo*	 FindAudioInfoInBGMImportedList( std::string NameofSound );
	AudioInfo*	 FindAudioInfoInBGSImportedList( std::string NameofSound );
	AudioInfo*	 FindAudioInfoInSEImportedList( std::string NameofSound );
	AudioInfo*	 ConvertStringIntoAudioInfoObject( std::string NameOfSound, std::string sSoundType);
	ChannelInfo* ConvertStringIntoChannelInfoIndex( std::string sChannelType );
	std::string  ConvertStringToChannelIdentifier( std::string sChannelType );
};

#endif