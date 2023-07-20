#include "syPrismPlainsScene.h"
#include "syInput.h"
#include "sySceneManager.h"
#include "syLevel_BG.h"
#include "syObject.h"


namespace sy
{
	PrismPlainsScene::PrismPlainsScene()
		: mType(eLevelType::Level1)
		, mlevelBG(nullptr)
	{
	}

	PrismPlainsScene::~PrismPlainsScene()
	{
	}

	void PrismPlainsScene::Initialize()
	{
		mlevelBG = object::Instantiate<Level_BG>(eLayerType::BackGround);

		Scene::Initialize();

		// mlevelBG 초기화 이후 호출
		mlevelBG->SetLevelType(mType);
	}

	void PrismPlainsScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::MOUSE_RBTN))
		{
			SceneManager::LoadScene(L"StageScene");
		}

		// 스테이지 클리어 시 배경화면 변경
		if (Input::GetKeyDown(eKeyCode::T))
		{
			mType = eLevelType::Level1_Clear;
			mlevelBG->SetLevelType(mType);
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