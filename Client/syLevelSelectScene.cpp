#include "syLevelSelectScene.h"

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
	}

	void LevelSelectScene::Update()
	{
		Scene::Update();
	}

	void LevelSelectScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
		ShowSceneName(hdc, GetName());
	}
}