#include "syNatureNotchScene.h"
#include "syInput.h"
#include "sySceneManager.h"
#include "syLevel_BG.h"
#include "syObject.h"

namespace sy
{
	NatureNotchScene::NatureNotchScene()
		: mType(eLevelType::Level2)
	{
	}

	NatureNotchScene::~NatureNotchScene()
	{
	}

	void NatureNotchScene::Initialize()
	{
		Level_BG* mlevelBG = object::Instantiate<Level_BG>(eLayerType::BackGround);

		Scene::Initialize();

		// mlevelBG 초기화 이후 호출
		mlevelBG->SetLevelType(mType);
	}

	void NatureNotchScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::MOUSE_RBTN))
		{
			SceneManager::LoadScene(L"StageScene");
		}

		Scene::Update();
	}

	void NatureNotchScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void NatureNotchScene::Enter()
	{
	}

	void NatureNotchScene::Exit()
	{
	}
}