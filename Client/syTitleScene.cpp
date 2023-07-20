#include "syTitleScene.h"
#include "syObject.h"
#include "syInput.h"
#include "sySceneManager.h"
#include "syTransform.h"
#include "syVideo.h"
#include "syApplication.h"
#include "syAnimator.h"
#include "syCamera.h"
#include "syCollisionManager.h"

namespace sy
{
	TitleScene::TitleScene()
		: mVideo(nullptr)
	{
	}

	TitleScene::~TitleScene()
	{
	}

	void TitleScene::Initialize()
	{
		// 생성
		mVideo = object::Instantiate<Video>(eLayerType::Video);
		
		// 위치 설정
		mVideo->GetComponent<Transform>()->SetPosition(Vector2(Application::GetResolution()) / 2.f); 
		mVideo->SetSpeed(1.f); // 재생속도 설정

		Animator* videoAnimator = mVideo->AddComponent<Animator>();
		videoAnimator->CreateAnimationFolder(L"TitleVideo", L"..\\Resources\\Video\\Title", 0.033224f / mVideo->GetSpeed());
		videoAnimator->PlayAnimation(L"TitleVideo", true);
		videoAnimator->SetAffectedCamera(false);

		Scene::Initialize();
	}

	void TitleScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::MOUSE_RBTN))
		{
			SceneManager::LoadScene(L"LevelSelectScene");
		}
	}

	void TitleScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void TitleScene::Enter()
	{
		// 카메라 설정 
		Camera::SetTarget(nullptr);

		Animator* videoAnimator = mVideo->GetComponent<Animator>();
		videoAnimator->PlayAnimation(L"TitleVideo", true);
		videoAnimator->ActiveAnimationReset();
	}

	void TitleScene::Exit()
	{
		// 카메라 설정 해제
		Camera::SetTarget(nullptr);
		CollisionManager::Clear();
	}
}