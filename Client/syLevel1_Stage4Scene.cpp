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
		// �� ����
		SirKibble* sirKibble1 = object::Instantiate<SirKibble>(eLayerType::Enemy);

		SirKibble* sirKibble2 = object::Instantiate<SirKibble>(eLayerType::Enemy);
		sirKibble2->GetComponent<Transform>()->SetPosition(Vector2(42.f, 169.f));

		// ��׶��� ����
		Texture* tex = ResourceManager::Load<Texture>(L"World1_Backgrounds", L"..\\Resources\\Map\\World1_Backgrounds.bmp"); // �̹��� ����

		BackGround* Bg = object::Instantiate<BackGround>(eLayerType::BackGround);
		Vector2 BgPos = Vector2(tex->GetWidth() / 2 - 2, tex->GetHeight() / 2 - 2);
		Bg->GetComponent<Transform>()->SetPosition(BgPos); // ���� ����

		SpriteRenderer* BgRenderer = Bg->AddComponent<SpriteRenderer>();
		BgRenderer->SetAffectedCamera(false);
		BgRenderer->SetTexture(tex);

		// �������� ����
		tex = ResourceManager::Load<Texture>(L"Stage1", L"..\\Resources\\Map\\Foreground\\Stage1.bmp"); // �̹��� ����
		ForeGround* Fg = object::Instantiate<ForeGround>(eLayerType::ForeGround);
		Vector2 FgPos = Vector2(134.5f, 208.5f);
		Fg->GetComponent<Transform>()->SetPosition(FgPos); // ���� ����

		SpriteRenderer* FgRenderer = Fg->AddComponent<SpriteRenderer>();
		FgRenderer->SetAffectedCamera(true);
		FgRenderer->SetTexture(tex);
		FgRenderer->SetRenderSize(Vector2(269.f, 417.f));
		FgRenderer->SetRednerLeftTop(Vector2(1604.f, 137.f));

		// �ȼ� �̹��� �ε�
		Texture* Pixeltex = ResourceManager::Load<Texture>(L"Stage1_Pixel"
			, L"..\\Resources\\Map\\Foreground\\Stage1_Pixel.bmp");

		Vector2 PixelPos = Vector2(134.5f, 208.5f);
		mPixelBG = object::Instantiate<BackGround>(eLayerType::Pixel);
		mPixelBG->GetComponent<Transform>()->SetPosition(PixelPos); // ���� ����

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

		// ������ ��� ������Ʈ �ʱ�ȭ 
		Scene::Initialize();

		// Init �� �� ������ ����
		Transform* sirKibble1tr = sirKibble1->GetComponent<Transform>();
		sirKibble1tr->SetPosition(Vector2(178.f, 122.f));
		sirKibble1tr->SetDirection(eDirection::LEFT);
		sirKibble1->GetComponent<Animator>()->PlayAnimation(L"SirKibble_Left_Idle", true);
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
		// �÷��̾� ����
		Player* player = SceneManager::GetPlayer();
		Transform* playerTrans = player->GetComponent<Transform>();
		playerTrans->SetPosition(Vector2(21.f, 300.f));

		// ī�޶� ���� 
		Camera::SetTarget(player);
		Camera::SetCameraLimit(Vector2(269.f, 417.f));

		// ���̾� �浹 ����
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Enemy, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Effect, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Portal, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::AbilityItem, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Enemy, eLayerType::Effect, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Enemy, eLayerType::Enemy, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Effect, eLayerType::AbilityItem, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Effect, eLayerType::Effect, true);

		// ����� ���
		ResourceManager::Find<Sound>(L"Stage1BGMSound")->Play(true);
	}

	void Level1_Stage4Scene::Exit()
	{
		// ����� ����
		ResourceManager::AllSoundStop();

		// ī�޶� ���� ����
		Camera::SetTarget(nullptr);
		CollisionManager::Clear();

		PrismPlainsScene* scene = dynamic_cast<PrismPlainsScene*>(SceneManager::GetScene(L"PrismPlainsScene"));
		scene->SetClearActiveUI(eStageState::Stage1);	// Stage1 Ŭ���� ó��
		scene->SetActiveUI(eStageState::Boss);			// ���� �������� Ȱ��ȭ

		DanceScene* danceScene = dynamic_cast<DanceScene*>(SceneManager::GetScene(L"DanceScene"));
		danceScene->SetNextSceneName(L"PrismPlainsScene");
		danceScene->SetType(eDanceSceneType::NormalClear);
	}
}