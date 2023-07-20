#include "syVocalVolcanoScene.h"
#include "syInput.h"
#include "sySceneManager.h"
#include "syLevel_BG.h"
#include "syObject.h"

namespace sy
{
	VocalVolcanoScene::VocalVolcanoScene()
		: mType(eLevelType::Level5)
	{
	}

	VocalVolcanoScene::~VocalVolcanoScene()
	{
	}

	void VocalVolcanoScene::Initialize()
	{
		Level_BG* mlevelBG = object::Instantiate<Level_BG>(eLayerType::BackGround);

		Scene::Initialize();

		// mlevelBG 초기화 이후 호출
		mlevelBG->SetLevelType(mType);
	}

	void VocalVolcanoScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::MOUSE_RBTN))
		{
			SceneManager::LoadScene(L"StageScene");
		}

		Scene::Update();
	}

	void VocalVolcanoScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void VocalVolcanoScene::Enter()
	{
	}

	void VocalVolcanoScene::Exit()
	{
	}
}