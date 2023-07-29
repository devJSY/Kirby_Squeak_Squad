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
#include "syTime.h"
namespace sy
{
	TunnelScene::TunnelScene()
		: mBackGround(nullptr)
		, mCurLevelState()
		, mPassedTime(0.f)
		, mPrevSceneName()
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

		mPassedTime += Time::DeltaTime();

		if (mPassedTime > 2.f)
		{
			if (mPrevSceneName == L"LevelSelectScene")
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
			else
			{
				SceneManager::LoadScene(L"LevelSelectScene");
			}
		}
	}

	void TunnelScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void TunnelScene::Enter()
	{
		mPassedTime = 0.f;

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

		// 플레이어 설정
		Player* player = SceneManager::GetPlayer();
		player->SetPlayerMode(ePlayerMode::LevelMode);
		Animator* playerAni = player->GetComponent<Animator>();
		playerAni->SetAffectedCamera(true);
		Collider* playerCol = player->GetComponent<Collider>();
		playerCol->SetAffectedCamera(true);


		Transform* playerTrans = player->GetComponent<Transform>();

		if (mCurLevelState == eLevelState::Level1)
		{
			if (mPrevSceneName == L"LevelSelectScene")
			{
				playerTrans->SetDirection(eDirection::RIGHT);
				playerTrans->SetPosition(Vector2(0.f, 125.f));
			}
			else
			{
				playerTrans->SetDirection(eDirection::LEFT);
				playerTrans->SetPosition(Vector2(256.f, 125.f));
			}

		}
		else if (mCurLevelState == eLevelState::Level2)
		{
			playerTrans->SetDirection(eDirection::RIGHT);

			if (mPrevSceneName == L"LevelSelectScene")
			{				
				playerTrans->SetPosition(Vector2(128.f, 0.f));
			}
			else
			{
				playerTrans->SetPosition(Vector2(128.f, 192.f));
			}
		}
		else if (mCurLevelState == eLevelState::Level3)
		{

		}
		else if (mCurLevelState == eLevelState::Level4)
		{

		}
		else if (mCurLevelState == eLevelState::Level5)
		{

		}
		else if (mCurLevelState == eLevelState::Level6)
		{

		}
		else if (mCurLevelState == eLevelState::Level7)
		{

		}
		else if (mCurLevelState == eLevelState::Level8)
		{

		}



		// 플레이어 타입에따라 상태 설정 
		eAbilityType playerType = player->GetAbilityType();
		DefaultKirby* defaultKirby = dynamic_cast<DefaultKirby*>(player);


		if (playerType == eAbilityType::Normal)
		{
			if (mCurLevelState == eLevelState::Level1)
			{
				defaultKirby->SetKirbyState(eDefaultKirbyState::Run);

				if (playerTrans->GetDirection() == eDirection::RIGHT)
					playerAni->PlayAnimation(L"DefaultKirby_Right_Run", true);
				else
					playerAni->PlayAnimation(L"DefaultKirby_Left_Run", true);
			}
			else if (mCurLevelState == eLevelState::Level2)
			{
				if (mPrevSceneName == L"LevelSelectScene")
				{
					defaultKirby->SetKirbyState(eDefaultKirbyState::Drop);
					playerAni->PlayAnimation(L"DefaultKirby_Right_Drop", true);
				}
				else
				{
					defaultKirby->SetKirbyState(eDefaultKirbyState::Fly_Up);
					playerAni->PlayAnimation(L"DefaultKirby_Right_FlyUp", true);
				}
			}
			else if (mCurLevelState == eLevelState::Level3)
			{

			}
			else if (mCurLevelState == eLevelState::Level4)
			{

			}
			else if (mCurLevelState == eLevelState::Level5)
			{

			}
			else if (mCurLevelState == eLevelState::Level6)
			{

			}
			else if (mCurLevelState == eLevelState::Level7)
			{

			}
			else if (mCurLevelState == eLevelState::Level8)
			{

			}
		}

		// 카메라 설정 
		Camera::SetTarget(nullptr);
		Camera::fadeIn(1.f, RGB(0,0,0));
		Camera::fadeOut(1.f, RGB(255,255,255));
	}

	void TunnelScene::Exit()
	{
		// 카메라 설정 해제
		Camera::SetTarget(nullptr);
		CollisionManager::Clear();

		mPassedTime = 0.f;
	}
}