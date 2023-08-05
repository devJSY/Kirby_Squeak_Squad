#include "syStage3Scene.h"
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


#include "sySirKibble.h"
#include "syCrimp.h"

namespace sy
{
	Stage3Scene::Stage3Scene()
		: mPixelBG(nullptr)
	{
	}

	Stage3Scene::~Stage3Scene()
	{
	}

	void Stage3Scene::Initialize()
	{
		// �� ����
		Blockin* blockin = object::Instantiate<Blockin>(eLayerType::Enemy);
		blockin->GetComponent<Transform>()->SetPosition(Vector2(154.f, 141.f));

		WaddleDee* waddleDee = object::Instantiate<WaddleDee>(eLayerType::Enemy);
		waddleDee->GetComponent<Transform>()->SetPosition(Vector2(174.f, 47.f));

		WaddleDee* waddleDee2 = object::Instantiate<WaddleDee>(eLayerType::Enemy);
		waddleDee2->GetComponent<Transform>()->SetPosition(Vector2(1025.f, 46.f));

		WaddleDee* waddleDee3 = object::Instantiate<WaddleDee>(eLayerType::Enemy);
		waddleDee3->GetComponent<Transform>()->SetPosition(Vector2(1279.f, 79.f));

		WaddleDee* waddleDee4 = object::Instantiate<WaddleDee>(eLayerType::Enemy);
		waddleDee4->GetComponent<Transform>()->SetPosition(Vector2(1218.f, 160.f));

		HotHead* hotHead = object::Instantiate<HotHead>(eLayerType::Enemy);
		hotHead->GetComponent<Transform>()->SetPosition(Vector2(726.f, 92.f));


		// ��׶��� ����
		Texture* tex = ResourceManager::Load<Texture>(L"World1_Backgrounds", L"..\\Resources\\Map\\World1_Backgrounds.bmp"); // �̹��� ����

		BackGround* Bg = object::Instantiate<BackGround>(eLayerType::BackGround);
		Vector2 BgPos = Vector2(tex->GetWidth() / 2 - 2, tex->GetHeight() / 2 - 2);
		BgPos.y -= 389.f;
		Bg->GetComponent<Transform>()->SetPosition(BgPos); // ���� ����

		SpriteRenderer* BgRenderer = Bg->AddComponent<SpriteRenderer>();
		BgRenderer->SetAffectedCamera(true);
		BgRenderer->SetTexture(tex);
		BgRenderer->SetCameraSpeedRatio(Vector2(5.5f, 1.f));

		// �������� ����
		tex = ResourceManager::Load<Texture>(L"Stage1", L"..\\Resources\\Map\\Foreground\\Stage1.bmp"); // �̹��� ����
		ForeGround* Fg = object::Instantiate<ForeGround>(eLayerType::ForeGround);
		Vector2 FgPos = Vector2(775.5f, 107.5f);
		Fg->GetComponent<Transform>()->SetPosition(FgPos); // ���� ����

		SpriteRenderer* FgRenderer = Fg->AddComponent<SpriteRenderer>();
		FgRenderer->SetAffectedCamera(true);
		FgRenderer->SetTexture(tex);
		FgRenderer->SetRenderSize(Vector2(1551.f, 215.f));
		FgRenderer->SetRednerLeftTop(Vector2(0, 679.f));

		// �ȼ� �̹��� �ε�
		Texture* Pixeltex = ResourceManager::Load<Texture>(L"Stage1_Pixel"
			, L"..\\Resources\\Map\\Foreground\\Stage1_Pixel.bmp");

		Vector2 PixelPos = Vector2(775.5f, 107.5f);
		mPixelBG = object::Instantiate<BackGround>(eLayerType::Pixel);
		mPixelBG->GetComponent<Transform>()->SetPosition(PixelPos); // ���� ����

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

		// ������ ��� ������Ʈ �ʱ�ȭ 
		Scene::Initialize();
	}

	void Stage3Scene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::MOUSE_RBTN))
		{
			SceneManager::LoadScene(L"Stage4Scene");
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

	void Stage3Scene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void Stage3Scene::Enter()
	{
		// �÷��̾� ����
		Player* player = SceneManager::GetPlayer();
		Transform* playerTrans = player->GetComponent<Transform>();
		playerTrans->SetPosition(Vector2(30.f, 100.f));

		// ī�޶� ���� 
		Camera::SetTarget(player);
		Camera::SetCameraLimit(Vector2(1551.f, 215.f));

		// ���̾� �浹 ����
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Enemy, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Effect, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Portal, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::AbilityItem, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Enemy, eLayerType::Effect, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Effect, eLayerType::AbilityItem, true);

		// ����� ����
		ResourceManager::Find<Sound>(L"StageSelectSound")->Stop(true);
		// ����� ���
		ResourceManager::Find<Sound>(L"Stage1BGMSound")->Play(true);
	}

	void Stage3Scene::Exit()
	{
		// ī�޶� ���� ����
		Camera::SetTarget(nullptr);
		CollisionManager::Clear();

		// ����� ���
		ResourceManager::Find<Sound>(L"Stage1BGMSound")->Stop(true);
	}
}