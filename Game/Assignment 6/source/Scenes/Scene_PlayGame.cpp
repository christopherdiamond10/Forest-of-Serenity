#include "Scene_PlayGame.h"

#include "Level.h"
#include "Player.h"
#include "HUD.h"
#include "CollisionHandler.h"
#include "AudioManager.h"
#include "AnimationHandler.h"


PlayGameState::PlayGameState(SceneManager* p_Game)
{
	m_pSceneManager			= p_Game;
	m_pLevel				= new Level( this );
	m_pCollisionHandler		= new CollisionHandler( m_pLevel );
	m_pPlayer				= new Player();
	m_pHUD					= new HUD( m_pPlayer );
}

PlayGameState::~PlayGameState()
{
	delete m_pLevel;
	delete m_pCollisionHandler;
	delete m_pPlayer;
	delete m_pHUD;
}

void PlayGameState::OnLoad()
{
	m_pCollisionHandler	->OnLoad();
	m_pLevel			->OnLoad();
	m_pPlayer			->OnLoad();
	m_pHUD				->OnLoad();
}

void PlayGameState::OnUnload()
{
	m_pCollisionHandler	->OnUnload();
	m_pLevel			->OnUnload();
	m_pPlayer			->OnUnload();
	m_pHUD				->OnUnload();
}

void PlayGameState::SceneStart()
{
	m_pLevel  ->LoadLevel();
	m_pPlayer ->Reset();
}

void PlayGameState::SceneTerminate()
{

}


void PlayGameState::SetPlayerPosition( Vector2 vPlayerPos )
{
	m_pPlayer->SetPlayerPos( vPlayerPos );
}

void PlayGameState::Update()
{
	if( m_pPlayer->Get_HasCompletedLevel() )
	{
		m_pSceneManager->ChangeState(SceneManager::eTITLEMENU_STATE);
		m_pSceneManager->FixCamera();
		return;
	}

	m_pPlayer			->Update();
	m_pLevel			->Update( m_pPlayer->GetPlayerPos() );
	m_pHUD				->Update( m_pLevel->GetCameraPosition() );
	AnimationHandler::GetInstance()->Update();
}

void PlayGameState::Draw()
{
	m_pLevel			->Draw();
	m_pPlayer			->Draw();
	m_pHUD				->Draw();
	AnimationHandler::GetInstance()->Draw();
}