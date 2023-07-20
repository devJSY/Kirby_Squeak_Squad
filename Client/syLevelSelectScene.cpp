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
	{
	}

	LevelSelectScene::~LevelSelectScene()
	{
	}

	void LevelSelectScene::Initialize()
	{
		// 상단 화면 오브젝트 생성 
		Level_BG* Bg = object::Instantiate<Level_BG>(eLayerType::BackGround);
		Vector2 vec = Vector2(Application::GetResolution()) / 2.f;
		vec.y /= 2.f;
		Bg->GetComponent<Transform>()->SetPosition(vec); // 중점 설정		

		Scene::Initialize();
	}

	void LevelSelectScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D))
		{
			// 특정 조건에 따라 Level 설정
			if (true)
				SceneManager::LoadScene(L"PrismPlainsScene");
			else if (false)
				SceneManager::LoadScene(L"NatureNotchScene");
			else if (false)
				SceneManager::LoadScene(L"CushyCloudScene");
			else if (false)
				SceneManager::LoadScene(L"JamJungleScene");
			else if (false)
				SceneManager::LoadScene(L"VocalVolcanoScene");
			else if (false)
				SceneManager::LoadScene(L"IceIslandScene");
			else if (false)
				SceneManager::LoadScene(L"SecretSeaScene");
			else if (false)
				SceneManager::LoadScene(L"GambleGalaxyScene");
		}
	}

	void LevelSelectScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void LevelSelectScene::Enter()
	{
		// 카메라 설정 
		Camera::SetTarget(nullptr);
	}

	void LevelSelectScene::Exit()
	{
		// 카메라 설정 해제
		Camera::SetTarget(nullptr);
		CollisionManager::Clear();
	}
}