#include "syLevelSelectScene.h"
#include "syInput.h"
#include "sySceneManager.h"
#include "syObject.h"
#include "syTransform.h"
#include "syApplication.h"
#include "syAnimator.h"
#include "syCamera.h"
#include "syLevel_BG.h"
#include "syCollisionManager.h"

#include "syPrismPlainsScene.h"
#include "syNatureNotchScene.h"
#include "syCushyCloudScene.h"
#include "syJamJungleScene.h"
#include "syVocalVolcanoScene.h"
#include "syIceIslandScene.h"
#include "sySecretSeaScene.h"
#include "syGambleGalaxyScene.h"

namespace sy
{
	LevelSelectScene::LevelSelectScene()
		: mType(eLevelType::LevelSelect)
		, mlevelBG(nullptr)
	{
	}

	LevelSelectScene::~LevelSelectScene()
	{
	}

	void LevelSelectScene::Initialize()
	{
		// ��� ȭ�� ������Ʈ ���� 
		mlevelBG = object::Instantiate<Level_BG>(eLayerType::BackGround);

		Scene::Initialize();

		mlevelBG->SetLevelType(eLevelType::LevelSelect);
	}

	void LevelSelectScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::MOUSE_RBTN))
		{
			// Ư�� ���ǿ� ���� Level ����
			if (0)
				SceneManager::LoadScene(L"PrismPlainsScene");
			else if (0)
				SceneManager::LoadScene(L"NatureNotchScene");
			else if (0)
				SceneManager::LoadScene(L"CushyCloudScene");
			else if (0)
				SceneManager::LoadScene(L"JamJungleScene");
			else if (0)
				SceneManager::LoadScene(L"VocalVolcanoScene");
			else if (1)
				SceneManager::LoadScene(L"IceIslandScene");
			else if (0)
				SceneManager::LoadScene(L"SecretSeaScene");
			else if (0)
				SceneManager::LoadScene(L"GambleGalaxyScene");
		}


		// �������� ���� Ŭ���� �� ���ȭ�� ����
		if (Input::GetKeyDown(eKeyCode::T))
		{
			mType = eLevelType::AllClear_LevelSelect;
			mlevelBG->SetLevelType(mType);
		}

	}

	void LevelSelectScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void LevelSelectScene::Enter()
	{
		// ī�޶� ���� 
		Camera::SetTarget(nullptr);
	}

	void LevelSelectScene::Exit()
	{
		// ī�޶� ���� ����
		Camera::SetTarget(nullptr);
		CollisionManager::Clear();
	}
}