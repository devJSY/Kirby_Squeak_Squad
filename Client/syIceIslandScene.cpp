#include "syIceIslandScene.h"
#include "syInput.h"
#include "sySceneManager.h"
#include "syLevel_BG.h"
#include "syObject.h"

namespace sy
{
	IceIslandScene::IceIslandScene()
		: mType(eLevelType::Level6)
		, mlevelBG(nullptr)
	{
	}

	IceIslandScene::~IceIslandScene()
	{
	}

	void IceIslandScene::Initialize()
	{
		mlevelBG = object::Instantiate<Level_BG>(eLayerType::BackGround);

		Scene::Initialize();

		mlevelBG->SetLevelType(eLevelType::Level6);
	}

	void IceIslandScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::MOUSE_RBTN))
		{
			SceneManager::LoadScene(L"StageScene");
		}

		// 스테이지 클리어 시 배경화면 변경
		if (Input::GetKeyDown(eKeyCode::T))
		{
			mType = eLevelType::Level6_Clear;
			mlevelBG->SetLevelType(mType);
		}

		Scene::Update();
	}

	void IceIslandScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void IceIslandScene::Enter()
	{
	}

	void IceIslandScene::Exit()
	{
	}
}