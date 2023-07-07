#include "syTitleScene.h"
#include "syPlayer.h"
#include "sySpriteRenderer.h"
#include "syObject.h"
#include "syInput.h"
#include "sySceneManager.h"

namespace sy
{
	TitleScene::TitleScene()
	{
	}

	TitleScene::~TitleScene()
	{
	}

	void TitleScene::Initialize()
	{
	}

	void TitleScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::W))
		{
			SceneManager::LoadScene(L"LevelSelectScene");
		}
	}

	void TitleScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
		ShowSceneName(hdc, GetName(), L"Change to LevelSelectScene : W");
	}
}