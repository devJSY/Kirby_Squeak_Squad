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

		Scene* check = CreateScene<OpeningScene>(L"OpeningScene");
		assert(check);

		check = CreateScene<TitleScene>(L"TitleScene");
		assert(check);

		check = CreateScene<LevelSelectScene>(L"LevelSelectScene");
		assert(check);

		check = CreateScene<StageScene>(L"StageScene");
		assert(check);

		check = CreateScene<WorldTunnelScene>(L"WorldTunnelScene");
		assert(check);

		check = CreateScene<EndingScene>(L"EndingScene");
		assert(check);

		check = LoadScene(L"OpeningScene");

		assert(check);
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
}
