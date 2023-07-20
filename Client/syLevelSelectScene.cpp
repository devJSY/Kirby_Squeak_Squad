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
		// ��� ȭ�� ������Ʈ ���� 
		Level_BG* Bg = object::Instantiate<Level_BG>(eLayerType::BackGround);
		Vector2 vec = Vector2(Application::GetResolution()) / 2.f;
		vec.y /= 2.f;
		Bg->GetComponent<Transform>()->SetPosition(vec); // ���� ����		

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