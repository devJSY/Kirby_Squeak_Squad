#include "syLevelSelectScene.h"
#include "syInput.h"
#include "sySceneManager.h"
#include "syPlayer.h"
#include "syObject.h"
#include "sySpriteRenderer.h"
#include "syTransform.h"
#include "syResourceManager.h"
#include "syTexture.h"
#include "syBackGround.h"
#include "syApplication.h"
#include "syAnimator.h"
#include "syInventory.h"

namespace sy
{
	LevelSelectScene::LevelSelectScene()
	{
	}

	LevelSelectScene::~LevelSelectScene()
	{
	}

	void LevelSelectScene::Initialize()
	{
		// ��� ȭ�� ������Ʈ ���� 
		BackGround* Bg = object::Instantiate<BackGround>(eLayerType::BackGround);
		assert(Bg);
		SpriteRenderer* BgRenderer = Bg->AddComponent<SpriteRenderer>();
		assert(BgRenderer);
		BgRenderer->SetTexture(ResourceManager::Load<Texture>(L"LevelSelectImage", L"..\\Resources\\Map\\Level_Select.bmp")); // �̹��� ����
		BgRenderer->SetBmpRGB(255, 0, 255); // ����Ÿ ����
		BgRenderer->SetAffectCamera(false);

		Vector2 vec = Vector2(Application::GetResolution()) / 2.f;
		vec.y /= 2.f;
		Bg->GetComponent<Transform>()->SetPosition(vec); // ���� ����

		// �ϴ� ȭ�� ������Ʈ ���� 
		Inventory* Inven = object::Instantiate<Inventory>(eLayerType::Inventory);
		assert(Inven);

		// �κ��丮 Ŭ���� ��ġ ����
		vec = Vector2(Application::GetResolution()) / 2.f;
		vec.y += vec.y / 2.f;
		(Inven->GetComponent<Transform>())->SetPosition(vec);

		// �κ��丮 �ִϸ��̼� ����
		Animator* InvenAt = Inven->AddComponent<Animator>();
		Texture* image = ResourceManager::Load<Texture>(L"Inventory"
			, L"..\\Resources\\\Inventory\\Inventory.bmp");

		InvenAt->CreateAnimation(L"Inventory", image, Vector2(0.f, 0.f), Vector2(256.f, 192.f)
			, Vector2(0.f, 0.f), 16, 0.1f);
		InvenAt->PlayAnimation(L"Inventory", true);
		InvenAt->SetAffectedCamera(false);

		Scene::Initialize();
	}

	void LevelSelectScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::E) || Input::GetKeyDown(eKeyCode::MOUSE_LBTN))
		{
			SceneManager::LoadScene(L"StageScene");
		}
	}

	void LevelSelectScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
		ShowSceneName(hdc, GetName(), L"Change to StageScene : E or Mouse LBTN");
	}
}