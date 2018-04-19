#include "AnimationHandler.h"

#include <assert.h>
#include <string>
#include "AudioManager.h"
#include "XMLHandler.h"
#include "DeltaTime.h"
#include "DrawManager.h"
#include "ScreenResolution.h"





AnimationHandler* AnimationHandler::m_Instance = nullptr;

//===============================================
//	Get Instance
//===============================================
AnimationHandler* AnimationHandler::GetInstance()
{
	return m_Instance;
}




//===============================================
//	Constructor
//===============================================
AnimationHandler::AnimationHandler()
{
	if( m_Instance == nullptr )
	{	m_Instance = this;	}
	else
	{	assert(0);	}
}


//===============================================
//	Destructor
//===============================================
AnimationHandler::~AnimationHandler()
{

}



//===============================================
//	OnLoad
//===============================================
void AnimationHandler::OnLoad()
{
	m_iNextAnimationID = 0;


	// 20 is the size of the Array
	for( int i = 0; i < 20; i++ )
	{
		m_AnimatedFrameInfoArray[i] = AnimationMaintainanceStruct();
		m_AnimatedFrameInfoArray[i].AnimationCompleted = true;
	}
}


//===============================================
//	OnUnload
//===============================================
void AnimationHandler::OnUnload()
{
	// 20 is the size of the Array
	for( int i = 0; i < 20; i++ )
	{
		DeleteArrayItem(i);
	}
}



void AnimationHandler::DeleteArrayItem( int Element )
{
	for( int i = 0; i < m_AnimatedFrameInfoArray[Element].TotalFrames; i++ )
	{
		delete[] m_AnimatedFrameInfoArray[Element].AnimationList[i].SprInfoList;
	}
	delete[] m_AnimatedFrameInfoArray[Element].AnimationList;
	//delete m_AnimatedFrameInfoArray;
}


//===============================================
//	Get 'Is Animation Complete'?
//===============================================
bool AnimationHandler::Get_IsAnimationComplete( unsigned int iAnimationID )
{
	return m_AnimatedFrameInfoArray[iAnimationID].PartiallyCompleted;
}











//===============================================
//	Start Animation
//===============================================
unsigned int AnimationHandler::StartAnimation( unsigned int iWhichAnimation, Vector2 vAnimationLocation )
{
	//////////////////////////////
	if( m_iNextAnimationID > 19 ){ m_iNextAnimationID = 0; }
	//////////////////////////////
	DeleteArrayItem(m_iNextAnimationID);
	m_AnimatedFrameInfoArray[m_iNextAnimationID] = GetAnimationFromXML(iWhichAnimation);
	for( int i = 0; i < m_AnimatedFrameInfoArray[m_iNextAnimationID].TotalFrames; i++ )
	{
		for( int j = 0; j < m_AnimatedFrameInfoArray[m_iNextAnimationID].AnimationList[i].iTotalSprites; j++)
		{
			m_AnimatedFrameInfoArray[m_iNextAnimationID].AnimationList[i].SprInfoList[j].X += (int)vAnimationLocation.X;
			m_AnimatedFrameInfoArray[m_iNextAnimationID].AnimationList[i].SprInfoList[j].Y += (int)vAnimationLocation.Y;
		}
	}
	//////////////////////////////
	m_iNextAnimationID++;

	return ( m_iNextAnimationID - 1 );
}



AnimationHandler::AnimationMaintainanceStruct AnimationHandler::GetAnimationFromXML( unsigned int iWhichAnimation )
{
	if(iWhichAnimation == eFire1) { XMLHandler::GetInstance()->LoadAnimationXMLDocument("Fire1.xml"); }



	
	AnimationMaintainanceStruct AMS;
	AMS.AnimationList	= new AnimatedFrameInfo[XMLHandler::GetInstance()->GetAnimationTotalFrames()];
	AMS.TotalFrames		= XMLHandler::GetInstance()->GetAnimationTotalFrames();

	int iCurrentElement = 0;
	std::list<AnimatedFrameInfo> TempAnimFrame = XMLHandler::GetInstance()->GetAnimationAnimFrameInfoList();
	for( std::list<AnimatedFrameInfo>::iterator iter = TempAnimFrame.begin(); iter != TempAnimFrame.end(); iter++ )
	{
		AnimatedFrameInfo AFI;
		AFI.iTotalSprites				= iter->iTotalSprites;
		AFI.bTintCharacter				= iter->bTintCharacter;
		AFI.bTintScreen					= iter->bTintScreen;
		AFI.fWaitTimeTillNextFrame		= iter->fWaitTimeTillNextFrame;
		AFI.iTintCharacterColour[0]		= iter->iTintCharacterColour[0];
		AFI.iTintCharacterColour[1]		= iter->iTintCharacterColour[1];
		AFI.iTintCharacterColour[2]		= iter->iTintCharacterColour[2];
		AFI.iTintScreenColour[0]		= iter->iTintScreenColour[0];
		AFI.iTintScreenColour[1]		= iter->iTintScreenColour[1];
		AFI.iTintScreenColour[2]		= iter->iTintScreenColour[2];
		AFI.iTintScreenColour[3]		= iter->iTintScreenColour[3];
		AFI.sSoundFilename				= iter->sSoundFilename;
		
		AFI.SprInfoList = new SpriteInfo[AFI.iTotalSprites];
		for( int i = 0; i < AFI.iTotalSprites; i++ )
		{
			SpriteInfo SprInfo;
			SprInfo.TextureID	= iter->SprInfoList[i].TextureID;
			SprInfo.X			= iter->SprInfoList[i].X;
			SprInfo.Y			= iter->SprInfoList[i].Y;
			SprInfo.W			= iter->SprInfoList[i].W;
			SprInfo.H			= iter->SprInfoList[i].H;
			SprInfo.UvStartX	= iter->SprInfoList[i].UvStartX;
			SprInfo.UvStartY	= iter->SprInfoList[i].UvStartY;
			SprInfo.UvEndX		= iter->SprInfoList[i].UvEndX;
			SprInfo.UvEndY		= iter->SprInfoList[i].UvEndY;
			
			AFI.SprInfoList[i] = SprInfo;
		}


		AMS.AnimationList[iCurrentElement] = AFI;
		iCurrentElement++;
	}
	
	//AMS.AnimListIter				= AMS.AnimationList.begin();
	AMS.CurrentTime					= 0.f;
	AMS.CurrentWaitTime				= AMS.AnimationList[0].fWaitTimeTillNextFrame;
	AMS.CurrentFrame				= 0;
	AMS.PartiallyCompletedFrame		= XMLHandler::GetInstance()->GetAnimationPartialAnimationCompleteFrame();
	AMS.RelativeToScreen			= XMLHandler::GetInstance()->Get_IsAnimationRelativeToScreen();
	AMS.PartiallyCompleted			= false;
	AMS.AnimationCompleted			= false;

	XMLHandler::GetInstance()->SetClassVariablesToNil();
	return AMS;
}









//===============================================
//	Update
//===============================================
void AnimationHandler::Update()
{
	// 20 is the size of the Array
	for( int i = 0; i < 20; i++ )
	{
		if(m_AnimatedFrameInfoArray[i].AnimationCompleted) { continue; }

		m_AnimatedFrameInfoArray[i].CurrentTime += DeltaTime::GetInstance()->GetDeltaTime();
		if(m_AnimatedFrameInfoArray[i].CurrentTime >= m_AnimatedFrameInfoArray[i].CurrentWaitTime)
		{
			m_AnimatedFrameInfoArray[i].CurrentFrame++;
			m_AnimatedFrameInfoArray[i].PartiallyCompleted = m_AnimatedFrameInfoArray[i].CurrentFrame >= m_AnimatedFrameInfoArray[i].PartiallyCompletedFrame;

			// If Completed
			if(m_AnimatedFrameInfoArray[i].CurrentFrame == m_AnimatedFrameInfoArray[i].TotalFrames)
			{
				m_AnimatedFrameInfoArray[i].AnimationCompleted = true;
				continue;
			}
			m_AnimatedFrameInfoArray[i].CurrentTime = 0.f;
			

			if(m_AnimatedFrameInfoArray[i].AnimationList[m_AnimatedFrameInfoArray[i].CurrentFrame].sSoundFilename != "")
			{
				AudioManager::GetInstance()->PlaySound(m_AnimatedFrameInfoArray[i].AnimationList[m_AnimatedFrameInfoArray[i].CurrentFrame].sSoundFilename);
			}
		}
	}
}










//===============================================
//	Draw
//===============================================
void AnimationHandler::Draw()
{
	// 20 is the size of the Array
	for( int i = 0; i < 20; i++ )
	{
		if(m_AnimatedFrameInfoArray[i].AnimationCompleted) { continue; }



		if(m_AnimatedFrameInfoArray[i].AnimationList[m_AnimatedFrameInfoArray[i].CurrentFrame].bTintScreen)
		{
			//int X = ScreenResolution::GetInstance()->
			//DrawManager::GetInstance()->DrawQuadi(iter->X, iter->Y, iter->W, iter->H, iter->TextureID, false, 0, UvCoords);
		}

		for( int j = 0; j < m_AnimatedFrameInfoArray[i].AnimationList[m_AnimatedFrameInfoArray[i].CurrentFrame].iTotalSprites; j++ )
		{
			SpriteInfo Sprite = m_AnimatedFrameInfoArray[i].AnimationList[m_AnimatedFrameInfoArray[i].CurrentFrame].SprInfoList[j];
			float* UvCoords = new float[4];
			UvCoords[0] = Sprite.UvStartX; UvCoords[1] = Sprite.UvStartY; UvCoords[2] = Sprite.UvEndX; UvCoords[3] = Sprite.UvEndY; 
			DrawManager::GetInstance()->DrawTexturei(Sprite.X, Sprite.Y, Sprite.W, Sprite.H, Sprite.TextureID, false, 0, UvCoords);
		}
	}
}