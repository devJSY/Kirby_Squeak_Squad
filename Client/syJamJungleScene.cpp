#include "syJamJungleScene.h"
#include "syInput.h"
#include "sySceneManager.h"
#include "syLevel_BG.h"
#include "syObject.h"

namespace sy
{
	JamJungleScene::JamJungleScene()
		: mType(eLevelType::Level4)
	{
	}

	JamJungleScene::~JamJungleScene()
	{
	}

	void JamJungleScene::Initialize()
	{
		Level_BG* mlevelBG = object::Instantiate<Level_BG>(eLayerType::BackGround);

		Scene::Initialize();

		// mlevelBG 초기화 이후 호출
		mlevelBG->SetLevelType(mType);
	}

	void JamJungleScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::MOUSE_RBTN))
		{
			SceneManager::LoadScene(L"StageScene");

		}
		Scene::Update();
	}

	void JamJungleScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void JamJungleScene::Enter()
	{
	}

	void JamJungleScene::Exit()
	{
	}
}