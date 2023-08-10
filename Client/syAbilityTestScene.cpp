#include "syAbilityTestScene.h"
#include "syPlayer.h"
#include "syCamera.h"
#include "syCollisionManager.h"
#include "sySceneManager.h"
#include "syTransform.h"
#include "syRigidbody.h"
#include "syResourceManager.h"
#include "syAbilityItem.h"
#include "syAnimator.h"
#include "syDefaultKirby.h"
#include "syFireKirby.h"
#include "syIceKirby.h"
#include "syCutterKirby.h"
#include "syTornadoKirby.h"
#include "syNinjaKirby.h"
#include "sySparkKirby.h"
#include "syWheelKirby.h"
#include "sySound.h"
#include "syPortalUI.h"
#include "syBackGround.h"
#include "syObject.h"
#include "sySpriteRenderer.h"
#include "syForeGround.h"
#include "syInput.h"

namespace sy
{
	AbilityTestScene::AbilityTestScene()
	{
	}

	AbilityTestScene::~AbilityTestScene()
	{
	}

	void AbilityTestScene::Initialize()
	{
		// 백그라운드 설정
		Texture* tex = ResourceManager::Load<Texture>(L"World3_Backgrounds", L"..\\Resources\\Map\\Stage\\World3_Backgrounds.png"); // 이미지 설정

		BackGround* Bg = object::Instantiate<BackGround>(eLayerType::BackGround);
		Vector2 BgPos = Vector2(tex->GetWidth() / 2 - 2, tex->GetHeight() / 2 - 2);
		BgPos.y -= 584.f;
		Bg->GetComponent<Transform>()->SetPosition(BgPos); // 중점 설정

		SpriteRenderer* BgRenderer = Bg->AddComponent<SpriteRenderer>();
		BgRenderer->SetAffectedCamera(true);
		BgRenderer->SetTexture(tex);

		// 스테이지 설정
		tex = ResourceManager::Load<Texture>(L"Stage1", L"..\\Resources\\Map\\Foreground\\Stage2.bmp"); // 이미지 설정
		ForeGround* Fg = object::Instantiate<ForeGround>(eLayerType::ForeGround);
		Vector2 FgPos = Vector2(136.f, 104.f);
		Fg->GetComponent<Transform>()->SetPosition(FgPos); // 중점 설정

		SpriteRenderer* FgRenderer = Fg->AddComponent<SpriteRenderer>();
		FgRenderer->SetAffectedCamera(true);
		FgRenderer->SetTexture(tex);
		FgRenderer->SetRenderSize(Vector2(272.f, 208.f));
		FgRenderer->SetRednerLeftTop(Vector2(5.f, 380.f));
		FgRenderer->SetBmpRGB(0, 18, 127);

		// 픽셀 이미지 로드
		Texture* Pixeltex = ResourceManager::Load<Texture>(L"Stage1_Pixel"
			, L"..\\Resources\\Map\\Foreground\\AbilityTest.bmp");

		mPixelBG = object::Instantiate<BackGround>(eLayerType::Pixel);
		mPixelBG->GetComponent<Transform>()->SetPosition(Vector2(Pixeltex->GetWidth() / 2, Pixeltex->GetHeight() / 2)); // 중점 설정

		SpriteRenderer* PixelBgRenderer = mPixelBG->AddComponent<SpriteRenderer>();
		PixelBgRenderer->SetAffectedCamera(true);
		PixelBgRenderer->SetTexture(Pixeltex);
		PixelBgRenderer->SetRenderTrig(false);

		// Portal
		PortalUI* portalUI = object::Instantiate<PortalUI>(eLayerType::Portal);
		portalUI->GetComponent<Transform>()->SetPosition(Vector2(130.f, 120.f));
		// Sound Load
		ResourceManager::Load<Sound>(L"Stage1BGMSound", L"..\\Resources\\Sound\\Theme\\Stage1BGM.wav");

		// 생성한 모든 오브젝트 초기화 
		Scene::Initialize();

		// Sound Load
		ResourceManager::Load<Sound>(L"Stage1BGMSound", L"..\\Resources\\Sound\\Theme\\Stage1BGM.wav");

	}

	void AbilityTestScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::T))
		{
			SpriteRenderer* PixelBgRenderer = mPixelBG->GetComponent<SpriteRenderer>();

			if (PixelBgRenderer->GetRenderTrig())
				PixelBgRenderer->SetRenderTrig(false);
			else
				PixelBgRenderer->SetRenderTrig(true);
		}

		Scene::Update();
	}

	void AbilityTestScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void AbilityTestScene::Enter()
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
		Camera::SetCameraLimit(Vector2(272.f, 208.f));
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
		ResourceManager::Find<Sound>(L"Stage1BGMSound")->Play(true);
	}

	void AbilityTestScene::Exit()
	{
		Camera::Pause(1.f, RGB(255, 255, 255));
		Camera::fadeIn(1.f, RGB(255, 255, 255));
	}
}