#include "sySceneManager.h"
#include "syTitleScene.h"
#include "syLevelSelectScene.h"
#include "syEndingScene.h"
#include "syOpeningScene.h"
#include "syStageScene.h"
#include "syWorldTunnelScene.h"
#include "syObject.h"
#include "syApplication.h"
#include "syTransform.h"
#include "syInventory.h"
#include "syAbilityUI.h"
#include "syHPbarUI.h"
#include "syLifeUI.h"

namespace sy
{
	std::map<std::wstring, Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::mActiveScene = nullptr;

	Inventory* SceneManager::mInventory = new Inventory;
	AbilityUI* SceneManager::mAbilityUI = new AbilityUI;
	HPbarUI* SceneManager::mHPbarUI = new HPbarUI;
	LifeUI* SceneManager::mLifeUI = new LifeUI;

	SceneManager::SceneManager()
	{
	}

	void SceneManager::Release()
	{
		std::wstring SceneName = mActiveScene->GetName();

		// ������� ���� UI�� �߰����� ���� ���̶�� ���� UI �޸� ���� �������
		if (SceneName == L"OpeningScene" || SceneName == L"TitleScene" || SceneName == L"EndingScene")
		{
			delete mInventory;
			mInventory = nullptr;

			delete mAbilityUI;
			mAbilityUI = nullptr;

			delete mHPbarUI;
			mHPbarUI = nullptr;

			delete mLifeUI;
			mLifeUI = nullptr;			
		}

		for (auto iter : mScenes)
		{
			if (nullptr != iter.second)
			{
				delete iter.second;
				iter.second = nullptr;
			}
		}

		mScenes.clear();
	}

	void SceneManager::Initialize()
	{
		CreateScene<OpeningScene>(L"OpeningScene");
		CreateScene<TitleScene>(L"TitleScene");
		CreateScene<LevelSelectScene>(L"LevelSelectScene");
		CreateScene<StageScene>(L"StageScene");
		CreateScene<WorldTunnelScene>(L"WorldTunnelScene");
		CreateScene<EndingScene>(L"EndingScene");

		for (auto iter : mScenes)
		{
			mActiveScene = iter.second;
			iter.second->Initialize();
		}

		UIInitialize();

		LoadScene(L"OpeningScene");
	}

	void SceneManager::Update()
	{
		mActiveScene->Update();
	}

	void SceneManager::Render(HDC hdc)
	{
		mActiveScene->Render(hdc);
	}

	Scene* SceneManager::LoadScene(const std::wstring& name)
	{
		// ������ ���� Scene Exit ȣ��
		mActiveScene->Exit();

		// ���� ���� UI�� �����Ѵٸ� ����
		mActiveScene->RemoveGameObject(eLayerType::Inventory, mInventory);
		mActiveScene->RemoveGameObject(eLayerType::UI, mAbilityUI);
		mActiveScene->RemoveGameObject(eLayerType::UI, mHPbarUI);
		mActiveScene->RemoveGameObject(eLayerType::UI, mLifeUI);

		// �Ķ��Ÿ�� ���� name �� Scene �� ã�� ActiveScene���� �������ش�
		std::map<std::wstring, Scene*>::iterator iter = mScenes.find(name);

		if (iter == mScenes.end())
			return nullptr;

		mActiveScene = iter->second;

		// ������ ���� ������ ���� UI �߰�
		if (name != L"OpeningScene" && name != L"TitleScene" && name != L"EndingScene")
		{
			mActiveScene->AddGameObject(eLayerType::Inventory, mInventory);
			mActiveScene->AddGameObject(eLayerType::UI, mAbilityUI);
			mActiveScene->AddGameObject(eLayerType::UI, mHPbarUI);
			mActiveScene->AddGameObject(eLayerType::UI, mLifeUI);
		}

		mActiveScene->Enter();

		return iter->second;
	}

	Scene* SceneManager::GetScene(const std::wstring& name)
	{
		std::map<std::wstring, Scene*>::iterator iter = mScenes.find(name);

		if (iter == mScenes.end())
			return nullptr;

		return iter->second;
	}

	void SceneManager::UIInitialize()
	{
		// UI ��ġ ����
		Vector2 vec = Vector2(Application::GetResolution()) / 2.f;
		vec.y += vec.y / 2.f;
		mInventory->GetComponent<Transform>()->SetPosition(vec);

		Vector2 Uivec = Vector2(Application::GetResolution()) / 2.f;
		Uivec.x = 20.0f;
		Uivec.y -= 25.f;
		mAbilityUI->GetComponent<Transform>()->SetPosition(Uivec);
		mAbilityUI->SetOwner(nullptr); // ���ʼ��� ���߿� ��������

		Uivec = Vector2(Application::GetResolution()) / 2.f;
		Uivec.x = 85.0f;
		Uivec.y -= 12.f;
		mHPbarUI->GetComponent<Transform>()->SetPosition(Uivec);
		mHPbarUI->SetOwner(nullptr); // ���ʼ��� ���߿� ��������

		Uivec = Vector2(Application::GetResolution()) / 2.f;
		Uivec.x = 65.0f;
		Uivec.y -= 27.f;
		mLifeUI->GetComponent<Transform>()->SetPosition(Uivec);
		mLifeUI->SetOwner(nullptr); // ���ʼ��� ���߿� ��������

		mInventory->Initialize();
		mAbilityUI->Initialize();
		mHPbarUI->Initialize();
		mLifeUI->Initialize();
	}
}
