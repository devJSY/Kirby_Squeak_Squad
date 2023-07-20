#include "syGambleGalaxyScene.h"
#include "syInput.h"
#include "sySceneManager.h"
#include "syLevel_BG.h"
#include "syObject.h"

namespace sy
{
	GambleGalaxyScene::GambleGalaxyScene()
		: mType(eLevelType::Level8)
	{
	}

	GambleGalaxyScene::~GambleGalaxyScene()
	{
	}

	void GambleGalaxyScene::Initialize()
	{
		Level_BG* mlevelBG = object::Instantiate<Level_BG>(eLayerType::BackGround);

		Scene::Initialize();

		// mlevelBG 초기화 이후 호출
		mlevelBG->SetLevelType(mType);
	}

	void GambleGalaxyScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::MOUSE_RBTN))
		{
			SceneManager::LoadScene(L"StageScene");
		}

		Scene::Update();
	}

	void GambleGalaxyScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void GambleGalaxyScene::Enter()
	{
	}

	void GambleGalaxyScene::Exit()
	{
	}
}