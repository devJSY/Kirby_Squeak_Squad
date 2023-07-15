#include "syStageScene.h"
#include "syKirby.h"
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
#include "syInventory.h"
#include "syAnimator.h"

namespace sy
{
	StageScene::StageScene()
		: mPlayer(nullptr)
	{
	}

	StageScene::~StageScene()
	{
	}

	void StageScene::Initialize()
	{
		// ��׶��� ����
		BackGround* Bg = object::Instantiate<BackGround>(eLayerType::BackGround);
		assert(Bg);
		SpriteRenderer* BgRenderer = Bg->AddComponent<SpriteRenderer>();
		assert(BgRenderer);
		Texture* tex = ResourceManager::Load<Texture>(L"World1_Backgrounds", L"..\\Resources\\Map\\World1_Stage_BackGround.bmp"); // �̹��� ����
		assert(tex);
		BgRenderer->SetTexture(tex);
		Bg->GetComponent<Transform>()->SetPosition(Vector2(tex->GetWidth() / 2, tex->GetHeight() / 2)); // ���� ����
		BgRenderer->SetAffectCamera(true);


		// �������� ����
		ForeGround* Fg = object::Instantiate<ForeGround>(eLayerType::ForeGround);
		assert(Fg);
		SpriteRenderer* FgRenderer = Fg->AddComponent<SpriteRenderer>();
		assert(FgRenderer);

		tex = ResourceManager::Load<Texture>(L"Stage1", L"..\\Resources\\Map\\Stage1.bmp"); // �̹��� ����
		assert(tex);
		FgRenderer->SetTexture(tex);
		FgRenderer->SetBmpRGB(255, 0, 255); // ����Ÿ ����
		Fg->GetComponent<Transform>()->SetPosition(Vector2(tex->GetWidth() / 2, tex->GetHeight() / 2)); // ���� ����
		FgRenderer->SetAffectCamera(true);

		// �÷��̾� ����
		mPlayer = object::Instantiate<Kirby>(eLayerType::Player);
		assert(mPlayer);


		/////////////// Inventory ��ü�� ���߿� ��� ������ �ϳ��� �����ϵ��� �����ؾ���
		// �ϴ� ȭ�� ������Ʈ ���� 
		Inventory* Inven = object::Instantiate<Inventory>(eLayerType::Inventory);
		assert(Inven);

		// �κ��丮 Ŭ���� ��ġ ����
		Vector2 vec = Vector2(Application::GetResolution()) / 2.f;
		vec.y += vec.y / 2.f;
		(Inven->GetComponent<Transform>())->SetPosition(vec);

		// �κ��丮 �ִϸ��̼� ����
		Animator* InvenAt = Inven->AddComponent<Animator>();
		Texture* image = ResourceManager::Load<Texture>(L"Inventory"
			, L"..\\Resources\\Inventory\\Inventory.bmp");

		InvenAt->CreateAnimation(L"Inventory", image, Vector2(0.f, 0.f), Vector2(256.f, 192.f), Vector2(256.f, 0.f), 0.2f, 16);
		InvenAt->PlayAnimation(L"Inventory", true);
		InvenAt->SetAffectedCamera(false);

		Scene::Initialize();
	}

	void StageScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::MOUSE_RBTN))
		{
			SceneManager::LoadScene(L"WorldTunnelScene");
		}
	}

	void StageScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void StageScene::Enter()
	{
		// ī�޶� ���� 
		Camera::SetTarget(mPlayer);
	}

	void StageScene::Exit()
	{
		// ī�޶� ���� ����
		Camera::SetTarget(nullptr);

	}
}