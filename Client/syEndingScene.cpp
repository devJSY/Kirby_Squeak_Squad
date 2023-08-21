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
#include "syCollisionManager.h"
#include "sySoundManager.h"
#include "sySound.h"
#include "syResourceManager.h"
#include "syTime.h"

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
		//mVideo->SetSpeed(1.f); // 재생속도 설정
		mVideo->SetSpeed(2.f); // 재생속도 설정

		Animator* videoAnimator = mVideo->AddComponent<Animator>();
		videoAnimator->CreateAnimationFolder(L"EndingVideo", L"..\\Resources\\Video\\Ending", 0.0486358244365362f / mVideo->GetSpeed());
		videoAnimator->SetAffectedCamera(false);

		// Sound Load
		ResourceManager::Load<Sound>(L"EndingSound", L"..\\Resources\\Sound\\Theme\\Ending.wav");

		Scene::Initialize();
	}

	void EndingScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D) || Input::GetKeyDown(eKeyCode::W))
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
		Camera::Pause(1.f, RGB(255, 255, 255));
		Camera::fadeIn(1.f, RGB(255, 255, 255));

		Animator* videoAnimator = mVideo->GetComponent<Animator>();
		videoAnimator->PlayAnimation(L"EndingVideo", false);
		videoAnimator->ActiveAnimationReset();

		// 오디오 재생
		ResourceManager::Find<Sound>(L"EndingSound")->Play(false);
	}

	void EndingScene::Exit()
	{
		// 카메라 설정 해제
		Camera::SetTarget(nullptr);
		CollisionManager::Clear();

		// 오디오 정지
		ResourceManager::Find<Sound>(L"EndingSound")->Stop(true);
	}
}