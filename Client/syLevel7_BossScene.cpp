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
#include "sySecretSeaScene.h"
#include "syDaroach.h"
#include "syDanceScene.h"
#include "syForeGround.h"

namespace sy
{
	Level7_BossScene::Level7_BossScene()
		: mBackGround(nullptr)
		, mPixelBG(nullptr)
		, mPortalUI(nullptr)
	{
	}

	Level7_BossScene::~Level7_BossScene()
	{
	}

	void Level7_BossScene::Initialize()
	{
		// 보스 생성


		// 백그라운드 설정
		Texture* tex = ResourceManager::Load<Texture>(L"Meta_Knight_Stage", L"..\\Resources\\Map\\Stage\\Meta_Knight_Stage.bmp"); // 이미지 설정

		BackGround* Bg = object::Instantiate<BackGround>(eLayerType::BackGround);
		Bg->GetComponent<Transform>()->SetPosition(Vector2(128.f, 96.f));
		Animator* animator = Bg->AddComponent<Animator>();
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
		FgRenderer->SetRenderSize(Vector2(256.f, 191.f));
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

		//// Sound Load
		//ResourceManager::Load<Sound>(L"Level7BossSound", L"..\\Resources\\Sound\\Theme\\Level7Boss.wav");

		// 생성한 모든 오브젝트 초기화 
		Scene::Initialize();
	}

	void Level7_BossScene::Update()
	{
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

		//if (mDaroach->GetDaroachState() == eDaroachState::Dead)
		//{
		//	// Portal
		//	if (mPortalUI == nullptr)
		//	{
		//		mPortalUI = object::Instantiate<PortalUI>(eLayerType::Portal);
		//		mPortalUI->GetComponent<Transform>()->SetPosition(Vector2(128.f, 150.f));
		//		mPortalUI->Initialize();

		//		// 오디오 재생
		//		ResourceManager::Find<Sound>(L"Level7BossSound")->Stop(true);
		//	}
		//}

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

		// 오디오 정지
		ResourceManager::Find<Sound>(L"StageSelectSound")->Stop(true);
		//// 오디오 재생
		//ResourceManager::Find<Sound>(L"Level7BossSound")->Play(true);
	}

	void Level7_BossScene::Exit()
	{
		// 카메라 설정 해제
		Camera::SetTarget(nullptr);
		CollisionManager::Clear();

		//// 오디오 정지
		//ResourceManager::Find<Sound>(L"Level7BossSound")->Stop(true);

		SecretSeaScene* scene = dynamic_cast<SecretSeaScene*>(SceneManager::GetScene(L"SecretSeaScene"));
		scene->SetClearActiveUI(eStageState::Boss);	 // 보스 스테이지 클리어 처리

		DanceScene* danceScene = dynamic_cast<DanceScene*>(SceneManager::GetScene(L"DanceScene"));
		danceScene->SetNextSceneName(L"SecretSeaScene");
		danceScene->SetType(eDanceSceneType::BossClear);
	}
}