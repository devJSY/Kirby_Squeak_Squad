#include "syOpeningScene.h"
#include "syInput.h"
#include "sySceneManager.h"
#include "syObject.h"
#include "syTransform.h"
#include "syVideo.h"
#include "syApplication.h"
#include "syAnimator.h"
#include "syCamera.h"

namespace sy
{
	OpeningScene::OpeningScene()
		: mVideo(nullptr)
	{
	}

	OpeningScene::~OpeningScene()
	{
	}

	void OpeningScene::Initialize()
	{
		// 비디오 생성
		mVideo = object::Instantiate<Video>(eLayerType::Video);
		
		// 위치 설정
		mVideo->GetComponent<Transform>()->SetPosition(Vector2(Application::GetResolution()) / 2.f);
		mVideo->SetSpeed(1.f); // 재생속도 설정
		
		Animator* videoAnimator = mVideo->AddComponent<Animator>();
		videoAnimator->CreateAnimationFolder(L"OpeningVideo", L"..\\Resources\\Video\\Opening", 0.03196546f / mVideo->GetSpeed());
		videoAnimator->PlayAnimation(L"OpeningVideo", false);
		videoAnimator->SetAffectedCamera(false);

		Scene::Initialize();
	}

	void OpeningScene::Update()
	{
		Scene::Update();

		// 비디오 재생이 끝나면 다음 씬으로 이동
		if ( mVideo != nullptr && mVideo->GetComponent<Animator>()->IsActiveAnimationComplete())
		{
			SceneManager::LoadScene(L"TitleScene");
		}

		if (Input::GetKeyDown(eKeyCode::MOUSE_RBTN))
		{
			SceneManager::LoadScene(L"TitleScene");
		}

	}

	void OpeningScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void OpeningScene::Enter()
	{
		// 카메라 설정 
		Camera::SetTarget(nullptr);

		// 비디오 재생
		Animator* videoAnimator = mVideo->GetComponent<Animator>();
		videoAnimator->PlayAnimation(L"OpeningVideo", false);
		videoAnimator->ActiveAnimationReset();
	}

	void OpeningScene::Exit()
	{
		// 카메라 설정 해제
		Camera::SetTarget(nullptr);
	}
}