#include "sySecretSeaScene.h"
#include "syInput.h"
#include "sySceneManager.h"
#include "syLevel_BG.h"
#include "syObject.h"

namespace sy
{
	SecretSeaScene::SecretSeaScene()
		: mType(eLevelType::Level7)
	{
	}

	SecretSeaScene::~SecretSeaScene()
	{
	}

	void SecretSeaScene::Initialize()
	{
		Level_BG* mlevelBG = object::Instantiate<Level_BG>(eLayerType::BackGround);

		Scene::Initialize();

		// mlevelBG 초기화 이후 호출
		mlevelBG->SetLevelType(mType);
	}

	void SecretSeaScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::MOUSE_RBTN))
		{
			SceneManager::LoadScene(L"StageScene");
		}

		Scene::Update();
	}

	void SecretSeaScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void SecretSeaScene::Enter()
	{
	}

	void SecretSeaScene::Exit()
	{
	}
}