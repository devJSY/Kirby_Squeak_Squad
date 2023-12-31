#include "syLevel1_Stage4Scene.h"
#include "syDefaultKirby.h"
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
#include "syForeGround.h"
#include "syAnimator.h"
#include "syPlayer.h"
#include "syCollider.h"
#include "syCollisionManager.h"
#include "syRigidbody.h"
#include "sySound.h"
#include "syResourceManager.h"
#include "syPortalUI.h"
#include "syPrismPlainsScene.h"
#include "syDanceScene.h"
#include "sySirKibble.h"
#include "syHeavyKnight.h"
#include "syPengy.h"
#include "syHotHead.h"
#include "sySparky.h"

namespace sy
{
	Level1_Stage4Scene::Level1_Stage4Scene()
		: mPixelBG(nullptr)
	{
	}

	Level1_Stage4Scene::~Level1_Stage4Scene()
	{
	}

	void Level1_Stage4Scene::Initialize()
	{
		// 적 생성
		SirKibble* sirKibble1 = object::Instantiate<SirKibble>(eLayerType::Enemy);
		sirKibble1->GetComponent<Transform>()->SetPosition(Vector2(178.f, 122.f));

		SirKibble* sirKibble2 = object::Instantiate<SirKibble>(eLayerType::Enemy);
		sirKibble2->GetComponent<Transform>()->SetPosition(Vector2(42.f, 169.f));

		Sparky* sparky = object::Instantiate<Sparky>(eLayerType::Enemy);
		sparky->GetComponent<Transform>()->SetPosition(Vector2(116.f, 250.f));

		Pengy* pengy = object::Instantiate<Pengy>(eLayerType::Enemy);
		pengy->GetComponent<Transform>()->SetPosition(Vector2(120.f, 280.f));

		HotHead* hotHead = object::Instantiate<HotHead>(eLayerType::Enemy);
		hotHead->GetComponent<Transform>()->SetPosition(Vector2(150.f, 280.f));

		// 백그라운드 설정
		Texture* tex = ResourceManager::Load<Texture>(L"World1_Backgrounds", L"..\\Resources\\Map\\World1_Backgrounds.bmp"); // 이미지 설정

		BackGround* Bg = object::Instantiate<BackGround>(eLayerType::BackGround);
		Vector2 BgPos = Vector2(tex->GetWidth() / 2 - 2, tex->GetHeight() / 2 - 2);
		Bg->GetComponent<Transform>()->SetPosition(BgPos); // 중점 설정

		SpriteRenderer* BgRenderer = Bg->AddComponent<SpriteRenderer>();
		BgRenderer->SetAffectedCamera(false);
		BgRenderer->SetTexture(tex);

		// 스테이지 설정
		tex = ResourceManager::Load<Texture>(L"Stage1", L"..\\Resources\\Map\\Foreground\\Stage1.bmp"); // 이미지 설정
		ForeGround* Fg = object::Instantiate<ForeGround>(eLayerType::ForeGround);
		Vector2 FgPos = Vector2(134.5f, 208.5f);
		Fg->GetComponent<Transform>()->SetPosition(FgPos); // 중점 설정

		SpriteRenderer* FgRenderer = Fg->AddComponent<SpriteRenderer>();
		FgRenderer->SetAffectedCamera(true);
		FgRenderer->SetTexture(tex);
		FgRenderer->SetRenderSize(Vector2(269.f, 417.f));
		FgRenderer->SetRednerLeftTop(Vector2(1604.f, 137.f));

		// 픽셀 이미지 로드
		Texture* Pixeltex = ResourceManager::Load<Texture>(L"Stage1_Pixel"
			, L"..\\Resources\\Map\\Foreground\\Stage1_Pixel.bmp");

		Vector2 PixelPos = Vector2(134.5f, 208.5f);
		mPixelBG = object::Instantiate<BackGround>(eLayerType::Pixel);
		mPixelBG->GetComponent<Transform>()->SetPosition(PixelPos); // 중점 설정

		SpriteRenderer* PixelBgRenderer = mPixelBG->AddComponent<SpriteRenderer>();
		PixelBgRenderer->SetAffectedCamera(true);
		PixelBgRenderer->SetTexture(Pixeltex);
		PixelBgRenderer->SetRenderTrig(false);
		PixelBgRenderer->SetRenderSize(Vector2(269.f, 417.f));
		PixelBgRenderer->SetRednerLeftTop(Vector2(1604.f, 137.f));

		// Portal
		PortalUI* portalUI = object::Instantiate<PortalUI>(eLayerType::Portal);
		portalUI->GetComponent<Transform>()->SetPosition(Vector2(231.f, 121.f));

		// Sound Load
		ResourceManager::Load<Sound>(L"Stage1BGMSound", L"..\\Resources\\Sound\\Theme\\Stage1BGM.wav");

		// 생성한 모든 오브젝트 초기화 
		Scene::Initialize();
	}

	void Level1_Stage4Scene::Update()
	{
		Scene::Update();

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
	}

	void Level1_Stage4Scene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void Level1_Stage4Scene::Enter()
	{
		// 플레이어 설정
		Player* player = SceneManager::GetPlayer();
		Transform* playerTrans = player->GetComponent<Transform>();
		playerTrans->SetPosition(Vector2(21.f, 300.f));

		// 카메라 설정 
		Camera::SetTarget(player);
		Camera::SetCameraLimit(Vector2(269.f, 417.f));

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
		ResourceManager::Find<Sound>(L"Stage1BGMSound")->Play(true);
	}

	void Level1_Stage4Scene::Exit()
	{
		// 오디오 정지
		ResourceManager::AllSoundStop();

		// 카메라 설정 해제
		Camera::SetTarget(nullptr);
		CollisionManager::Clear();

		PrismPlainsScene* scene = dynamic_cast<PrismPlainsScene*>(SceneManager::GetScene(L"PrismPlainsScene"));
		scene->SetClearActiveUI(eStageState::Stage1);	// Stage1 클리어 처리
		scene->SetActiveUI(eStageState::Boss);			// 보스 스테이지 활성화

		DanceScene* danceScene = dynamic_cast<DanceScene*>(SceneManager::GetScene(L"DanceScene"));
		danceScene->SetNextSceneName(L"PrismPlainsScene");
		danceScene->SetType(eDanceSceneType::NormalClear);
	}
}