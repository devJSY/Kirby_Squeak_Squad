#include "syOpeningScene.h"
#include "syInput.h"
#include "sySceneManager.h"
#include "syObject.h"
#include "sySpriteRenderer.h"
#include "syKirby.h"
#include "syTransform.h"
#include "syResourceManager.h"
#include "syTexture.h"
#include "syBackGround.h"
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
		assert(mVideo);
		Animator* videoAnimator = mVideo->AddComponent<Animator>();
		assert(videoAnimator);
		mVideo->GetComponent<Transform>()->SetPosition(Vector2(Application::GetResolution()) / 2.f); // 중점 설정
		mVideo->SetSpeed(3.f); // 재생속도 3배 설정
		videoAnimator->CreateAnimationFolder(L"OpeningVideo", L"..\\Resources\\Video\\Opening", Vector2::Zero, 0.03196546f / mVideo->GetSpeed());
		videoAnimator->SetAffectedCamera(false);
		videoAnimator->PlayAnimation(L"OpeningVideo", false);

		Scene::Initialize();
	}

	void OpeningScene::Update()
	{
		Scene::Update();

		// 비디오 재생이 끝나면 다음 씬으로 이동
		if ( mVideo != nullptr && mVideo->GetComponent<Animator>()->IsComplete())
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
	}

	void OpeningScene::Exit()
	{
		// 카메라 설정 해제
		Camera::SetTarget(nullptr);
	}
}