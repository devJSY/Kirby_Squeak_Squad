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
#include "syLevel_BG.h"

namespace sy
{
	LevelSelectScene::LevelSelectScene()
		: mInventory(nullptr)
		, mAbilityUI(nullptr)
		, mHPbarUI(nullptr)
		, mLifeUI(nullptr)
	{
	}

	LevelSelectScene::~LevelSelectScene()
	{
	}

	void LevelSelectScene::Initialize()
	{
		// ��� ȭ�� ������Ʈ ���� 
		Level_BG* Bg = object::Instantiate<Level_BG>(eLayerType::BackGround);
		Vector2 vec = Vector2(Application::GetResolution()) / 2.f;
		vec.y /= 2.f;
		Bg->GetComponent<Transform>()->SetPosition(vec); // ���� ����		


		// Inventory ���� 
		mInventory = object::Instantiate<Inventory>(eLayerType::Inventory);
		vec = Vector2(Application::GetResolution()) / 2.f;
		vec.y += vec.y / 2.f;
		mInventory->GetComponent<Transform>()->SetPosition(vec);

		// UI ����
		mAbilityUI = object::Instantiate<AbilityUI>(eLayerType::UI);
		Vector2 Uivec = Vector2(Application::GetResolution()) / 2.f;
		Uivec.x = 20.0f; 
		Uivec.y -= 25.f; 
		mAbilityUI->GetComponent<Transform>()->SetPosition(Uivec);
		mAbilityUI->SetOwner(nullptr); // ���ʼ��� ���߿� ��������

		mHPbarUI = object::Instantiate<HPbarUI>(eLayerType::UI);
		Uivec = Vector2(Application::GetResolution()) / 2.f;
		Uivec.x = 85.0f;
		Uivec.y -= 12.f;
		mHPbarUI->GetComponent<Transform>()->SetPosition(Uivec);
		mHPbarUI->SetOwner(nullptr); // ���ʼ��� ���߿� ��������

		mLifeUI = object::Instantiate<LifeUI>(eLayerType::UI);
		Uivec = Vector2(Application::GetResolution()) / 2.f;
		Uivec.x = 65.0f;
		Uivec.y -= 27.f;
		mLifeUI->GetComponent<Transform>()->SetPosition(Uivec);
		mLifeUI->SetOwner(nullptr); // ���ʼ��� ���߿� ��������

		//// StageScene�� ��ü ����
		//Scene* NextScene = SceneManager::GetScene(L"StageScene");
		//NextScene->AddGameObject(eLayerType::UI, AbilityUi);
		//NextScene->AddGameObject(eLayerType::UI, HPbarUi);
		//NextScene->AddGameObject(eLayerType::UI, LifeUi);
		//NextScene->AddGameObject(eLayerType::Inventory, Inven);

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

		// ��ü ����
		if (mInventory != nullptr)
		{
			PassGameObject(L"StageScene", eLayerType::Inventory, mInventory);
			mInventory = nullptr;
		}
		if (mAbilityUI != nullptr)
		{
			PassGameObject(L"StageScene", eLayerType::UI, mAbilityUI);
			mAbilityUI = nullptr;
		}
		if (mHPbarUI != nullptr)
		{
			PassGameObject(L"StageScene", eLayerType::UI, mHPbarUI);
			mHPbarUI = nullptr;
		}
		if (mLifeUI != nullptr)
		{
			PassGameObject(L"StageScene", eLayerType::UI, mLifeUI);
			mLifeUI = nullptr;
		}
	}
}