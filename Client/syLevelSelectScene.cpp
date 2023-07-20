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

		if (Input::GetKeyDown(eKeyCode::MOUSE_RBTN))
		{
			SceneManager::LoadScene(L"StageScene");
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