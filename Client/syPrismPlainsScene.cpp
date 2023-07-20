#include "syPrismPlainsScene.h"
#include "syInput.h"
#include "sySceneManager.h"

namespace sy
{
	PrismPlainsScene::PrismPlainsScene()
	{
	}

	PrismPlainsScene::~PrismPlainsScene()
	{
	}

	void PrismPlainsScene::Initialize()
	{
		Scene::Initialize();
	}

	void PrismPlainsScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::MOUSE_RBTN))
		{
			SceneManager::LoadScene(L"StageScene");
		}

		Scene::Update();
	}

	void PrismPlainsScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void PrismPlainsScene::Enter()
	{
	}

	void PrismPlainsScene::Exit()
	{
	}
}