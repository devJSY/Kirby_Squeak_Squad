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
		
		// ��ġ ����
		mVideo->GetComponent<Transform>()->SetPosition(Vector2(Application::GetResolution()) / 2.f); 
		//mVideo->SetSpeed(1.f); // ����ӵ� ����
		mVideo->SetSpeed(2.f); // ����ӵ� ����

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
		// ī�޶� ���� 
		Camera::SetTarget(nullptr);
		Camera::Pause(1.f, RGB(255, 255, 255));
		Camera::fadeIn(1.f, RGB(255, 255, 255));

		Animator* videoAnimator = mVideo->GetComponent<Animator>();
		videoAnimator->PlayAnimation(L"EndingVideo", false);
		videoAnimator->ActiveAnimationReset();

		// ����� ���
		ResourceManager::Find<Sound>(L"EndingSound")->Play(false);
	}

	void EndingScene::Exit()
	{
		// ī�޶� ���� ����
		Camera::SetTarget(nullptr);
		CollisionManager::Clear();

		// ����� ����
		ResourceManager::Find<Sound>(L"EndingSound")->Stop(true);
	}
}