#include "sySceneManager.h"
#include "syTitleScene.h"
#include "syLevelSelectScene.h"
#include "syEndingScene.h"
#include "syOpeningScene.h"
#include "syStageScene.h"
#include "syWorldTunnelScene.h"

namespace sy
{
	std::map<std::wstring, Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::mActiveScene = nullptr;

	SceneManager::SceneManager()
	{
	}

	void SceneManager::Release()
	{
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

		// �Ķ��Ÿ�� ���� name �� Scene �� ã�� ActiveScene���� �������ش�
		std::map<std::wstring, Scene*>::iterator iter = mScenes.find(name);

		if (iter == mScenes.end())
			return nullptr;

		mActiveScene = iter->second;
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
}
