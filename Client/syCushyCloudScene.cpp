#include "syCushyCloudScene.h"
#include "syInput.h"
#include "sySceneManager.h"
#include "syLevel_BG.h"
#include "syObject.h"

namespace sy
{
	CushyCloudScene::CushyCloudScene()
		: mType(eLevelType::Level3)
	{
	}

	CushyCloudScene::~CushyCloudScene()
	{
	}

	void CushyCloudScene::Initialize()
	{
		Level_BG* mlevelBG = object::Instantiate<Level_BG>(eLayerType::BackGround);

		Scene::Initialize();

		// mlevelBG 초기화 이후 호출
		mlevelBG->SetLevelType(mType);
	}

	void CushyCloudScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::MOUSE_RBTN))
		{
			SceneManager::LoadScene(L"StageScene");
		}

		Scene::Update();
	}

	void CushyCloudScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void CushyCloudScene::Enter()
	{
	}

	void CushyCloudScene::Exit()
	{
	}
}