#include "syEndingScene.h"
#include "syInput.h"
#include "sySceneManager.h"
#include "syObject.h"
#include "syTransform.h"
#include "syResourceManager.h"
#include "syApplication.h"
#include "syAnimator.h"
#include "syCamera.h"
#include "syVideo.h"

namespace sy
{
	EndingScene::EndingScene()
		: mVideo(nullptr)
	{
	}

	EndingScene::~EndingScene()
	{
	}

	void EndingScene::Initialize()
	{
		mVideo = object::Instantiate<Video>(eLayerType::Video);
		
		// 위치 설정
		mVideo->GetComponent<Transform>()->SetPosition(Vector2(Application::GetResolution()) / 2.f); 
		mVideo->SetSpeed(1.f); // 재생속도 설정

		Animator* videoAnimator = mVideo->AddComponent<Animator>();
		videoAnimator->CreateAnimationFolder(L"EndingVideo", L"..\\Resources\\Video\\Ending", 0.0444931f / mVideo->GetSpeed());
		videoAnimator->PlayAnimation(L"EndingVideo", true);
		videoAnimator->SetAffectedCamera(false);

		Scene::Initialize();
	}

	void EndingScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::MOUSE_RBTN))
		{
			SceneManager::LoadScene(L"OpeningScene");
		}
	}

	void EndingScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void EndingScene::Enter()
	{
		// 카메라 설정 
		Camera::SetTarget(nullptr);

		Animator* videoAnimator = mVideo->GetComponent<Animator>();
		videoAnimator->PlayAnimation(L"EndingVideo", false);
		videoAnimator->ActiveAnimationReset();
	}

	void EndingScene::Exit()
	{
		// 카메라 설정 해제
		Camera::SetTarget(nullptr);
	}
}