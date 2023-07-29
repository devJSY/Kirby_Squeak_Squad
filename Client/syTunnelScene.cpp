#include "syTunnelScene.h"
#include "syInput.h"
#include "sySceneManager.h"
#include "syObject.h"
#include "syDefaultKirby.h"
#include "syTransform.h"
#include "syResourceManager.h"
#include "syApplication.h"
#include "syCamera.h"
#include "syAnimator.h"
#include "syTunnel_BG.h"
#include "syPlayer.h"
#include "syCollisionManager.h"
#include "syLevelSelectScene.h"

namespace sy
{
	TunnelScene::TunnelScene()
		: mBackGround(nullptr)
	{
	}

	TunnelScene::~TunnelScene()
	{
	}

	void TunnelScene::Initialize()
	{
		mBackGround = object::Instantiate<Tunnel_BG>(eLayerType::BackGround);
		Vector2 vec = Vector2(Application::GetResolution()) / 2.f;
		vec.y /= 2.f;
		mBackGround->GetComponent<Transform>()->SetPosition(vec); // 중점 설정

		Scene::Initialize();
	}

	void TunnelScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D) || Input::GetKeyDown(eKeyCode::W))
		{
			// mCurLevel 상태에 따라 진입할 Level 설정
			if (mCurLevelState == eLevelState::Level1)
				SceneManager::LoadScene(L"PrismPlainsScene");
			else if (mCurLevelState == eLevelState::Level2)
				SceneManager::LoadScene(L"NatureNotchScene");
			else if (mCurLevelState == eLevelState::Level3)
				SceneManager::LoadScene(L"CushyCloudScene");
			else if (mCurLevelState == eLevelState::Level4)
				SceneManager::LoadScene(L"JamJungleScene");
			else if (mCurLevelState == eLevelState::Level5)
				SceneManager::LoadScene(L"VocalVolcanoScene");
			else if (mCurLevelState == eLevelState::Level6)
				SceneManager::LoadScene(L"IceIslandScene");
			else if (mCurLevelState == eLevelState::Level7)
				SceneManager::LoadScene(L"SecretSeaScene");
			else if (mCurLevelState == eLevelState::Level8)
				SceneManager::LoadScene(L"GambleGalaxyScene");
		}
	}

	void TunnelScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void TunnelScene::Enter()
	{
		// 플레이어 설정
		Player* player = SceneManager::GetPlayer();
		Transform* playerTrans = player->GetComponent<Transform>();
		playerTrans->SetPosition(Vector2(275.f, 100.f));
		Animator* playerAni = player->GetComponent<Animator>();
		playerAni->SetAffectedCamera(true);
		Collider* playerCol = player->GetComponent<Collider>();
		playerCol->SetAffectedCamera(true);
		player->SetPlayerMode(ePlayerMode::LevelMode);

		// BackGround Animator Set
		LevelSelectScene* levelSelectScene = dynamic_cast<LevelSelectScene*>(SceneManager::GetScene(L"LevelSelectScene"));
		mCurLevelState = levelSelectScene->GetCurLevelState();

		if (mCurLevelState == eLevelState::Level1)
			mBackGround->GetComponent<Animator>()->PlayAnimation(L"Tunnel_1");
		else if (mCurLevelState == eLevelState::Level2)
			mBackGround->GetComponent<Animator>()->PlayAnimation(L"Tunnel_2");
		else if (mCurLevelState == eLevelState::Level3)
			mBackGround->GetComponent<Animator>()->PlayAnimation(L"Tunnel_3");
		else if (mCurLevelState == eLevelState::Level4)
			mBackGround->GetComponent<Animator>()->PlayAnimation(L"Tunnel_4");
		else if (mCurLevelState == eLevelState::Level5)
			mBackGround->GetComponent<Animator>()->PlayAnimation(L"Tunnel_5");
		else if (mCurLevelState == eLevelState::Level6)
			mBackGround->GetComponent<Animator>()->PlayAnimation(L"Tunnel_6");
		else if (mCurLevelState == eLevelState::Level7)
			mBackGround->GetComponent<Animator>()->PlayAnimation(L"Tunnel_7");
		else if (mCurLevelState == eLevelState::Level8)
			mBackGround->GetComponent<Animator>()->PlayAnimation(L"Tunnel_8");

		// 카메라 설정 
		//Camera::SetTarget(nullptr);
		Camera::SetTarget(player);

		// 레이어 충돌 설정
		CollisionManager::CollisionLayerCheck(eLayerType::Enemy, eLayerType::Effect, true);
	}

	void TunnelScene::Exit()
	{
		// 카메라 설정 해제
		Camera::SetTarget(nullptr);
		CollisionManager::Clear();
	}
}