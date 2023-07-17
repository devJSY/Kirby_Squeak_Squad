#include "syLevelSelectScene.h"
#include "syInput.h"
#include "sySceneManager.h"
#include "syDefaultKirby.h"
#include "syObject.h"
#include "sySpriteRenderer.h"
#include "syTransform.h"
#include "syResourceManager.h"
#include "syTexture.h"
#include "syBackGround.h"
#include "syApplication.h"
#include "syAnimator.h"
#include "syInventory.h"
#include "syAbilityUI.h"
#include "syHPbarUI.h"
#include "syLifeUI.h"
#include "syCamera.h"

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
		SpriteRenderer* BgRenderer = Bg->AddComponent<SpriteRenderer>();
		Texture* tex = ResourceManager::Load<Texture>(L"LevelSelectImage", L"..\\Resources\\Map\\Level_Select.bmp");
		
		BgRenderer->SetAffectedCamera(false);
		BgRenderer->SetTexture(tex); // �̹��� ����
		BgRenderer->SetBmpRGB(255, 0, 255); // ����Ÿ ����

		Vector2 vec = Vector2(Application::GetResolution()) / 2.f;
		vec.y /= 2.f;
		Bg->GetComponent<Transform>()->SetPosition(vec); // ���� ����


		// Inventory ���� 
		Inventory* Inven = object::Instantiate<Inventory>(eLayerType::Inventory);

		// Inventory ��ġ ����
		vec = Vector2(Application::GetResolution()) / 2.f;
		vec.y += vec.y / 2.f;
		Inven->GetComponent<Transform>()->SetPosition(vec);


		// UI ����
		AbilityUI* AbilityUi = object::Instantiate<AbilityUI>(eLayerType::UI);
		AbilityUi->GetComponent<Transform>()->SetPosition(Vector2(Application::GetResolution()) / 2.f);

		Scene::Initialize();
	}

	void LevelSelectScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::MOUSE_RBTN))
		{
			SceneManager::LoadScene(L"StageScene");
		}
	}

	void LevelSelectScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void LevelSelectScene::Enter()
	{
		// ī�޶� ���� 
		Camera::SetTarget(nullptr);
	}

	void LevelSelectScene::Exit()
	{
		// ī�޶� ���� ����
		Camera::SetTarget(nullptr);
	}
}