#include "syLevel7_BossScene.h"
#include "syObject.h"
#include "syGameObject.h"
#include "sySpriteRenderer.h"
#include "syInput.h"
#include "sySceneManager.h"
#include "syTransform.h"
#include "syResourceManager.h"
#include "syTexture.h"
#include "syBackGround.h"
#include "syApplication.h"
#include "syCamera.h"
#include "syAnimator.h"
#include "syPlayer.h"
#include "syCollider.h"
#include "syCollisionManager.h"
#include "syRigidbody.h"
#include "sySound.h"
#include "syResourceManager.h"
#include "syPortalUI.h"
#include "syAbilityItem.h"
#include "syMixItem.h"
#include "syInventory.h"
#include "syDefaultKirby.h"
#include "syFireKirby.h"
#include "syIceKirby.h"
#include "syCutterKirby.h"
#include "syTornadoKirby.h"
#include "syNinjaKirby.h"
#include "sySparkKirby.h"
#include "syWheelKirby.h"
#include "sySwordKirby.h"
#include "sySecretSeaScene.h"
#include "syDaroach.h"
#include "syDanceScene.h"
#include "syForeGround.h"
#include "syTime.h"
#include "syMetaKnight.h"
#include "sySwordItem.h"

namespace sy
{
	Level7_BossScene::Level7_BossScene()
		: mMetaKnight(nullptr)
		, mBackGround(nullptr)
		, mPixelBG(nullptr)
		, mPortalUI(nullptr)
		, mBgSpeed(300.f)
		, mDuration(0.f)
		, mbBGChange(false)
	{
	}

	Level7_BossScene::~Level7_BossScene()
	{
	}

	void Level7_BossScene::Initialize()
	{
		// 보스 생성
		mMetaKnight = new MetaKnight(eAbilityType::Normal);
		object::ActiveSceneAddGameObject(eLayerType::Enemy, mMetaKnight);
		mMetaKnight->GetComponent<Transform>()->SetPosition(Vector2(222.f, 55.f));

		SwordItem* swordItem = new SwordItem(mMetaKnight);
		object::ActiveSceneAddGameObject(eLayerType::Enemy, swordItem);
		swordItem->GetComponent<Transform>()->SetPosition(Vector2(128.f, 97.f));

		// 백그라운드 설정
		Texture* tex = ResourceManager::Load<Texture>(L"Meta_Knight_Stage", L"..\\Resources\\Map\\Stage\\Meta_Knight_Stage.bmp"); // 이미지 설정

		mBackGround = object::Instantiate<BackGround>(eLayerType::BackGround);
		mBackGround->GetComponent<Transform>()->SetPosition(Vector2(128.f, -28.f));
		Animator* animator = mBackGround->AddComponent<Animator>();
		animator->SetAffectedCamera(true);
		animator->CreateAnimation(tex, L"Meta_Knight_Stage_Normal", Vector2(284.f, 105.f), Vector2(256.f, 384.f), Vector2(256.f, 0.f), 1.f, 1);
		animator->CreateAnimation(tex, L"Meta_Knight_Stage_Final", Vector2(280.f, 519.f), Vector2(256.f, 218.f), Vector2(280.f, 0.f), 1.f, 1);
		animator->PlayAnimation(L"Meta_Knight_Stage_Normal", true);

		// 스테이지 설정
		ForeGround* Fg = object::Instantiate<ForeGround>(eLayerType::ForeGround);
		Fg->GetComponent<Transform>()->SetPosition(Vector2(128.f, 96.f));

		SpriteRenderer* FgRenderer = Fg->AddComponent<SpriteRenderer>();
		FgRenderer->SetAffectedCamera(true);
		FgRenderer->SetTexture(tex);
		FgRenderer->SetRenderSize(Vector2(256.f, 192.f));
		FgRenderer->SetRednerLeftTop(Vector2(15.f, 109.f));
		FgRenderer->SetBmpRGB(0, 0, 100);

		// 픽셀 이미지 로드
		Texture* Pixeltex = ResourceManager::Load<Texture>(L"Meta_Knight_Pixel"
			, L"..\\Resources\\Map\\Foreground\\Meta_Knight_Stage_Pixel.bmp");

		mPixelBG = object::Instantiate<BackGround>(eLayerType::Pixel);
		mPixelBG->GetComponent<Transform>()->SetPosition(Vector2(128.f, 96.f)); // 중점 설정

		SpriteRenderer* PixelBgRenderer = mPixelBG->AddComponent<SpriteRenderer>();
		PixelBgRenderer->SetAffectedCamera(true);
		PixelBgRenderer->SetTexture(Pixeltex);
		PixelBgRenderer->SetRenderTrig(false);

		// Sound Load
		ResourceManager::Load<Sound>(L"Level7BossSound", L"..\\Resources\\Sound\\Theme\\Level7Boss.wav");

		// 생성한 모든 오브젝트 초기화 
		Scene::Initialize();
	}

	void Level7_BossScene::Update()
	{
		mDuration += Time::DeltaTime();

		if (mDuration > 40.f && mbBGChange == false)
		{
			mbBGChange = true;
			mBackGround->GetComponent<Animator>()->PlayAnimation(L"Meta_Knight_Stage_Final");
			mBgSpeed = 50.f;
			Vector2 pos = mBackGround->GetComponent<Transform>()->GetPosition();
			pos.y = 30.f;			
			mBackGround->GetComponent<Transform>()->SetPosition(pos);
		}

		if (mbBGChange)
		{
			mBgSpeed -= Time::DeltaTime() * 10.f;
			if (mBgSpeed < 0.f)
			{
				mBgSpeed = 0.f;
			}
			Vector2 pos = mBackGround->GetComponent<Transform>()->GetPosition();
			pos.y += Time::DeltaTime() * mBgSpeed;
			if (pos.y > 117.f)
			{
				pos.y = 117.f;
			}
			mBackGround->GetComponent<Transform>()->SetPosition(pos);
		}
		else
		{
			mBgSpeed += Time::DeltaTime() * 10.f;

			if (mBgSpeed > 600.f)
			{
				mBgSpeed = 600.f;
			}

			Vector2 pos = mBackGround->GetComponent<Transform>()->GetPosition();
			pos.y += Time::DeltaTime() * mBgSpeed;
			if (pos.y > 192.f)
			{
				pos.y = -28.f;
			}
			mBackGround->GetComponent<Transform>()->SetPosition(pos);
		}


		if (Input::GetKeyDown(eKeyCode::MOUSE_MBTN))
		{
			SceneManager::LoadScene(L"DanceScene");
		}

		if (Input::GetKeyDown(eKeyCode::T))
		{
			SpriteRenderer* PixelBgRenderer = mPixelBG->GetComponent<SpriteRenderer>();

			if (PixelBgRenderer->GetRenderTrig())
				PixelBgRenderer->SetRenderTrig(false);
			else
				PixelBgRenderer->SetRenderTrig(true);
		}

		if (mMetaKnight->GeteMetaKnightState() == eMetaKnightState::Dead3)
		{
			// Portal
			if (mPortalUI == nullptr)
			{
				mPortalUI = object::Instantiate<PortalUI>(eLayerType::Portal);
				mPortalUI->GetComponent<Transform>()->SetPosition(Vector2(128.f, 133.f));
				mPortalUI->Initialize();

				// 오디오 재생
				ResourceManager::Find<Sound>(L"Level7BossSound")->Stop(true);
			}
		}

		Scene::Update();
	}

	void Level7_BossScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void Level7_BossScene::Enter()
	{
		// 플레이어 설정
		Player* player = SceneManager::GetPlayer();
		Transform* playerTrans = player->GetComponent<Transform>();
		playerTrans->SetPosition(Vector2(30.f, 100.f));
		Animator* playerAni = player->GetComponent<Animator>();
		playerAni->SetAffectedCamera(true);
		Collider* playerCol = player->GetComponent<Collider>();
		playerCol->SetAffectedCamera(true);
		player->SetPlayerMode(ePlayerMode::PlayMode);
		playerTrans->SetDirection(eDirection::RIGHT);

		// 플레이어 타입에따라 상태 설정 
		eAbilityType playerType = player->GetAbilityType();
		if (playerType == eAbilityType::Normal)
		{
			DefaultKirby* defaultKirby = dynamic_cast<DefaultKirby*>(player->GetActiveKirby());
			defaultKirby->SetKirbyState(eDefaultKirbyState::Turn);
			playerAni->PlayAnimation(L"DefaultKirby_Right_Turn", false);
		}
		else if (playerType == eAbilityType::Fire)
		{
			FireKirby* fireKirby = dynamic_cast<FireKirby*>(player->GetActiveKirby());
			fireKirby->SetKirbyState(eFireKirbyState::Turn);
			playerAni->PlayAnimation(L"FireKirby_Right_Turn", false);
		}
		else if (playerType == eAbilityType::Ice)
		{
			IceKirby* iceKirby = dynamic_cast<IceKirby*>(player->GetActiveKirby());
			iceKirby->SetKirbyState(eIceKirbyState::Turn);
			playerAni->PlayAnimation(L"IceKirby_Right_Turn", false);
		}
		else if (playerType == eAbilityType::Cutter)
		{
			CutterKirby* cutterKirby = dynamic_cast<CutterKirby*>(player->GetActiveKirby());
			cutterKirby->SetKirbyState(eCutterKirbyState::Turn);
			playerAni->PlayAnimation(L"CutterKirby_Right_Turn", false);
		}
		else if (playerType == eAbilityType::Tornado)
		{
			TornadoKirby* tornadoKirby = dynamic_cast<TornadoKirby*>(player->GetActiveKirby());
			tornadoKirby->SetKirbyState(eTornadoKirbyState::Turn);
			playerAni->PlayAnimation(L"TornadoKirby_Right_Turn", false);
		}
		else if (playerType == eAbilityType::Ninja)
		{
			NinjaKirby* ninjaKirby = dynamic_cast<NinjaKirby*>(player->GetActiveKirby());
			ninjaKirby->SetKirbyState(eNinjaKirbyState::Turn);
			playerAni->PlayAnimation(L"NinjaKirby_Right_Turn", false);
		}
		else if (playerType == eAbilityType::Spark)
		{
			SparkKirby* sparkKirby = dynamic_cast<SparkKirby*>(player->GetActiveKirby());
			sparkKirby->SetKirbyState(eSparkKirbyState::Turn);
			playerAni->PlayAnimation(L"SparkKirby_Right_Turn", false);
		}
		//else if (playerType == eAbilityType::Wheel)
		//{
		//	WheelKirby* wheelKirby = dynamic_cast<WheelKirby*>(player->GetActiveKirby());
		//	wheelKirby->SetKirbyState(eWheelKirbyState::Turn);
		//	playerAni->PlayAnimation(L"WheelKirby_Right_Turn", false);
		//}
		else if (playerType == eAbilityType::Sword)
		{
			SwordKirby* swordKirby = dynamic_cast<SwordKirby*>(player->GetActiveKirby());
			swordKirby->SetKirbyState(eSwordKirbyState::Turn);
			playerAni->PlayAnimation(L"SwordKirby_Right_Turn", false);
		}

		player->GetComponent<Rigidbody>()->SetGround(false);

		// 카메라 설정 
		Camera::SetTarget(player);
		Camera::SetCameraLimit(Vector2(256.f, 192.f));
		Camera::Pause(1.f, RGB(255, 255, 255));
		Camera::fadeIn(1.f, RGB(255, 255, 255));

		// 레이어 충돌 설정
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Enemy, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Effect, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Portal, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::AbilityItem, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Enemy, eLayerType::Effect, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Enemy, eLayerType::Enemy, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Effect, eLayerType::AbilityItem, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Effect, eLayerType::Effect, true);

		// 오디오 재생
		ResourceManager::Find<Sound>(L"Level7BossSound")->Play(true);
	}

	void Level7_BossScene::Exit()
	{
		// 오디오 정지
		ResourceManager::AllSoundStop();

		// 카메라 설정 해제
		Camera::SetTarget(nullptr);
		CollisionManager::Clear();

		SecretSeaScene* scene = dynamic_cast<SecretSeaScene*>(SceneManager::GetScene(L"SecretSeaScene"));
		scene->SetClearActiveUI(eStageState::Boss);	 // 보스 스테이지 클리어 처리

		DanceScene* danceScene = dynamic_cast<DanceScene*>(SceneManager::GetScene(L"DanceScene"));
		danceScene->SetNextSceneName(L"SecretSeaScene");
		danceScene->SetType(eDanceSceneType::Level7_BossClear);
	}
}