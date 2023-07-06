#include "syEndingScene.h"

namespace sy
{
	EndingScene::EndingScene()
	{
	}

	EndingScene::~EndingScene()
	{
	}

	void EndingScene::Initialize()
	{
	}

	void EndingScene::Update()
	{
		Scene::Update();
	}

	void EndingScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
		ShowSceneName(hdc, GetName());
	}
}