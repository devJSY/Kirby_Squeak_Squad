#include "syLevel1_BossScene.h"
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
#include "syPrismPlainsScene.h"
#include "syKingDedede.h"

namespace sy
{
	Level1_BossScene::Level1_BossScene()
		: mPixelBG(nullptr)
	{
	}

	Level1_BossScene::~Level1_BossScene()
	{
	}

	void Level1_BossScene::Initialize()
	{
		// 보스 생성
		KingDedede* kingDedede = new KingDedede(eAbilityType::Normal);
		object::ActiveSceneAddGameObject(eLayerType::Enemy, kingDedede);
		kingDedede->GetComponent<Transform>()->SetPosition(Vector2(210.f, 100.f));


		// 백그라운드 설정
		Texture* tex = ResourceManager::Load<Texture>(L"King_Dedede_Stage", L"..\\Resources\\Map\\Stage\\King_Dedede_Stage.png"); // 이미지 설정

		BackGround* Bg = object::Instantiate<BackGround>(eLayerType::BackGround);
		Bg->GetComponent<Transform>()->SetPosition(Vector2(128.f, 96.f));
		Animator* animator = Bg->AddComponent<Animator>();
		animator->SetAffectedCamera(true);
		animator->CreateAnimation(tex, L"King_Dedede_Stage", Vector2(8.f, 108.f), Vector2(256.f, 192.f), Vector2(261.f, 0.f), 0.05f, 4);
		animator->SetBmpRGB(L"King_Dedede_Stage", 0, 0, 100);
		animator->PlayAnimation(L"King_Dedede_Stage", true);

		// 픽셀 이미지 로드
		Texture* Pixeltex = ResourceManager::Load<Texture>(L"King_Dedede_Stage_Pixel"
			, L"..\\Resources\\Map\\Foreground\\King_Dedede_Stage_Pixel.bmp");

		mPixelBG = object::Instantiate<BackGround>(eLayerType::Pixel);
		mPixelBG->GetComponent<Transform>()->SetPosition(Vector2(128.f, 96.f)); // 중점 설정

		SpriteRenderer* PixelBgRenderer = mPixelBG->AddComponent<SpriteRenderer>();
		PixelBgRenderer->SetAffectedCamera(true);
		PixelBgRenderer->SetTexture(Pixeltex);
		PixelBgRenderer->SetRenderTrig(false);

		// Sound Load
		ResourceManager::Load<Sound>(L"BossSound", L"..\\Resources\\Sound\\Theme\\Boss.wav");
		ResourceManager::Load<Sound>(L"BossClearSound", L"..\\Resources\\Sound\\Theme\\BossClear.wav");

		// 생성한 모든 오브젝트 초기화 
		Scene::Initialize();
	}

	void Level1_BossScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::MOUSE_RBTN))
		{
			SceneManager::LoadScene(L"PrismPlainsScene");
		}

		if (Input::GetKeyDown(eKeyCode::T))
		{
			SpriteRenderer* PixelBgRenderer = mPixelBG->GetComponent<SpriteRenderer>();

			if (PixelBgRenderer->GetRenderTrig())
				PixelBgRenderer->SetRenderTrig(false);
			else
				PixelBgRenderer->SetRenderTrig(true);
		}

		//if (보스잡은경우)
		//{
		//	// Portal
		//	PortalUI* portalUI = object::Instantiate<PortalUI>(eLayerType::Portal);
		//	portalUI->GetComponent<Transform>()->SetPosition(Vector2(128.f, 135.f));
		//	portalUI->Initialize();
		//}
	}

	void Level1_BossScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void Level1_BossScene::Enter()
	{
		// 플레이어 설정
		Player* player = SceneManager::GetPlayer();
		Transform* playerTrans = player->GetComponent<Transform>();
		playerTrans->SetPosition(Vector2(30.f, 100.f));
		Animator* playerAni = player->GetComponent<Animator>();
		playerAni->SetAffectedCamera(true);
		Collider* playerCol = player->GetComponent<Collider>();
		playerCol->SetAffectedCamera(true);
		//playerCol->SetSize(Vector2(50.f, 50.f));
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

		// 오디오 정지
		ResourceManager::Find<Sound>(L"StageSelectSound")->Stop(true);
		// 오디오 재생
		ResourceManager::Find<Sound>(L"BossSound")->Play(true);
	}

	void Level1_BossScene::Exit()
	{
		// 카메라 설정 해제
		Camera::SetTarget(nullptr);
		CollisionManager::Clear();

		// 오디오 재생
		ResourceManager::Find<Sound>(L"BossSound")->Stop(true);
		// 오디오 재생
		ResourceManager::Find<Sound>(L"BossClearSound")->Play(false);

		PrismPlainsScene* scene = dynamic_cast<PrismPlainsScene*>(SceneManager::GetScene(L"PrismPlainsScene"));
		scene->SetClearActiveUI(eStageState::Boss);	 // 보스 스테이지 클리어 처리
	}
}