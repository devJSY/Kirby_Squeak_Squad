#include "syLevel1_Stage3Scene.h"
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

#include "syWaddleDee.h"
#include "syBlockin.h"
#include "syHotHead.h"
#include "syHotHead_Fire.h"
#include "syHeavyKnight.h"
#include "syTwister.h"
#include "syPengy.h"
#include "syBioSpark.h"

namespace sy
{
	Level1_Stage3Scene::Level1_Stage3Scene()
		: mPixelBG(nullptr)
	{
	}

	Level1_Stage3Scene::~Level1_Stage3Scene()
	{
	}

	void Level1_Stage3Scene::Initialize()
	{
		// 적 생성
		Blockin* blockin = object::Instantiate<Blockin>(eLayerType::Enemy);
		blockin->GetComponent<Transform>()->SetPosition(Vector2(154.f, 141.f));

		WaddleDee* waddleDee = object::Instantiate<WaddleDee>(eLayerType::Enemy);
		waddleDee->GetComponent<Transform>()->SetPosition(Vector2(174.f, 47.f));

		WaddleDee* waddleDee2 = object::Instantiate<WaddleDee>(eLayerType::Enemy);
		waddleDee2->GetComponent<Transform>()->SetPosition(Vector2(1025.f, 46.f));

		HotHead* hotHead = object::Instantiate<HotHead>(eLayerType::Enemy);
		hotHead->GetComponent<Transform>()->SetPosition(Vector2(800.f, 92.f));

		Pengy* pengy = object::Instantiate<Pengy>(eLayerType::Enemy);
		pengy->GetComponent<Transform>()->SetPosition(Vector2(410.f, 120.f));

		HeavyKnight* heavyKnight = object::Instantiate<HeavyKnight>(eLayerType::Enemy);
		heavyKnight->GetComponent<Transform>()->SetPosition(Vector2(620.f, 90.f));

		HeavyKnight* heavyKnight2 = object::Instantiate<HeavyKnight>(eLayerType::Enemy);
		heavyKnight2->GetComponent<Transform>()->SetPosition(Vector2(800.f, 90.f));

		Twister* twister = object::Instantiate<Twister>(eLayerType::Enemy);
		twister->GetComponent<Transform>()->SetPosition(Vector2(1400.f, 80.f));

		Twister* twister2 = object::Instantiate<Twister>(eLayerType::Enemy);
		twister2->GetComponent<Transform>()->SetPosition(Vector2(1200.f, 79.f));

		Twister* twister3 = object::Instantiate<Twister>(eLayerType::Enemy);
		twister3->GetComponent<Transform>()->SetPosition(Vector2(990.f, 60.f));

		BioSpark* bioSpark1 = object::Instantiate<BioSpark>(eLayerType::Enemy);
		bioSpark1->GetComponent<Transform>()->SetPosition(Vector2(170.f, 60.f));

		BioSpark* bioSpark2 = object::Instantiate<BioSpark>(eLayerType::Enemy);
		bioSpark2->GetComponent<Transform>()->SetPosition(Vector2(1050.f, 60.f));

		// 백그라운드 설정
		Texture* tex = ResourceManager::Load<Texture>(L"World1_Backgrounds", L"..\\Resources\\Map\\World1_Backgrounds.bmp"); // 이미지 설정

		BackGround* Bg = object::Instantiate<BackGround>(eLayerType::BackGround);
		Vector2 BgPos = Vector2(tex->GetWidth() / 2 - 2, tex->GetHeight() / 2 - 2);
		BgPos.y -= 389.f;
		Bg->GetComponent<Transform>()->SetPosition(BgPos); // 중점 설정

		SpriteRenderer* BgRenderer = Bg->AddComponent<SpriteRenderer>();
		BgRenderer->SetAffectedCamera(true);
		BgRenderer->SetTexture(tex);
		BgRenderer->SetCameraSpeedRatio(Vector2(5.5f, 1.f));

		// 스테이지 설정
		tex = ResourceManager::Load<Texture>(L"Stage1", L"..\\Resources\\Map\\Foreground\\Stage1.bmp"); // 이미지 설정
		ForeGround* Fg = object::Instantiate<ForeGround>(eLayerType::ForeGround);
		Vector2 FgPos = Vector2(775.5f, 107.5f);
		Fg->GetComponent<Transform>()->SetPosition(FgPos); // 중점 설정

		SpriteRenderer* FgRenderer = Fg->AddComponent<SpriteRenderer>();
		FgRenderer->SetAffectedCamera(true);
		FgRenderer->SetTexture(tex);
		FgRenderer->SetRenderSize(Vector2(1551.f, 215.f));
		FgRenderer->SetRednerLeftTop(Vector2(0, 679.f));

		// 픽셀 이미지 로드
		Texture* Pixeltex = ResourceManager::Load<Texture>(L"Stage1_Pixel"
			, L"..\\Resources\\Map\\Foreground\\Stage1_Pixel.bmp");

		Vector2 PixelPos = Vector2(775.5f, 107.5f);
		mPixelBG = object::Instantiate<BackGround>(eLayerType::Pixel);
		mPixelBG->GetComponent<Transform>()->SetPosition(PixelPos); // 중점 설정

		SpriteRenderer* PixelBgRenderer = mPixelBG->AddComponent<SpriteRenderer>();
		PixelBgRenderer->SetAffectedCamera(true);
		PixelBgRenderer->SetTexture(Pixeltex);
		PixelBgRenderer->SetRenderTrig(false);
		PixelBgRenderer->SetRenderSize(Vector2(1551.f, 215.f));
		PixelBgRenderer->SetRednerLeftTop(Vector2(0, 679.f));

		// Portal
		PortalUI* portalUI = object::Instantiate<PortalUI>(eLayerType::Portal);
		portalUI->GetComponent<Transform>()->SetPosition(Vector2(1514.f, 80.f));

		// Sound Load
		ResourceManager::Load<Sound>(L"Stage1BGMSound", L"..\\Resources\\Sound\\Theme\\Stage1BGM.wav");

		// 생성한 모든 오브젝트 초기화 
		Scene::Initialize();
	}

	void Level1_Stage3Scene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::MOUSE_MBTN))
		{
			SceneManager::LoadScene(L"Level1_Stage4Scene");
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

	void Level1_Stage3Scene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void Level1_Stage3Scene::Enter()
	{
		// 플레이어 설정
		Player* player = SceneManager::GetPlayer();
		Transform* playerTrans = player->GetComponent<Transform>();
		playerTrans->SetPosition(Vector2(30.f, 100.f));

		// 카메라 설정 
		Camera::SetTarget(player);
		Camera::SetCameraLimit(Vector2(1551.f, 215.f));

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

	void Level1_Stage3Scene::Exit()
	{
		// 오디오 정지
		ResourceManager::AllSoundStop();

		// 카메라 설정 해제
		Camera::SetTarget(nullptr);
		CollisionManager::Clear();
	}
}