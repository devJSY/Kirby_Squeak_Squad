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

	SceneManager::~SceneManager()
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
		Scene* check = CreateScene<TitleScene>(L"TitleScene");
		assert(check);

		check = CreateScene<LevelSelectScene>(L"LevelSelectScene");
		assert(check);

		check = CreateScene<EndingScene>(L"EndingScene");
		assert(check);

		check = CreateScene<OpeningScene>(L"OpeningScene");
		assert(check);

		check = CreateScene<StageScene>(L"StageScene");
		assert(check);

		check = CreateScene<WorldTunnelScene>(L"WorldTunnelScene");
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
		// 변경전 기존 Scene Exit 호출
		mActiveScene->Exit();

		// 파라메타로 들어온 name 의 Scene 을 찾아 ActiveScene으로 설정해준다
		std::map<std::wstring, Scene*>::iterator iter = mScenes.find(name);

		if (iter == mScenes.end())
			return nullptr;

		mActiveScene = iter->second;
		mActiveScene->Enter();

		return iter->second;
	}
}
