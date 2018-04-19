//\====================================================================================
//\ Author: Christopher Diamond
//\ About : AnimationHandler.h - 
//\ 
//\ Defines the AnimationHandler Class. This class is used to process and continue animations.
//\ As of the moment this class does nothing.
//\====================================================================================
#ifndef _ANIMATIONHANDLER_H_
#define _ANIMATIONHANDLER_H_


#include <list>
#include "Vector2.h"



//===============================================
//	Structs
//===============================================
struct SpriteInfo
{
    int TextureID, X, Y, W, H;
    float UvStartX, UvStartY, UvEndX, UvEndY;     
};


struct AnimatedFrameInfo
{
    SpriteInfo*				SprInfoList;
    bool					bTintScreen;
    bool					bTintCharacter;
	int						iTotalSprites;
    int						iTintScreenColour[4];
    int						iTintCharacterColour[3];
    float					fWaitTimeTillNextFrame;
    std::string				sSoundFilename;
};



//===============================================
//	Class Declarations
//===============================================
class Animation_Revive;





//===============================================
//	Animation Handler Class
//===============================================
class AnimationHandler
{
public:

	AnimationHandler();
	~AnimationHandler();

	void OnLoad();
	void OnUnload();

	void Update();
	void Draw();

	bool Get_IsAnimationComplete( unsigned int iAnimationID );

	unsigned int StartAnimation( unsigned int iWhichAnimation, Vector2 vAnimationLocation );

	static AnimationHandler* GetInstance();


	enum eAnimation
	{
		eRevive,
		eFire1,
	};

private:

	void DeleteArrayItem( int Element );

	struct AnimationMaintainanceStruct
	{
		AnimatedFrameInfo* AnimationList;
		float CurrentWaitTime;
		float CurrentTime;
		int CurrentFrame;
		int TotalFrames;
		int PartiallyCompletedFrame;
		bool PartiallyCompleted;
		bool RelativeToScreen;
		bool AnimationCompleted;
	};

	static AnimationHandler* m_Instance;
	unsigned int m_iNextAnimationID;


	AnimationMaintainanceStruct GetAnimationFromXML( unsigned int iWhichAnimation );
	AnimationMaintainanceStruct m_AnimatedFrameInfoArray[20];
};




#endif