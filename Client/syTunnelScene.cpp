#include "syTunnelScene.h"
#include "syInput.h"
#include "sySceneManager.h"
#include "syObject.h"
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
#include "sySound.h"
#include "syResourceManager.h"
#include "syDefaultKirby.h"
#include "syFireKirby.h"
#include "syIceKirby.h"
#include "syCutterKirby.h"
#include "syTornadoKirby.h"
#include "syNinjaKirby.h"
#include "sySparkKirby.h"
#include "syWheelKirby.h"
#include "sySwordKirby.h"

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
		playerAni->SetAffectedCamera(false);
		Collider* playerCol = player->GetComponent<Collider>();
		playerCol->SetAffectedCamera(false);


		Transform* playerTrans = player->GetComponent<Transform>();

		// Tunnel 진입 Kirby위치 설정
		if (mCurLevelState == eLevelState::Level2 || mCurLevelState == eLevelState::Level6)
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
		else if (mCurLevelState == eLevelState::Level1)
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
		else if (mCurLevelState == eLevelState::Level3)
		{
			if (mPrevSceneName == L"LevelSelectScene")
			{
				playerTrans->SetDirection(eDirection::RIGHT);
				playerTrans->SetPosition(Vector2(0.f, 70.f));
			}
			else
			{
				playerTrans->SetDirection(eDirection::LEFT);
				playerTrans->SetPosition(Vector2(256.f, 192.f));
			}
		}
		else if (mCurLevelState == eLevelState::Level5)
		{
			if (mPrevSceneName == L"LevelSelectScene")
			{
				playerTrans->SetDirection(eDirection::LEFT);
				playerTrans->SetPosition(Vector2(256.f, 125.f));
			}
			else
			{
				playerTrans->SetDirection(eDirection::RIGHT);
				playerTrans->SetPosition(Vector2(0.f, 125.f));
			}
		}
		else if (mCurLevelState == eLevelState::Level4 || mCurLevelState == eLevelState::Level7)
		{
			if (mPrevSceneName == L"LevelSelectScene")
			{
				playerTrans->SetDirection(eDirection::LEFT);
				playerTrans->SetPosition(Vector2(256.f, 70.f));
			}
			else
			{
				playerTrans->SetDirection(eDirection::RIGHT);
				playerTrans->SetPosition(Vector2(10.f, 192.f));
			}
		}
		else if (mCurLevelState == eLevelState::Level8)
		{
			if (mPrevSceneName == L"LevelSelectScene")
			{
				playerTrans->SetDirection(eDirection::LEFT);
				playerTrans->SetPosition(Vector2(245.f, 192.f));
			}
			else
			{
				playerTrans->SetDirection(eDirection::RIGHT);
				playerTrans->SetPosition(Vector2(0.f, 70.f));
			}
		}



		// 플레이어 타입에따라 상태 설정 
		eAbilityType playerType = player->GetAbilityType();

		if (playerType == eAbilityType::Normal)
		{
			DefaultKirby* defaultKirby = dynamic_cast<DefaultKirby*>(player->GetActiveKirby());

			if (mCurLevelState == eLevelState::Level2 || mCurLevelState == eLevelState::Level6)
			{
				if (mPrevSceneName == L"LevelSelectScene")
				{
					defaultKirby->SetKirbyState(eDefaultKirbyState::Drop);
					playerAni->PlayAnimation(L"DefaultKirby_Right_Drop", true);
				}
				else
				{
					// 오디오 재생
					ResourceManager::Find<Sound>(L"FlySound")->Play(true);

					defaultKirby->SetKirbyState(eDefaultKirbyState::Fly_Up);
					playerAni->PlayAnimation(L"DefaultKirby_Right_FlyUp", true);
				}
			}
			else
			{
				// 오디오 재생
				ResourceManager::Find<Sound>(L"RunSound")->Play(false);

				defaultKirby->SetKirbyState(eDefaultKirbyState::Run);

				if (playerTrans->GetDirection() == eDirection::RIGHT)
					playerAni->PlayAnimation(L"DefaultKirby_Right_Run", true);
				else
					playerAni->PlayAnimation(L"DefaultKirby_Left_Run", true);
			}
		}
		else if (playerType == eAbilityType::Fire)
		{
			FireKirby* fireKirby = dynamic_cast<FireKirby*>(player->GetActiveKirby());

			if (mCurLevelState == eLevelState::Level2 || mCurLevelState == eLevelState::Level6)
			{
				if (mPrevSceneName == L"LevelSelectScene")
				{
					fireKirby->SetKirbyState(eFireKirbyState::Drop);
					playerAni->PlayAnimation(L"FireKirby_Right_Drop", true);
				}
				else
				{
					// 오디오 재생
					ResourceManager::Find<Sound>(L"FlySound")->Play(true);

					fireKirby->SetKirbyState(eFireKirbyState::Fly_Up);
					playerAni->PlayAnimation(L"FireKirby_Right_FlyUp", true);
				}
			}
			else
			{
				// 오디오 재생
				ResourceManager::Find<Sound>(L"RunSound")->Play(false);

				fireKirby->SetKirbyState(eFireKirbyState::Run);

				if (playerTrans->GetDirection() == eDirection::RIGHT)
					playerAni->PlayAnimation(L"FireKirby_Right_Run", true);
				else
					playerAni->PlayAnimation(L"FireKirby_Left_Run", true);
			}
		}
		else if (playerType == eAbilityType::Ice)
		{
			IceKirby* iceKirby = dynamic_cast<IceKirby*>(player->GetActiveKirby());

			if (mCurLevelState == eLevelState::Level2 || mCurLevelState == eLevelState::Level6)
			{
				if (mPrevSceneName == L"LevelSelectScene")
				{
					iceKirby->SetKirbyState(eIceKirbyState::Drop);
					playerAni->PlayAnimation(L"IceKirby_Right_Drop", true);
				}
				else
				{
					// 오디오 재생
					ResourceManager::Find<Sound>(L"FlySound")->Play(true);

					iceKirby->SetKirbyState(eIceKirbyState::Fly_Up);
					playerAni->PlayAnimation(L"IceKirby_Right_FlyUp", true);
				}
			}
			else
			{
				// 오디오 재생
				ResourceManager::Find<Sound>(L"RunSound")->Play(false);

				iceKirby->SetKirbyState(eIceKirbyState::Run);

				if (playerTrans->GetDirection() == eDirection::RIGHT)
					playerAni->PlayAnimation(L"IceKirby_Right_Run", true);
				else
					playerAni->PlayAnimation(L"IceKirby_Left_Run", true);
			}
		}
		else if (playerType == eAbilityType::Cutter)
		{
			CutterKirby* cutterKirby = dynamic_cast<CutterKirby*>(player->GetActiveKirby());

			if (mCurLevelState == eLevelState::Level2 || mCurLevelState == eLevelState::Level6)
			{
				if (mPrevSceneName == L"LevelSelectScene")
				{
					cutterKirby->SetKirbyState(eCutterKirbyState::Drop);
					playerAni->PlayAnimation(L"CutterKirby_Right_Drop", true);
				}
				else
				{
					// 오디오 재생
					ResourceManager::Find<Sound>(L"FlySound")->Play(true);

					cutterKirby->SetKirbyState(eCutterKirbyState::Fly_Up);
					playerAni->PlayAnimation(L"CutterKirby_Right_FlyUp", true);
				}
			}
			else
			{
				// 오디오 재생
				ResourceManager::Find<Sound>(L"RunSound")->Play(false);

				cutterKirby->SetKirbyState(eCutterKirbyState::Run);

				if (playerTrans->GetDirection() == eDirection::RIGHT)
					playerAni->PlayAnimation(L"CutterKirby_Right_Run", true);
				else
					playerAni->PlayAnimation(L"CutterKirby_Left_Run", true);
			}
		}
		else if (playerType == eAbilityType::Tornado)
		{
			TornadoKirby* tornadoKirby = dynamic_cast<TornadoKirby*>(player->GetActiveKirby());

			if (mCurLevelState == eLevelState::Level2 || mCurLevelState == eLevelState::Level6)
			{
				if (mPrevSceneName == L"LevelSelectScene")
				{
					tornadoKirby->SetKirbyState(eTornadoKirbyState::Drop);
					playerAni->PlayAnimation(L"TornadoKirby_Right_Drop", true);
				}
				else
				{
					// 오디오 재생
					ResourceManager::Find<Sound>(L"FlySound")->Play(true);

					tornadoKirby->SetKirbyState(eTornadoKirbyState::Fly_Up);
					playerAni->PlayAnimation(L"TornadoKirby_Right_FlyUp", true);
				}
			}
			else
			{
				// 오디오 재생
				ResourceManager::Find<Sound>(L"RunSound")->Play(false);

				tornadoKirby->SetKirbyState(eTornadoKirbyState::Run);

				if (playerTrans->GetDirection() == eDirection::RIGHT)
					playerAni->PlayAnimation(L"TornadoKirby_Right_Run", true);
				else
					playerAni->PlayAnimation(L"TornadoKirby_Left_Run", true);
			}
		}
		else if (playerType == eAbilityType::Ninja)
		{
			NinjaKirby* ninjaKirby = dynamic_cast<NinjaKirby*>(player->GetActiveKirby());

			if (mCurLevelState == eLevelState::Level2 || mCurLevelState == eLevelState::Level6)
			{
				if (mPrevSceneName == L"LevelSelectScene")
				{
					ninjaKirby->SetKirbyState(eNinjaKirbyState::Drop);
					playerAni->PlayAnimation(L"NinjaKirby_Right_Drop", true);
				}
				else
				{
					// 오디오 재생
					ResourceManager::Find<Sound>(L"FlySound")->Play(true);

					ninjaKirby->SetKirbyState(eNinjaKirbyState::Fly_Up);
					playerAni->PlayAnimation(L"NinjaKirby_Right_FlyUp", true);
				}
			}
			else
			{
				// 오디오 재생
				ResourceManager::Find<Sound>(L"RunSound")->Play(false);

				ninjaKirby->SetKirbyState(eNinjaKirbyState::Run);

				if (playerTrans->GetDirection() == eDirection::RIGHT)
					playerAni->PlayAnimation(L"NinjaKirby_Right_Run", true);
				else
					playerAni->PlayAnimation(L"NinjaKirby_Left_Run", true);
			}
		}
		else if (playerType == eAbilityType::Spark)
		{
			SparkKirby* sparkKirby = dynamic_cast<SparkKirby*>(player->GetActiveKirby());

			if (mCurLevelState == eLevelState::Level2 || mCurLevelState == eLevelState::Level6)
			{
				if (mPrevSceneName == L"LevelSelectScene")
				{
					sparkKirby->SetKirbyState(eSparkKirbyState::Drop);
					playerAni->PlayAnimation(L"SparkKirby_Right_Drop", true);
				}
				else
				{
					// 오디오 재생
					ResourceManager::Find<Sound>(L"FlySound")->Play(true);

					sparkKirby->SetKirbyState(eSparkKirbyState::Fly_Up);
					playerAni->PlayAnimation(L"SparkKirby_Right_FlyUp", true);
				}
			}
			else
			{
				// 오디오 재생
				ResourceManager::Find<Sound>(L"RunSound")->Play(false);

				sparkKirby->SetKirbyState(eSparkKirbyState::Run);

				if (playerTrans->GetDirection() == eDirection::RIGHT)
					playerAni->PlayAnimation(L"SparkKirby_Right_Run", true);
				else
					playerAni->PlayAnimation(L"SparkKirby_Left_Run", true);
			}
		}
		//else if (playerType == eAbilityType::Wheel)
		//{
		//	WheelKirby* wheelKirby = dynamic_cast<WheelKirby*>(player->GetActiveKirby());

		//	if (mCurLevelState == eLevelState::Level2 || mCurLevelState == eLevelState::Level6)
		//	{
		//		if (mPrevSceneName == L"LevelSelectScene")
		//		{
		//			wheelKirby->SetKirbyState(eWheelKirbyState::Drop);
		//			playerAni->PlayAnimation(L"WheelKirby_Right_Drop", true);
		//		}
		//		else
		//		{
		// 			// 오디오 재생
					//ResourceManager::Find<Sound>(L"FlySound")->Play(true);

		//			wheelKirby->SetKirbyState(eWheelKirbyState::Fly_Up);
		//			playerAni->PlayAnimation(L"WheelKirby_Right_FlyUp", true);
		//		}
		//	}
		//	else
		//	{
		//		// 오디오 재생
		//		ResourceManager::Find<Sound>(L"RunSound")->Play(false);

		//		wheelKirby->SetKirbyState(eWheelKirbyState::Run);

		//		if (playerTrans->GetDirection() == eDirection::RIGHT)
		//			playerAni->PlayAnimation(L"WheelKirby_Right_Run", true);
		//		else
		//			playerAni->PlayAnimation(L"WheelKirby_Left_Run", true);
		//	}
		//}
		else if (playerType == eAbilityType::Sword)
		{
			SwordKirby* swordKirby = dynamic_cast<SwordKirby*>(player->GetActiveKirby());

			if (mCurLevelState == eLevelState::Level2 || mCurLevelState == eLevelState::Level6)
			{
				if (mPrevSceneName == L"LevelSelectScene")
				{
					swordKirby->SetKirbyState(eSwordKirbyState::Drop);
					playerAni->PlayAnimation(L"SwordKirby_Right_Drop", true);
				}
				else
				{
					// 오디오 재생
					ResourceManager::Find<Sound>(L"FlySound")->Play(true);

					swordKirby->SetKirbyState(eSwordKirbyState::Fly_Up);
					playerAni->PlayAnimation(L"SwordKirby_Right_FlyUp", true);
				}
			}
			else
			{
				// 오디오 재생
				ResourceManager::Find<Sound>(L"RunSound")->Play(false);

				swordKirby->SetKirbyState(eSwordKirbyState::Run);

				if (playerTrans->GetDirection() == eDirection::RIGHT)
					playerAni->PlayAnimation(L"SwordKirby_Right_Run", true);
				else
					playerAni->PlayAnimation(L"SwordKirby_Left_Run", true);
			}
		}

		// 카메라 설정 
		Camera::SetTarget(nullptr);
		Camera::fadeIn(1.f, RGB(0,0,0));
		Camera::fadeOut(1.f, RGB(255,255,255));
	}

	void TunnelScene::Exit()
	{
		// 오디오 정지
		ResourceManager::AllSoundStop();

		// 카메라 설정 해제
		Camera::SetTarget(nullptr);
		CollisionManager::Clear();

		mPassedTime = 0.f;
	}
}